/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Memory.h"

Memory::Memory()
{
    for(int i = 0; i < 50; ++i)
        mem[i] = 0;
}
Memory::Memory(int o)
{
    for(int i = 0; i < 50; ++i)
        mem[i] = 0;
    option = o;
}
void Memory::setMem(int index, int value)
{
    mem[index] = value;
}


void Memory::printAll() const
{
    cout << endl;
    for(int i = 0; i < 50; ++i)
    {
        cout << "#" << i << "=" << getMem(i) << ", ";
        if(i!= 0 && i%9 == 0)
            cout << endl;
    }
    cout << endl;
}