//
// Created by Filipe souza on 09/04/2021.
//
#ifndef ROAED2012_SEARCH_H
#define ROAED2012_SEARCH_H
#include "Instance.cpp"
//#include "../../../vcpkg/installed/x64-osx/include/matplotlibcpp.h"
//#include <cmath>

//namespace plt = matplotlibcpp;

namespace MRBD {

    struct TreeSearch {
        Id id;
        Id idParent;
        Id idProcess;
        Id idMachine;
        Cost currentCost;
        bool isBest;
    };

    struct CpData {
        Qtt qttSearch;
        Qtt iteretion;
        Qtt failures;
        Qtt unassignedProcess;
        Qtt machines;
        Qtt neighbourhoodSize;
        Cost currentCost;
        double improv;
    };

    struct neighbourData {
        std::vector<Id> process;
        std::vector<Id> changedProcess;
        Cost improv;
    };

    struct CostMachine{
        Cost cost;
        Cost intCost;
        Id updated;
        Id itera;
    };
    struct LNS {
        Id idProcess;
        Qtt dsize;
        Qtt dUnSAT;
        Qtt dRemoved;
        std::vector<Id> values;
    };
    class Search {
    public:
        Search();
        void (Search::*updateSubProblemSize)();
        void (Search::*getNumMachine)();
        Id (Search::*getBestProcess)(Id p , Id p1);
        void start();
        void CP(Id parent);
        void LDS(Id parent);
        void RandRestrat(Id parent);
        void lnsMachineSelection();
        void LNSnew();
//        void createSubproblem(Id numMachine);
        void createSubProblemRandom();
        void createSubProblemMaxCost();
        void createSubProblemProcessMaxCost();
        void createSubProblemUnbalancedMachine();
        void createSubProblemUnbalancedMachine2();
        void createSubProblemUnbalancedMachine3();
        void createSubProblemWeightedVariableImprov();
        void createSubProblemWeightedVariableChange();
        void createSubProblemWeightedVariableUsed();
        void createSubProblemWeightedVariableConflictDirect();
        void createSubProblemWeightedVariableCost();
        void createSubProblemWeightedVariableCostOverUsed();
        void createSubProblemWeightedOverUsed();
        void setUnassigned(Id p);
        void createDomain();
        void removeMachinesFromDomain(Id p);
        void undo(Id m, Id p, Id reason);
        Id getMachineBasedOnCost(bool doSort);
        Id selectAndRemoveProcess();
        Id selectAndRemoveProcessRandom();
        bool consistent(Id p, Id m);
        inline Id getRandomProcess(){
            Id p = randNum()%instance_.qttProcesses();
            while(instance_.process(p)->currentMachineId==UNASSIGNED_){
                p = randNum()%instance_.qttProcesses();
            }
            return p;
        }
        inline Id getRandomProcess(Id s){
            Id j = randNum()%instance_.service(s)->processesRelatedQtt;
            Id p = instance_.service(s)->processesRelated[j];
            Id t = 0;
            while(instance_.process(p)->currentMachineId==UNASSIGNED_){
                j = randNum()%instance_.service(s)->processesRelatedQtt;
                p = instance_.service(s)->processesRelated[j];
                notFound = false;
                if ((instance_.process(p)->currentMachineId==UNASSIGNED_) and (t>5)){
                    p = randNum()%instance_.qttProcesses();
                    notFound = true;
                }
                t++;
            }
            return p;
        }
        inline Id getRandomProcessRelated(Id s){
            Id j = randNum()%instance_.service(s)->processesRelatedQtt;
            Id p1 = instance_.service(s)->processesRelated[j];
            while(instance_.process(p1)->currentMachineId==UNASSIGNED_){
                j = randNum()%instance_.service(s)->processesRelatedQtt;
                p1 = instance_.service(s)->processesRelated[j];
            }
            return p1;
        }
        inline Id getBestProcessBasedOnCost(Id p, Id p1){
            Id pBest = p;
            instance_.updateCostByProcess(p);
            instance_.updateCostByProcess(p1);
            if((instance_.process(p)->cost/pow(instance_.process(p)->used+1.0,2)) <
               (instance_.process(p1)->cost/pow(instance_.process(p1)->used+1.0,2))){
//            if((instance_.process(p)->cost) < (instance_.process(p1)->cost)){
                pBest = p1;
            }
            return pBest;
        }
        inline Id getBestProcessBasedOnConflictDirect(Id p, Id p1){
            Id pBest = p;
            if((instance_.process(p)->conflict/pow(instance_.process(p)->used+1.0,2)) <
               (instance_.process(p1)->conflict/pow(instance_.process(p1)->used+1.0,2))){
 //           if((instance_.process(p)->conflict) < (instance_.process(p1)->conflict)){
                pBest = p1;
            }
            return pBest;
        }
        inline Id getBestProcessBasedOnUsage(Id p, Id p1){
            Id pBest = p;
            if(instance_.process(p)->used>instance_.process(p1)->used){
                pBest = p1;
            }
            return pBest;
        }
        inline Id getBestProcessBasedOnChanges(Id p, Id p1){
            Id pBest = p;
            if((instance_.process(p)->changes/(instance_.process(p)->used+1.0)) <
               (instance_.process(p1)->changes/(instance_.process(p1)->used+1.0))){
 //           if(instance_.process(p)->changes<instance_.process(p1)->changes){
                pBest = p1;
            }
            return pBest;
        }
        inline Id getBestProcessBasedOnImprovement(Id p, Id p1){
            Id pBest = p;
            if((instance_.process(p)->improv/(instance_.process(p)->used+1.0)) <
               (instance_.process(p1)->improv/(instance_.process(p1)->used+1.0))){
 //           if(instance_.process(p)->improv<instance_.process(p1)->improv){
                pBest = p1;
            }
            return pBest;
        }
        inline void getNumMachinePlusOne(){
            if(numMachine<10){
                numMachine++;
            }else{
                numMachine = 1;}
        }
        inline void getNumMachineAdapt(){
            Qtt success = successItera[0] < 10? 10 : successItera[0];
            double successRat = success/(totalItera[0]*1.0);
            numMachine =1;
            for (Id i=1;i<MRBD::maxNumMachine;i++){
                success = successItera[i] < 10? 10 : successItera[i];
                if (success/(totalItera[i]*1.0) > successRat) {
                    numMachine = i+1;
                    successRat = success/(totalItera[i]*1.0);
                }
            }
        }
        inline Id getSubProblemSize(){
            Qtt success = successSize[0] < 10? 10 : successSize[0];
            double successRat = success/(totalSize[0]*1.0);
            subProblemId=0;
            for (Id i=1;i<subProblemSizes.size();i++){
                success = successSize[i] < 10? 10 : successSize[i];
                if (success/(totalSize[i]*1.0) > successRat) {
                    subProblemId = i;
                    successRat = success/(totalSize[i]*1.0);
                }
            }
            return subProblemSizes[subProblemId];
        }

