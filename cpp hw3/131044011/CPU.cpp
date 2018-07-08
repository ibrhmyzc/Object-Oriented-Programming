/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include "CPU.h"
using namespace std;

CPU::CPU()
{
    for(int i = 0; i < 5; ++i)
        r[i] = 0;
    PC = 1;
    
}

void CPU::print() const
{
    for(int i = 0; i < 5; ++i)
        cout << "R" << i+1 << "=" << r[i] << " "; 
    cout << endl;
}


//Calling error-checking function and other necessary functions for our program
void CPU::execute(string instruction)
{
    string ins;
    string reg;
    string value;
    int valuePassed;
    
    if(!errorCheckForInstruction(instruction,ins, reg, value, valuePassed))
    {
        setFinish(true);
        return;
    }
    
    if(halted() == true)
        return;
    
    
    //Halt instruction
    if(ins == "HLT")
    {
        setFinish(true);
        if(getOption() == "1")
            cout << ins << " -";
        print();
    }
    
    //mov instruction 
    else if(ins == "MOV")
    {
        mov(ins, reg, value, valuePassed);
        if(getOption() == "1")
        {
            cout << ins << " " << reg << ", " << value << " -";
            print();
        }
    }
    
    //add instruction
    else if(ins == "ADD")
    {
        add(ins, reg, value, valuePassed);
        if(getOption() == "1")
        {
            cout << ins << " " << reg << ", " << value << " -";
            print();
        }    
    }
    
    //sub instruction     
    else if(ins == "SUB")
    {
        sub(ins, reg, value, valuePassed );
        if(getOption() == "1")
        {
            cout << ins << " " << reg << ", " << value << " -";
            print();
        }    
    }
    
    //jmp instruction
    else if(ins == "JMP")
    {
        jmp(ins, reg, value, valuePassed);
        if(getOption() == "1")
        {
            if(valuePassed == 0)
                cout << ins << " " << reg << ", " << value << " -";
            else
                cout << ins << " " << reg << " -";
            print();
        }
    }
    
    //prn instruction
    else if(ins == "PRN")
    { 
        if(getOption() == "1")
        {
            if(valuePassed == 0)
                cout << ins << " " << reg << ", " << value << " -";
            else
                cout << ins << " " << reg << " -";
            print();
        }
        prn(ins, reg, value, valuePassed);
    }
    
    //increasing counter
    setPCplus1();
}

//mov instruction 
void CPU::mov(string& ins,string& reg, string& value, int& valuePassed)
{
    string s1;
    string s2;
    int i1;
    int i2;
    int iValue;
    
    iValue = stringToInteger(value);
    s1 = reg.substr(1,1);
    i1 = stringToInteger(s1);
    
    //like mov r1, 10
    if(valuePassed == 0)
    {
        if(reg == "R1")
            setRegister(0,iValue);
        else if(reg == "R2")
            setRegister(1,iValue); 
        else if(reg == "R3")
            setRegister(2,iValue); 
        else if(reg == "R4")
            setRegister(3,iValue); 
        else if(reg == "R5")
            setRegister(4,iValue); 
    }
    //like mov r1,r2
    else
    {
        s2 = value.substr(1,1);
        i2 = stringToInteger(s2);
        setRegister(i2-1,getRegister(i1-1));      
    }
}

//add instruction 
void CPU::add(string& ins,string& reg, string& value, int& valuePassed)
{
    string s1;
    string s2;
    int i1;
    int i2;
    int iValue;
    
    iValue = stringToInteger(value);
    s1 = reg.substr(1,1);
    i1 = stringToInteger(s1);
    
    //like add r1, 10
    if(valuePassed == 0)
    {
        if(reg == "R1")
            setRegister(0,getRegister(0) + iValue);
        else if(reg == "R2")
            setRegister(1,getRegister(1) + iValue);
        else if(reg == "R3")
            setRegister(2,getRegister(2) + iValue);
        else if(reg == "R4")
            setRegister(3,getRegister(3) + iValue);
        else if(reg == "R5")
            setRegister(4,getRegister(4) + iValue);
    }
    //like add r1,r2
    else
    {
        s2 = value.substr(1,1);
        i2 = stringToInteger(s2);
        setRegister(i1-1,getRegister(i1-1) + getRegister(i2-1)); 
    }
}

