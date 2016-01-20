#include "VirtualStack.h"

VirtualStack::VirtualStack()
{
    //ctor
    stackOffset = 0;
}

VirtualStack::~VirtualStack()
{
    //dtor
}

void VirtualStack::push(const Variable& var)
{
    //std::cout << "\nPush type: " << dataTypeToString(var.type) << ". Stack size: " << stackOffset;
    if(stackOffset == maxStackSize)
        throw std::string("Can't push to virtual stack, stack full");
    stack[stackOffset++] = var;
}

Variable VirtualStack::pop()
{
   // std::cout << "\nPop type: " << dataTypeToString(stack[stackOffset-1].type) << ". Stack size: " << stackOffset-1;
    if(stackOffset == 0)
        throw std::string("Can't pop from virtual stack, stack empty");
    return stack[--stackOffset];
}

int VirtualStack::isVariable(const std::string& identifier)
{
    for(unsigned int a = 0; a < stackOffset; a++)
    {
        if(stack[a].identifier == identifier)
            return getStackSize() - a - 1; //Found, return stack offset
    }
    return -1; //Not found
}

unsigned int VirtualStack::getStackSize()
{
    return stackOffset;
}

void VirtualStack::resize(unsigned int newSize)
{
    stackOffset -= newSize;
}

Variable VirtualStack::getVariable(unsigned int stackPos)
{
    if(stackPos >= stackOffset)
        return Variable("", DataType::INT);
    return stack[stackPos];
}

void VirtualStack::renameVariable(unsigned int stackPos, const std::string &identifier)
{
    stack[stackPos].identifier = identifier;
}
