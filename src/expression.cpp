#include "expression.h"

using namespace std;

bool Process::is_atomic(string s) {
    vector<string> keywords = {
        ")", "(", "+", "-", "*", "/", "&", "|", "!", "^", 
        ">", "<", "<=", ">=", "==", "!=", "concat", "index"
    };
    bool in_quote = false;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '\"')
            in_quote = !in_quote;
        if(in_quote)
            continue;

        for(int j = 0; j < keywords.size(); j++) {
            if(i + keywords[j].size() > s.size())
                continue;
            if(s.substr(i, keywords[j].size()) == keywords[j]) {
                return false;
            }
        }
    }
    return true;
}

Value Process::eval_expression(string s) {
    if(is_atomic(s)) {
        Value res;
        regex number_pattern("^\\d+$");
        if(regex_match(s, number_pattern)) {
            res = stoi(s);
        } else {
            if(s[0] == '\"')
                res = s.substr(1, s.size()-2);
            else
                return data[s];
        }
        return res;
    }
    int count[s.size()];
    count[0] = (s.at(0) == '(') ? 1 : 0;
    for (int i = 1; i < s.size(); i++) {
        if (s.at(i) == '(')
            count[i] = count[i - 1] + 1;
        else if (s.at(i) == ')')
            count[i] = count[i - 1] - 1;
        else
            count[i] = count[i - 1];
    }

    for (int i = s.length()-1; i > -1; i--) {
        string op = s.substr(i,1);

        if(count[i]==0 && (
                op == "|" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op == "|")
                res = operand1 | operand2;
            return res;
        }
    }

    for (int i = s.length()-1; i > -1; i--) {
        string op = s.substr(i,1);

        if(count[i]==0 && (
                op == "^" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op == "^")
                res = operand1 ^ operand2;
            return res;
        }
    }

    for (int i = s.length()-1; i > -1; i--) {
        string op = s.substr(i,1);

        if(count[i]==0 && (
                op == "&" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op == "&")
                res = operand1 & operand2;
            return res;
        }
    }

    for (int i = s.length()-2; i > -1; i--) {
        string op1 = s.substr(i,1);
        string op2 = s.substr(i,2);

        if (count[i] == 0 && (
                op2 == "==" ||
                op2 == "!=" ||
                op2 == ">=" ||
                op2 == "<=" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 2));

            Value res;
            if(op2 == "==")
                res = (operand1 == operand2);
            if(op2 == "!=")
                res = (operand1 != operand2);
            if(op2 == ">=")
                res = (operand1 >= operand2);
            if(op2 == "<=")
                res = (operand1 <= operand2);
            return res;
        }
        if(count[i]==0 && (
                op1 == ">" ||
                op1 == "<" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op1 == "<")
                res = (operand1 < operand2);
            if (op1 == ">")
                res = (operand1 > operand2);
            return res;
        }
    }

    for (int i = s.length()-1; i > -1; i--) {
        string op = s.substr(i,1);

        if(count[i]==0 && (
                op == "+" ||
                op == "-" )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op == "+")
                res = operand1 + operand2;
            if (op == "-") {
                res = operand1 - operand2;
            }
            return res;
        }
    }

    for (int i = s.length()-1; i > -1; i--) {
        char op = s[i];

        if(count[i]==0 && (
                op == '*' ||
                op == '/' ||
                op == '%' )) {
            Value operand1 = eval_expression(s.substr(0, i));
            Value operand2 = eval_expression(s.substr(i + 1));

            Value res;
            if (op == '*')
                res = operand1 * operand2;
            if (op == '/')
                res = operand1 / operand2;
            if (op == '%')
                res = operand1 % operand2;
            return res;
        }
    }

    if(s.substr(0,1) == "(" && s.substr(s.size()-1, 1) == ")")
        return eval_expression(s.substr(1,s.length()-2));

    if(s.substr(0,1) == "!") {
        Value res = eval_expression(s.substr(1));
        return !res;
    }

    if(s.substr(0,5) == "index") {
        string args_text = s.substr(6, s.size() - 7);
        vector<string> args = compiler.get_args(args_text);
        return eval_index(args[0], args[1], args[2]);
    }

    if(s.substr(0,6) == "concat") {
        string args_text = s.substr(7, s.size() - 8);
        vector<string> args = compiler.get_args(args_text);
        return eval_concat(args[0], args[1]);
    }

    // todo: throw exception due to bad syntax(none of the conditions matched)
}
