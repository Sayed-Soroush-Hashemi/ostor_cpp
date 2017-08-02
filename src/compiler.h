#ifndef __OSTOR_COMPILER_HEADER__
#define __OSTOR_COMPILER_HEADER__


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Compiler {

protected: 

	int labels_count = 0;

	/*
		"block": is part of code starting with "{" and ending with "}"
		given a start of the block, this method finds its endpoint
	*/
	int find_block_end(string& text, int start);

	/*
		"instruction": starts with a text followed by "(" and some more text 
			which finally ends with ")"

		given an index in text before "(", this method find its ")" 
			counterpart's index
	*/
	int get_instruction_end(string& text, int start);

	/*
		compile if to conditional jumps and labels

			if(ex) { <block> }

			cj(ex, false, end)
			<block>
			end:
	*/
	vector<string> compile_if(string if_command, vector<string> block_instructions);

	/*
		compile while to conditional jumps and labels
			
			while (ex) { <block> }

			start:
			cj(ex, false, end)
			<block>
			j start
			end:
	*/
	vector<string> compile_while(string while_command, vector<string> block_instructions);

	/*
		compile for to conditional jumps and labels

			for(ex1; ex2; ex3) { <block> }

			ex1
			start:
			cj(ex2, false, end)
			<block>
			ex3
			j start
			end:
	*/
	vector<string> compile_for(string for_command, vector<string> block_instructions);

	/*
		whitespaces: ' ', '\n', '\n', '\r'
	*/
	bool is_whitespace(char ch);

	/*
		delete all whitespaces, except for those in quotes
	*/
	void delete_whitespaces(string& str);

	/*
		clean a list of instructions by deleting whitespaces in each 
			instruction and etc.
	*/
	void clean(vector<string>& instructions);

	/*
		compile a program into instructions
	*/
	vector<string> compile(string text);

	/*
		returns line number of all labels
			ans[i] is line number of #i
	*/
	vector<int> link(vector<string> instructions);

public: 

	/*
		for an instruction "my_ins(arg1, arg2, ...)", this method gets 
			"arg1, arg2, ..." and a delimiter and returns all args
	*/
	vector<string> get_args(string args_text, char delimiter=',');

	/* 
		compile and link a program
	*/
	pair<vector<string>, vector<int> > compile_and_link(string text);
	
};


#endif