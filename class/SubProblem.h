//
// Created by Filipe De Souza on 15/03/2022.
//

#ifndef ROAED2012_SUBPROBLEM_H
#define ROAED2012_SUBPROBLEM_H
#include <cstdio>
#include <cassert>
#include <chuffed/core/engine.h>
#include <chuffed/core/propagator.h>
#include <chuffed/branching/branching.h>
#include <chuffed/vars/modelling.h>
#include <chuffed/ldsb/ldsb.h>
#include "../base/Parameter.h"
#include "Instance.cpp"


namespace MRBD {

    class SubProblem {
    public:
        SubProblem(Instance _instance, std::vector<Id> _idProcesses);

    private:
        Instance instance;
        std::vector<Id> idProcesses;
        Qtt subProblemSize;
        vec<IntVar*> DProcesses;
    };

}
#endif //ROAED2012_SUBPROBLEM_H
