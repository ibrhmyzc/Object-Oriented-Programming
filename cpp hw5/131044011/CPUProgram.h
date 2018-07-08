/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgram.h
 * Author: ibrahim yazici 131044011
 *
 * Created on October 18, 2016, 10:53 AM
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <vector>
using namespace std;



class CPUProgram{
public:
    CPUProgram();
    CPUProgram(int o);
    int getOption() const{return option;}
    void setOption(int o){ option = o;}
    CPUProgram(string fileName);
    void ReadFile(string fileName);
    string getLine(int lineNumber)const;
    int size()const;
    string& operator[](int index);
    CPUProgram operator+(string line);
    CPUProgram& operator+=(string line);
    CPUProgram operator+(const CPUProgram& p);
    friend ostream& operator <<(ostream& output, const CPUProgram& p);
    bool operator ==(const CPUProgram& p);
    bool operator <=(const CPUProgram& p);
    bool operator >(const CPUProgram& p);
    bool operator !=(const CPUProgram& p);
    bool operator >=(const CPUProgram& p);
    bool operator <(const CPUProgram& p);
    CPUProgram& operator--();
    CPUProgram operator--(int);
    CPUProgram operator()(int index1, int index2);
private:
    vector<string> instruction; 
    int numberOfLines=0;
    int option;
};


#endif /* CPUPROGRAM_H */

