//
// Created by Filipe De Souza on 22/04/2022.
//


#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/minimodel.hh>
#include <gecode/driver.hh>
#include "CarSeqProblem.cpp"

using namespace Gecode;

class carSequencing : public IntMinimizeSpace {
protected:
    Instance inst;
    IntVarArray slot;
    BoolVarArray setup;
    IntVar total;
    Id col = 0;
public:
    carSequencing(Instance inst):
    inst(inst),
    slot(*this, inst.qttCar, 0, inst.qttClass),
    setup(*this, inst.qttCar*inst.qttOption),
    total(*this,0,inst.TotalOptionDemand)
    {
        std::vector<IntArgs> optionClass;
        for(Id o=0;o<inst.qttOption;o++){
            optionClass.push_back(IntArgs(inst.qttClass+1));
            optionClass[o][0]=0;
            for(Id c=1;c<=inst.qttClass;c++){
                optionClass[o][c]=inst.optionsRequired[c-1][o];
            }
        }
        // connects slot and setup
        for(Id o=0;o<inst.qttOption;o++){
            col= o*inst.qttCar;
            IntSharedArray temp(optionClass[o]);
            for(Id c=0;c<inst.qttCar;c++){
                element(*this,temp,slot[c],setup[(col+c)]);
            }
        }

        // Not over prodution
        for(Id c=0;c<inst.qttClass;c++){
            count(*this, slot, c+1, IRT_LQ, inst.carPerClass[c]);
        }

        //constraint capacity
        for(Id o=0;o<inst.qttOption;o++){
            col= o*inst.qttCar;
            for(Id w=0;w<(inst.qttCar-inst.windowSize[o]);w++){
                linear(*this,setup.slice(col+w,1,inst.windowSize[o]),IRT_LQ,inst.capacity[o]);
            }
        }

        total = expr(*this, inst.TotalOptionDemand-sum(setup) );
        // post branching
        branch(*this, slot, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    // Return solution cost
    virtual IntVar cost(void) const {
        return total;
    }

    // search support
    carSequencing(carSequencing& s) :
    IntMinimizeSpace(s),
    inst(s.inst)
    {
        slot.update(*this, s.slot);
        setup.update(*this, s.setup);
        total.update(*this, s.total);
    }

    virtual Space* copy(void) {
        return new carSequencing(*this);
    }

    // print solution
    void print(void) const {
        std::cout << slot << std::endl;
    }
};

