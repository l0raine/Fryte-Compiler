#ifndef VMTYPES_H
#define VMTYPES_H
//List of instructions which the virtual machine supports
enum Instruction
{
    //COMPILER ONLY
    NONE = -1, //Indicates not found, compiler side only

    //BOTH COMPILER AND INTERPRETER
    CONSOLE_OUT = 0, //Prints out a series of values, CONSOLE_OUT(argCount, data)
    CREATE_INT = 1, //Pushes an integer to the stack, CREATE_INT(data)
    CREATE_CHAR = 2, //Pushes a character to the stack, CREATE_CHAR(data)
    CREATE_BOOL = 3, //Pushes a boolean to the stack, CREATE_BOOL(data)
    CREATE_STRING = 4, //Pushes a string to the stack, CREATE_STRING(length, data1, data2, etc)
    GOTO = 5, //Sets the current bytecode position, GOTO(stackDepth)
    CONSOLE_IN = 6, //Reads in a value, CONSOLE_IN(data)
    MATH_ADD = 7, //Adds two or more numbers. MATH_ADD(NumberOfThingsToAdd, data1, data2, etc)
    MATH_SUBTRACT = 8, //Subtracts two or more numbers. MATH_SUBTRACT(NumberOfThingsToAdd, data1, data2, etc)
    MATH_MULTIPLY = 9, //Multiplies two or more numbers together. MATH_MULTIPLY(NumberOfThingsToAdd, data1, data2, etc)
    MATH_DIVIDE = 10, //Divides two or more numbers. MATH_DIVIDE(NumberOfThingsToAdd, data1, data2, etc)
    MATH_MOD = 11, //Modulus two or more things. MATH_MOD(NumberOfThingsToAdd, data1, data2, etc)
    CLONE_TOP = 12, //Clones a variable's contents from a position in the stack to the top of the stack. CLONE_TOP(StackPos)
    CONCENTRATE_STRINGS = 13, //Concentrates strings together into a new string. CONCENTRATE_STRINGS(NumberOfStrings)
    COMPARE_EQUAL = 14, //Compare the last X things on the stack and add true or false if they are equal
    CONDITIONAL_IF = 15, //If last thing on stack is true/false, runs specified bytecode position
    SET_VARIABLE = 16, //Sets the data of a variable in the stack. SET_VARIABLE(stackPos). New value taken from top of stack.
    COMPARE_UNEQUAL = 17, //Compare the last X things on the stack and add true or false if they are unequal
    COMPARE_LESS_THAN = 18, //Compare last two things on the stack and push true if object one is less than object two
    COMPARE_MORE_THAN = 19, //Compare last two things on the stack and push true if object one is more than object two
    COMPARE_LESS_THAN_OR_EQUAL = 20, //Compare last two things on the stack and pushes true if object one is less than or equal to object two
    COMPARE_MORE_THAN_OR_EQUAL = 21, //Compare last two things on the stack and pushes true if object one is more than or equal to object two
    COMPARE_OR = 22, //Compare a series of values and return true if one of them is true. False otherwise. COMPARE_OR(numberOfThings, v1, v2, v3...)
    STACK_WALK = 23, //Sets the current stack size, STACK_WALK(pos)
    DYNAMIC_GOTO = 24, //Sets the bytecode to a position which is found on top of the stack. DYNAMIC_GOTO(pos)
    TO_INTEGER = 25, //Converts the value on the top of the stack to a string and pushes the new value
    TO_STRING = 26, //Converts the value on the top of the stack to an integer and then pushes the new value
    COMPARE_AND = 27, //Compares a series of values. If all are true, push true, else push false. COMPARE_AND(ArgCount, Args...)
    DYNAMIC_CLONE_TOP = 28, //Takes an offset from the top of the stack and clones the variable at that offset to the top. DYNAMIC_CLONE_TOP(pos)
    DYNAMIC_SET_VARIABLE = 29, //Takes a variable position and variable value from the top of the stack and sets that variable to that value. DYNAMIC_SET_VARIABLE(VALUE, POSITION)
};

