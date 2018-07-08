// Ibrahim Yazici 131044011
#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Bigram.h"

using namespace std;
using namespace BigramNamespace;

namespace BigramMapNamespace
{
    template<class T>
    class BigramMap: public Bigram<T>
    {
    public:
        BigramMap();
        BigramMap(int t);
        virtual void readFile(string filename)  throw (iostream::failure);
        virtual int numGrams () const;
        virtual int numOfGrams(T b1, T b2) const;
        virtual void helperFunctionForPrinting(ostream& output) const;
        virtual std::pair<T, T> maxGrams();
        //Virtual destructor to avoid memory leaks
        virtual ~BigramMap();
    private:
        std::map<std::pair<T, T> , int > mBiGram;
    };
    
}// end of namespace


#endif /* BIGRAMMAP_H */