//sub instruction 
void CPU::sub(string& ins,string& reg, string& value, int& valuePassed)
{
    string s1;
    string s2;
    int i1;
    int i2;
    int iValue;
    
    iValue = stringToInteger(value);
    s1 = reg.substr(1,1);
    i1 = stringToInteger(s1);
    
    //like add r1, 10
    if(valuePassed == 0)
    {
        if(reg == "R1")
            r[0] -= iValue;
        else if(reg == "R2")
            r[1] -= iValue; 
        else if(reg == "R3")
            r[2] -= iValue; 
        else if(reg == "R4")
            r[3] -= iValue; 
        else if(reg == "R5")
            r[4] -= iValue; 
    }
    //like add r1,r2
    else
    {
        s2 = value.substr(1,1);
        i2 = stringToInteger(s2);
        r[i1-1] -= r[i2-1];     
    }
}

//jmp instruction 
void CPU::jmp(string& ins,string& reg, string& value, int& valuePassed) 
{
    string s;
    int i;
    // 0 -> jmp r1,5
    // 1 -> jmp 5
    if(valuePassed == 0)
    {
        s = reg.substr(1,1);
        i = stringToInteger(s);
        if(r[i-1] == 0)
            PC = stringToInteger(value) - 1;             
    }
    else if(valuePassed == 1)
    {
        PC = stringToInteger(value) - 1; 
    }
    
}

//prn instruction 
void CPU::prn(string& ins,string& reg, string& value, int& valuePassed)
{
    string s;
    int i;
    
    s = reg.substr(1,1);
    i = stringToInteger(s);
    
    cout << r[i-1] << endl;
    
}

bool CPU::halted() 
{ 
    return finish;
} 

