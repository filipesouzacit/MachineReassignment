//
// Created by Filipe De Souza on 12/04/2022.
//
#include <gecode/int.hh>
#include <gecode/search.hh>
#include "../base/Parameter.h"

using namespace MRBD;
using namespace Gecode;

class MRP : public Space {
protected:
    IntVarArray mapP;
public:
    MRP(Qtt nM, Qtt nP, Qtt nS,
        std::vector<std::vector<Id>> services,
        std::vector<std::vector<Id>> depends) :
        mapP(*this, nP, 0, nM-1) {

        for(Id s = 0;s<nS;s++){

        }



        // no leading zeros
        rel(*this, s, IRT_NQ, 0);
        rel(*this, m, IRT_NQ, 0);
        // all letters distinct
        distinct(*this, mapP);
        // linear equation
        IntArgs c(4+4+5); IntVarArgs x(4+4+5);
        c[0]=1000; c[1]=100; c[2]=10; c[3]=1;
        x[0]=s;    x[1]=e;   x[2]=n;  x[3]=d;
        c[4]=1000; c[5]=100; c[6]=10; c[7]=1;
        x[4]=m;    x[5]=o;   x[6]=r;  x[7]=e;
        c[8]=-10000; c[9]=-1000; c[10]=-100; c[11]=-10; c[12]=-1;
        x[8]=m;      x[9]=o;     x[10]=n;    x[11]=e;   x[12]=y;
        linear(*this, c, x, IRT_EQ, 0);
        // post branching
        branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    // search support
    MRP(MRP& s) : Space(s) {
        l.update(*this, s.l);
    }
    virtual Space* copy(void) {
        return new MRP(*this);
    }
    // print solution
    void print(void) const {
        std::cout << l << std::endl;
    }
};

// main function
int main(int argc, char* argv[]) {
    // create model and search engine
    MRP* m = new MRP;
    DFS<MRP> e(m);
    delete m;
    // search and print all solutions
    while (MRP* s = e.next()) {
        s->print(); delete s;
    }
    return 0;
}