        inline void mapIdsForLNS(){
            for (Id i=0; i < unassignedProcessQtt; i++)
                mapId[LNS_[i].idProcess] = i;
        }
        inline void printBestSolution(){
            std::cout << "iteration: " << iterations
                      << " best Cost: " << instance_.bestObjectiveCostFull()
                      << " size: "<< subProblemSize
                      << " numMachine: "<< numMachine << std::endl;
        }
        inline bool terminateLDS(Qtt D, Id pid){
            return (LNS_[pid].dsize+LNS_[pid].dRemoved-LNS_[pid].dUnSAT) > 0 && MRBD::checkTime()
                   && D <= MRBD::discrepancyMax
                   && failuresQtt < MRBD::failuresMax;
        }
        inline bool terminateRR(Id pid){
            return (LNS_[pid].dsize+LNS_[pid].dRemoved-LNS_[pid].dUnSAT) > 0 && MRBD::checkTime()
                   && failuresQtt < maxFailures
                   && failuresQtt < MRBD::failuresMax;
        }
        inline void assignProcess(){
            Id bestMachineId;
            Id lnsMachineId;
            neighbourData nD;
            Cost improv = oldObjectiveCost-instance_.bestObjectiveCost();
            for (Id i = 0; i < unassignedProcessQtt; i++) {
                bestMachineId = instance_.process(LNS_[i].idProcess)->bestMachineId;
                lnsMachineId = instance_.process(LNS_[i].idProcess)->lnsMachineId;
                nD.process.push_back(LNS_[i].idProcess);
                instance_.assignMachineToProcess(bestMachineId,LNS_[i].idProcess);
                if (bestMachineId!=lnsMachineId){
                   // instance_.setUsedMachine(bestMachineId);
                   // instance_.setUsedMachine(lnsMachineId);
                    instance_.setNotUpdatedMachine(bestMachineId);
                    instance_.setNotUpdatedMachine(lnsMachineId);
                    instance_.setLnsMachine(LNS_[i].idProcess,bestMachineId);
                    nD.changedProcess.push_back(LNS_[i].idProcess);
                    if(instance_.process(LNS_[i].idProcess)->improv==0){
                        changedProcesses.push_back(LNS_[i].idProcess);
                    }
                    instance_.addImprov(LNS_[i].idProcess, improv);
                    instance_.addChanges(LNS_[i].idProcess);
                    improvement+=improv;
                    changes+=1;

                }
            }
            nD.improv = improv;
            neighbourData_.push_back(nD);
        }
        inline void optimise(){
            currentUnassignedProcessQtt = unassignedProcessQtt;
            oldObjectiveCost = instance_.bestObjectiveCost();
            parent_ = MRBD::iterationToPrint == (iterations+1) ? -1:-2;
            qttSearch = 0;
            failuresQtt = 0;
            if (MRBD::typeSearch == 1){
                MRBD::discrepancyMax = instance_.qttMachines();
                LDS(parent_);
            } else if(MRBD::typeSearch == 2){
                LDS(parent_);
            }else if(MRBD::typeSearch == 3){
                maxFailures = MRBD::failuresinitialMax;
                Qtt failures_ = maxFailures;
                Qtt runs = 0;
                while((MRBD::failuresMax > failuresQtt) && MRBD::checkTime() && (runs<5)){
                    RandRestrat(parent_);
                    failures_ *= MRBD::fatorFailuresMax;
                    maxFailures += failures_;
                    runs++;
                }
            }else{
                LDS_RRS();
            }
            assignProcess();
            iterations++;
            bestCosts.push_back(instance_.getObjectiveCostFull());
        }

