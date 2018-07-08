// Ibrahim Yazici 131044011
#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
using namespace std;

namespace BigramNamespace
{
    template<class T>
    class Bigram
    {
    public:
        virtual void readFile(string filename) throw (iostream::failure) = 0;
        virtual int numGrams () const = 0;
        virtual int numOfGrams(T b1, T b2) const = 0;
        friend ostream& operator<<(ostream& output, const Bigram<T> &b)
        {
            //only way i could find this on the internet
            //since bigram.h does not have a cpp file we write this here
            b.helperFunctionForPrinting(output);
            return output;
        }
        virtual void helperFunctionForPrinting(ostream& output) const = 0;
        virtual std::pair<T, T> maxGrams() = 0;
        //virtual ~Bigram() = 0;
        
    }; // end of class
    
}// end of namespace


#endif /* BIGRAM_H */

