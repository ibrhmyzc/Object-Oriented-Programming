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
    
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram[0] << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    
    cout << myCPUProgram.size() << endl;
    // op +
    cout << ((myCPUProgram + "prn r1")[myCPUProgram.size()-1]) << endl;
    cout << myCPUProgram.size() << endl;
    // op +=
    myCPUProgram += "prn r2";
    cout << myCPUProgram.size() << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    
    // op + <<
    CPUProgram myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    
    cout << (myCPUProgram + myOtherCPUProgram) << endl;
    
    //op comp --
    cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    
    //op()
    
    cout << myCPUProgram(5,10) << endl;
    
    //Error check
    cout << myCPUProgram[myCPUProgram.size()] << endl;
    
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    ////////////////////////////////////////////////////////////////////////////
    return 0;
    
//END_OF_MAIN
}


















































