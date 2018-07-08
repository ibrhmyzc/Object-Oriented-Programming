/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgramDyn.h
 * Author: ibrahim
 *
 * Created on November 29, 2016, 10:58 AM
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <iostream>
using namespace std;

namespace CPUProgramDynNameSpace
{
    
    
class CPUProgramDyn{
public:
    CPUProgramDyn();
    CPUProgramDyn(int o);
    CPUProgramDyn(const CPUProgramDyn& c);
    ~CPUProgramDyn(){delete [] instruction;}
    int getOption() const{return option;}
    int getMaximum() const{return maximum;}
    void setMaximum(int m){ maximum=m;}
    void setOption(int o){ option = o;}
    CPUProgramDyn(string fileName);
    void ReadFile(string fileName);
    string getLine(int lineNumber)const;
    int size()const;
    void addLine(string);
    string& operator[](int index);
    CPUProgramDyn& operator=(const CPUProgramDyn& c);
    CPUProgramDyn operator+(string line);
    CPUProgramDyn& operator+=(string line);
    CPUProgramDyn operator+(const CPUProgramDyn& p);
    friend ostream& operator <<(ostream& output, const CPUProgramDyn& p);
    bool operator ==(const CPUProgramDyn& p);
    bool operator <=(const CPUProgramDyn& p);
    bool operator >(const CPUProgramDyn& p);
    bool operator !=(const CPUProgramDyn& p);
    bool operator >=(const CPUProgramDyn& p);
    bool operator <(const CPUProgramDyn& p);
    CPUProgramDyn& operator--();
    CPUProgramDyn operator--(int);
    CPUProgramDyn operator()(int index1, int index2);
private:
    string *instruction;
    int maximum;
    int numberOfLines=0;
    int option;
};

}
#endif /* CPUPROGRAMDYN_H */

