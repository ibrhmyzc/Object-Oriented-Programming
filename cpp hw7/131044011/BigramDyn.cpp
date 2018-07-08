#include "BigramDyn.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace BigramNamespace;

namespace BigramDynNamespace
{
    template<class T>
    BigramDyn<T>::BigramDyn()
    {
        used = 0;
        capacity = 100;
        p = new T [capacity];
        
    }
    
    template<class T>
    BigramDyn<T>::BigramDyn(int t)
    {
        type = t;
        used = 0;
        capacity = 100;
        p = new T [capacity];
    }
    
    template<class T>
    BigramDyn<T>::BigramDyn(const BigramDyn<T>& c)
    {
        type = c.type;
        used = c.getUsed();
        capacity = c.getCapacity();
        p = new T (capacity);
        for(int i = 0; i < capacity; ++i)
            p[i] = c.p[i];
    }
    
    template<class T>
    BigramDyn<T>::~BigramDyn()
    {
        //frees the memory
    }
   
    template<class T>
    BigramDyn<T>& BigramDyn<T>::operator =(const BigramDyn<T>& a)
    {
        //checking for the same object
        if(capacity != a.getCapacity())
        {
            //frees the memory
            delete [] p;
            p = new T [a.getCapacity()];
        }
        capacity = a.getCapacity();
        used = a.getUsed();
        for(int i = 0; i < a.getCapacity(); ++i)
            p[i] = a.p[i];
        
        return *this;
    }
    
    template<class T>
    void BigramDyn<T>::readFile(string filename) throw (iostream::failure)
    {
        ifstream openAndCheckFile(filename);
        T current; // previous is storing the current ot make a pair between them
        int counter=0;
        
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
        
        
        
        while(openAndCheckFile >> current)
        { 
            addT(current);
            counter++;
        }      
        if(counter == 0)
            throw iostream::failure("File is empty");
    }
    
    template<class T>
    void BigramDyn<T>::addT(T temp)
    {
        if(used < capacity - 1)
        {
            p[used] = temp;
            used++;
        }
        else
        {
            T *tempArray;
            tempArray = new T [capacity + 50];
            
            for(int i = 0;i < used; ++i)
                tempArray[i] = p[i];
            
            delete [] p;
            p = new T [capacity+50];
            
            for(int i = 0; i < used; ++i)
                p[i] = tempArray[i];
            
            p[used] = temp;
            used++;
            
            delete [] tempArray;
            
            
        }
    }
    
    template<class T>
    int BigramDyn<T>::numGrams() const
    {
        int size=0;
        if(used < 2)
            return 0;
        else
            size  = used - 1;
        
        return size;
    }
    
    template<class T>
    int BigramDyn<T>::numOfGrams(T b1, T b2) const
    {
        int counter=0;
        for(int i = 0; i < used-1; ++i)
        {
            if(b1 == p[i] && b2 == p[i+1])
                counter++;
        }
        return counter;
    }
    
    template<class T>
    std::pair<T, T> BigramDyn<T>::maxGrams() 
    {
        std::pair<T,T> max;
        
        max = make_pair(p[0], p[1]);
        
        return max;
    }
    
    template<class T>
    void BigramDyn<T>::helperFunctionForPrinting(ostream& output) const
    {
        for(int i = 0; i < used-1; ++i)
            output << "(" << p[i] << "," << p[i+1] << ")" << endl;
    }
}