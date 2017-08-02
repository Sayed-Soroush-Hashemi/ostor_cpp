#include "shell_process.h"

using namespace std;

ShellProcess::ShellProcess() {
	is_started = false;
}

void ShellProcess::start() {
	if(is_started) 
		return;
	is_started = true;
	buffer = "";
	cout << "OStore version 0.1 started" << endl;
	cout << ">>> ";
	while(true) {
		string line;
		getline(cin, line);
		if(add_text(line))
			cout << ">>> ";
		else
			cout << "... ";
	}
}

bool ShellProcess::add_text(string text) {
	buffer += text;
	if(is_complete()) {
		execute_buffer();
		return true;
	} else
		return false;
}

bool ShellProcess::is_complete() { 
	int paranthesis = 0;
	int bracket = 0;
	bool in_quote = false;
	for(int i = 0; i < buffer.size(); i++) {
		if(buffer[i] == '\"')
			in_quote = !in_quote;
		if(in_quote) 
			continue;

		if(buffer[i] == '(')
			paranthesis++;
		if(buffer[i] == ')')
			paranthesis--;
		
		if(buffer[i] == '{')
			bracket++;
		if(buffer[i] == '}')
			bracket--;
	}
	if(bracket == 0 && 
			paranthesis == 0 && 
			in_quote == false)
		return true;
	return false;
}

void ShellProcess::execute_buffer() {
	eval(buffer);
	buffer = "";
}
