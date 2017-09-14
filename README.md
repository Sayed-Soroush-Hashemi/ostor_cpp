# ostor_cpp
Operating System university course project - phase 1 in c++

### 1. What is this project about?
This project is an interpreter for a dummy language, which contains only 4 commands along with `if`, `for`, and `while` statements, similar to C language. This project is the first phase of a project that meant to simulate hardware and implement an operating system on it. The introduced language in phase 1 is the only language that can be run on this OS. This phase is only a simple interpreter for the first version of this language.

### 2. What is the introduced language's specification?
First of all, this language only has 2 data types: integer and string. A variable has no data type, so you can save a string in a variable and then save an integer in it (i.e. it's a weak type language).

Along with 4 commands and flow control statements(e.g. `if`), this language contains expressions which the interpreter must evaluate. Expressions consist of numbers, strings, elementary arithmetic operators, boolean operators, and 2 string manipulation commands which will be described soon. 

commands description:
  * `set(expression, variable_name)`: it evaluates the given expression and save the evaluated value in the given variable name
  * `echo(expression)`: it evaluates the given expression and print the result on screen
  * `index(start_ind, end_ind, expression)`: it first evaluates the expression. The result must be a string. Then it returns all characters of it starting from `start_ind` to `end_ind-1` inclusive. 
  * `concat(expression1, expression2)`: it first evaluates the given expressions. The evaluated results must be strings. Then it concatenates the first result with the second one and returns the final string.

Now a simple example can consolidate your understanding of this language:
```C++
set(k, 1)
for(set(i, 0); i < 12; set(i, i+1)) {
  set(k, k*2+1)
  echo(k)
  if(k > 100) {
    set(k, k / 100)
  }
}
```
If you run this program, it prints `3, 7, 15, 31, 63, 127, 3, 7, 15, 31, 63, 127` each number on a separate line. 

### 3. How does this project execute programs?
First, it compiles the program. It converts all flow control commands(e.g. `if`) to a series of `cj`s(conditional jump) and labels. More specifically, an `if` statement checks whether its expression evaluates to `true` or `false`. If it is `true`, it should run all commands in its block and if it doesn't, it should jump to the end of its block. So it's very intuitive to convert all control flow commands to conditional jumps and labels. Details of these new low-level commands can be checked in the source code.

### 4. How to run the project?
For compiling the project, you need `cmake`. After installing `cmake`, you just need to run the following commands in the terminal:
```shell
cd <project directory>
mkdir build
cd build
cmake ..
make
```
Now you only need to run the following command to run `my_first_program.ostor`:
```shell
./ostor my_first_program.ostor
```
You can also run `oster` in interpreter mode. You just need to run `./ostor` in the terminal. Now you can type in your commands one by one and see the result.

### 5. Who are the contributors?
The team consists of [Elnaz Mehrzadeh](https://github.com/elie-naz), Bahar Salamatian, and of course me. The contributors' Github account will be added to this README file soon. 

### 6. Why hasn't this project be added to git until it was over?
As the team leader, I was responsible for such decisions and convincing team members. After so many failures, I learned something about the mixture of team work and learning: Never learn two new things at once in the same project. 

### 7. Why is this readme structured like this?
I always struggled to find the information I want in readme pages. I found the "question-answer" format the best for those who just want to skim, like me.
