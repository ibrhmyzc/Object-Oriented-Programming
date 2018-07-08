/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPUProgramDyn.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace CPUProgramDynNameSpace
{

CPUProgramDyn::CPUProgramDyn()
{
    maximum = 500;
    instruction = new string[maximum];
    
}
CPUProgramDyn::CPUProgramDyn(int o)
{
    setOption(o);
    maximum = 500;
    instruction = new string[maximum];
}

//CopyConstructor
CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& c)
{
    setOption(c.getOption());
    maximum = c.getMaximum();
    instruction = new string[c.getMaximum()];
    for(int i = 0; i < c.size(); ++i)
        instruction[i] = c.instruction[i];
    numberOfLines = c.size();
}

CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& c)
{
    setOption(c.getOption());
    maximum = c.getMaximum();
    instruction = new string[c.getMaximum()];
    for(int i = 0; i < c.size(); ++i)
        instruction[i] = c.instruction[i];
    numberOfLines = c.size();
}

//Overloading operator [] 
string& CPUProgramDyn::operator[](int index)
{
    if(index < 0 || index >= numberOfLines)
    {
        cerr << "Out of index";
        cerr << ". so it returns first index(instead of empty) :";
        return instruction[0];
    }
    return instruction[index];
}

//Overloading operator +
CPUProgramDyn CPUProgramDyn::operator+(string line)
{
    CPUProgramDyn newProgram;
    
    newProgram.setOption(getOption());
    newProgram.setMaximum(getMaximum());
    
    for(int i = 0; i < size(); ++i)
        newProgram.instruction[i] = instruction[i];
    newProgram.numberOfLines = size();
    newProgram.addLine(line);
    
    return newProgram;
}  
//Overloading operator +=
CPUProgramDyn& CPUProgramDyn::operator+=(string line)
{
    this->addLine(line);
    return *this;
}

//Overloading operator +
CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn& p)
{
    CPUProgramDyn newProgram;
    
    newProgram.setOption(getOption());
    
    
    for(int i = 0; i < size(); ++i)
        newProgram.addLine(instruction[i]);
    
    for(int i = 0; i < p.size(); ++i)
        newProgram.addLine(p.instruction[i]);
    
    
    
    return newProgram; 
}

ostream& operator <<(ostream& output, const CPUProgramDyn& p)
{
    for(int i = 0; i < p.size(); ++i)
        output << p.instruction[i] << endl;
    return output;
}


bool CPUProgramDyn::operator ==(const CPUProgramDyn& p)
{
    return (this->size() == p.size());
}
bool CPUProgramDyn::operator <=(const CPUProgramDyn& p)
{
    return (this->size() <= p.size());
}
bool CPUProgramDyn::operator >(const CPUProgramDyn& p)
{
    return (this->size() > p.size());
}
bool CPUProgramDyn::operator !=(const CPUProgramDyn& p)
{
    return (this->size() !=  p.size());
}
bool CPUProgramDyn::operator >=(const CPUProgramDyn& p)
{
    return (this->size() >=  p.size());
}
bool CPUProgramDyn::operator <(const CPUProgramDyn& p)
{
    return (this->size() <  p.size());
}

CPUProgramDyn& CPUProgramDyn::operator--()
{
    this->numberOfLines--;
    return *this;
}

CPUProgramDyn CPUProgramDyn::operator--(int)
{
    CPUProgramDyn newProgram;
    newProgram.setOption(getOption());
    newProgram.setMaximum(getMaximum());
    
    for(int i = 0; i < size(); ++i)
        newProgram.instruction[i] = instruction[i];
    newProgram.numberOfLines = size() - 1;
    return newProgram;
}

CPUProgramDyn CPUProgramDyn::operator()(int index1, int index2)
{
    if(index1 < 0 || index2 >= numberOfLines || (index1 > index2))
    {
        cerr << "Invalid index" << endl;
        CPUProgramDyn newProgram;
        newProgram.numberOfLines = 0;
        return newProgram;
    }
    else
    {
        CPUProgramDyn newProgram;
        newProgram.numberOfLines = 0;
        for(int i = index1; i <= index2; ++i)
            newProgram.addLine(instruction[i]);
        newProgram.numberOfLines = newProgram.size();
        newProgram.option = option;
        return newProgram;
    }
   
}

//Reading the file
void CPUProgramDyn::ReadFile(string fileName)
{
    ifstream inputFile;
    string instructionOnLine;
    
    inputFile.open(fileName);
    /*Checking the file*/
    if(inputFile.is_open())
    {
        while(getline(inputFile,instructionOnLine))
        {
            addLine(instructionOnLine);
        }
    }
    else
        cerr << "File error" << endl;
}

void CPUProgramDyn::addLine(string newLine)
{
    //If it reached the maximum size of the array
    //We need to allocate, if possible, more spaces
    if(maximum > numberOfLines)
    {
        string *temp;
        maximum = maximum + 10;
        temp = new string[maximum];
        
        if(temp == nullptr)
        {
            cerr << "Not enough memory for expanding the array\n";
            exit(1);
        }
        
        for(int i = 0; i < numberOfLines; ++i)
            temp[i] = instruction[i];
        
        instruction = new string[maximum];
        
        for(int i = 0; i < numberOfLines; ++i)
            instruction[i] = temp[i];
        
        delete [] temp;
    }
    instruction[numberOfLines] = newLine;
    numberOfLines++;
    if(newLine == "")
    {
        cerr << "Empty string was not added" << endl;
        numberOfLines--;
    }
}

int CPUProgramDyn::size() const
{
    return numberOfLines;
}

string CPUProgramDyn::getLine(int lineNumber) const
{
    return instruction[lineNumber];
}

}//end of namespace