        inline void LDS_RRS(){
            LDS(parent_);
            qttSearch = 0;
            failuresQtt = 0;
            maxFailures = MRBD::failuresinitialMax;
            Qtt failures_ = maxFailures;
            while(MRBD::failuresMax > failuresQtt && MRBD::checkTime()){
                RandRestrat(parent_);
                failures_ *= MRBD::fatorFailuresMax;
                maxFailures += failures_;
            }
        }
        inline void setSubProblemHeuristic(Id i){
            switch (i) {
                case 0:
                    getBestProcess = &Search::getBestProcessBasedOnCost;
                    break;
                case 1:
                    getBestProcess = &Search::getBestProcessBasedOnImprovement;
                    break;
                case 2:
                    getBestProcess = &Search::getBestProcessBasedOnChanges;
                    break;
                case 3:
                    getBestProcess = &Search::getBestProcessBasedOnUsage;
                    break;
                case 4:
                    getBestProcess = &Search::getBestProcessBasedOnConflictDirect;
                    break;
                default:
                    break;
            }
        }
        inline void setSubProblemHeuristicRandom(){
            Id i = randNum()%5;
            setSubProblemHeuristic(i);
        }
        inline void AdapSubProblemHeuristic(){
            Qtt successVal = success[0] < 10? 10 : success[0];
            double successRat = successVal/(total[0]*1.0);
            heuristicId=0;
            for (Id i=1;i<5;i++){
                successVal = success[i] < 10? 10 : success[i];
                if (successVal/(total[i]*1.0) > successRat) {
                    heuristicId = i;
                    successRat = successVal/(total[0]*1.0);
                }
            }
            setSubProblemHeuristic(heuristicId);
        }

