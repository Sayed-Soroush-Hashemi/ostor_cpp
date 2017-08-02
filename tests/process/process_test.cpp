#include "process_test.h"

using namespace std;

namespace {

	// to list files in directories
	vector<string> glob_vector(const string& pattern){
	    glob_t glob_result;
	    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
	    vector<string> files;
	    for(int i = 0; i < glob_result.gl_pathc; i++)
	        files.push_back(string(glob_result.gl_pathv[i]));
	    globfree(&glob_result);
	    return files;
	}

	string read_file(string file_path) {
		ifstream file(file_path);
		string content = "";
		while(true) {
			string line;
			getline(file, line);
			if(line == "\0") 
				break;
			content += line + "\n";
		}
		return content;
	}

	TEST(ProcessTest, Verification) { 
		Process process;
		vector<string> inputs = glob_vector("../tests/process/data/in*");
		for(int i = 0; i < inputs.size(); i++) {
			cout << "\e[0;33m" << "Testing " << inputs[i] << "\e[0;37m" << endl;
			string output_file_path = inputs[i].substr(0, 22) + "out" + inputs[i].substr(24);

			string input = read_file(inputs[i]);
			string expected = read_file(output_file_path);

			testing::internal::CaptureStdout();
			process.eval(input);
			string actual = testing::internal::GetCapturedStdout();
			
			EXPECT_EQ(expected, actual) << "\e[0;31m" << 
					"Failed on " + inputs[i] << "\e[0;37m";
		}

	}

}