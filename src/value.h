#ifndef __OSTOR_VALUE_HEADER__
#define __OSTOR_VALUE_HEADER__

#include <iostream>
#include <string>

using namespace std;

class Value {

public:

	enum ValueType { 
		str,
		number,
	};

	string value;
	ValueType type;

	Value operator=(Value val2);
	Value operator=(int val2);
	Value operator=(bool val2);
	Value operator=(string val2);
	Value operator==(Value val2);
	Value operator!=(Value val2);
	Value operator<(Value val2);
	Value operator<=(Value val2);
	Value operator>(Value val2);
	Value operator>=(Value val2);
	Value operator&(Value val2);
	Value operator&=(Value val2);
	Value operator^(Value val2);
	Value operator^=(Value val2);
	Value operator|(Value val2);
	Value operator|=(Value val2);
	Value operator!();

	Value operator+(Value val2);
	Value operator+=(Value val2);
	Value operator-(Value val2);
	Value operator-=(Value val2);
	Value operator*(Value val2);
	Value operator*=(Value val2);
	Value operator%(Value val2);
	Value operator%=(Value val2);
	Value operator/(Value val2);
	Value operator/=(Value val2);
};


#endif