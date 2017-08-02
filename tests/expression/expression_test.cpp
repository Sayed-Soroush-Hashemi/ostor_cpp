#include "expression_test.h"

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
		getline(file, content);
		return content;
	}

	TEST(ExpressionTest, Verification) { 
		Process process;
		vector<string> inputs = glob_vector("../tests/expression/data/in*");
		for(int i = 0; i < inputs.size(); i++) {
			cout << "\e[0;33m" << "Testing " << inputs[i] << "\e[0;37m" << endl;
			string output_file_path = inputs[i].substr(0, 25) + "out" + inputs[i].substr(27);

			string input = read_file(inputs[i]);
			string expected = read_file(output_file_path);

			string actual = process.eval_expression(input).value;
			
			EXPECT_EQ(expected, actual) << "\e[0;31m" << 
					"Failed on " + inputs[i] << "\e[0;37m";
		}

	}

}