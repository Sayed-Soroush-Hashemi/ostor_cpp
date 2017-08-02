#include "file_process.h"

using namespace std;

void FileProcess::read_file() {
	this->file_text = "";
	while(true) {
		string line;
		getline(this->in_file, line);
		if(line == "\0") 
			break;
		this->file_text += line + "\n";
	}
}

void FileProcess::init_process(string in_file_path) {
	this->in_file.open(in_file_path);
	this->read_file();
}

void FileProcess::execute() {
	eval(this->file_text);
}
