/* 
 * File:   main.cpp
 * Author: ibrahim yazici 131044011
 * simulates a basic cpu program
 * Created on September 27, 2016, 1:43 PM
 */

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//Converts a string to integer
int stringToInteger(string temp);

//Checking the character if it is a number
int isANumber(char temp);

//Converts all characters to uppercase in a string
void upperChar(string &temp);

//File reader function
void fileReader(ifstream& file, string filename, string option, int& r1, int& r2, int& r3, int& r4, int& r5);

//Checking the line for error
int errorCheck(string instruction, string& reg, string& value, int &count, int& valuePassed);

//for MOV instruction
void mov(string instruction, string *reg, string *value, int *error, int *valuePassed);

//for ADD instruction
void add(string instruction, string *reg, string *value, int *error, int *valuePassed);

//for SUB instruction
void sub(string instruction, string *reg, string *value, int *error, int *valuePassed);

//for PRN instruction
void prn(string instruction, string *reg, string *value, int *error, int *valuePassed);

//for JMP instruction
void jmp(string instruction, string *reg, string *value, int *error, int *valuePassed);

//for PRN instruction
void hlt(int r1, int r2, int r3, int r4, int r5);


int main(int argc, char** argv) {
 //START OF MAIN   
    
 //Variable
    //Only registers that the program has
    int R1=0;
    int R2=0;
    int R3=0;
    int R4=0;
    int R5=0;
    
    //Variables for File
    ifstream input;
    string filename;
    string option;
    
    input.open(argv[1]);
    filename = argv[1];
    option = argv[2];
    
    if(input.is_open())
    {
        fileReader(input, filename, option, R1, R2, R3, R4, R5);  
    }  
    else
    {
        cerr << "File is not open" << endl;
    }
   
    return 0;
//END OF MAIN
}

