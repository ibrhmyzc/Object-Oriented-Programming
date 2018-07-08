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

#include <iostream>
#include <string>
using namespace std;

class CPU{
public:
    CPU();
    inline void setOption(string mode){ option = mode;}
    inline string getOption() const {return option;}
    inline int getPC() const {return PC-1;}
    inline void setPC(int line){PC = line - 1;}
    inline void setPCplus1(){++PC;}
    inline bool getFinish()const{return finish;}
    inline void setFinish(bool end){finish = end;}
    inline int getRegister(int index) const{return r[index];}
    inline void setRegister(int index, int temp){r[index] = temp;}
    void print() const;
    bool halted();
    void execute(string instruction);
    bool errorCheckForInstruction(string instruction,string& ins,string& reg, string& value, int& valuePassed);
    string upperChar(string temp);
    bool isANumber(char temp) const;
    int stringToInteger(string temp);
    void mov(string& ins,string& reg, string& value, int& valuePassed);
    void sub(string& ins,string& reg, string& value, int& valuePassed);
    void add(string& ins,string& reg, string& value, int& valuePassed);
    void jmp(string& ins,string& reg, string& value, int& valuePassed);
    void prn(string& ins,string& reg, string& value, int& valuePassed);
    
private:
    int r[5];
    bool finish = false; 
    string option;
    int PC; 
};

#endif /* CPU_H */

