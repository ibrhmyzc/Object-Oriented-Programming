/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: ibrahim
 *
 * Created on November 5, 2016, 12:18 PM
 */

#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <cstdint>
using namespace std;

class Memory{
public:
    Memory();
    Memory(int o);
    inline int getMem(int index) const {return (int)mem[index];}
    void setMem(int index, int value);
    void printAll() const;
private:
    uint8_t mem[50]; 
    int option;
};

#endif /* MEMORY_H */

