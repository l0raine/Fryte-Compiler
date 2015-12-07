#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <vector>
#include <string>

#include "Parser.h"
#include "BytecodeIO.h"
#include "VMTypes.h"

class Compiler
{
    public:
        Compiler();
        virtual ~Compiler();
        bool compile(std::vector<std::string> &data);
    protected:
    private:
        Parser parser;
        std::vector<unsigned char> bytecode; //Keeps track of bytecode to write to file
        std::vector<Variable> variableStack; //Keeps track of variable position on the stack to be

        unsigned int variablesOnStack = 0;

        void validateArgumentCount(unsigned int expected, unsigned int got);

        void declareInt(const std::vector<std::string>& line);
        void declareString(const std::vector<std::string>& line);
        void declareChar(const std::vector<std::string>& line);
        void declareBool(const std::vector<std::string>& line);

        int isVariable(const std::string &identifier); //Returns the stack position of the variable if found, -1 otherwise

        void processLine(const std::vector<std::string> &line);

        void processConsole(const std::vector<std::string> &line); //Console.*

        unsigned int evaluateBracket(const std::string &line); //Converts bracket information into stack instructions. Returns the number of things added to the stack.
};

#endif // COMPILER_H
