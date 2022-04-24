//
// Created by Filipe De Souza on 01/04/2022.
//
#ifndef ROAED2012_CARSEQPROBLEM_H
#define ROAED2012_CARSEQPROBLEM_H
#include "../base/CarParameter.h"

namespace carSeq {
    struct Instance {
        Qtt qttCar;
        Qtt qttOption;
        Qtt qttClass;
        Qtt TotalOptionDemand;
        std::vector<Id> classes;
        std::vector<std::vector<bool>> optionsRequired;
        std::vector<Qtt> carPerClass;
        std::vector<Qtt> windowSize;
        std::vector<Qtt> capacity;
    };
    struct Solution {
        Cost cost;
        std::vector<Id> sequency;
    };

    class CarSeqProblem {
    public:
        CarSeqProblem(Str fileName);
        void InitSolution();

        inline Qtt qttCar() {return inst.qttCar;}
        inline Qtt qttOption() {return inst.qttOption;}
        inline Qtt qttClass() {return inst.qttClass;}
        inline Qtt TotalOptionDemand() {return inst.TotalOptionDemand;}

        inline std::vector<Qtt> carPerClass() {return inst.carPerClass;}
        inline std::vector<Qtt> windowSize() {return inst.windowSize;}
        inline std::vector<Qtt> capacity() {return inst.capacity;}
        inline std::vector<std::vector<bool>> optionsRequired() {return inst.optionsRequired;}

        inline Instance instance() {return inst;}

        inline Qtt cost() {return sol.cost;}
    private:
        Instance inst;
        Solution sol;

    };

};
#endif //ROAED2012_CARSEQPROBLEM_H