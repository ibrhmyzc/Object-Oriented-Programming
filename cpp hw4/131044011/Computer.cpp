/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Computer.h"

    Computer::Computer()
    {
        
    }
    Computer::Computer(CPU c, CPUProgram p, Memory m, int o)
    {
        setCPU(c);
        setMemory(m);
        setCPUProgram(p);
        setOption(o);
    }
    Computer::Computer(int o)
    {
        setOption(o);
    }
    void Computer::setCPU(CPU c)
    {
        myCPU = c;
    }
    void Computer::setMemory(Memory m)
    {
        myMemory = m;
    }
    void Computer::setCPUProgram(CPUProgram p)
    {
        myProgram = p;
    }
    void Computer::setOption(int o)
    {
        option = o;
    }
    void Computer::execute()
    {
        string instruction;
        while(!myCPU.halted())
        {
            instruction = myProgram.getLine(myCPU.getPC());
            myCPU.execute(instruction, myMemory);     
        } 
    }
   