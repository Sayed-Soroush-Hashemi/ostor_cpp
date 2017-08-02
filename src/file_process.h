#ifndef __OSTOR_FILE_PROCESS_HEADER__
#define __OSTOR_FILE_PROCESS_HEADER__


#include <string>
#include <vector>
#include <fstream>

#include "process.h"

using namespace std;

class FileProcess: public Process {
protected:
	ifstream in_file;
	string file_text;
	
	void read_file();

public:
	void init_process(string in_file_path);
	void execute();

};


#endif