//Returns false if there is an error in the instruction AND if none, it gives us register and values 
bool CPU::errorCheckForInstruction(string instruction,string& ins,string& reg, string& value, int& valuePassed) 
{
    
    int i;
    int jCounter;
    int count;
    
    count = 0;
    valuePassed = -1;
    jCounter = 0;
    
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            reg = instruction.substr(i, 3);
            reg = upperChar(reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(reg != "PRN" && reg != "SUB" && reg != "ADD" && reg != "MOV" && reg != "JMP"  && reg != "HLT" )
                {                   
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    return false;
                }
            } 
            else if(reg == "HLT")
            {}
            else
            {         
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                return false;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
    //store instruction in ins
    ins = reg;
    
    if(reg == "MOV" || reg == "ADD" || reg == "SUB")
    {
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through white spaces
            if(instruction[i] != ' ')
            {
                //Register must have two characters
                reg = instruction.substr(i, 2);
                reg = upperChar(reg);

                if(instruction[i+2] == ' ' || instruction[i+2] == ',')
                {
                    if(reg != "R1" && reg != "R2" && reg != "R3" && reg != "R4" && reg != "R5")
                    {
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return false;                   
                    }
                }
                else
                {
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    return false;
                }

                count = i+2;
                //Halting the for loop
                i = instruction.size();   

            }
        }
        //Reading until comma is found
        for(i=count; i < instruction.size(); ++i)
        {
            if(instruction[i] == ',')
            {
                count = i+1;
                //Halting the for loop
                i = instruction.size();
            }
        }
        //Getting the first register or the value
        //Starting after where the comma is located
        for(i=count; i < instruction.size(); ++i)
        {

            //Reading through white spaces
            if(instruction[i] != ' ')
            {         
                jCounter = 0;
                value = instruction.substr(i, 2);

                //If the first character represents a number or minus (-) than we check the rest
                if(isANumber(instruction[i+1]) == true && instruction[i] == '-')
                { 
                    for(int j=i+1; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == true)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }
                    //cout << jCounter << endl;
                    value = instruction.substr(i, jCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    valuePassed = 0;

                    i = instruction.size();
                   
                }
                else if(isANumber(instruction[i]) == true)
                {

                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == true)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << endl << jCounter << endl;
                    value = instruction.substr(i, jCounter);
                    //cout<<endl<< *reg << endl << *value << endl;
                    valuePassed = 0;

                    i = instruction.size();
                }
                else if(instruction[i+2] == ' ' || instruction[i+2] == ';' || instruction[i+2] == '\0')
                {
                    value = upperChar(value);
                    if(value != "R1" && value != "R2" && value != "R3" && value != "R4" && value != "R5")
                    {  
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return false;                
                    }
                }                   
                else
                { 
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    return false;  
                }

                count = i + 2;
                //Halting the for loop
                i = instruction.size();   

            }

        }
        //Checking for comments which should be written after a semicolon
        for(i=count; i < instruction.size(); ++i)
        {
            if(instruction[i] != ' ' && instruction[i] != ';')
            {
                cerr << "Invalid register" << endl;  
                //Exiting the while loop
                return false; 
                //Halting the for loop
                i = instruction.size();   
            }
            //Ignore what is written after semicolon
            if(instruction[i] == ';')
            {
                //Halting the for loop
                i = instruction.size();  
            }

        }
    }
    else if(reg == "PRN")
    {
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through whitespaces
            if(instruction[i] != ' ')
            {         
                jCounter = 0;
                value = instruction.substr(i, 2);

                //If the first character represents a number or minus (-) than we check the rest
                if(isANumber(instruction[i+1]) == true && instruction[i] == '-')
                { 
                    for(int j=i+1; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == true)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << jCounter << endl;
                    value = instruction.substr(i, jCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    valuePassed = 0;

                    i = instruction.size();
                }
                else if(isANumber(instruction[i]) == true)
                {

                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == true)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << endl << jCounter << endl;
                    value = instruction.substr(i, jCounter);
                    //cout<<endl<< *reg << endl << *value << endl;
                    valuePassed = 0;

                    i = instruction.size();
                }
                else if(instruction[i+2] == ' ' || instruction[i+2] == ';' || instruction[i+2] == '\0')
                { 
                     value = upperChar(value);
                    if(value != "R1" && value != "R2" && value != "R3" && value != "R4" && value != "R5")
                    {  
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return false;                  
                    }
                    reg = value;
                }                   
                else
                { 
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    return false;  
                }
                count = i + 2;
                //Halting the for loop
                i = instruction.size();   

            }
        }
        //Checking for comments which should be written after a semicolon
        for(i=count; i < instruction.size(); ++i)
        {
            if(instruction[i] != ' ' && instruction[i] != ';')
            {
                cerr << "Invalid register" << endl;  
                //Exiting the while loop
                return false; 
                //Halting the for loop
                i = instruction.size();   
            }
            //Ignore what is written after semicolon
            if(instruction[i] == ';')
            {
                //Halting the for loop
                i = instruction.size();  
            }

        }

    }
    else if(reg == "JMP")
    { 
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through whitespaces
            if(instruction[i] != ' ')
            {
                //Register must have two characters
                reg = instruction.substr(i, 2);
                reg = upperChar(reg);
                //cout << reg << endl;
                if(isANumber(instruction[i]) == true)
                {
                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == true)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }
                    //cout << endl << jCounter << endl;
                    value = instruction.substr(i, jCounter);

                    //cout<<endl<< *reg << endl << *value << endl;
                    valuePassed = 1;
                    count = count + jCounter;
                    i = instruction.size();
                }
                if(instruction[i+jCounter] == ' ' || instruction[i+jCounter] == ';')
                {


                }
                count = i+2;
                //Halting the for loop
                i = instruction.size();   

            }
        } 
        //if it is like jmp 5
        if(reg != "R1" && reg != "R2" && reg != "R3" && reg != "R4" && reg != "R5")
        {
            //Getting the first register or the value
            for(i=count-2; i < instruction.size(); ++i)
            {    
                //Reading through whitespaces
                if(instruction[i] != ' ')
                {         
                    jCounter = 0;
                    value = instruction.substr(i, 1);

                    //If the first character represents a number than we check the rest
                    if(isANumber(instruction[i]) == true)
                    {

                        for(int j=i; j < instruction.size(); ++j)
                        {
                            if(isANumber(instruction[j]) == true)
                            {
                               jCounter++;   
                            }
                            else
                                j = instruction.size();

                        }

                        //cout << endl << jCounter << endl;
                        value = instruction.substr(i, jCounter);

                        //cout<<endl<< *reg << endl << *value << endl;
                        valuePassed = 1;
                        count = count + jCounter;
                        i = instruction.size();
                    }
                    else if(instruction[i+jCounter] == ' ' || instruction[i+jCounter] == ';' || instruction[i+jCounter] != '\0')
                    {
                        cerr << "Invalid jmp" << endl;
                        //Exiting the while loop
                        return false; 
                    }                   
                    else
                    { 
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return false;  
                    }
                    count = i + 2;
                    //Halting the for loop
                    i = instruction.size();   
                }

            }
            //Checking for comments which should be written after a semicolon
            for(i=count; i < instruction.size(); ++i)
            {
                if(instruction[i] != ' ' && instruction[i] != ';')
                {
                    cerr << "Invalid register" << endl;  
                    //Exiting the while loop
                    return false;; 
                    //Halting the for loop
                    i = instruction.size();   
                }
                //Ignore what is written after semicolon
                if(instruction[i] == ';')
                {
                    //Halting the for loop
                    i = instruction.size();  
                }

            }

        }
        else
        { 
            //Reading until comma is found
            for(i=count; i < instruction.size(); ++i)
            {

                if(instruction[i] == ',')
                {
                    count = i+1;
                    //Halting the for loop
                    i = instruction.size();
                }
            }
            //Getting the first register or the value
            for(i=count; i < instruction.size(); ++i)
            {
                //Reading through whitespaces
                if(instruction[i] != ' ')
                {         
                    jCounter = 0;
                    value = instruction.substr(i, 2);

                    //If the first character represents a number than we check the rest
                    if(isANumber(instruction[i]) == true)
                    {

                        for(int j=i; j < instruction.size(); ++j)
                        {
                            if(isANumber(instruction[j]) == true)
                            {
                               jCounter++;   
                            }
                            else
                                j = instruction.size();

                        }

                        //cout << endl << jCounter << endl;
                        value = instruction.substr(i, jCounter);
                        //cout<<endl<< *reg << endl << *value << endl;
                        valuePassed = 0;
                        
                        i = instruction.size();
                    }
                    else if(instruction[i+jCounter] == ' ' || instruction[i+jCounter] == ';' || instruction[i+jCounter] == '\0')
                    {
                        value = upperChar(value);
                        if(value != "R1" && value != "R2" && value != "R3" && value != "R4" && value != "R5")
                        {  
                            cerr << "Invalid register" << endl;
                            //Exiting the while loop
                            return false;                   
                        }
                    }                   
                    else
                    { 
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return -1; 
                    }

                    count = i + 2;
                    //Halting the for loop
                    i = instruction.size();   


                }

            }
            //Checking for comments which should be written after a semicolon
            for(i=count; i < instruction.size(); ++i)
            {
                if(instruction[i] != ' ' && instruction[i] != ';')
                {

                    cerr << "Invalid register" << endl;  
                    //Exiting the while loop
                    return -1; 
                    //Halting the for loop
                    i = instruction.size();   
                }
                //Ignore what is written after semicolon
                if(instruction[i] == ';')
                {
                    //Halting the for loop
                    i = instruction.size();  
                }

            }

        }

    }
    else if(reg == "HLT")
    {
        
    }
    return true;
}
    
