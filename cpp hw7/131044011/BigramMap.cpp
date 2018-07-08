#include "BigramMap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;
using namespace BigramNamespace;

namespace BigramMapNamespace
{
    template<class T>
    BigramMap<T>::BigramMap()
    {
        //intentionally empty
    }
    
    template<class T>
    BigramMap<T>::BigramMap(int t)
    {
        //intentionally empty
    }
    
    template<class T>
    BigramMap<T>::~BigramMap()
    {
        //intentionally empty
    }
    
    template<class T>
    void BigramMap<T>::readFile(string filename) throw (iostream::failure)
    {
        ifstream openAndCheckFile(filename);
        pair<int,int> countPair;
        T current,previous; // previous is storing the current ot make a pair between them
        int counter = 0;
        //Looking for file errors here
        try
        {
            if(!openAndCheckFile.is_open())
                 throw iostream::failure("File not found");
        }
        catch(exception& error)
        {
            cerr << error.what() << endl;
        }

        openAndCheckFile >> previous;
        while(openAndCheckFile >> current)
        { 
            mBiGram[make_pair(previous, current)]; 
            for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
            {
                //if it repeats, we increases its size
                if(previous == it->first.first && current == it->first.second)
                {
                    //cout << "(" << it->first.first << " " << it->first.second << ") = "<< it->second<< endl;
                    mBiGram[make_pair(previous, current)]++;
                }             
            }    
            previous = current;
            counter++;
        }
        
        if(counter == 0)
            throw iostream::failure("File is empty");
    }
    
    template<class T>
    int BigramMap<T>::numGrams() const
    {
        int size = 0; 
        //Obviously return the numgrams
        for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
        {
            size = size + it->second;           
        }    
        return size;
    }
    
    template<class T>
    int BigramMap<T>::numOfGrams(T b1, T b2) const
    {
        int counter = 0;

        for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
        {
            //cout << "(" << it->first.first << " " << it->first.second << ") = "<< it->second<< endl;
            //if this returns true we increases the counter by 1
            if(b1 == it->first.first && b2 == it->first.second)
                counter = it->second;
        }        
        return counter;
    }
    
    template<class T>
    std::pair<T, T> BigramMap<T>::maxGrams() 
    {
        int biggest=0;
        std::pair<T,T> max;
        
        for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
        {
            if(it->second > biggest)
            {
                biggest = it->second;
                max = make_pair(it->first.first, it->first.second);
            }              
        }
        return max;
    }
    
    template<class T>
    void BigramMap<T>::helperFunctionForPrinting(ostream& output) const 
    {
        int biggest=0;

        
        //Here I find the biggest of them
        for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
        {
            if(it->second > biggest)
            {
                biggest = it->second;
            }              
        }
        
        //Printing from the biggest to lowest
        while(biggest !=0)
        {
            for(auto it=mBiGram.begin(); it!= mBiGram.end(); ++it)
            {
                if(it->second == biggest)
                {
                    output << "(" << it->first.first << " " << it->first.second << ") = "<< it->second<< endl;
                }              
            }
            --biggest;
        }
    }
    
}// end of namespace