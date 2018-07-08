/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ibrahim
 * no : 131044011
 * Created on October 18, 2016, 10:43 AM
 */
#include "CPUProgram.h"
#include "CPU.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv) {
//START_OF_MAIN
    //Variables
    string instruction;
    string option;
    CPUProgram myProgram(argv[1]);
    CPU myCPU;
    
    //Output option
    option = argv[2];
    myCPU.setOption(option);
    
    //Main loop for out program
    while(!myCPU.halted())
    {
        instruction = myProgram.getLine(myCPU.getPC());
        myCPU.execute(instruction);     
    } 
    return 0;
    
//END_OF_MAIN
}


















