        inline void createSubProblem() {
            unassignedProcesses = {};
            LNS_ = {};
            unassignedProcessQtt = 0;
            if (MRBD::selectProcesses == 1) {
                createSubProblemRandom();
            } else if (MRBD::selectProcesses == 2) {
                createSubProblemMaxCost();
            }else if (MRBD::selectProcesses == 3){
                createSubProblemProcessMaxCost();
            } else if (MRBD::selectProcesses == 4){
                createSubProblemUnbalancedMachine();
            } else if (MRBD::selectProcesses == 5){
                createSubProblemUnbalancedMachine2();
            } else if (MRBD::selectProcesses == 6){
                createSubProblemUnbalancedMachine3();
            }else  if (MRBD::selectProcesses == 7){
                createSubProblemWeightedVariableImprov();
            }else  if (MRBD::selectProcesses == 8){
                createSubProblemWeightedVariableChange();
            }else  if (MRBD::selectProcesses == 9){
                createSubProblemWeightedVariableUsed();
            }else  if (MRBD::selectProcesses == 10){
                createSubProblemWeightedVariableConflictDirect();
            }else  if (MRBD::selectProcesses == 11){
                createSubProblemWeightedVariableCost();
            }else  if (MRBD::selectProcesses < 17){
                createSubProblemWeightedOverUsed();
            }else if (MRBD::selectProcesses == 17){
                setSubProblemHeuristicRandom(); // remove
                createSubProblemWeightedOverUsed();
            }else if (MRBD::selectProcesses == 18){
                AdapSubProblemHeuristic(); // remove
                createSubProblemWeightedOverUsed();
            }
            mapIdsForLNS();
            createDomain();
        }
        inline void createSubProblem1() {
            unassignedProcesses = {};
            LNS_ = {};
            unassignedProcessQtt = 0;
            for (Id i = 0; i < instance_.qttProcesses(); i++){
                setUnassigned(i);
                instance_.unassignProcess(i);
            }
            mapIdsForLNS();
            createDomain();
        }
        inline void saveSolution() {
            if (instance_.bestObjectiveCost() >= ((instance_).*(instance_.getObjectiveCost))()) {
                instance_.setBestObjectiveCost(((instance_).*(instance_.getObjectiveCost))());
//                if(parent_==-1)
//                    ts_[ts_.size()-1].isBest = TRUE_;
//                saveBest();
//                failuresQtt = 0;
                for (Id i = 0; i < unassignedProcessQtt; i++)
                    instance_.setBestMachine(LNS_[i].idProcess,
                                             instance_.process(LNS_[i].idProcess)->currentMachineId);

                instance_.updateBestSolution();
                //if (instance_.bestObjectiveCost() > ((instance_).*(instance_.getObjectiveCost))()) {
                //    failuresQtt = MRBD::failuresMax; // removes it
               // }
            }
            else{
                failuresQtt++;
            }
        }

        inline Cost processHeuristicWeight(Id pid){
            Id p = LNS_[pid].idProcess;
            return LNS_[pid].dsize/(instance_.process(p)->conflict/(instance_.process(p)->used*1.0));
        }

        inline Id selectAndRemoveMachine(Id p){
            Id pid = mapId[p];
            LNS *lns = &LNS_[pid];
            lns->dsize--;
            Id bestId = lns->dsize;
            Cost BestWeight = 99999999999;
            Cost weight;
            Id tempD ;
            for(Id i=lns->dsize;i>=0;i--){
                weight = costMachine[pid][lns->values[i]].cost;
                if (weight < BestWeight){
                    BestWeight = weight;
                    bestId = i;
                }else if(weight==99999999999){
                    tempD = lns->values[lns->dsize];
                    lns->values[lns->dsize] = lns->values[i];
                    lns->values[i] = tempD;
                    if(bestId==lns->dsize){
                        bestId = i;
                    }
                    lns->dsize--;
                    lns->dRemoved++;
                }
            }
            if (bestId < lns->dsize){
                tempD = lns->values[lns->dsize];
                lns->values[lns->dsize] = lns->values[bestId];
                lns->values[bestId] = tempD;
            }else if(lns->dsize<0){
                return -1;
            }

            return lns->values[lns->dsize];
        }

