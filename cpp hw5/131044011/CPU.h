/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: ibrahim yazici 131044011
 *
 * Created on October 18, 2016, 11:10 AM
 */
#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include <iostream>
#include <string>
using namespace std;

class CPU{
public:
    CPU();
    CPU(int s);
    inline void setOption(int mode){ option = mode;}
    inline int getOption() const {return option;}
    inline int getPC() const {return PC-1;}
    inline void setPC(int line){PC = line;}
    inline void setPCplus1(){++PC;}
    inline bool getFinish()const{return finish;}
    inline void setFinish(bool end){finish = end;}
    inline int getRegister(int index) const{return r[index];}
    inline void setRegister(int index, int temp){r[index] = temp;}
    void print() const;
    bool halted();
    void execute(string instruction, Memory& myMemory);
    bool errorCheckForInstruction(string instruction,string& ins,string& reg, string& value, int& valuePassed, int& address);
    string upperChar(string temp);
    bool isANumber(char temp) const;
    bool isMemoryValid(string check);
    int stringToInteger(string temp);
    void mov(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    void sub(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    void add(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    void jmp(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    void jpn(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    void prn(string& ins,string& reg, string& value, int& valuePassed, Memory& myMemory);
    
private:
    int r[5];
    bool finish = false; 
    int option;
    int PC=1; 
};

#endif /* CPU_H */

