/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: ibrahim
 *
 * Created on November 5, 2016, 12:29 PM
 */

#ifndef COMPUTER_H
#define COMPUTER_H
#include "CPU.h"
#include "Memory.h"
#include "CPUProgramDyn.h"
using namespace std;
using namespace CPUProgramDynNameSpace;
class Computer{
public:
    Computer();
    Computer(CPU c,CPUProgramDyn p,Memory m, int o);
    Computer(int o);
    void setCPU(CPU c);
    CPU getCPU()const{return myCPU;}
    void setMemory(Memory m);
    Memory getMemory()const{return myMemory;}
    void setCPUProgram(CPUProgramDyn p);
    CPUProgramDyn getCPUProgram()const{return myProgram;}
    void setOption(int o);
    int getOption()const{return option;}
    void execute();
private:
    CPU myCPU;
    Memory myMemory;
    CPUProgramDyn myProgram;
    int option;
};

#endif /* COMPUTER_H */

