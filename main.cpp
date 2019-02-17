#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include"libcore/library.h"
#include"os.h"
using namespace lib;
using namespace std;
bool saved=true;
string name;
Library *library;
void getline(string &str,bool loop=true){
	auto read=[&str]{
		getline(cin,str);
		auto first=str.find_first_not_of(" \t\n\v\f\r"),last=str.find_last_not_of(" \t\n\v\f\r");
		if(first!=string::npos)
			str.erase(0,first);
		if(last!=string::npos)
			str.erase(last+1);
	};
	if(loop)
		do
			read();
		while(str.empty());
	else
		read();
}
void version(){
	cout<<"lib4console beta 1.4.1\n"
		<<"license: GPL-3.0\n"
		<<"GitHub address: https://github.com/lrcno6/lib4console\n";
}
bool main_menu(){
	cout<<"lib4console > ";
	string cmd;
	getline(cmd,false);
	call(cmd);
	ifstream arg("command");
	vector<string> argv;
	while(arg){
		string s;
		getline(arg,s);
		if(!s.empty())
			argv.push_back(s);
	}
	if(argv.empty())
		return true;
	string &command=argv[0];
	if(command=="newid")
		cout<<Library::new_id(8)<<endl;
	else if(command=="lend"){
		string id,name;
		if(argv.size()>1)
			id=argv[1];
		else{
			cout<<"the book's ID: ";
			do
				getline(id);
			while(id.empty());
		}
		if(argv.size()>2)
			name=argv[2];
		else{
			cout<<"borrower: ";
			do
				getline(name);
			while(name.empty());
		}
		try{
			library->lend(id,name);
			saved=false;
		}
		catch(logic_error&){
			cerr<<"error: the ID is used\n";
		}
	}
	else if(command=="return"){
		string id;
		if(argv.size()>1)
			id=argv[1];
		else{
			cout<<"the book's ID: ";
			do
				getline(id);
			while(id.empty());
		}
		try{
			library->Return(id);
			saved=false;
		}
		catch(out_of_range&){
			cerr<<"error: the ID is not used\n";
		}
	}
	else if(command=="show"){
		if(library->books.empty())
			cout<<"no books are borrowed\n";
		else
			for(auto i:library->sort_by_time())
				cout<<i.show();
	}
	else if(command=="save"){
		if(!saved){
			if(name.empty()){
				if(argv.size()>1)
					name=argv[1];
				else{
					cout<<"enter file name: ";
					do
						getline(name);
					while(name.empty());
				}
			}
			ofstream fout(name);
			if(fout.is_open()){
				library->save(fout);
				saved=true;
			}
			else
				cerr<<"error: the file cannot be written - maybe it is read-only?\n";
		}
	}
	else if(command=="exit"){
		if(saved)
			return false;
		cout<<"Are you sure that you do not need to save? [y/n] :";
		string judge;
		loop:
		getline(judge);
		if(judge=="y" || judge=="Y")
			return false;
		if(judge!="n" && judge!="N")
			goto loop;
	}
	else if(command=="help")
		cout<<"newid\tcreate a new ID\n"
			<<"lend\tlend a book\n"
			<<"return\treturn a book\n"
			<<"show\tshow the borrowed books in chronological order\n"
			<<"save\n"
			<<"exit\n"
			<<"help\tget help\n"
			<<"version\tget the version information\n";
	else if(command=="version")
		version();
	else
		cerr<<"error: command not found\n";
	return true;
}
int main(int argc,char **argv){
	srand(time(nullptr));
	switch(argc){
		case 0:
			cerr<<"error: How do you do it? You make argc==0!\n";
			return 256;
		case 1:
			cerr<<"warning: a new file\n\n";
			library=new Library;
			break;
		case 2:{
			name=argv[1];
			if(argv[1][0]=='-'){
				if(argv[1][1]=='-'){
					if(name=="--help")
						cout<<"usage: [./]lib4console [-h | --help] [-v | --version] <file>\n";
					else if(name=="--version")
						version();
					else{
						cerr<<"error: invalid option\n";
						return 256;
					}
				}
				else{
					if(name=="-h")
						cout<<"usage: [./]lib4console [-h | --help] [-v | --version] <file>\n";
					else if(name=="-v")
						version();
					else{
						cerr<<"error: invalid option\n";
						return 256;
					}
				}
				return 0;
			}
			ifstream fin(argv[1]);
			if(!fin.is_open()){
				cerr<<"error: "<<argv[1]<<": cannot find the file\n";
				return 256;
			}
			library=new Library(fin);
			break;
		}
		default:
			cerr<<"error: too many args\n";
			return 256;
	}
	version();
	cout<<"please enter \"help\" for help or \"version\" for version information\n";
	while(main_menu());
	delete library;
	return 0;
}