#ifndef __OSTOR_PROCESS_HEADER__
#define __OSTOR_PROCESS_HEADER__


#include <string>
#include <map>
#include <vector>

#include "compiler.h"
#include "value.h"

using namespace std; 

class Process {

public:

	void eval(string program);

// protected:
	Compiler compiler;
	map<string, Value> data;
	vector<string> instructions;
	vector<int> labels;
	int pc;

	Value eval_expression(string expression);
	bool is_atomic(string expression);
	void eval_set(string var_name, string value_str);
	void eval_echo(string echo_text);
	Value eval_concat(string arg1_str, string arg2_str);
	Value eval_index(string start_ind_exp, string end_ind_exp, string text_exp);
	void eval_cj(string actual_exp, string expected_exp, string label);
	void eval_quit();

};


#endif