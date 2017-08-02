#ifndef __OSTOR_SHELL_PROCESS_HEADER__
#define __OSTOR_SHELL_PROCESS_HEADER__


#include <string>

#include "process.h"

using namespace std;

class ShellProcess: public Process {
protected:
	bool is_started;
	string buffer;
	bool add_text(string text);
	bool is_complete();
	void execute_buffer();
public:
	ShellProcess();
	void start();
};


#endif