        inline Id selectAndRemoveMachineRandom(Id p){
            Id pid = mapId[p];
            LNS *lns = &LNS_[pid];
            Id bestId, tempD;
            Cost weight;
            if((lns->dsize - lns->dUnSAT + lns->dRemoved) <= MRBD::topValueSeletion){
                bestId = randNum()%lns->dsize;
                weight = costMachine[pid][lns->values[bestId]].cost;
                while(weight==99999999999){
                    tempD = lns->values[lns->dsize-1];
                    lns->values[lns->dsize-1] = lns->values[bestId];
                    lns->values[bestId] = tempD;
                    lns->dsize--;
                    lns->dRemoved++;
                    bestId = randNum()%lns->dsize;
                    weight = costMachine[pid][lns->values[bestId]].cost;
                }
            }else {
                Cost weight;
                Id wostId = 0;
                std::vector<Id> bestIds = {wostId};
                std::vector<Cost> bestWeights = {costMachine[pid][lns->values[wostId]].cost};
                Cost wostWeight = bestWeights[wostId];
                for(Id i=1; i < MRBD::topValueSeletion;i++){
                    bestIds.push_back(i);
                    bestWeights.push_back(costMachine[pid][lns->values[i]].cost);
                    if(bestWeights[i] > wostWeight){
                        wostId = i;
                        wostWeight = bestWeights[i];
                    }
                }
                for(Id i=MRBD::topValueSeletion;i < lns->dsize;i++){
                    weight = costMachine[pid][lns->values[i]].cost;
                    if(weight<wostWeight){
                        bestWeights[wostId] = weight;
                        bestIds[wostId] = i;
                        wostWeight = weight;
                        for (Id j=0; j<MRBD::topValueSeletion;j++){
                            if(bestWeights[j] > wostWeight){
                                wostId = j;
                                wostWeight = bestWeights[j];
                            }
                        }
                    }
                }
                bestId = bestIds[randNum()%MRBD::topValueSeletion];
            }
            lns->dsize--;
            if (bestId < lns->dsize){
                tempD = lns->values[lns->dsize];
                lns->values[lns->dsize] = lns->values[bestId];
                lns->values[bestId] = tempD;
            }
            return lns->values[lns->dsize];
        }

        inline Id saveNode(Id parent, Id p, Id m){
//            if(parent>-2) {
//                TreeSearch treeSearch;
//                treeSearch.idParent = parent;
//                treeSearch.id = ts_.size();
//                treeSearch.currentCost = instance_.getObjectiveCost();
//                treeSearch.isBest = FALSE_;
//                treeSearch.idProcess = p;
//                treeSearch.idMachine = m;
//                ts_.push_back(treeSearch);
//                return treeSearch.id;
//            }
            return -2;
        }

        inline void saveBest(){
            CpData cpData;
            cpData.qttSearch = qttSearch;
            cpData.iteretion = iterations +1;
            cpData.failures = failuresQtt;
            cpData.unassignedProcess = unassignedProcessQtt;
            cpData.machines = instance_.qttMachines();
            cpData.currentCost = instance_.bestObjectiveCost();
            cpData.improv = 1 - (cpData.currentCost/(oldObjectiveCost*1.0));
            cpData.neighbourhoodSize = subProblemSize;
            cpData_.push_back(cpData);
        }

        void printPlot(){
            std::ofstream fileOut{MRBD::dataPlotPath};
            if (!fileOut.good()) {
                std::cerr << "ERROR - File not found \"" << MRBD::dataPlotPath << "\"" << std::endl;
                return;
            }
            for (Id i=0; i < bestCosts.size(); i++)
                fileOut << bestCosts[i] << ";";
            fileOut.close();
        }

