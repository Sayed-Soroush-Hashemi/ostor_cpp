#include "compiler.h"

using namespace std;

int Compiler::find_block_end(string& text, int start) {
	int end = start + 1, count = 1;
	bool in_quote = false;
	while(count > 0) {
		if(text[end] == '\"')
			in_quote = !in_quote;
		if(in_quote) {
			end++;
			continue;
		}
		if(text[end] == '{') 
			count ++;
		if(text[end] == '}')
			count --;
		end ++;
	}
	return end - 1;
}

int Compiler::get_instruction_end(string& text, int start) {
	bool flag = false;
	int count = 0;
	bool in_quote = false;
	while(flag == false || count > 0) {
		if(text[start] == '\"')
			in_quote = !in_quote;
		if(in_quote) {
			start++;
			continue;
		}
		if(text[start] == '(' || text[start] == ')')
			flag = true;
		if(text[start] == '(') 
			count++;
		if(text[start] == ')')
			count--;
		start++;
	}
	return start - 1;
}

vector<string> Compiler::get_args(string args_text, char delimiter) {
	vector<string> args;
	int brackets_count = 0, paranthesis_count = 0;
	bool in_quote = false;
	int arg_start = 0;
	for(int i = 0; i < args_text.size(); i++) {
		
		// handle quotes
		if(args_text[i] == '\"')
			in_quote = !in_quote;
		if(in_quote)
			continue;

		// handle brackets
		if(args_text[i] == '{')
			brackets_count++;
		if(args_text[i] == '}')
			brackets_count--;
		
		// handle paranthesises
		if(args_text[i] == '(')
			paranthesis_count++;
		if(args_text[i] == ')')
			paranthesis_count--;

		if(brackets_count == 0 &&
				paranthesis_count == 0 && 
				args_text[i] == delimiter) {
			string new_arg = args_text.substr(arg_start, i - arg_start);
			args.push_back(new_arg);
			arg_start = i+1;
		}
	}
	args.push_back(args_text.substr(arg_start, args_text.size() - arg_start));

	return args;
}

vector<string> Compiler::compile_if(string if_command, vector<string> block_instructions) {
	
	int start = 0;
	while(if_command[start++] != '(');
	string args_text = if_command.substr(start, if_command.size() - start - 1);
	string expression = get_args(args_text)[0];

	// generate instructions
	/*
		cj(expression, false, end)
		<block>
		end:
	*/
	vector<string> instructions;
	string end_label_number = to_string(labels_count++);
	instructions.push_back("cj(" + expression + ",0," + end_label_number + ")");
	instructions.insert(instructions.end(), block_instructions.begin(), block_instructions.end());
	instructions.push_back("#" + end_label_number);

	return instructions;
}

vector<string> Compiler::compile_while(string while_command, vector<string> block_instructions) {
	int start = 0;
	while(while_command[start++] != '(');
	string args_text = while_command.substr(start, while_command.size() - start - 1);
	string expression = get_args(args_text)[0];

	// generate instructions
	/*
		start:
		cj(expression, false, end)
		<block>
		j start
		end:
	*/
	vector<string> instructions;
	string start_label_number = to_string(labels_count++);
	string end_label_number = to_string(labels_count++);
	instructions.push_back("#" + start_label_number);
	instructions.push_back("cj(" + expression + ",0," + end_label_number + ")");
	instructions.insert(instructions.end(), block_instructions.begin(), block_instructions.end());
	instructions.push_back("cj(0,0," + start_label_number + ")");
	instructions.push_back("#" + end_label_number);

	return instructions;
}

vector<string> Compiler::compile_for(string for_command, vector<string> block_instructions) {
	int start = 0;
	while(for_command[start++] != '(');
	string args_text = for_command.substr(start, for_command.size() - start - 1);
	vector<string> args = get_args(args_text, ';');

	// generate instructions
	/*
		for(ex1; ex2; ex3) { <block> }

		ex1
		start:
		cj(ex2, false, end)
		<block>
		ex3
		j start
		end:
	*/
	vector<string> instructions;
	string start_label_number = to_string(labels_count++);
	string end_label_number = to_string(labels_count++);
	instructions.push_back(args[0]);
	instructions.push_back("#" + start_label_number);
	instructions.push_back("cj(" + args[1] + ",0," + end_label_number + ")");
	instructions.insert(instructions.end(), block_instructions.begin(), block_instructions.end());
	instructions.push_back(args[2]);
	instructions.push_back("cj(0,0," + start_label_number + ")");
	instructions.push_back("#" + end_label_number);

	return instructions;
}

