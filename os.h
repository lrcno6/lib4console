#ifndef _OS_H_
#define _OS_H_
#include<string>
#include<cstdlib>
inline void call(const std::string &str){
	#ifdef WIN_OS
	char exe[]="inside ";
	#else
	char exe[]="./inside ";
	#endif
	system((exe+str).c_str());
}
#endif