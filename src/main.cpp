#include <iostream>
#include <string>
#include <fstream>

#include "shell_process.h"
#include "file_process.h"

using namespace std;

int main(int n, char** args) {
	if(n < 2) {
		// run shell process
		ShellProcess sp;
		sp.start();
	} else {
		// run file process
		FileProcess fp; 
		fp.init_process(string(args[1]));
		fp.execute();
	}
	return 0;
}