//List of data types which the virtual machine supports
enum class DataType
{
    //Compiler only types
    CLASS = -3,
    UNKNOWN = -2,
    VOID = -1,
    //Compiler & Interpreter types
    INT = 0,
    CHAR = 1,
    BOOL = 2,
    STRING = 3,
};

struct Variable
{
    DataType type;
    std::string identifier;
    bool isArray;
    unsigned int arrayLength;

    Variable()
    : type(DataType::UNKNOWN), identifier(""), isArray(false), arrayLength(0) {}

    Variable(const std::string &name, DataType varType)
    : type(varType), identifier(name), isArray(false), arrayLength(0) {}
};

static Instruction stringToInstruction(const std::string& operation)
{
    if(operation == "+")
        return Instruction::MATH_ADD;
    else if(operation == "-")
        return Instruction::MATH_SUBTRACT;
    else if(operation == "*")
        return Instruction::MATH_MULTIPLY;
    else if(operation == "/")
        return Instruction::MATH_DIVIDE;
    else if(operation == "%")
        return Instruction::MATH_MOD;
    else if(operation == "@")
        return Instruction::CONCENTRATE_STRINGS;
    else if(operation == "==")
        return Instruction::COMPARE_EQUAL;
    else if(operation == "!=")
        return Instruction::COMPARE_UNEQUAL;
    else if(operation == "<")
        return Instruction::COMPARE_LESS_THAN;
    else if(operation == ">")
        return Instruction::COMPARE_MORE_THAN;
    else if(operation == "<=")
        return Instruction::COMPARE_LESS_THAN_OR_EQUAL;
    else if(operation == ">=")
        return Instruction::COMPARE_MORE_THAN_OR_EQUAL;
    else if(operation == "&")
        return Instruction::COMPARE_AND;
    else if(operation == "|")
        return Instruction::COMPARE_OR;
    return NONE; //Not found
}

static DataType stringToDataType(const std::string& type)
{
    if(type == "int")
        return DataType::INT;
    else if(type == "string")
        return DataType::STRING;
    else if(type == "char")
        return DataType::CHAR;
    else if(type == "bool")
        return DataType::BOOL;
    else if(type == "void")
        return DataType::VOID;
    return DataType::UNKNOWN;
}

static std::string dataTypeToString(DataType type)
{
    if(type == DataType::INT)
        return "int";
    else if(type == DataType::STRING)
        return "string";
    else if(type == DataType::CHAR)
        return "char";
    else if(type == DataType::BOOL)
        return "bool";
    else if(type == DataType::VOID)
        return "void";
    return "unknown";
}

struct Scope
{
    enum ScopeType
    {
        IF, WHILE, ELSE, FOR, FUNCTION, CLASS
    };
    Scope()
    {
        argumentCount = 0;
        endPos = 0;
        wasOptimisedOut = false;
        startPos = 0;
        scopeDepth = 0;
        statementPos = 0;
        stackSize = 0;
        bytecodeSizeBefore = 0;
        returnType = DataType::UNKNOWN;
        scopeReturned = false;
        initialisationVariableCount = 0;
    }
    Scope(unsigned int statPos, unsigned int spos, unsigned int sdep, unsigned int ssize, std::string sincrem, std::string sidentifier, unsigned int sizeBefore, DataType returnT, ScopeType &t)
    {
        statementPos = statPos;
        startPos = spos;
        scopeDepth = sdep;
        stackSize = ssize;
        type = t;
        incrementor = sincrem;
        identifier = sidentifier;
        bytecodeSizeBefore = sizeBefore;
        returnType = returnT;
    }
    void reset() //Resets the struct to default values. MUST be called before a new expected scope is set up if the variable has previously been used
    {
        *this = Scope();
    }
    ScopeType type;
    unsigned int startPos;
    int scopeDepth;
    unsigned int statementPos;
    unsigned int stackSize;
    unsigned int endPos;
    unsigned int bytecodeSizeBefore;
    std::string incrementor;
    std::string identifier;
    bool wasOptimisedOut;
    unsigned int argumentCount;
    DataType returnType;
    bool scopeReturned;
    unsigned int initialisationVariableCount;

    std::vector<Scope> childMemberScopes;
    std::vector<Variable> childDataMembers;
};
#endif // VMTYPES_H