        void printTree(){
            std::ofstream fileOut{MRBD::treeDataPlotPath};
            if (!fileOut.good()) {
                std::cerr << "ERROR - File not found \"" << MRBD::treeDataPlotPath << "\"" << std::endl;
                return;
            }
            for (Id i=0; i < ts_.size(); i++)
                fileOut << ts_[i].id << ";"
                        << ts_[i].idParent << ";"
                        << ts_[i].idProcess << ";"
                        << ts_[i].idMachine << ";"
                        << ts_[i].currentCost << ";"
                        << ts_[i].isBest << std::endl;
            fileOut.close();
        }

        void printLDS_RRS(){
            std::ofstream fileOut{MRBD::treeDataPlotPath};
            if (!fileOut.good()) {
                std::cerr << "ERROR - File not found \"" << MRBD::treeDataPlotPath << "\"" << std::endl;
                return;
            }
            for (Id i=0; i < bestMachines_.size(); i++){
                for (Id j=0; j < bestMachines_[i].size(); j++){
                    fileOut << bestMachines_[i][j] << ";";
                }
                fileOut << std::endl;
            }
            fileOut.close();
        }

        inline void updateSubProblemSizeAdapt(){
            totalItera[numMachine-1]++;
            totalSize[subProblemId]++;
            total[heuristicId]++;
            if (oldObjectiveCost > instance_.bestObjectiveCost()) {
//                printBestSolution();
                qttObjetiveFunctionNotImp = 0;
                isImprov = true;
                successItera[numMachine-1]++;
                successSize[subProblemId]++;
                success[heuristicId]+= (oldObjectiveCost - instance_.bestObjectiveCost()) * (iterations*0.01);
            }else{
                qttObjetiveFunctionNotImp++;
            }
            subProblemSize = getSubProblemSize();
        }

        inline void updateSubProblemSizePlusOne(){
            totalItera[numMachine-1]++;
            total[heuristicId]++;
            if (oldObjectiveCost > instance_.bestObjectiveCost()) {
//                printBestSolution();
                notImprovements = 0;
                qttObjetiveFunctionNotImp = 0;
                isImprov = true;
                successItera[numMachine-1]++;
                success[heuristicId]+= (oldObjectiveCost - instance_.bestObjectiveCost()) * (iterations*0.01);
                subProblemSize = MRBD::subProblemSizeInit;
            }else{
                notImprovements++;
                qttObjetiveFunctionNotImp++;
            }
            if (notImprovements > MRBD::improvementThreshold){
                notImprovements = 0;
                subProblemSize++;
                if (subProblemSize > subProblemSizeMax){
                    subProblemSize = MRBD::subProblemSizeInit;
                }
            }
        }
        inline void updateObjetiveCost(){
            switch (ObjetiveFunctions[IdObjetiveFunction]) {
                case 1:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost1;
                    isOriginalOF = false;
                    break;
                case 2:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost2;
                    isOriginalOF = false;
                    break;
                case 3:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost3;
                    isOriginalOF = false;
                    break;
                case 4:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost4;
                    isOriginalOF = false;
                    break;
                case 5:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost5;
                    isOriginalOF = false;
                    break;
                case 6:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost6;
                    isOriginalOF = false;
                    break;
                case 7:
                    instance_.getObjectiveCost = &Instance::getObjectiveCost7;
                    isOriginalOF = false;
                    break;
                default:
                    instance_.getObjectiveCost = &Instance::getObjectiveCostFull;
                    isOriginalOF = true;
                    break;
            }
            instance_.setBestObjectiveCost(((instance_).*(instance_.getObjectiveCost))());
            IdObjetiveFunction++;
            if(IdObjetiveFunction==ObjetiveFunctions.size())
                IdObjetiveFunction = 0;
            qttObjetiveFunctionNotImp = 0;
            qttObjetiveFunctionAlt = 0;
        }
        inline void ObjFuncNoise(){
            if ((qttObjetiveFunctionNotImp > MRBD::improvementThresholdOF)
                and (MRBD::checkTimeObjFunc())){
                updateObjetiveCost();
            }
            if (!isOriginalOF){
                if(qttObjetiveFunctionAlt> MRBD::thresholdAltObjFunc){
                    isOriginalOF = true;
                    instance_.getObjectiveCost = &Instance::getObjectiveCostFull;
                    instance_.setBestObjectiveCost(((instance_).*(instance_.getObjectiveCost))());
                    qttObjetiveFunctionNotImp = 0;
                    qttObjetiveFunctionAlt = 0;
                }else{
                    qttObjetiveFunctionAlt++;
                }
            }
        }