bool Compiler::is_whitespace(char ch) {
	return ch == ' ' || 
			ch == '\n' || 
			ch == '\t' || 
			ch == '\r';
}

void Compiler::delete_whitespaces(string& str) {
	bool in_quote = false;
	for(int i = 0; i < str.size(); i++) {
		if(str[i] == '\"')
			in_quote = !in_quote;
		if(in_quote)
			continue;
		if(is_whitespace(str[i])) {
			str = str.erase(i, 1);
			i--;
		}
	}
}

void Compiler::clean(vector<string>& instructions) {
	for(int i = 0; i < instructions.size(); i++) {
		delete_whitespaces(instructions[i]);
		if(instructions[i].size() == 0) {
			instructions.erase(instructions.begin() + i);
			i--;
		}
	}
}

vector<string> Compiler::compile(string text) {
	vector<string> all_instructions; 
	
	for(int i = 0; i < text.size(); ) {
		// delete whitespaces from the beginning
		while(i < text.size() && is_whitespace(text[i++]));
		if(i >= text.size())
			break;
		i--;

		// compile "if", "for", and "while" commands
		if(text[i] == '{') {
			
			// complie this block to vector of instructions
			int block_end = find_block_end(text, i);
			string block_text = text.substr(i+1, block_end - i - 1);
			vector<string> block_instructions = compile(block_text);
			// setting next index to search for commands
			i = block_end + 1;

			// exclude last instruction from all_instructions
			string last_command = all_instructions[all_instructions.size()-1];
			all_instructions.pop_back();
			
			// compile "if", "while", and "for" command
			vector<string> new_instructions;
			if(last_command.substr(0, 2) == "if")
				new_instructions = compile_if(last_command, block_instructions);
			else if(last_command.substr(0, 3) == "for")
				new_instructions = compile_for(last_command, block_instructions);
			else if(last_command.substr(0, 5) == "while")
				new_instructions = compile_while(last_command, block_instructions);
			else {
				// TODO: invalid command exception
			}

			// add compiled instruction
			all_instructions.insert(all_instructions.end(), new_instructions.begin(), new_instructions.end());

		} else {

			// compile next instruction
			int new_instruction_end = get_instruction_end(text, i);
			string new_instruction = text.substr(i, new_instruction_end - i + 1);
			all_instructions.push_back(new_instruction);

			// setting index for next command
			i = new_instruction_end + 1;
		}
	}

	clean(all_instructions);

	return all_instructions;	
}

vector<int> Compiler::link(vector<string> instructions) {
	vector<int> labels;
	labels_count = 0;

	for(int i = 0; i < instructions.size(); i++) 
		if(instructions[i][0] == '#') {
			int label_number = stoi(instructions[i].substr(1));
			if(labels.size() <= label_number)
				labels.resize(label_number + 1);
			labels[label_number] = i;
		}

	return labels;
}

pair<vector<string>, vector<int> > Compiler::compile_and_link(string text) {
	vector<string> instructions = compile(text);
	vector<int> labels = link(instructions);
	return make_pair(instructions, labels);	
}


// int main() {
// 	Compiler compiler;
// 	while(true) {
// 		string commands;
// 		getline(cin, commands);
// 		pair<vector<string>, vector<int> > program = compiler.compile_and_link(commands);

// 		cout << "\e[1;31mlabels: \e[0;37m" << endl;
// 		for(int i = 0; i < program.second.size(); i++) 
// 			cout << i << ": " << program.second[i] << endl;
// 		cout << "\e[1;31minstructions: \e[0;37m" << endl;
// 		for(int i = 0; i < program.first.size(); i++) 
// 			cout << program.first[i] << endl;
// 		cout << "*****************************"<<endl;
// 	}
// }