/* 
 * File:   main.cpp
 * Author: ibrahim yazici 131044011
 * simulates a basic cpu program
 * Created on September 27, 2016, 1:43 PM
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;

//Converts a string to integer
int stringToInteger(string temp);

//Checking the character if it is a number
int isANumber(char temp);

//Converts all characters to uppercase in a string
void upperChar(string &temp);

//File reader function
void fileReader(ifstream& file, string filename, string option, int& r1, int& r2, int& r3, int& r4, int& r5, uint8_t mem[]);

//Checking the line for error
int errorCheck(string instruction, string *reg, string *value, int *valuePassed, int& address);

//for MOV instruction
void mov(string instruction, string reg, string temp, string option, int type, int& r1, int& r2, int& r3, int& r4, int& r5, uint8_t mem[], int address);

//for ADD instruction
void add(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address);

//for SUB instruction
void sub(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address);

//for PRN instruction
void prn(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address);

//for JMP instruction
void jmp(ifstream& input, string filename, string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5);

//for JMN instruction
void jpn(ifstream& input, string filename, string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5);

//for PRN instruction
void hlt(int r1, int r2, int r3, int r4, int r5);

//memory edit
void setMemory(uint8_t mem[], int index, int value);

//memory read
int getMemory(uint8_t mem[], int index);

//Check if the memory address is valid
int memoryValid(string& check);

//Prints all memory 
void printMemory(uint8_t mem[]);


int main(int argc, char** argv) {
 //START OF MAIN   
    
 //Variable
    //Only registers that the program has
    int R1=0;
    int R2=0;
    int R3=0;
    int R4=0;
    int R5=0;
    unsigned char mem[50];
    
    //Variables for File
    ifstream input;
    string filename;
    string option;
    
    input.open(argv[1]);
    filename = argv[1];
    option = argv[2];
    
    for(int i=0; i < 50; ++i)
        mem[i] = 0;
    
    if(input.is_open())
    {
        fileReader(input, filename, option, R1, R2, R3, R4, R5, mem);  
    }  
    else
    {
        cerr << "File is not open" << endl;
    }
   
    return 0;
//END OF MAIN
}

void printMemory(uint8_t mem[])
{
    for(int i = 0; i < 50; ++i)
    {
        cout << "#" << i << "=" << (int)mem[i] << ",";
    }
    cout << endl;
}

void setMemory(uint8_t mem[], int index, int value)
{
    mem[index] = value;
    
}

int getMemory(uint8_t mem[], int index)
{
    return (int)mem[index];
}

int memoryValid(string& check)
{
    int temp;
    string s;
    s = check;
    s = s.erase(0,1);
    temp = stringToInteger(s);
    if(temp >= 0 && temp < 50)
        return 0;
    return 1;
}

void mov(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address)
{
    int value;
    string a;
    
    //type=0 r1,10
    //type=1 r1,r1
    //type=2 #13,r1
    //type=3 r1,#13
    //type=4 #13,5
    address = 0;
    
    if(type == 0)
    {       
        //cout << "temp2:" << temp2 << endl;
        value = stringToInteger(temp);
        //cout << "value:" << value << endl;
        if(reg == "R1")
            R1 = value;
        else if(reg == "R2")
            R2 = value;
        else if(reg == "R3")
            R3 = value;
        else if(reg == "R4")
            R4 = value;
        else if(reg == "R5")
            R5 = value;  
    }
    else if(type == 1)
    {
        if(reg == "R1" && temp == "R1")
            R1 = R1;
        else if(reg == "R1" && temp == "R2")
            R2 = R1;
        else if(reg == "R1" && temp == "R3")
            R2 = R1;
        else if(reg == "R1" && temp == "R4")
            R4 = R1;
        else if(reg == "R1" && temp == "R5")
            R5 = R1;
        else if(reg == "R2" && temp == "R1")
            R1 = R2;
        else if(reg == "R2" && temp == "R2")
            R2 = R2;
        else if(reg == "R2" && temp == "R3")
            R3 = R2;
        else if(reg == "R2" && temp == "R4")
            R4 = R2;
        else if(reg == "R2" && temp == "R5")
            R5 = R2;
        else if(reg == "R3" && temp == "R1")
            R1 = R3;
        else if(reg == "R3" && temp == "R2")
            R2 = R3;
        else if(reg == "R3" && temp == "R3")
            R3 = R3;
        else if(reg == "R3" && temp == "R4")
            R4 = R3;
        else if(reg == "R3" && temp == "R5")
            R5 = R3;
        else if(reg == "R4" && temp == "R1")
            R1 = R4;
        else if(reg == "R4" && temp == "R2")
            R2 = R4;
        else if(reg == "R4" && temp == "R3")
            R3 = R4;
        else if(reg == "R4" && temp == "R4")
            R4 = R4;
        else if(reg == "R4" && temp == "R5")
            R5 = R4;
        else if(reg == "R5" && temp == "R1")
            R1 = R5;
        else if(reg == "R5" && temp == "R2")
            R2 = R5;
        else if(reg == "R5" && temp == "R3")
            R3 = R5;
        else if(reg == "R5" && temp == "R4")
            R4 = R5;
        else if(reg == "R5" && temp == "R5")
            R5 = R5;
    }
    else if(type == 2)
    {
        a = reg;
        a = a.erase(0,1);

        address = stringToInteger(a);
        
        if(temp == "R1")
            R1 = getMemory(mem, address);
        else if(temp == "R2")
            R2 = getMemory(mem, address);
        else if(temp == "R3")
            R3 = getMemory(mem, address);
        else if(temp == "R4")
            R4 = getMemory(mem, address);
        else if(temp == "R5")
            R5 = getMemory(mem, address);
    }
    else if(type == 3)
    {
        a = temp;
        a = a.erase(0,1);
                
        address = stringToInteger(a);
               
        if(reg == "R1")
            setMemory(mem, address, R1);
        else if(reg == "R2")
            setMemory(mem, address, R2);
        else if(reg == "R3")
            setMemory(mem, address, R3);
        else if(reg == "R4")
            setMemory(mem, address, R4);
        else if(reg == "R5")
            setMemory(mem, address, R5);
    }
    else if(type == 4)
    {
        a = reg;
        a = a.erase(0,1);
        address = stringToInteger(a);
        value = stringToInteger(temp);
        setMemory(mem, address, value);
    }
    if(option == "1" || option == "2")
    {
        cout << instruction << " "<< reg << ", " << temp << "-";
        cout << "R1=" << R1;
        cout << ",R2=" << R2;
        cout << ",R3=" << R3;
        cout << ",R4=" << R4;
        cout << ",R5=" << R5 << endl;
        if(option == "2")
            printMemory(mem);
    }
}

void add(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address)
{
    int value;
    string a;

    //type=0 r1,10
    //type=1 r1,r1
    //type=3 r1,#34
    
    if(type == 0)
    {
        //cout << "temp2:" << temp2 << endl;
        value = stringToInteger(temp);
        //cout << "value:" << value << endl;
        if(reg == "R1")
            R1 += value;
        else if(reg == "R2")
            R2 += value;
        else if(reg == "R3")
            R3 += value;
        else if(reg == "R4")
            R4 += value;
        else if(reg == "R5")
            R5 += value;
    }
    else if(reg == "R1" && temp == "R1")
        R1 += R1;
    else if(reg == "R1" && temp == "R2")
        R1 += R2;
    else if(reg == "R1" && temp == "R3")
        R1 += R3;
    else if(reg == "R1" && temp == "R4")
        R1 += R4;
    else if(reg == "R1" && temp == "R5")
        R1 += R5;
    else if(reg == "R2" && temp == "R1")
        R2 += R1;
    else if(reg == "R2" && temp == "R2")
        R2 += R2;
    else if(reg == "R2" && temp == "R3")
        R2 += R3;
    else if(reg == "R2" && temp == "R4")
        R2 += R4;
    else if(reg == "R2" && temp == "R5")
        R2 += R5;
    else if(reg == "R3" && temp == "R1")
        R3 += R1;
    else if(reg == "R3" && temp == "R2")
        R3 += R2;
    else if(reg == "R3" && temp == "R3")
        R3 += R3;
    else if(reg == "R3" && temp == "R4")
        R3 += R4;
    else if(reg == "R3" && temp == "R5")
        R3 += R5;
    else if(reg == "R4" && temp == "R1")
        R4 += R1;
    else if(reg == "R4" && temp == "R2")
        R4 += R2;
    else if(reg == "R4" && temp == "R3")
        R4 += R3;
    else if(reg == "R4" && temp == "R4")
        R4 += R4;
    else if(reg == "R4" && temp == "R5")
        R4 += R5;
    else if(reg == "R5" && temp == "R1")
        R5 += R1;
    else if(reg == "R5" && temp == "R2")
        R5 += R2;
    else if(reg == "R5" && temp == "R3")
        R5 += R3;
    else if(reg == "R5" && temp == "R4")
        R5 += R4;
    else if(reg == "R5" && temp == "R5")
        R5 += R5;  
    if(type == 3)
    {
        a = temp;
        a = a.erase(0,1);
        address = stringToInteger(a);
        
        if(reg == "R1")
            R1 += getMemory(mem, address);
        else if(reg == "R2")
            R2 += getMemory(mem, address);
        else if(reg == "R3")
            R3 += getMemory(mem, address);
        else if(reg == "R4")
            R4 += getMemory(mem, address);
        else if(reg == "R5")
            R5 += getMemory(mem, address);
    }
    if(option == "1" || option == "2")
    {
        cout << instruction << " " << reg << ", " << temp << "-";
        cout << "R1=" << R1;
        cout << ",R2=" << R2;
        cout << ",R3=" << R3;
        cout << ",R4=" << R4;
        cout << ",R5=" << R5 << endl;
        
        if(option == "2")
            printMemory(mem);
    }
}

void sub(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address)
{
    int value;
    string a;

    //type=0 r1,10
    //type=1 r1,r1
    //type=2 r1,#34

    if(type == 0)
    {
        //cout << "temp2:" << temp2 << endl;
        value = stringToInteger(temp);
        //cout << "value:" << value << endl;
        if(reg == "R1")
            R1 -= value;
        else if(reg == "R2")
            R2 -= value;
        else if(reg == "R3")
            R3 -= value;
        else if(reg == "R4")
            R4 -= value;
        else if(reg == "R5")
            R5 -= value;
    }
    else if(reg == "R1" && temp == "R1")
        R1 -= R1;
    else if(reg == "R1" && temp == "R2")
        R1 -= R2;
    else if(reg == "R1" && temp == "R3")
        R1 -= R3;
    else if(reg == "R1" && temp == "R4")
        R1 -= R4;
    else if(reg == "R1" && temp == "R5")
        R1 -= R5;
    else if(reg == "R2" && temp == "R1")
        R2 -= R1;
    else if(reg == "R2" && temp == "R2")
        R2 -= R2;
    else if(reg == "R2" && temp == "R3")
        R2 -= R3;
    else if(reg == "R2" && temp == "R4")
        R2 -= R4;
    else if(reg == "R2" && temp == "R5")
        R2 -= R5;
    else if(reg == "R3" && temp == "R1")
        R3 -= R1;
    else if(reg == "R3" && temp == "R2")
        R3 -= R2;
    else if(reg == "R3" && temp == "R3")
        R3 -= R3;
    else if(reg == "R3" && temp == "R4")
        R3 -= R4;
    else if(reg == "R3" && temp == "R5")
        R3 -= R5;
    else if(reg == "R4" && temp == "R1")
        R4 -= R1;
    else if(reg == "R4" && temp == "R2")
        R4 -= R2;
    else if(reg == "R4" && temp == "R3")
        R4 -= R3;
    else if(reg == "R4" && temp == "R4")
        R4 -= R4;
    else if(reg == "R4" && temp == "R5")
        R4 -= R5;
    else if(reg == "R5" && temp == "R1")
        R5 -= R1;
    else if(reg == "R5" && temp == "R2")
        R5 -= R2;
    else if(reg == "R5" && temp == "R3")
        R5 -= R3;
    else if(reg == "R5" && temp == "R4")
        R5 -= R4;
    else if(reg == "R5" && temp == "R5")
        R5 -= R5;  
    if(type == 3)
    {
        a = temp;
        a = a.erase(0,1);
        address = stringToInteger(a);
        
        if(reg == "R1")
            R1 -= getMemory(mem, address);
        else if(reg == "R2")
            R2 -= getMemory(mem, address);
        else if(reg == "R3")
            R3 -= getMemory(mem, address);
        else if(reg == "R4")
            R4 -= getMemory(mem, address);
        else if(reg == "R5")
            R5 -= getMemory(mem, address);
    }
    if(option == "1" || option == "2")
    {
        cout << instruction << " " << reg << ", " << temp << "-";
        cout << "R1=" << R1;
        cout << ",R2=" << R2;
        cout << ",R3=" << R3;
        cout << ",R4=" << R4;
        cout << ",R5=" << R5 << endl;
        if(option == "2")
            printMemory(mem);
    }
}

void prn(string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[], int address)
{
    string a;
    
   //type=0 19
    //type=1 r1
    //type=2 #43
   
    
    if(type == 0)
    {
        cout << temp << endl;
    }
    else if(type == 1)
    {
            if(reg == "R1")
        {
            if(option == "1" || option =="2")
            {
                cout << instruction << " " << temp <<"-";
                cout << "R1=" << R1;
                cout << ",R2=" << R2;
                cout << ",R3=" << R3;
                cout << ",R4=" << R4;
                cout << ",R5=" << R5 << endl;
            }
            cout << R1 << endl;
            if(option == "2")
            printMemory(mem);
        }
        else if(reg == "R2")
        {
            if(option == "1" || option =="2")
            {
                cout << instruction << " " << temp <<"-";
                cout << "R1=" << R1;
                cout << ",R2=" << R2;
                cout << ",R3=" << R3;
                cout << ",R4=" << R4;
                cout << ",R5=" << R5 << endl;
            }
            cout << R2 << endl;
            if(option == "2")
            printMemory(mem);
        }
        else if(reg == "R3")
        {
            if(option == "1" || option =="2")
            {
                cout << instruction << " " << temp <<"-";
                cout << "R1=" << R1;
                cout << ",R2=" << R2;
                cout << ",R3=" << R3;
                cout << ",R4=" << R4;
                cout << ",R5=" << R5 << endl;
            }
            cout << R3 << endl;
            if(option == "2")
            printMemory(mem);
        }
        else if(reg == "R4")
        {
            if(option == "1" || option =="2")
            {
                cout << instruction << " " << temp <<"-";
                cout << "R1=" << R1;
                cout << ",R2=" << R2;
                cout << ",R3=" << R3;
                cout << ",R4=" << R4;
                cout << ",R5=" << R5 << endl;
            }
            cout << R4 << endl;
            if(option == "2")
            printMemory(mem);
        }
        else if(reg == "R5")
        {
            if(option == "1" || option =="2")
            {
                cout << instruction << " " << temp <<"-";
                cout << "R1=" << R1;
                cout << ",R2=" << R2;
                cout << ",R3=" << R3;
                cout << ",R4=" << R4;
                cout << ",R5=" << R5 << endl;
            }
            cout << R5 << endl;
            if(option == "2")
            printMemory(mem);
        }
    }
    else if(type == 2)
    {
        a = temp;
        a = a.erase(0,1);
        address = stringToInteger(a);
        
        cout << getMemory(mem, address) << endl;
        
    }
}

void jmp(ifstream& input, string filename, string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[])
{
    int value;
    int i;
    
    if(type == 0)
    {            
        if(option == "1" || option =="2")
        {
        cout << instruction << " " << reg << ", " << temp <<  "-";
        cout << "R1=" << R1;
        cout << ",R2=" << R2;
        cout << ",R3=" << R3;
        cout << ",R4=" << R4;
        cout << ",R5=" << R5 << endl;
        if(option == "2")
            printMemory(mem);

        }
        if(reg == "R1" && R1 == 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=0; i < value-1; ++i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R2" && R2 == 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=0; i < value-1; ++i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R3" && R3 == 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=0; i < value-1; ++i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R4" && R4 == 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=0; i < value-1; ++i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R5" && R5 == 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=0; i < value-1; ++i)
            {
                getline(input,instruction);
            }
        }
    }
    else
    {
        if(option == "1" || option =="2")
        {
            cout << instruction << " " << reg << "-";
            cout << "R1=" << R1;
            cout << ",R2=" << R2;
            cout << ",R3=" << R3;
            cout << ",R4=" << R4;
            cout << ",R5=" << R5 << endl;
            if(option == "2")
                printMemory(mem);
            
        }
        value = stringToInteger(temp);
        input.close();
        input.open(filename.c_str());
        for(i=0; i < value-1; ++i)
        {
            getline(input,instruction);
        }
    }
}

void jpn(ifstream& input, string filename, string instruction, string reg, string temp, string option, int type, int& R1, int& R2, int& R3, int& R4, int& R5, uint8_t mem[])
{
    int value;
    int i;
    
    
    if(type == 0)
    {            
        if(option == "1" || option == "2")
        {
            cout << instruction << " " << reg << ", " << temp <<  "-";
            cout << "R1=" << R1;
            cout << ",R2=" << R2;
            cout << ",R3=" << R3;
            cout << ",R4=" << R4;
            cout << ",R5=" << R5 << endl;
            if(option == "2")
                printMemory(mem);

        }
        if(reg == "R1" && R1 <= 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=value - 1; i > 0; --i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R2" && R2 <= 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=value - 1; i > 0; --i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R3" && R3 <= 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=value - 1; i > 0; --i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R4" && R4 <= 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=value - 1; i > 0; --i)
            {
                getline(input,instruction);
            }
        }
        else if(reg == "R5" && R5 <= 0)
        {
            value = stringToInteger(temp);
            input.close();
            input.open(filename.c_str());
            for(i=value - 1; i > 0; --i)
            {
                getline(input,instruction);
            }
        }
    }
    else
    {
        if(option == "1" || option == "2")
        {
            cout << instruction << " " << reg << "-";
            cout << "R1=" << R1;
            cout << ",R2=" << R2;
            cout << ",R3=" << R3;
            cout << ",R4=" << R4;
            cout << ",R5=" << R5 << endl;
            if(option == "2")
                printMemory(mem);
        }
        value = stringToInteger(temp);
        input.close();
        input.open(filename.c_str());
        for(i=value; i > 0; --i)
        {
            getline(input,instruction);
        }
    }
}

void hlt(int r1, int r2, int r3, int r4, int r5)
{
    cout << "R1=" << r1;
    cout << ",R2=" << r2;
    cout << ",R3=" << r3;
    cout << ",R4=" << r4;
    cout << ",R5=" << r5 << endl;
}

int stringToInteger(string temp)
{
    //Used for stoi() which is forbidden
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
    if(temp[0] == '-')
        return -number;
    
    return number;
}

int isANumber(char temp)
{
    //If the character is a number returns 0,otherwise returns 1
     if(temp == '0' || temp == '1' || temp == '2' 
             || temp == '3' || temp == '4' || temp == '5'
             || temp == '6' || temp== '7' || temp == '8' 
             || temp == '9' )
     {
         return 0;
     }
     return 1;
}

void upperChar(string &temp)
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
}

int errorCheck(string instruction, string *ins, string *reg, string *value, int *valuePassed, int& address)
{
    int i;
    int jCounter;
    int count;
    int mCounter;
    
    string temp;
    
    count = 0;
    *valuePassed = -1;
    jCounter = 0;
    mCounter = 0;
    
    
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT"  && *reg != "JPN")
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    return -1;
                }
            } 
            else if(*reg != "HLT")
            {         
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                return -1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
    //store instruction in ins
    *ins = *reg;
    
    if(*reg == "MOV" || *reg == "ADD" || *reg == "SUB")
    {
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through whitespaces
            if(instruction[i] != ' ')
            {
                //Register must have two characters
                *reg = instruction.substr(i, 2);
                
                //If a memory adress is found
                if(*ins == "MOV" && instruction[i] == '#')
                {
                    for(int m=i+1; m < instruction.size(); ++m)
                    {
                        if(isANumber(instruction[m]) == 0)
                        {
                           mCounter++;   
                        }
                        else
                            m = instruction.size();
                    }
                    *reg = instruction.substr(i, mCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    *valuePassed = 2;
                }
                
                
                upperChar(*reg);

                if(instruction[i+2] == ' ' || instruction[i+2] == ',')
                {
                    if(*reg != "R1" && *reg != "R2" && *reg != "R3" && *reg != "R4" && *reg != "R5" && memoryValid(*reg) != 0)
                    {
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return -1;                   
                    }
                }
                else if( memoryValid(*reg) != 0)
                {
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    return -1; 
                }

                count = i+2;
                //Halting the for loop
                i = instruction.size();   

            }
        }
        if(memoryValid(*reg) == 0)
        {
            temp = *reg;
            address = stringToInteger(temp.erase(0,1));
        }
        else
        {
            cerr << "Invalid memory address" << endl;
            return -1;
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

            //Reading through whitespaces
            if(instruction[i] != ' ')
            {         
                jCounter = 0;
                *value = instruction.substr(i, 2);
                upperChar(*value);
                if(*value == "R1" || *value == "R2" || *value == "R3" || *value == "R4" || *value == "R5")
                {
                    if(*valuePassed != 2)
                        *valuePassed = 1;
                }
                //If the first character represents a number or minus (-) than we check the rest
                if(isANumber(instruction[i+1]) == 0 && instruction[i] == '-')
                { 
                    for(int j=i+1; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == 0)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << jCounter << endl;
                    *value = instruction.substr(i, jCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    if(*valuePassed == 2)
                        *valuePassed = 4;
                    else
                        *valuePassed = 0;

                    i = instruction.size();
                }
                else if(isANumber(instruction[i]) == 0)
                {

                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == 0)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();
                        
                    }
                    //cout << endl << jCounter << endl;
                    *value = instruction.substr(i, jCounter);
                    //cout<<endl<< *reg << endl << *value << endl;
                    if(*valuePassed == 2)
                        *valuePassed = 4;
                    else
                        *valuePassed = 0;

                    i = instruction.size();
                }
                else if(instruction[i] == '#')
                {
                    for(int m=i+1; m < instruction.size(); ++m)
                    {
                        if(isANumber(instruction[m]) == 0)
                        {
                           mCounter++;   
                        }
                        else
                            m = instruction.size();
                    }
                    *value = instruction.substr(i, mCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    if(*valuePassed != 2)
                        *valuePassed = 3;
                    else
                        *valuePassed = -1;
                    
                    i = instruction.size();
                }
                else if(instruction[i+2] == ' ' || instruction[i+2] == ';' || instruction[i+2] == '\0')
                {
                    upperChar(*value);
                    if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5" && memoryValid(*value) != 0)
                    {  
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return -1;                  
                    }
                }                   
                else if(memoryValid(*reg) != 0)
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
    else if(*reg == "PRN")
    {
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through whitespaces
            if(instruction[i] != ' ')
            {         
                jCounter = 0;
                mCounter = 0;
                *value = instruction.substr(i, 2);
                *valuePassed = 1;
                if(instruction[i] == '#')
                {
                    for(int m=i+1; m < instruction.size(); ++m)
                    {
                        if(isANumber(instruction[m]) == 0)
                        {
                           mCounter++;   
                        }
                        else
                            m = instruction.size();
                    }
                    *value = instruction.substr(i, mCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    *valuePassed = 2;
                    
                    i = instruction.size();
                }
                //If the first character represents a number or minus (-) than we check the rest
                if(isANumber(instruction[i+1]) == 0 && instruction[i] == '-')
                { 
                    for(int j=i+1; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == 0)
                        {
                            jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << jCounter << endl;
                    *value = instruction.substr(i, jCounter+1);
                    //cout<<endl<< *reg << endl << *value << endl;
                    *valuePassed = 0;

                    i = instruction.size();
                }
                else if(isANumber(instruction[i]) == 0)
                {

                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == 0)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << endl << jCounter << endl;
                    *value = instruction.substr(i, jCounter);
                    //cout<<endl<< *reg << endl << *value << endl;
                    *valuePassed = 0;

                    i = instruction.size();
                }
                else if(instruction[i+2] == ' ' || instruction[i+2] == ';' || instruction[i+2] == '\0')
                { 
                    upperChar(*value);
                    if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5"  && memoryValid(*value) != 0)
                    {  
                        cerr << "Invalid register" << endl;
                        //Exiting the while loop
                        return -1;                   
                    }
                    *reg = *value;
                }                   
                else if(memoryValid(*value) != 0)
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
    else if(*reg == "JMP" || *reg == "JPN")
    { 
        //Getting the first register
        //Starting from where the instruction ends
        for(i=count; i < instruction.size(); ++i)
        {
            //Reading through whitespaces
            if(instruction[i] != ' ')
            {
                //Register must have two characters
                *reg = instruction.substr(i, 2);
                upperChar(*reg);
                if(isANumber(instruction[i]) == 0)
                {

                    for(int j=i; j < instruction.size(); ++j)
                    {
                        if(isANumber(instruction[j]) == 0)
                        {
                           jCounter++;   
                        }
                        else
                            j = instruction.size();

                    }

                    //cout << endl << jCounter << endl;
                    *value = instruction.substr(i, jCounter);

                    //cout<<endl<< *reg << endl << *value << endl;
                    *valuePassed = 1;
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
        if(*reg != "R1" && *reg != "R2" && *reg != "R3" && *reg != "R4" && *reg != "R5")
        {
            //Getting the first register or the value
            for(i=count-2; i < instruction.size(); ++i)
            {    
                //Reading through whitespaces
                if(instruction[i] != ' ')
                {         
                    jCounter = 0;
                    *value = instruction.substr(i, 1);

                    //If the first character represents a number than we check the rest
                    if(isANumber(instruction[i]) == 0)
                    {

                        for(int j=i; j < instruction.size(); ++j)
                        {
                            if(isANumber(instruction[j]) == 0)
                            {
                               jCounter++;   
                            }
                            else
                                j = instruction.size();

                        }

                        //cout << endl << jCounter << endl;
                        *value = instruction.substr(i, jCounter);

                        //cout<<endl<< *reg << endl << *value << endl;
                        *valuePassed = 1;
                        count = count + jCounter;
                        i = instruction.size();
                    }
                    else if(instruction[i+jCounter] == ' ' || instruction[i+jCounter] == ';' || instruction[i+jCounter] != '\0')
                    {
                        cerr << "Invalid jmp" << endl;
                        //Exiting the while loop
                        return -1; 
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
                    *value = instruction.substr(i, 2);

                    //If the first character represents a number than we check the rest
                    if(isANumber(instruction[i]) == 0)
                    {

                        for(int j=i; j < instruction.size(); ++j)
                        {
                            if(isANumber(instruction[j]) == 0)
                            {
                               jCounter++;   
                            }
                            else
                                j = instruction.size();

                        }

                        //cout << endl << jCounter << endl;
                        *value = instruction.substr(i, jCounter);
                        //cout<<endl<< *reg << endl << *value << endl;
                        *valuePassed = 0;

                        i = instruction.size();
                    }
                    else if(instruction[i+jCounter] == ' ' || instruction[i+jCounter] == ';' || instruction[i+jCounter] == '\0')
                    {
                        upperChar(*value);
                        if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5")
                        {  

                            cerr << "Invalid register" << endl;
                            //Exiting the while loop
                            return -1;                   
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
    else if(*reg == "HLT")
    {
        
    }
}

void fileReader(ifstream& input, string filename, string option, int& R1, int& R2, int& R3, int& R4, int& R5, unsigned char mem[])
{
    /*Variables*/
   
    /*File*/
    string instruction;
    string ins;
    string reg;
    string temp2;
    
    /*Loop*/
    int i;
    int value;
    int count;
    int check;
    int error;
    int digits;
    int valuePassed;
    int address;
    
    check = 0;
    valuePassed = -1;
    
    if(input.is_open())
    {        
        //Reads the file line by line when check is not 0
        while((getline(input, instruction)) && check == 0)
        {                
            
            if(errorCheck(instruction, &ins, &reg, &temp2, &valuePassed, address) == -1)
            {          
 
                check = 1;               
            }   
            //If the instruction HLT
            else if(ins == "HLT")
            {
                if(option == "1")
                {
                    cout << "HLT-";
                }
                hlt(R1, R2, R3, R4, R5);
                if(option == "2")
                    printMemory(mem);
                check = 1; 
            }           
            /*If the instruction is MOV*/
            else if(ins == "MOV")
            {          
                mov(ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem, address);                  
            }
            else if(ins == "ADD")
            {
                add(ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem, address);                 
            }
            else if(ins == "SUB")
            {
                sub(ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem, address);                
            }
            else if(ins == "JMP")
            {                             
                jmp(input, filename, ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem);              
            }
            else if(ins == "JPN")
            {                             
                jpn(input, filename, ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem);             
            }
            else if(ins == "PRN")
            {
                prn(ins, reg, temp2, option, valuePassed, R1, R2, R3, R4, R5, mem, address);               
            }
            
        }
     
    }
    else
    {
        cerr << "File is not open" << endl;
    }   
}