        void printCpData(){
            std::ofstream fileOut{MRBD::treeDataPlotPath + ".csv"};
            if (!fileOut.good()) {
                std::cerr << "ERROR - File not found \"" << MRBD::treeDataPlotPath + ".csv" << "\"" << std::endl;
                return;
            }
            fileOut << "iteretion,"
                    << "qttSearch,"
                    << "failures,"
                    << "unassignedProcess,"
                    << "machines,"
                    << "neighbourhoodSize,"
                    << "currentCost,"
                    << "improv" << std::endl;
            for (Id i=0; i < cpData_.size(); i++)
                fileOut << cpData_[i].iteretion << ","
                        << cpData_[i].qttSearch << ","
                        << cpData_[i].failures << ","
                        << cpData_[i].unassignedProcess << ","
                        << cpData_[i].machines << ","
                        << cpData_[i].neighbourhoodSize << ","
                        << cpData_[i].currentCost << ","
                        << cpData_[i].improv << std::endl;
            fileOut.close();
        }

        void printNeighbourhood(){
            std::ofstream fileOut{MRBD::neighbourhoodPath};
            if (!fileOut.good()) {
                std::cerr << "ERROR - File not found \"" << MRBD::neighbourhoodPath << "\"" << std::endl;
                return;
            }
            fileOut << "neighbourhood;"
                    << "changes;"
                    << "improv" << std::endl;
            for (Id i=0; i < neighbourData_.size(); i++)
                fileOut << getstring(neighbourData_[i].process)  << ";"
                        << getstring(neighbourData_[i].changedProcess) << ";"
                        << neighbourData_[i].improv << std::endl;
            fileOut.close();
        }

        Id getMachine(){
            if (machineIndicesSize==0 or isImprov){
                instance_.loadAvaliableMachine();
                isImprov = false;
                machineIndicesSize = machineIndices.size();
                if(firstSort) {
                    firstSort = false;
                    sort(machineIndices.begin(), machineIndices.end(),
                         [this](Id m1, Id m2) { return instance_.compare2(m1, m2); });
                }else{
                    firstSort = true;
                    sort(machineIndices.begin(),machineIndices.end(),
                         [this] (Id m1, Id m2) {return instance_.compare(m1,m2);});
                }
            }

            Id m;
            Id mIndex_;
            if (toGetBestMachine){
                machineIndicesSize--;
                mIndex_ = machineIndicesSize;
                m = machineIndices[mIndex_];
                if (instance_.machine(m)->totalCost > 0){
                    instance_.sortProcessMaxBenefit(m);
                }else{
                    machineIndicesSize=0;
                    toGetBestMachine = false;
                }
            }else{
                mIndex_ = randNum()%machineIndices.size();
                m = machineIndices[mIndex_];
                instance_.sortProcessMaxBenefit(m);
            }

            while(instance_.machine(m)->n == 0){
                m = getMachine();
            }
            return m;
        }
        Id getMachine1(){
            if (machineIndicesSize==0 or isImprov){
                instance_.loadAvaliableMachine();
                isImprov = false;
                machineIndicesSize = machineIndices.size();
                if(firstSort) {
                    firstSort = false;
                    sort(machineIndices.begin(), machineIndices.end(),
                         [this](Id m1, Id m2) { return instance_.compare2(m1, m2); });
                }else{
                    firstSort = true;
                    sort(machineIndices.begin(),machineIndices.end(),
                         [this] (Id m1, Id m2) {return instance_.compare(m1,m2);});
                }
            }

            Id m;
            Id mIndex_;
            if (toGetBestMachine){
                machineIndicesSize--;
                mIndex_ = machineIndicesSize;
                toGetBestMachine = false;
                m = machineIndices[mIndex_];
                instance_.sortProcessMaxBenefit(m);
            }else{
                mIndex_ = randNum()%machineIndices.size();
                toGetBestMachine = true;
                m = machineIndices[mIndex_];
            }

            while(instance_.machine(m)->n == 0){
                m = getMachine1();
            }
            return m;
        }
        Id getMachine2(){
            Id m;
            Id mIndex_;
            if ((machineIndicesSize<0) or (machineIndicesSize1<0) or isImprov or (instance_.machine(machineIndices[machineIndicesSize])->totalCost == 0)) {
                instance_.loadAvaliableMachine();
                isImprov = false;
                machineIndicesSize = machineIndices.size() - 1;
                machineIndicesSize1 = machineIndices.size() - 1;
                sort(machineIndices.begin(), machineIndices.end(),
                     [this](Id m1, Id m2) { return instance_.compare(m1, m2); });
    //            sort(machineIndices1.begin(), machineIndices1.end(),
    //                 [this](Id m1, Id m2) { return instance_.compare1(m1, m2); });
            }
            if(firstSort) {
                mIndex_ = machineIndicesSize;
                m = machineIndices[mIndex_];
                machineIndicesSize--;
            }else{
 //               if ((MRBD::dis(MRBD::randNum) > MRBD::pctChangeMachine)){
 //                   mIndex_ = machineIndicesSize1;
 //                   m = machineIndices1[mIndex_];
//                    machineIndicesSize1--;
//                }else{
                    mIndex_ = randNum()%machineIndices.size();
                    m = machineIndices[mIndex_];
 //               }
            }
            while(instance_.machine(m)->n == 0){
                m = getMachine2();
            }
            instance_.sortProcessMaxBenefit(m);
            return m;
        }

