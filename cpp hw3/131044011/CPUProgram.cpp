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

//Constructor with filename
CPUProgram::CPUProgram(string fileName)
{
    readFile(fileName);
}

//Reading the file
void CPUProgram::readFile(string fileName)
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
    return numberOfLines;
}

string CPUProgram::getLine(int lineNumber) const
{
    return instruction[lineNumber];
}