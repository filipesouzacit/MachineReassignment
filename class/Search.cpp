//
// Created by Filipe souza on 09/04/2021.
//

#include "Search.h"
using namespace MRBD;

Search::Search()
{
    instance_ = Instance();
    ObjetiveFunctions = MRBD::ObjetiveFunctions;
    std::cout << "Test: " << MRBD::testId << " Seed: " << MRBD::seed <<  " Instance: " << MRBD::inst <<
    " - Init Cost: " << ((instance_).*(instance_.getObjectiveCost))() << std::endl;
    switch (MRBD::AdaptSubProblemSize) {
        case 0:
            updateSubProblemSize = &Search::updateSubProblemSizeAdapt;
            MRBD::subProblemSizeInit = 10;
            MRBD::subProblemSizeMax = 100;
            break;
        default:
            updateSubProblemSize = &Search::updateSubProblemSizePlusOne;
            break;
    }
    subProblemSizeMax = MRBD::subProblemSizeMax > instance_.qttProcesses() ? instance_.qttProcesses(): MRBD::subProblemSizeMax;
    switch (MRBD::AdaptNumMachine) {
        case 0:
            getNumMachine = &Search::getNumMachineAdapt;
            break;
        default:
            getNumMachine = &Search::getNumMachinePlusOne;
            break;
    }

    switch (MRBD::selectProcesses) {
        case 12:
            getBestProcess = &Search::getBestProcessBasedOnCost;
            break;
        case 13:
            getBestProcess = &Search::getBestProcessBasedOnImprovement;
            break;
        case 14:
            getBestProcess = &Search::getBestProcessBasedOnChanges;
            break;
        case 15:
            getBestProcess = &Search::getBestProcessBasedOnUsage;
            break;
        case 16:
            getBestProcess = &Search::getBestProcessBasedOnConflictDirect;
            break;
        default:
            break;
    }


    machineIndices.reserve(instance_.qttMachines()+1);
    machineIndices1.reserve(instance_.qttMachines()+1);
    machineIndices2.reserve(instance_.qttMachines()+1);
    machineCosts.reserve(instance_.qttMachines()+1);
    CostMachine cm;
    cm.cost = -1;
    cm.intCost = -1;
    cm.updated = -1;
    cm.itera   = -1;
    for(Id i=0;i<instance_.qttMachines();i++){
        machineIndices.push_back(i);
        machineIndices1.push_back(i);
        machineIndices2.push_back(i);
        machineCosts.push_back(cm);
    }
    usedMachines.reserve(subProblemSizeMax+1);
    costMachine.reserve(subProblemSizeMax+1);
    LNS_.reserve(subProblemSizeMax+1);
    unassignedProcesses.reserve(subProblemSizeMax+1);
    for(Id i=0; i<subProblemSizeMax+1; i++){
        costMachine.push_back(machineCosts);
    }
    mapId.reserve(instance_.qttProcesses());
    for(Id i=0;i<instance_.qttProcesses();i++){
        mapId.push_back(-1);
    }
    for(Id i=0;i<MRBD::maxNumMachine;i++){
        successItera.push_back(0);
        totalItera.push_back(1);
    }
    for(Id i=0;i<subProblemSizes.size();i++){
        successSize.push_back(0);
        totalSize.push_back(1);
    }
    for(Id i=0;i<5;i++){
        success.push_back(0);
        total.push_back(1);
    }
}

Id Search::getMachineBasedOnCost(bool doSort){
    Id m;
    if (doSort) {
        sort(machineIndices.begin(),machineIndices.end(),
             [this] (Id m1, Id m2) {return instance_.compare(m1,m2);});
        mIndex = 0;
    }
    m = machineIndices[mIndex];
    while(instance_.machine(m)->n == 0){
        mIndex = (mIndex+1)%instance_.qttMachines();
        m = machineIndices[mIndex];
    }
    mIndex = (mIndex+1)%instance_.qttMachines();
    return m;
}

void Search::setUnassigned(Id p){
    unassignedProcesses.push_back(unassignedProcessQtt);
    unassignedProcessQtt++;
    LNS lns;
    lns.idProcess = p;
    lns.dsize     = 0;
    lns.values.reserve(MRBD::machineMaxSearch + 1);
    LNS_.push_back(lns);
}