//Checking whether a character represents a number or not
bool CPU::isANumber(char temp) const
{
    //If the character is a number returns 0,otherwise returns 1
     if(temp == '0' || temp == '1' || temp == '2' 
             || temp == '3' || temp == '4' || temp == '5'
             || temp == '6' || temp== '7' || temp == '8' 
             || temp == '9' )
     {
         return true;
     }
     return false;
}

//Converting all characters to uppercase
string CPU::upperChar(string temp)
{
    // THIS FUNCTION IS SHOWN IN PS
    // It may look similar because it is shown in the middle of the class
    for(int i=0; i < temp.size(); ++i)
    {
        //Replacing lower characters with upper ones
        if(temp[i] >= 'a' && temp[i] <= 'z')
        {
            temp[i] = temp[i] + 'A' - 'a';
        }
    }
    return temp;
}

//Converting a string to an integer value
int CPU::stringToInteger(string temp)
{
    //Used instead of stoi() which is forbidden
    int number = 0; 
  
    //Converting all of the strings elements to integer until the end of the string
    if(temp[0] == '-')
    {
       for(int i = 1; i < temp.size(); ++i)
        number = number * 10 + temp[i] - '0'; 
    }
    else
    {
        for(int i = 0; i < temp.size(); ++i)
        number = number * 10 + temp[i] - '0';
    }
    //If it is a negative number
    if(temp[0] == '-')
        return -number;
    
    return number;
}










































