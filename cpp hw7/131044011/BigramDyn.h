/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramDyn.h
 * Author: ibrahim
 *
 * Created on December 31, 2016, 4:30 AM
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include <fstream>
#include <string>
#include "Bigram.h"

using namespace std;
using namespace BigramNamespace;

namespace BigramDynNamespace
{
    template<class T>
    class BigramDyn: public Bigram<T>
    {
    public:
        BigramDyn();
        BigramDyn(int t);
        BigramDyn(const BigramDyn<T>& c); // copy constructor
        BigramDyn& operator =(const BigramDyn<T>& a); // assignment operator
        int getUsed() const {return used;}
        int getCapacity() const {return capacity;}
        virtual void readFile(string filename)  throw (iostream::failure);
        virtual void addT(T temp);
        virtual int numGrams () const;
        virtual int numOfGrams(T b1, T b2) const;
        virtual void helperFunctionForPrinting(ostream& output) const;
        virtual std::pair<T, T> maxGrams();
        //Virtual destructor to avoid memory leaks
        virtual ~BigramDyn();
    private:
        T *p;
        int used = 0;
        int capacity = 100;
        int type;
    };
    
}// end of namespace


#endif /* BIGRAMDYN_H */

