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
#include <iostream>
#include "Computer.h"
#include "CPUProgram.h"
#include "CPU.h"
#include "Memory.h"


using namespace std;


int main(int argc, char** argv) {
//START_OF_MAIN
    //Variables
    const char* filename = argv[1];
    int option = atoi(argv[2]);
    Memory myMemory(option);
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
    Computer myComputer2(option);
    
    
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
    cout << "\t\t START OF TESTING\n";
    //Testing memory  
    myMemory.setMem(0,100);
    cout << myMemory.getMem(0) << endl;
    myMemory.printAll();
    
    //testing cpu
    myCPU.execute("MOV #0, R1", myMemory);
    myCPU.execute("MOV R1, #1", myMemory);
    
    myCPU.print();
    myMemory.printAll();
    
    //testing cpuprogram  
    cout << myCPUProgram.getLine(0) << endl;
    cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
    
    cout << "\t\t END OF TESTING\n";
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
    myCPU.setPC(1);
    myCPU.setRegister(0,0);
    myMemory.setMem(0,0);
    myMemory.setMem(1,0);
    myComputer2.setCPU(myComputer1.getCPU());
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory());
    
    myComputer2.execute();

    return 0;
    
//END_OF_MAIN
}


















































