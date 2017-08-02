#include "process.h"

using namespace std;

void Process::eval(string program) {
	pair<vector<string>, vector<int> > compiled_program = compiler.compile_and_link(program);
	instructions = compiled_program.first;
	labels = compiled_program.second;

	// cout << "instructions: " << endl;
	// for(int i = 0; i < instructions.size(); i++)
	// 	cout << instructions[i] << endl;
	// cout << endl;

	// cout << "labels: " << endl;
	// for(int i = 0; i < labels.size(); i++)
	// 	cout << i << ": " << labels[i] << endl;
	// cout << endl;

	pc = 0;
	while(pc < instructions.size()) {
		string cur_ins = instructions[pc];

		// handling labels
		if(cur_ins.substr(0, 1) == "#") {
			pc++;
			continue;
		}

		// extracting instruction arguments
		int args_text_start = 0;
		while(cur_ins[args_text_start++] != '(');
		string args_text = cur_ins.substr(args_text_start, cur_ins.size()-args_text_start-1);
		vector<string> args = compiler.get_args(args_text);

		// handling instructions
		if(cur_ins.substr(0, 3) == "set") {
			eval_set(args[0], args[1]);
		} else if(cur_ins.substr(0, 4) == "echo") {
			eval_echo(args[0]);
		} else if(cur_ins.substr(0, 2) == "cj") {
			eval_cj(args[0], args[1], args[2]);
		} else if(cur_ins.substr(0, 4) == "quit") {
			eval_quit();
		}

		// get ready for the next instruction
		pc++;
	}
}

void Process::eval_set(string var_name, string value_str) {
	Value value = eval_expression(value_str);

	data[var_name] = value;
}

void Process::eval_echo(string echo_text) {
	Value echo_value = eval_expression(echo_text);
	cout << echo_value.value << endl;
}

Value Process::eval_concat(string arg1_str, string arg2_str) {
	Value arg1 = eval_expression(arg1_str);
	Value arg2 = eval_expression(arg2_str);

	Value ret;
	ret.value = arg1.value + arg2.value;
	ret.type = Value::ValueType::str;

	return ret;
}

Value Process::eval_index(string start_ind_exp, string end_ind_exp, string text_exp) {
	Value start_ind_val = eval_expression(start_ind_exp);
	Value end_ind_val = eval_expression(end_ind_exp);
	Value text = eval_expression(text_exp);

	int start_ind = stoi(start_ind_val.value);
	int end_ind = stoi(end_ind_val.value);

	text.value = text.value.substr(start_ind, end_ind - start_ind);
	text.type = Value::ValueType::str;

	return text;
}

void Process::eval_cj(string actual_exp, string expected_exp, string label) {
	Value actual = eval_expression(actual_exp);
	Value expected = eval_expression(expected_exp);
	Value label_line_number = eval_expression(label);

	if((actual == expected).value == "1")
		pc = labels[stoi(label_line_number.value)];
}

void Process::eval_quit() {
	exit(0);
}