void Search::createDomain(){
    LNS *lns;
    bool remove_m;
    Id m,j,bestM = -1;
    Cost maxCost= -99999999999;
    bool smallInst = instance_.qttMachines() <= MRBD::machineMaxInit;
    Qtt Nmachines =  smallInst ? instance_.qttMachines():MRBD::machineMaxInit;
    Cost cost_;
//    std::vector<int> machineIds_;
    Id wostId = 0;
    Id n_;
//    std::random_shuffle(machineIndices2.begin()+ (Nmachines/2), machineIndices2.end());
//    machineIds_ = {machineIndices2.begin() , machineIndices2.begin() + Nmachines};
    for (Id i = 0; i < unassignedProcessQtt; i++){
        lns = &LNS_[i];
        n_ = instance_.qttMachines();

        maxCost= -99999999999;
        if(!smallInst){
            m = instance_.process(lns->idProcess)->bestMachineId;
            bestM = m;
            cost_ = instance_.machineProcessSatCost(m,lns->idProcess);
            lns->dsize++;
            costMachine[i][m].cost = cost_;
            costMachine[i][m].intCost = cost_;
            costMachine[i][m].updated = -1;
            costMachine[i][m].itera = iterations;
            lns->values.push_back(m);
            maxCost = cost_;
            wostId = lns->dsize - 1;
        }
        for (Id mI = 0; mI<Nmachines; mI++) {
            if(smallInst){
                m = mI;
            }else{
                j = randNum()%n_;
                n_--;
                m = machineIndices2[j];
                machineIndices2[j] = machineIndices2[n_];
                machineIndices2[n_] = m;
            }
            cost_ = instance_.machineProcessSatCost(m,lns->idProcess);
            if ((cost_ != 99999999999) and (m!=bestM)){
                if (lns->dsize <= MRBD::machineMaxSearch){
                    lns->dsize++;
                    costMachine[i][m].cost = cost_;
                    costMachine[i][m].intCost = cost_;
                    costMachine[i][m].updated = -1;
                    costMachine[i][m].itera = iterations;
                    lns->values.push_back(m);
                    if (maxCost < cost_){
                        maxCost = cost_;
                        wostId = lns->dsize - 1;
                    }
                }else{
                    if(maxCost>cost_){
                        maxCost=cost_;
                        costMachine[i][m].cost = cost_;
                        costMachine[i][m].intCost = cost_;
                        costMachine[i][m].updated = -1;
                        costMachine[i][m].itera = iterations;
                        costMachine[i][lns->values[wostId]].itera = -1;
                        lns->values[wostId] = m;
                        for (Id d=0; d< MRBD::machineMaxSearch;d++){
                            if (maxCost < costMachine[i][lns->values[d]].cost){
                                maxCost = costMachine[i][lns->values[d]].cost;
                                wostId = d;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Search::createSubProblemRandom(){
    Id p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemMaxCost(){
    Id j,p,m;
    Machine *machine;
    m = instance_.getMachineByCost();
    machine = instance_.machine(m);

    p = instance_.getProcessMaxBenefit(m);
    setUnassigned(p);
    instance_.unassignProcess(p);

    while(unassignedProcessQtt < subProblemSize){
        if((MRBD::dis(MRBD::randNum) < MRBD::pctChangeMachine) or (machine->n == 0)){
            m = randNum()%instance_.qttMachines();
            while(instance_.machine(m)->n == 0){
                m = randNum()%instance_.qttMachines();
            }
            machine = instance_.machine(m);
        }
        j = randNum()%machine->n;
        p = machine->processes[j].idProcess;
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemProcessMaxCost(){
    Id p;
    Qtt numProcesses = subProblemSize*(1-MRBD::pctRandom);
    std::vector<Id> bestP = instance_.getProcessByCost(numProcesses);

    for(Id i=0; i<numProcesses;i++){
        p = bestP[i];
        setUnassigned(p);
        instance_.unassignProcess(p);
    }

    while(unassignedProcessQtt < subProblemSize){
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemUnbalancedMachine(){
    Qtt numProcess = 0;
    ((this)->*(this->getNumMachine))();
    Id j,p,s;
    Id m = getMachine1();
    Machine *machine = instance_.machine(m);
    while(unassignedProcessQtt < subProblemSize){
        if((numProcess > (subProblemSize/numMachine)) || machine->n==0){
            m=getMachine1();
            machine = instance_.machine(m);
            numProcess = 0;
        }
        if(toGetBestMachine){
            j = randNum()%machine->n;
        }else{
            j = machine->n-1;
        }
        p = machine->processes[j].idProcess;
        setUnassigned(p);
        instance_.unassignProcess(p);
        numProcess++;

        if(unassignedProcessQtt < subProblemSize){
            s = instance_.process(p)->serviceId;
            j = randNum()%instance_.service(s)->processQtt;
            p = instance_.service(s)->processes[j];
            if (instance_.process(p)->currentMachineId!=UNASSIGNED_) {
                    setUnassigned(p);
                    instance_.unassignProcess(p);
            }
        }

    }
}

void Search::createSubProblemUnbalancedMachine2(){
    Qtt numProcess = 0;
    ((this)->*(this->getNumMachine))();
    Id j,p,om;
    Id m = getMachine();
    Machine *omachine;
    Machine *machine = instance_.machine(m);
    while(unassignedProcessQtt < subProblemSize){
        if((numProcess > (subProblemSize/numMachine)) || machine->n==0){
            m=getMachine();
            machine = instance_.machine(m);
            numProcess = 0;
        }
        if(toGetBestMachine){
            j = machine->n-1;
            toGetBestMachine = false;
        }else{
            j = randNum()%machine->n;
            toGetBestMachine = true;
        }
        p = machine->processes[j].idProcess;
        setUnassigned(p);
        instance_.unassignProcess(p);
        numProcess++;
        if(unassignedProcessQtt < subProblemSize){
            om = instance_.process(p)->originalMachineId;
            if (om != m) {
                omachine = instance_.machine(om);
                if (omachine->n > 0){
                    j = randNum()%omachine->n;
                    p = omachine->processes[j].idProcess;
                    setUnassigned(p);
                    instance_.unassignProcess(p);
                    numProcess++;
                }
            }
        }
    }
}

void Search::createSubProblemUnbalancedMachine3(){
    Qtt numProcess = 0;
    ((this)->*(this->getNumMachine))();
    Id j,p,om;
    firstSort = true;
    toGetBestMachine = true;
    Id m = getMachine2();
    Machine *omachine;
    Machine *machine = instance_.machine(m);
    while(unassignedProcessQtt < subProblemSize){
        if((numProcess > (subProblemSize/numMachine)) || machine->n==0){
            firstSort = firstSort?false:true;
            m=getMachine2();
            machine = instance_.machine(m);
            numProcess = 0;
        }
        if(toGetBestMachine){
            j = machine->n-1;
        }else{
            j = randNum()%machine->n;
        }
        p = machine->processes[j].idProcess;
        setUnassigned(p);
        instance_.unassignProcess(p);
        numProcess++;
        if(unassignedProcessQtt < subProblemSize){
            om = instance_.process(p)->originalMachineId;
            if (om != m) {
                omachine = instance_.machine(om);
                if (omachine->n > 0){
                    j = randNum()%omachine->n;
                    p = omachine->processes[j].idProcess;
                    setUnassigned(p);
                    instance_.unassignProcess(p);
                    numProcess++;
                }
            }
        }
        toGetBestMachine = toGetBestMachine?false:true;
    }
}

void Search::createSubProblemWeightedVariableImprov(){
    Id p1,p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        for(Id i=0; i<10;i++){
            p1 = randNum()%instance_.qttProcesses();
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                p1 = randNum()%instance_.qttProcesses();
            }
            if((instance_.process(p)->improv/(instance_.process(p)->used*1.0))<
               (instance_.process(p1)->improv/(instance_.process(p1)->used*1.0))){
                p = p1;
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemWeightedVariableChange(){
    Id p1,p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        for(Id i=0; i<10;i++){
            p1 = randNum()%instance_.qttProcesses();
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                p1 = randNum()%instance_.qttProcesses();
            }
            if((instance_.process(p)->changes/(instance_.process(p)->used*1.0))<
               (instance_.process(p1)->changes/(instance_.process(p1)->used*1.0))){
                p = p1;
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemWeightedVariableUsed(){
    Id p1,p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        for(Id i=0; i<10;i++){
            p1 = randNum()%instance_.qttProcesses();
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                p1 = randNum()%instance_.qttProcesses();
            }
            if(instance_.process(p)->used>instance_.process(p1)->used){
                p = p1;
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}
void Search::createSubProblemWeightedVariableConflictDirect(){
    Id p1,p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        for(Id i=0; i<10;i++){
            p1 = randNum()%instance_.qttProcesses();
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                p1 = randNum()%instance_.qttProcesses();
            }
            if((instance_.process(p)->conflict/(instance_.process(p)->used*1.0))<
               (instance_.process(p1)->conflict/(instance_.process(p1)->used*1.0))){
                p = p1;
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}
void Search::createSubProblemWeightedVariableCost(){
    Id p1,p;
    while(unassignedProcessQtt < subProblemSize){
        p = randNum()%instance_.qttProcesses();
        while(instance_.process(p)->currentMachineId==UNASSIGNED_){
            p = randNum()%instance_.qttProcesses();
        }
        instance_.updateCostByProcess(p);
        for(Id i=0; i<10;i++){
            p1 = randNum()%instance_.qttProcesses();
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                p1 = randNum()%instance_.qttProcesses();
            }
            instance_.updateCostByProcess(p1);
            if((instance_.process(p)->cost/(instance_.process(p)->used*1.0))<
               (instance_.process(p1)->cost/(instance_.process(p1)->used*1.0))){
                p = p1;
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}

void Search::createSubProblemWeightedOverUsed(){
    Id p1,p,s;
    p = getRandomProcess();
    for(Id i=0; i<10;i++){
        p1 = getRandomProcess();
        p = ((this)->*(this->getBestProcess))(p,p1);
    }
    setUnassigned(p);
    instance_.unassignProcess(p);

    while(unassignedProcessQtt < subProblemSize){
        s = instance_.process(p)->serviceId;
        p = getRandomProcess(s);
        if(notFound){
            for(Id i=0; i<10;i++){
                p1 = getRandomProcess();
                p = ((this)->*(this->getBestProcess))(p,p1);
            }
        }else{
            for(Id i=0; i<10;i++){
                p1 = getRandomProcessRelated(s);
                p = ((this)->*(this->getBestProcess))(p,p1);
            }
        }
        setUnassigned(p);
        instance_.unassignProcess(p);
    }
}


Id Search::selectAndRemoveProcess(){
    currentUnassignedProcessQtt--;
    Id bestId = currentUnassignedProcessQtt;
    Id pid = unassignedProcesses[bestId];
    Cost BestWeight = processHeuristicWeight(pid);
    Qtt weight;
    for(Id i=0;i<currentUnassignedProcessQtt;i++){
        pid = unassignedProcesses[i];
        weight = processHeuristicWeight(pid);
        if (weight < BestWeight){
            BestWeight = weight;
            bestId = i;
        }
    }
    if (bestId != (currentUnassignedProcessQtt)){
        pid = unassignedProcesses[currentUnassignedProcessQtt];
        unassignedProcesses[currentUnassignedProcessQtt] = unassignedProcesses[bestId];
        unassignedProcesses[bestId] = pid;
    }
    return LNS_[unassignedProcesses[currentUnassignedProcessQtt]].idProcess;
}

Id Search::selectAndRemoveProcessRandom(){
    Id bestId, pid;
    if(currentUnassignedProcessQtt<=MRBD::topVariableSeletion){
        bestId = randNum()%currentUnassignedProcessQtt;
    }else{
        Cost weight;
        Id wostId = 0;
        std::vector<Id> bestIds = {wostId};
        std::vector<Cost> bestWeights = {processHeuristicWeight(unassignedProcesses[wostId])};
        Cost wostWeight = bestWeights[wostId];
        for(Id i=1; i < MRBD::topVariableSeletion;i++){
            bestIds.push_back(i);
            bestWeights.push_back(processHeuristicWeight(unassignedProcesses[i]));
            if(bestWeights[i] > wostWeight){
                wostId = i;
                wostWeight = bestWeights[i];
            }
        }
        for(Id i=MRBD::topVariableSeletion;i<currentUnassignedProcessQtt;i++){
            weight = processHeuristicWeight(unassignedProcesses[i]);
            if(weight<wostWeight){
                bestWeights[wostId] = weight;
                bestIds[wostId] = i;
                wostWeight = weight;
                for (Id j=0; j<MRBD::topVariableSeletion;j++){
                    if(bestWeights[j] > wostWeight){
                        wostId = j;
                        wostWeight = bestWeights[j];
                    }
                }
            }
        }
        bestId = bestIds[randNum()%MRBD::topVariableSeletion];
    }
    currentUnassignedProcessQtt--;
    if (bestId != (currentUnassignedProcessQtt)){
        pid = unassignedProcesses[currentUnassignedProcessQtt];
        unassignedProcesses[currentUnassignedProcessQtt] = unassignedProcesses[bestId];
        unassignedProcesses[bestId] = pid;
    }
    return LNS_[unassignedProcesses[currentUnassignedProcessQtt]].idProcess;
}

void Search::removeMachinesFromDomain(Id p){
    Id pid = mapId[p];
    Id m;
    Cost cost_;
    LNS *lns = &LNS_[pid];
    lns->dUnSAT = 0;
    lns->dRemoved = 0;
    updated_++;
    for(Id i=0; i<usedMachines.size(); i++){
        m = usedMachines[i];
        if (costMachine[pid][m].itera == iterations){
            if(costMachine[pid][m].updated != updated_){
                cost_ = instance_.machineProcessSatCost(m,lns->idProcess);
                if (cost_== 99999999999){
                    lns->dUnSAT++;
                }
                costMachine[pid][m].cost = cost_;
                costMachine[pid][m].updated = updated_;
            }
        }
    }
}

bool Search::consistent(Id p, Id m){
    Id s = instance_.serviceFromProcess(p);
    if (instance_.getObjectiveCost2() >= instance_.bestObjectiveCost()){
        return FALSE_;
    }
    if(!instance_.conflictConstraint(s))
        return FALSE_;
    if(!instance_.spreadConstraint(s))
        return FALSE_;
    if(!instance_.serviceDependencyConstraints(s))
        return FALSE_;
    return TRUE_;
}
void Search::RandRestrat(Id parent) {
    Id pid,p,m,dsize;
    if (currentUnassignedProcessQtt == 0) {
        saveSolution();
    } else {
        p = selectAndRemoveProcessRandom();
        pid = mapId[p];
        dsize = LNS_[pid].dsize;
        removeMachinesFromDomain(p);
        if ((LNS_[pid].dsize - LNS_[pid].dUnSAT) <= 0) {
            instance_.addConflict(p);
            failuresQtt++;
        }else {
            while(terminateRR(pid)){
                m=selectAndRemoveMachineRandom(p);
                instance_.addUsed(p);
                instance_.assignMachineToProcess(m, p);
//                qttSearch++;
                if (consistent(p,m)) {
                    usedMachines.push_back(m);
                    RandRestrat(saveNode(parent, p, m));
                    usedMachines.pop_back();
                } else {
                    instance_.addConflict(p);
                    failuresQtt++;
                }
                instance_.unassignProcess(p);
            }
        }
        for(Id i=0; i<usedMachines.size(); i++) {
            m = usedMachines[i];
            costMachine[pid][m].cost = costMachine[pid][m].intCost;
        }
        LNS_[pid].dsize = dsize;
        currentUnassignedProcessQtt++;
    }
}

void Search::LDS(Id parent) {
    Id pid,p,m,dsize;
    if (currentUnassignedProcessQtt == 0) {
        saveSolution();
    } else {
        p = selectAndRemoveProcess();
        pid = mapId[p];
        dsize = LNS_[pid].dsize;
        removeMachinesFromDomain(p);
        if ((LNS_[pid].dsize - LNS_[pid].dUnSAT) <= 0) {
            instance_.addConflict(p);
            failuresQtt++;
        }else {
            Qtt discrepancy = 0;
            while(terminateLDS(discrepancy, pid)){
                m=selectAndRemoveMachine(p);
                if(m==-1){
                    break;
                }
                instance_.addUsed(p);
                instance_.assignMachineToProcess(m, p);
 //               qttSearch++;
                if (consistent(p, m)) {
                    usedMachines.push_back(m);
                    LDS(saveNode(parent, p, m));
                    usedMachines.pop_back();
                    discrepancy++;
                    if (currentUnassignedProcessQtt == 0)
                        discrepancy = MRBD::discrepancyMax;
                } else {
                    instance_.addConflict(p);
                    failuresQtt++;
                }
                instance_.unassignProcess(p);
            }
        }
        for(Id i=0; i<usedMachines.size(); i++) {
            m = usedMachines[i];
            costMachine[pid][m].cost = costMachine[pid][m].intCost;
        }
        LNS_[pid].dsize = dsize;
        currentUnassignedProcessQtt++;
    }
}

void Search::LNSnew() {
    notImprovements = 0;
    subProblemSize = MRBD::subProblemSizeInit;
    bestCosts.push_back(instance_.getObjectiveCostFull());
    while (MRBD::checkTime()) {
        updated_ = 0;
        createSubProblem();
        optimise();
        if((iterations%MRBD::printFreq)==0){
            printBestSolution();
        }
        ((this)->*(this->updateSubProblemSize))();
        ObjFuncNoise();
    }
    bestCosts.push_back(instance_.bestObjectiveCostFull());
}

void Search::lnsMachineSelection() {
    Qtt notImprovements = 0;
    subProblemSize = MRBD::subProblemSizeInit;
    bestCosts.push_back(instance_.getObjectiveCostFull());
    while (MRBD::checkTime()) {
        updated_ = 0;
        createSubProblem();
        optimise();
        ((this)->*(this->updateSubProblemSize))();
        ObjFuncNoise();
    }
    bestCosts.push_back(instance_.bestObjectiveCostFull());
}

void Search::start() {
    LNSnew();
    printBestSolution();
    instance_.printSolutionInFile();
    printNeighbourhood();
    printPlot();
    printCpData();
    if (ts_.size() > 0)
        printTree();
}