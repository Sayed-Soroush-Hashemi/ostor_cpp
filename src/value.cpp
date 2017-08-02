#include "value.h"

using namespace std;

Value Value::operator=(Value val2) {
	this->type = val2.type;
	this->value = val2.value;
	return *this;
}

Value Value::operator=(int val2) {
	this->type = number;
	this->value = to_string(val2);
	return *this;
}

Value Value::operator=(bool val2) {
	this->type = number;
	this->value = to_string(val2 ? 1 : 0);
	return *this;
}

Value Value::operator=(string val2) {
	this->type = str;
	this->value = val2;
	return *this;
}

Value Value::operator==(Value val2) {
	Value res;
	res = ((this->type == val2.type) && (this->value == val2.value));
	return res;
}

Value Value::operator!=(Value val2) {
	return !(*this == val2);
}

Value Value::operator<(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (stoi(this->value) < stoi(val2.value));
	return res;
}

Value Value::operator<=(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (stoi(this->value) <= stoi(val2.value));
	return res;
}

Value Value::operator>(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (stoi(this->value) > stoi(val2.value));
	return res;
}

Value Value::operator>=(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (stoi(this->value) >= stoi(val2.value));
	return res;
}

Value Value::operator&(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (((this->value != "0") & (val2.value != "0")) != 0);
	return res;
}

Value Value::operator&=(Value val2) {
	*this = (*this & val2);
	return *this;
}

Value Value::operator^(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (((this->value != "0") ^ (val2.value != "0")) != 0);
	return res;
}

Value Value::operator^=(Value val2) {
	*this = (*this ^ val2);
	return *this;
}

Value Value::operator|(Value val2) {
	if(this->type != number ||
			val2.type != number) {
		// throw exception
	}
	Value res;
	res = (((this->value != "0") | (val2.value != "0")) != 0);
	return res;
}

Value Value::operator|=(Value val2) {
	*this = (*this | val2);
	return *this;
}

Value Value::operator!() {
	if(this->type != number) {
		// throw exception
	}
	Value res;
	res = !stoi(this->value);
	return res;
}

Value Value::operator+(Value val2) {
	Value res;
	if(this->type == number && 
			val2.type == number)
		res = stoi(this->value) + stoi(val2.value);
	else
		res = this->value + val2.value;
	return res;
}

Value Value::operator+=(Value val2) {
	*this = *this + val2;
	return *this;
}

Value Value::operator-(Value val2) {
	Value res;
	if(this->type == number && 
			val2.type == number)
		res = stoi(this->value) - stoi(val2.value);
	else {
		// TODO: throw exception
	}

	return res;
}

Value Value::operator-=(Value val2) {
	*this = *this - val2;
	return *this;
}

Value Value::operator*(Value val2) {
	Value res;
	if(this->type == number && 
			val2.type == number)
		res = stoi(this->value) * stoi(val2.value);
	else {
		// TODO: throw exception
	}
	return res;
}

Value Value::operator*=(Value val2) {
	*this = *this * val2;
	return *this;
}

Value Value::operator%(Value val2) {
	Value res;
	if(this->type == number && 
			val2.type == number)
		res = stoi(this->value) % stoi(val2.value);
	else {
		// TODO: throw exception
	}
	return res;
}

Value Value::operator%=(Value val2) {
	*this = *this % val2;
	return *this;	
}

Value Value::operator/(Value val2) {
	Value res;
	if(this->type == number && 
			val2.type == number)
		res = stoi(this->value) / stoi(val2.value);
	else {
		// TODO: throw exception
	}
	return res;
}

Value Value::operator/=(Value val2) {
	*this = *this / val2;
	return *this;	
}