void mov(string instruction,  string *reg, string *value, int *error, int *valuePassed)
{
    int i;
    int jCounter;
    int count;
    
    count = 0;
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    *error = 1;
                }
            } 
            else
            {         
                
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                *error = 1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
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
            if(instruction[i+2] == ' ' || instruction[i+2] == ',')
            {
                if(*reg != "R1" && *reg != "R2" && *reg != "R3" && *reg != "R4" && *reg != "R5")
                {
                    
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }
            else
            {
                
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
        
        //Reading through whitespaces
        if(instruction[i] != ' ')
        {         
            jCounter = 0;
            *value = instruction.substr(i, 2);
            
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
                if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5")
                {  
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }                   
            else
            { 
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
            *error = 1;  
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

void add(string instruction, string *reg, string *value, int *error, int *valuePassed)
{
    int i;
    int jCounter;
    int count;
    
    count = 0;
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    *error = 1;
                }
            } 
            else
            {         
                
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                *error = 1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
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
            if(instruction[i+2] == ' ' || instruction[i+2] == ',')
            {
                if(*reg != "R1" && *reg != "R2" && *reg != "R3" && *reg != "R4" && *reg != "R5")
                {
                    
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }
            else
            {
                
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
        
        //Reading through whitespaces
        if(instruction[i] != ' ')
        {         
            jCounter = 0;
            *value = instruction.substr(i, 2);
            
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
                if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5")
                {  
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }                   
            else
            { 
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
            *error = 1;  
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

void sub(string instruction, string *reg, string *value, int *error, int *valuePassed)
{
    int i;
    int jCounter;
    int count;
    
    count = 0;
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    *error = 1;
                }
            } 
            else
            {         
                
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                *error = 1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
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
            if(instruction[i+2] == ' ' || instruction[i+2] == ',')
            {
                if(*reg != "R1" && *reg != "R2" && *reg != "R3" && *reg != "R4" && *reg != "R5")
                {
                    
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }
            else
            {
                
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
        
        //Reading through whitespaces
        if(instruction[i] != ' ')
        {         
            jCounter = 0;
            *value = instruction.substr(i, 2);
            
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
                if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5")
                {  
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
            }                   
            else
            { 
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
            *error = 1;  
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

void prn(string instruction, string *reg, string *value, int *error, int *valuePassed)
{
    int i;
    int jCounter;
    int count;
    *valuePassed = 1;
    count = 0;
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    *error = 1;
                }
            } 
            else
            {         
                
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                *error = 1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
    //Getting the first register
    //Starting from where the instruction ends
    for(i=count; i < instruction.size(); ++i)
    {
        
        //Reading through whitespaces
        if(instruction[i] != ' ')
        {         
            jCounter = 0;
            *value = instruction.substr(i, 2);
            
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
                if(*value != "R1" && *value != "R2" && *value != "R3" && *value != "R4" && *value != "R5")
                {  
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;                    
                }
                *reg = *value;
            }                   
            else
            { 
                cerr << "Invalid register" << endl;
                //Exiting the while loop
                *error = 1;   
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
            *error = 1;  
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

void jmp(string instruction, string *reg, string *value, int *error, int *valuePassed)
{
    
    int i;
    int jCounter;
    int count;
    
    count = 0;
    jCounter = 0;
    for(i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            *reg = instruction.substr(i, 3);
            upperChar(*reg);
            
            if(instruction[i+3] == ' ')
            { 
                if(*reg != "PRN" && *reg != "SUB" && *reg != "ADD" && *reg != "MOV" && *reg != "JMP"  && *reg != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    //Exiting the while loop
                    *error = 1;
                }
            } 
            else
            {         
                
                cerr << "Invalid instruction" << endl;
                //Exiting the while loop
                *error = 1;   
            }
            //Index of the end of the instruction in the string
            count = i + 3;
            //Halting the for loop
            i = instruction.size();             
        }
    }
    
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
                    *error = 1;   
                }                   
                else
                { 
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;   
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
                *error = 1;  
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
                        *error = 1;                    
                    }
                }                   
                else
                { 
                    cerr << "Invalid register" << endl;
                    //Exiting the while loop
                    *error = 1;   
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
                *error = 1;  
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
        if(temp[i] >= 'a' && temp[i] <= 'z')
        {
            temp[i] = temp[i] + 'A' - 'a';
        }
    }
}

int errorCheck(string instruction, string &reg, string &value, int &count, int &valuePassed)
{
    string temp;
    
    for(int i=0; i < instruction.size(); ++i)
    {
        if(instruction[i] != ' ')
        {
            //Instruction must be three characters long
            temp = instruction.substr(i, 3);
            upperChar(temp);
            
            if(instruction[i+3] == ' ' || instruction[i+3] == '\0')
            { 

                if(temp != "PRN" && temp != "SUB" && temp != "ADD" && temp != "MOV" && temp != "JMP"  && temp != "HLT" )
                {
                    
                    cerr << "Invalid instruction" << endl;
                    
                    return 1;
                }
            } 
            else if(instruction[i+3] == ';' && temp == "HLT")
            {
                
            }
            else
            {     
                
                cerr << "Invalid instruction" << endl;
                
                return 1;   
            }
            /*Index of the end of the instruction in the string*/
            count = i +3;
            /*Halting the for loop*/
            i = instruction.size();             
        }
    }
    
    reg = temp;
    
    return 0;
}

void fileReader(ifstream& input, string filename, string option, int& R1, int& R2, int& R3, int& R4, int& R5)
{
    /*Variables*/
   
    /*File*/
    string instruction;
    string temp;
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
    
    check = 0;
    valuePassed = -1;
    
    if(input.is_open())
    {        
        //Reads the file line by line when check is not 0
        while((getline(input, instruction)) && check == 0)
        {                
            
            if(errorCheck(instruction, reg, temp2, count, valuePassed) != 0)
            {              
                check = 1;
            }           
            //If the instruction HLT
            else if(reg == "HLT")
            {
                if(option == "1")
                {
                    cout << "HLT-";
                }
                hlt(R1, R2, R3, R4, R5);
                check = 1; 
            }           
            /*If the instruction is MOV*/
            else if(reg == "MOV")
            {               
                valuePassed = -1;
                
                if(option == "1")
                {
                    cout << reg << " ";
                }
                mov(instruction, &reg, &temp2, &error, &valuePassed);
              
                
                //cout << reg << " " << temp2 << endl;      
                if(error == 1)
                {                     
                    check = 1;
                }
                /*If value is passed*/
                
                else if(valuePassed == 0)
                {
                    //cout << "temp2:" << temp2 << endl;
                    value = stringToInteger(temp2);
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
                else if(reg == "R1" && temp2 == "R1")
                    R1 = R1;
                else if(reg == "R1" && temp2 == "R2")
                    R2 = R1;
                else if(reg == "R1" && temp2 == "R3")
                    R2 = R1;
                else if(reg == "R1" && temp2 == "R4")
                    R4 = R1;
                else if(reg == "R1" && temp2 == "R5")
                    R5 = R1;
                else if(reg == "R2" && temp2 == "R1")
                    R1 = R2;
                else if(reg == "R2" && temp2 == "R2")
                    R2 = R2;
                else if(reg == "R2" && temp2 == "R3")
                    R3 = R2;
                else if(reg == "R2" && temp2 == "R4")
                    R4 = R2;
                else if(reg == "R2" && temp2 == "R5")
                    R5 = R2;
                else if(reg == "R3" && temp2 == "R1")
                    R1 = R3;
                else if(reg == "R3" && temp2 == "R2")
                    R2 = R3;
                else if(reg == "R3" && temp2 == "R3")
                    R3 = R3;
                else if(reg == "R3" && temp2 == "R4")
                    R4 = R3;
                else if(reg == "R3" && temp2 == "R5")
                    R5 = R3;
                else if(reg == "R4" && temp2 == "R1")
                    R1 = R4;
                else if(reg == "R4" && temp2 == "R2")
                    R2 = R4;
                else if(reg == "R4" && temp2 == "R3")
                    R3 = R4;
                else if(reg == "R4" && temp2 == "R4")
                    R4 = R4;
                else if(reg == "R4" && temp2 == "R5")
                    R5 = R4;
                else if(reg == "R5" && temp2 == "R1")
                    R1 = R5;
                else if(reg == "R5" && temp2 == "R2")
                    R2 = R5;
                else if(reg == "R5" && temp2 == "R3")
                    R3 = R5;
                else if(reg == "R5" && temp2 == "R4")
                    R4 = R5;
                else if(reg == "R5" && temp2 == "R5")
                    R5 = R5;
                if(option == "1")
                {
                    cout << reg << ", " << temp2 << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
        
                }
            }
            else if(reg == "ADD")
            {
                if(option == "1")
                {
                    cout << reg << " ";
                }
                valuePassed = -1;
               
                add(instruction, &reg, &temp2, &error, &valuePassed);
                //cout << reg << " " << temp2 << endl;
                
                if(error == 1)
                {                     
                    check = 1;
                }
                /*If value is passed*/
                
                else if(valuePassed == 0)
                {
                    //cout << "temp2:" << temp2 << endl;
                    value = stringToInteger(temp2);
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
                else if(reg == "R1" && temp2 == "R1")
                    R1 += R1;
                else if(reg == "R1" && temp2 == "R2")
                    R1 += R2;
                else if(reg == "R1" && temp2 == "R3")
                    R1 += R3;
                else if(reg == "R1" && temp2 == "R4")
                    R1 += R4;
                else if(reg == "R1" && temp2 == "R5")
                    R1 += R5;
                else if(reg == "R2" && temp2 == "R1")
                    R2 += R1;
                else if(reg == "R2" && temp2 == "R2")
                    R2 += R2;
                else if(reg == "R2" && temp2 == "R3")
                    R2 += R3;
                else if(reg == "R2" && temp2 == "R4")
                    R2 += R4;
                else if(reg == "R2" && temp2 == "R5")
                    R2 += R5;
                else if(reg == "R3" && temp2 == "R1")
                    R3 += R1;
                else if(reg == "R3" && temp2 == "R2")
                    R3 += R2;
                else if(reg == "R3" && temp2 == "R3")
                    R3 += R3;
                else if(reg == "R3" && temp2 == "R4")
                    R3 += R4;
                else if(reg == "R3" && temp2 == "R5")
                    R3 += R5;
                else if(reg == "R4" && temp2 == "R1")
                    R4 += R1;
                else if(reg == "R4" && temp2 == "R2")
                    R4 += R2;
                else if(reg == "R4" && temp2 == "R3")
                    R4 += R3;
                else if(reg == "R4" && temp2 == "R4")
                    R4 += R4;
                else if(reg == "R4" && temp2 == "R5")
                    R4 += R5;
                else if(reg == "R5" && temp2 == "R1")
                    R5 += R1;
                else if(reg == "R5" && temp2 == "R2")
                    R5 += R2;
                else if(reg == "R5" && temp2 == "R3")
                    R5 += R3;
                else if(reg == "R5" && temp2 == "R4")
                    R5 += R4;
                else if(reg == "R5" && temp2 == "R5")
                    R5 += R5;  
                if(option == "1")
                {
                    cout << reg << ", " << temp2 << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
        
                }
            }
            else if(reg == "SUB")
            {
                if(option == "1")
                {
                    cout << reg << " ";
                }
                valuePassed = -1;
                
                sub(instruction, &reg, &temp2, &error, &valuePassed);
                //cout << reg << " " << temp2 << endl;
                
                if(error == 1)
                {                     
                    check = 1;
                }
                /*If value is passed*/
                
                else if(valuePassed == 0)
                {
                    //cout << "temp2:" << temp2 << endl;
                    value = stringToInteger(temp2);
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
                else if(reg == "R1" && temp2 == "R1")
                    R1 -= R1;
                else if(reg == "R1" && temp2 == "R2")
                    R1 -= R2;
                else if(reg == "R1" && temp2 == "R3")
                    R1 -= R3;
                else if(reg == "R1" && temp2 == "R4")
                    R1 -= R4;
                else if(reg == "R1" && temp2 == "R5")
                    R1 -= R5;
                else if(reg == "R2" && temp2 == "R1")
                    R2 -= R1;
                else if(reg == "R2" && temp2 == "R2")
                    R2 -= R2;
                else if(reg == "R2" && temp2 == "R3")
                    R2 -= R3;
                else if(reg == "R2" && temp2 == "R4")
                    R2 -= R4;
                else if(reg == "R2" && temp2 == "R5")
                    R2 -= R5;
                else if(reg == "R3" && temp2 == "R1")
                    R3 -= R1;
                else if(reg == "R3" && temp2 == "R2")
                    R3 -= R2;
                else if(reg == "R3" && temp2 == "R3")
                    R3 -= R3;
                else if(reg == "R3" && temp2 == "R4")
                    R3 -= R4;
                else if(reg == "R3" && temp2 == "R5")
                    R3 -= R5;
                else if(reg == "R4" && temp2 == "R1")
                    R4 -= R1;
                else if(reg == "R4" && temp2 == "R2")
                    R4 -= R2;
                else if(reg == "R4" && temp2 == "R3")
                    R4 -= R3;
                else if(reg == "R4" && temp2 == "R4")
                    R4 -= R4;
                else if(reg == "R4" && temp2 == "R5")
                    R4 -= R5;
                else if(reg == "R5" && temp2 == "R1")
                    R5 -= R1;
                else if(reg == "R5" && temp2 == "R2")
                    R5 -= R2;
                else if(reg == "R5" && temp2 == "R3")
                    R5 -= R3;
                else if(reg == "R5" && temp2 == "R4")
                    R5 -= R4;
                else if(reg == "R5" && temp2 == "R5")
                    R5 -= R5; 
                
                if(option == "1")
                {
                    cout << reg << ", " << temp2 << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
        
                }
            }
            else if(reg == "JMP")
            {               
                valuePassed = -1;
                if(option == "1")
                {
                    cout << reg << " ";
                }
                jmp(instruction, &reg, &temp2, &error, &valuePassed);
                //cout << reg << " " << temp2 << " " << valuePassed << endl;
               
                if(error == 1)
                {         
                    check = 1;
                }
                /*If value is passed*/           
                if(valuePassed == 0)
                {            
                    if(option == "1")
                    {
                    cout << temp2 <<  "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
        
                    }
                    if(reg == "R1" && R1 == 0)
                    {
                        value = stringToInteger(temp2);
                        input.close();
                        input.open(filename.c_str());
                        for(i=0; i < value-1; ++i)
                        {
                            getline(input,instruction);
                        }
                    }
                    else if(reg == "R2" && R2 == 0)
                    {
                        value = stringToInteger(temp2);
                        input.close();
                        input.open(filename.c_str());
                        for(i=0; i < value-1; ++i)
                        {
                            getline(input,instruction);
                        }
                    }
                    else if(reg == "R3" && R3 == 0)
                    {
                        value = stringToInteger(temp2);
                        input.close();
                        input.open(filename.c_str());
                        for(i=0; i < value-1; ++i)
                        {
                            getline(input,instruction);
                        }
                    }
                    else if(reg == "R4" && R4 == 0)
                    {
                        value = stringToInteger(temp2);
                        input.close();
                        input.open(filename.c_str());
                        for(i=0; i < value-1; ++i)
                        {
                            getline(input,instruction);
                        }
                    }
                    else if(reg == "R5" && R5 == 0)
                    {
                        value = stringToInteger(temp2);
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
                    if(option == "1")
                    {
                    cout << reg << ", " << temp2 << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
        
                    }
                    value = stringToInteger(temp2);
                    input.close();
                    input.open(filename.c_str());
                    for(i=0; i < value-1; ++i)
                    {
                        getline(input,instruction);
                    }
                }
            }
            else if(reg == "PRN")
            {
                if(option == "1")
                {
                    cout << reg << " ";
                }
                prn(instruction, &reg, &temp2, &error, &valuePassed);
                
                if(error == 1)
                {
                    check = 1;
                }
                else if(valuePassed == 0)
                {
                    if(option == "1")
                    {
                    cout << temp2 << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    
                    cout << temp2 << endl;
                }
                else if(reg == "R1")
                {
                    if(option == "1")
                    {
                    cout << reg << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    cout << R1 << endl;
                }
                else if(reg == "R2")
                {
                    if(option == "1")
                    {
                    cout << reg << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    cout << R2 << endl;
                }
                else if(reg == "R3")
                {
                    if(option == "1")
                    {
                    cout << reg << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    cout << R3 << endl;
                }
                else if(reg == "R4")
                {
                    if(option == "1")
                    {
                    cout << reg << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    cout << R4 << endl;
                }
                else if(reg == "R5")
                {
                    if(option == "1")
                    {
                    cout << reg << "-";
                    cout << "R1=" << R1;
                    cout << ",R2=" << R2;
                    cout << ",R3=" << R3;
                    cout << ",R4=" << R4;
                    cout << ",R5=" << R5 << endl;
                    }
                    cout << R5 << endl;
                }
            }
        }
     
    }
    else
    {
        cerr << "File is not open" << endl;
    }   
}