    private:
        Instance instance_;
        std::vector<LNS> LNS_;
        std::vector<TreeSearch> ts_;
        std::vector<CpData> cpData_;
        std::vector<neighbourData> neighbourData_ = {};
        std::vector<Id> mapId;
        std::vector<Qtt> totalItera;
        std::vector<Qtt> successItera;
        std::vector<Qtt> totalSize;
        std::vector<Qtt> successSize;
        std::vector<Qtt> total;
        std::vector<Qtt> success;
        std::vector<Qtt> subProblemSizes = {10,20,30,40,50,60,70,80,90,100};
        std::vector<Id> machineIndices;
        std::vector<Id> machineIndices1;
        std::vector<Id> machineIndices2;
        std::vector<Id> changedProcesses;
        std::vector<std::vector<CostMachine>> costMachine;
        std::vector<std::vector<Cost>> bestMachines_;
        std::vector<Id> unassignedProcesses;
        std::vector<Id> noFitProcesses;
        std::vector<Id> usedMachines;
        std::vector<Cost> bestCosts;
        std::vector<CostMachine> machineCosts;
        std::vector<Id> processes_;
        std::vector<Id> ObjetiveFunctions;
        Qtt IdObjetiveFunction = 0;
        bool isOriginalOF = true;
        Qtt qttObjetiveFunctionAlt = 0;
        Qtt qttObjetiveFunctionNotImp = 0;
        Qtt machineIndicesSize = 0;
        Qtt machineIndicesSize1 = 0;
        Qtt unassignedProcessQtt = 0;
        Qtt currentUnassignedProcessQtt = 0;
        Qtt subProblemSize = 0;
        Id subProblemId = 0;
        Qtt subProblemSizeMax = 0;
        Qtt failuresQtt = 0;
        Qtt maxFailures = 0;
        Qtt numMachine = 1;
        Qtt NumImprovementThreshold = 0;
        Qtt iterations = 0;
        Qtt qttSearch = 0;
        Cost oldObjectiveCost = 0;
        Cost unassignedCost_ = 0;
        Id parent_ = -2;
        Id mIndex = 0;
        Id heuristicId = 0;
        bool toGetBestMachine = true;
        bool firstSort = false;
        bool isImprov = true;
        bool notFound = true;
        Qtt qttLoadAvaliable = 0;
        Cost improvement = 0;
        Qtt changes = 0;
        Qtt notImprovements = 0;
        Id updated_ = 0;

    };
}
#endif //ROAED2012_SEARCH_H
