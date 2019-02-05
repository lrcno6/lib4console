#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include"libcore/library.h"
using namespace lib;
using namespace std;
string name;
Library *library;
bool main_menu(){
	char c;
	cout<<"\n1.create a new ID\n"
		<<"2.lend a book\n"
		<<"3.return a book\n"
		<<"4.sort by time for all the books\n"
		<<"9.save and exit\n"
		<<"0.exit without saving\n"
		<<"You want to :";
	mainloop:
	cin>>c;
	switch(c){
		case '1':
			cout<<Library::new_id(8)<<endl;
			break;
		case '2':{
			string id,name;
			cout<<"the book's ID:";
			cin>>id;
			cout<<"borrower:";
			do
				getline(cin,name);
			while(name.empty());
			try{
				library->lend(id,name);
			}
			catch(logic_error&){
				cerr<<"error:the ID is used\n";
			}
			break;
		}
		case '3':{
			string id;
			cout<<"the book's ID:";
			cin>>id;
			try{
				library->Return(id);
			}
			catch(out_of_range&){
				cerr<<"error:the ID is not used\n";
			}
			break;
		}
		case '4':
			for(auto i:library->sort_by_time())
				cout<<i.show();
			break;
		case '9':{
			if(name.empty()){
				cout<<"enter file name:";
				do
					getline(cin,name);
				while(name.empty());
			}
			ofstream fout(name);
			if(fout.is_open()){
				library->save(fout);
				return false;
			}
			else
				cerr<<"error:the file cannot be writed-maybe it is read only?\n";
			break;
		}
		case '0':
			cout<<"Are you sure that you do not need to save?[y/n] :";
			loop:
			cin>>c;
			switch(c){
				case 'y':
				case 'Y':
					return false;
				case 'n':
				case 'N':
					break;
				default:
					goto loop;
			}
			break;
		default:
			goto mainloop;
	}
	return true;
}
int main(int argc,char **argv){
	srand(time(nullptr));
	switch(argc){
		case 0:
			cerr<<"error:How do you do it?You make argc==0!\n";
			return 256;
		case 1:
			cerr<<"warning:a new file\n";
			library=new Library;
			break;
		case 2:{
			name=argv[1];
			ifstream fin(argv[1]);
			if(!fin.is_open()){
				cerr<<"error:"<<argv[1]<<":cannot find the file\n";
				return 256;
			}
			library=new Library(fin);
			break;
		}
		default:
			cerr<<"error:too many args\n";
			return 256;
	}
	while(main_menu());
	delete library;
	return 0;
}