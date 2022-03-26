//
// Created by Filipe De Souza on 15/03/2022.
//

#include "SubProblem.h"

using namespace MRBD;

SubProblem::SubProblem(Instance _instance, std::vector<Id> _idProcesses ){
    instance = _instance;
    idProcesses = _idProcesses;
    subProblemSize = idProcesses.size();
    createVars(DProcesses,subProblemSize, 0, instance.qttMachines()-1);







}