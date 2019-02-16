#include<fstream>
using namespace std;
int main(int argc,char **argv){
	ofstream fout("command");
	for(int i=1;i<argc;i++)
		fout<<argv[i]<<endl;
	return 0;
}