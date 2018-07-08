/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgram.cpp
 * Author: ibrahim
 *
 * Created on October 22, 2016, 5:32 AM
 */
#include "CPUProgram.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

CPUProgram::CPUProgram()
{
    /*intentionally empty*/
}
CPUProgram::CPUProgram(int o)
{
    setOption(o);
}
//Overloading operator [] 
string& CPUProgram::operator[](int index)
{
    if(index < 0 || index >= numberOfLines)
    {
        cerr << "Index must be smaller than number of lines" << endl;
        exit(1);
    }
    return instruction[index];
}

//Overloading operator +
CPUProgram CPUProgram::operator+(string line)
{
    CPUProgram newProgram;
    newProgram.instruction = instruction;
    newProgram.numberOfLines = numberOfLines;
    newProgram.option = option;
    newProgram.instruction.push_back(line);
    return newProgram;
}  
//Overloading operator +=
CPUProgram& CPUProgram::operator+=(string line)
{
    this->instruction.push_back(line);
    this->numberOfLines++;
    return *this;
}

//Overloading operator +
CPUProgram CPUProgram::operator+(const CPUProgram& p)
{
    CPUProgram newProgram;
    newProgram.instruction = this->instruction;
    newProgram.instruction.insert(newProgram.instruction.end(), p.instruction.begin(), p.instruction.end());
    newProgram.numberOfLines = newProgram.size();
    newProgram.option = this->option;
    
    return newProgram; 
}

ostream& operator <<(ostream& output, const CPUProgram& p)
{
    for(int i = 0; i < p.size(); ++i)
        output << p.instruction[i] << endl;
    return output;
}


bool CPUProgram::operator ==(const CPUProgram& p)
{
    return (this->size() == p.size());
}
bool CPUProgram::operator <=(const CPUProgram& p)
{
    return (this->size() <= p.size());
}
bool CPUProgram::operator >(const CPUProgram& p)
{
    return (this->size() > p.size());
}
bool CPUProgram::operator !=(const CPUProgram& p)
{
    return (this->size() !=  p.size());
}
bool CPUProgram::operator >=(const CPUProgram& p)
{
    return (this->size() >=  p.size());
}
bool CPUProgram::operator <(const CPUProgram& p)
{
    return (this->size() <  p.size());
}

CPUProgram& CPUProgram::operator--()
{
    this->instruction.pop_back();
    this->numberOfLines--;
    return *this;
}

CPUProgram CPUProgram::operator--(int)
{
    CPUProgram newProgram;
    newProgram.instruction = instruction;
    newProgram.numberOfLines = numberOfLines;
    newProgram.option = option;
    this->instruction.pop_back();
    this->numberOfLines--;
    return newProgram;
}

CPUProgram CPUProgram::operator()(int index1, int index2)
{
    if(index1 < 0 || index2 >= numberOfLines || (index1 > index2))
    {
        cerr << "Invalid index" << endl;
        CPUProgram newProgram;
        newProgram.instruction.clear();
        return newProgram;
    }
    else
    {
        CPUProgram newProgram;
        newProgram.instruction.clear();
        for(int i = index1; i <= index2; ++i)
            newProgram.instruction.push_back(instruction[i]);
        newProgram.numberOfLines = newProgram.size();
        newProgram.option = option;
        return newProgram;
    }
   
}

//Reading the file
void CPUProgram::ReadFile(string fileName)
{
    ifstream inputFile;
    string instructionOnLine;
    
    inputFile.open(fileName);
    /*Checking the file*/
    if(inputFile.is_open())
    {
        while(getline(inputFile,instructionOnLine))
        {
            instruction.push_back(instructionOnLine);
            numberOfLines++;
        }
    }
    else
        cerr << "File error" << endl;
}

int CPUProgram::size() const
{
    return instruction.size();
}

string CPUProgram::getLine(int lineNumber) const
{
    return instruction[lineNumber];
}