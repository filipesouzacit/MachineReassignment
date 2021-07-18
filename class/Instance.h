//
// Created by Filipe souza on 22/03/2021.
//

#ifndef ROAED2012_INSTANCE_H
#define ROAED2012_INSTANCE_H
#include "../base/Parameter.h"

namespace MRBD
{
    struct Resource
    {
        Id id;
        bool transientUsage;
        weight weightloadCost;
    };


    struct MachineProcess
    {
        Cost processCost;
        Id idProcess;
    };
    struct Machine
    {
        Id id;
        Id neighborhood;
        Id location;
        std::vector<MachineProcess> processes;
        Size size;
        Size n;
        Qtt countAvaliable;
        Cost loadAvaliableCost; // new
        Cost loadCostMachine; // new
        Cost balanceCostMachine; // new
        Cost totalCost;// new
        Cost wostCostProcess;// new
        std::vector<Cost> usages;
        std::vector<Cost> transitiveUsages;
        std::vector<Cost> avaliable;
        std::vector<Capacity> capacities;
        std::vector<Capacity> scapacities;
        std::vector<Cost> moveCost;
    };
    struct Service{
        Id  id;
        Qtt spreadMin ;
        Qtt processQtt;
        Qtt dependsOnQtt;
        std::vector<Id> dependsOns;
        std::vector<Id> unassignedProcess;
        Qtt unassignedProcessQtt;
        Qtt movedProcessQtt;
        std::vector<Id> usedMachines;
        Qtt usedMachineQtt;
        Qtt availableMachineQtt;
        std::vector<Id> usedLocations;
        Qtt usedLocationQtt;
        std::vector<Id> neighborhoods;
        Qtt neighborhoodQtt;
        std::vector<Id> usedNeighborhoods;
        Qtt mandatoryNeighborhoodQtt;
        std::vector<Id> mandatoryNeighborhoods;
    };
    struct Process{
        Id  id;
        Id serviceId;
        Id originalMachineId;
        Id currentMachineId;
        Id bestMachineId;
        Id lnsMachineId;
        std::vector<Cost> requirements;
        Cost requirement;
        Cost moveCost;
        Cost moveCostProcess; // new
        Cost moveCostMachine; // new
    };
    struct Balance{
        Id id;
        Id resourceId1;
        Id resourceId2;
        Cost target;
        Cost weightCost;
    };
    class Instance{
    public:
        Instance();
        void resourceAdd(Str str);
        void machineAdd(Str str);
        void serviceAdd(Str str);
        void processAdd(Str str);
        void balanceAdd(Str str, Str str2);
        void weightAdd(Str str);
        void printSolutionInFile();
        void assignMachineToProcess(Id m, Id p);
        void unassignProcess(Id p);

        bool machineSatisfyRequirementOfProcess(Id m, Id p);
        inline Service *service(Id s) {return &services_[s];}
        inline Resource *resource(Id r) {return &resources_[r];}
        inline Machine *machine(Id m) {return &machines_[m];}
        inline Process *process(Id p) {return &processes_[p];}
        inline Balance *balance(Id b) {return &balances_[b];}
        inline Qtt qttMachines() {return machineQtt_;}
        inline Qtt qttProcesses() {return processQtt_;}
        inline Cost futureCost() {return futureCost_;}
        inline Cost totalLoadCost() {return totalLoadCost_;}
        inline Cost bestObjectiveCost() {return bestObjectiveCost_;}
        inline Id serviceFromProcess(Id p) {return processes_[p].serviceId;}
        inline void setUsedMachine(Id m) {usedMachines_.insert(m);}
        inline void setCheckCapacity(bool v) {checkCapacity = v;}
        inline void setBestObjectiveCost(Cost v) {bestObjectiveCost_ = v;}
        inline void setBestMachine(Id p,Id m) {processes_[p].bestMachineId=m;}
        inline void setLnsMachine(Id p,Id m) {processes_[p].lnsMachineId=m;}
        inline bool isAvaliable(Id m, Id p){
            return services_[processes_[p].serviceId].usedMachines[m]==AVAILABLE_;
        }

        inline void removeProcessFromMachine(Id m, Id p) {
            Machine *machine = &machines_[m];
            for (Id i=0; i < machine->n; i++)
                if (machine->processes[i].idProcess == p) {
                    machine->processes[i].idProcess=machine->processes[machine->n-1].idProcess;
                    machine->n--;
                    break;
                }
        }
        inline void addProcessToMachine(Id m, Id p) {
            Machine *machine = &machines_[m];
            if (machine->n == machine->size) {
                MachineProcess mp;
                machine->processes.push_back(mp);
                machine->size = machine->n+1;
            }
            machine->processes[machine->n].idProcess=p;
            machine->n++;
        }

        inline Cost tusages(Id r){
            return machine_->usages[r] + machine_->transitiveUsages[r];
        }

        inline bool isMoved(Id p){ return processes_[p].originalMachineId != processes_[p].currentMachineId;}
        inline Cost loadCost(Id m, Id r){
            Cost cost = (machines_[m].usages[r] - machines_[m].scapacities[r])
                   * resources_[r].weightloadCost;
            return cost>0 ? cost : 0;
        }
        inline Cost loadCostMachine(Id m){
            Cost cost = 0;
            for (Id r=0; r<resourceQtt_; r++){
                cost += loadCost(m,r);
            }
            machines_[m].loadCostMachine = cost;
            return cost;
        }

        inline Cost loadAvaliableCost(Id m, Id r){
            Cost cost = (machines_[m].usages[r] - machines_[m].scapacities[r])
                        * resources_[r].weightloadCost;
            machines_[m].avaliable[r] = cost;
            machines_[m].countAvaliable += cost<=0 ? 1 : 0;
            return cost<0 ? cost:0;
        }

        inline void loadAvaliableMachine(){
            for (auto m = usedMachines_.begin();m!=usedMachines_.end();m++){
                Machine *M = &machines_[*m];
                Id p;
                M->totalCost = M->loadCostMachine + M->balanceCostMachine;
                for(Id j=0;j<M->n;j++){
                    p = M->processes[j].idProcess;
                    if (isMoved(p)){
                        M->totalCost += processes_[p].moveCostProcess;
                        M->totalCost += processes_[p].moveCostMachine;
                    }
                }
                M->countAvaliable = 0;

                Cost cost = 0;
                for (Id r = 0; r < resourceQtt_; r++) {
                    cost += loadAvaliableCost(*m,r);
                }
                M->loadAvaliableCost = cost;
            }
            usedMachines_.clear();
        }

        inline Id getMachineByCost(){
            Machine *M;
            Id p,mm;
            std::vector<Id> bestM;
            bestM.reserve(100);
            Cost maxCost=0;
            for (auto m = usedMachines_.begin();m!=usedMachines_.end();m++){
                M = &machines_[*m];
                M->totalCost = M->loadCostMachine + M->balanceCostMachine;
                for(Id j=0;j<M->n;j++){
                    p = M->processes[j].idProcess;
                    if (isMoved(p)){
                        M->totalCost += processes_[p].moveCostProcess;
                        M->totalCost += processes_[p].moveCostMachine;
                    }
                }
            }
            usedMachines_.clear();
            for (Id m=0; m < machineQtt_; m++){
                M = &machines_[m];
                if((maxCost > M->totalCost) or (M->n==0)){
                    continue;
                }else if(maxCost==M->totalCost){
                    bestM.push_back(m);
                }else{
                    bestM.clear();
                    bestM.push_back(m);
                    maxCost = M->totalCost;
                }
            }
            mm = rand()%bestM.size();
            return bestM[mm];
        }

        inline Cost processRemoveBenefit(Id m, Id p){
            Cost cost = 0;
            Cost c,tempCost;
            Id r1,r2;
            Balance *B;
            Machine *M = &machines_[m];
            Process *P = &processes_[p];
            for (Id r = 0; r < resourceQtt_; r++) {
                if (M->scapacities[r] < M->usages[r]){
                    c = M->usages[r] - M->scapacities[r];
                    cost += ((c < P->requirements[r])?c:P->requirements[r]) * resources_[r].weightloadCost;
                }
            }

            cost -= M->balanceCostMachine;
            for (Id b=0; b<balanceQtt_; b++){
                B = &balances_[b];
                r1 = B->resourceId1;
                r2 = B->resourceId2;
                c = (B->target
                     *(M->capacities[r1] - M->usages[r1] + P->requirements[r1]))
                     -(M->capacities[r2] - M->usages[r2] + P->requirements[r2]);
                cost += c > 0 ? c * B->weightCost:0;
            }

            // Move cost
            if (isMoved(p)) {
                //ServiceMoveCost_
                Service *S = &services_[P->serviceId];
                if(S->movedProcessQtt==processesMovedInServiceMax_){
                    cost +=  weightServiceCost_;
                }
                //ProcessMoveCost_
                cost += P->moveCost * weightProcessCost_;
                //MachineMoveCost_
                cost += machines_[P->originalMachineId].moveCost[m] * weightMachineCost_;
            }
            return cost;
        }

        inline Id getProcessMaxBenefit(Id m){
            Id p,mp;
            std::vector<Id> bestP;
            bestP.reserve(20);
            Cost cost, maxCost=-999999999;

            Machine *machine = &machines_[m];
            for(Id n=0;n<machine->n;n++){
                p = machine->processes[n].idProcess;
                cost =  processRemoveBenefit(m,p);
                machine->processes[n].processCost = cost;
                if(maxCost > cost){
                    continue;
                }else if(maxCost==cost){
                    bestP.push_back(p);
                }else{
                    bestP.clear();
                    bestP.push_back(p);
                    maxCost = cost;
                }
            }
            mp = rand()%bestP.size();
            return bestP[mp];
        }

        inline void sortProcessMaxBenefit(Id m){
            Machine *M = &machines_[m];
            Id p;
            for(Id n=0;n<M->n;n++){
                p = M->processes[n].idProcess;
                M->processes[n].processCost = processRemoveBenefit(m,p);
            }
            sort(M->processes.begin(),M->processes.begin()+M->n,
                 [this] (MachineProcess m1, MachineProcess m2) {return m1.processCost < m2.processCost;});
        }

        inline std::vector<Id> getProcessByCost(Qtt numProcess){
            Machine *M;
            Id p;
            Cost cost;
            for (auto m = usedMachines_.begin();m!=usedMachines_.end();m++){
                M = &machines_[*m];
                M->wostCostProcess = 0;
                for(Id j=0;j<M->n;j++){
                    p = M->processes[j].idProcess;
                    cost = processRemoveBenefit(*m,p);
                    M->processes[j].processCost = cost;
                    if (cost>M->wostCostProcess){
                        M->wostCostProcess = cost;
                    }
                }
            }
            usedMachines_.clear();
            std::vector<Id> bestP;
            std::vector<Id> costsP;
            bestP.reserve(numProcess);
            costsP.reserve(numProcess);
            Cost minCost=-9999999;
            Id idW = 0;
            for(Id i=0; i<numProcess;i++){
               bestP.push_back(i);
               costsP.push_back(minCost);
            }
            for (Id m=0; m < machineQtt_; m++) {
                M = &machines_[m];
                if(M->wostCostProcess>minCost) {
                    for (Id j = 0; j < M->n; j++) {
                        cost = M->processes[j].processCost;
                        if (cost > minCost) {
                            bestP[idW] = M->processes[j].idProcess;
                            costsP[idW] = cost;
                            minCost = cost;
                            for (Id i = 0; i < numProcess; i++) {
                                if (costsP[i] < minCost) {
                                    minCost = costsP[i];
                                    idW = i;
                                }
                            }
                        }
                    }
                }
            }
            return bestP;
        }

        inline bool isFullLoad(Id m, Id p){
            for (Id r = 0; r < resourceQtt_; r++) {
                if ((machines_[m].usages[r] - machines_[m].scapacities[r]
                - processes_[p].requirements[r])<0)
                    return FALSE_;
            }
            return TRUE_;
        }

        inline Capacity available(Id m, Id r) {
            return (machines_[m].capacities[r] - machines_[m].usages[r]) ;
        }
        inline Cost balanceCost(Id m, Id b) {
            Balance *balance = &balances_[b];
            Cost cost = (balance->target*available(m,balance->resourceId1))
                        -available(m,balance->resourceId2);
            cost = cost * balance->weightCost;
            return cost > 0 ? cost : 0;
        }
        inline Cost balanceCostMachine(Id m){
            Cost cost = 0;
            for (Id b=0; b<balanceQtt_; b++){
                cost += balanceCost(m,b);
            }
            machines_[m].balanceCostMachine = cost;
            return cost;
        }
        inline void updateLoadAndBalanceCost(Id m){
            totalLoadCost_    -= machines_[m].loadCostMachine;
            totalBalanceCost_ -= machines_[m].balanceCostMachine;
            totalLoadCost_    += loadCostMachine(m);
            totalBalanceCost_ += balanceCostMachine(m);
        }

        inline Cost machineMoveCost(Id p, bool isAdd){
            Id originalMachineId = processes_[p].originalMachineId;
            Id currentMachineId = processes_[p].currentMachineId;
            Cost cost = machines_[originalMachineId].moveCost[currentMachineId] * weightMachineCost_;
            processes_[p].moveCostMachine = isAdd ? cost:0;
            return cost;
        }

        inline Cost processMoveCost(Id p, bool isAdd) {
            Cost cost = (isMoved(p)) ? processes_[p].moveCost : 0;
            cost = cost * weightProcessCost_;
            processes_[p].moveCostProcess = isAdd ? cost:0;
            return cost;
        }

        inline void incrementTransitiveUsageOfOriginalMachine(Id p){
            for (Id r=0; r<resourceQtt_; r++) {
                if (resources_[r].transientUsage)
                    machines_[processes_[p].originalMachineId].transitiveUsages[r] += processes_[p].requirements[r];
            }
        }

        inline void incrementUsageOfMachine(Id m, Id p){
            machine_ = &machines_[m];
            process_ = &processes_[p];
            for (Id r=0; r<resourceQtt_; r++) {
                machine_->usages[r] += process_->requirements[r];
                if ((resources_[r].transientUsage && m == process_->originalMachineId))
                    machine_->transitiveUsages[r] -= process_->requirements[r];
            }
        }

        inline void decrementUsageOfMachine(Id m, Id p){
            machine_ = &machines_[m];
            process_ = &processes_[p];
            for (Id r=0; r<resourceQtt_; r++) {
                machine_->usages[r] -= process_->requirements[r];
                if ((resources_[r].transientUsage && m == process_->originalMachineId))
                    machine_->transitiveUsages[r] += process_->requirements[r];
            }
        }

        inline void addNeighborhoodToService(Service *service, Id n){
            if (service->usedNeighborhoods[n] == 0) {
                if (service->mandatoryNeighborhoods[n]) {
                    service->mandatoryNeighborhoodQtt--;
                }
                for (Id d=0; d<service->dependsOnQtt; d++) {
                    Service *sr = &services_[service->dependsOns[d]];
                    if (sr->mandatoryNeighborhoods[n]++ == 0 && sr->usedNeighborhoods[n] == 0)
                        sr->mandatoryNeighborhoodQtt++;
                }
            }
            service->usedNeighborhoods[n]++;
        }
        static inline void addLocationToService(Service *service, Id l){
            if (service->usedLocations[l] == 0)
                service->usedLocationQtt++;
            service->usedLocations[l]++;
        }
        static inline void addMachineToService(Service *service, Id m) {
            service->usedMachines[m] = USED_;
            service->usedMachineQtt++;
            service->availableMachineQtt--;
        }
        inline void addProcessMoveToService(Service *service, Id p) {
            service->unassignedProcessQtt--;
            if (isMoved(p)) {
                service->movedProcessQtt++;
                if (service->movedProcessQtt == processesMovedInServiceMax_) {
                    processesMovedInServiceMaxQtt_++;
                } else if (service->movedProcessQtt > processesMovedInServiceMax_) {
                    processesMovedInServiceMaxQtt_ = 1;
                    processesMovedInServiceMax_ = service->movedProcessQtt;
                    totalServiceMoveCost_  = processesMovedInServiceMax_ * weightServiceCost_;
                }
            }
        }
        inline Qtt getprocessesMovedInServiceMaxQtt() {
            Qtt qtt = 1;
            for (Id s=0;s<serviceQtt_;s++){
                if(services_[s].movedProcessQtt==processesMovedInServiceMax_)
                    qtt++;
            }
            return qtt;
        }
        inline void removeProcessMoveToService(Service *service, Id p) {
            service->unassignedProcess[service->unassignedProcessQtt] = p;
            service->unassignedProcessQtt++;
            if (isMoved(p)) {
                if (service->movedProcessQtt == processesMovedInServiceMax_) {
                    processesMovedInServiceMaxQtt_--;
                    if (processesMovedInServiceMaxQtt_==0){
                        processesMovedInServiceMax_--;
                        totalServiceMoveCost_  = processesMovedInServiceMax_ * weightServiceCost_;
                        processesMovedInServiceMaxQtt_= getprocessesMovedInServiceMaxQtt();
                    }
                }
                service->movedProcessQtt--;
            }
        }

        inline void removeLocationFromService(Service *service, Id l){
            if (--service->usedLocations[l] == 0)
                service->usedLocationQtt--;
        }
        inline void removeMachineFromService(Service *service, Id m){
            service->usedMachines[m] = AVAILABLE_;
            service->usedMachineQtt--;
            service->availableMachineQtt++;
        }
        inline void removeNeighborhoodFromService(Service *service, Id n){
            Service *sr;
            if (--service->usedNeighborhoods[n] == 0) {
                if (service->mandatoryNeighborhoods[n])
                    service->mandatoryNeighborhoodQtt++;
                for (Id d = 0; d < service->dependsOnQtt; d++) {
                    sr = &services_[service->dependsOns[d]];
                    if (--sr->mandatoryNeighborhoods[n] == 0 && sr->usedNeighborhoods[n] == 0)
                        sr->mandatoryNeighborhoodQtt--;
                }
            }
        }

        inline Cost getObjectiveCost(){
            return totalLoadCost_ + totalBalanceCost_
            + totalProcessMoveCost_ + totalServiceMoveCost_
            + totalMachineMoveCost_;
        }

        inline Cost getObjectiveCost2(){
            return totalLoadCost_
                   + totalProcessMoveCost_ + totalServiceMoveCost_
                   + totalMachineMoveCost_;
        }

        inline bool machineCapacityConstraint(Id m){
            if (checkCapacity){
                machine_ = &machines_[m];
                for (Id r=0;r<resourceQtt_;r++) {
                    if(tusages(r) > machine_->capacities[r])
                        return false;
                }
            }
            return true;
        }
        inline bool conflictConstraint(Id s){
            return (services_[s].availableMachineQtt >= services_[s].unassignedProcessQtt);
        }
        inline bool spreadConstraint(Id s){
            return (services_[s].usedLocationQtt + services_[s].unassignedProcessQtt >=
                    services_[s].spreadMin);
        }
        inline bool serviceDependencyConstraints(Id s){
            Service *sr,*service = &services_[s];
            if(service->mandatoryNeighborhoodQtt > service->unassignedProcessQtt)
                return FALSE_;
            for (Id d = 0; d < service->dependsOnQtt; d++){
                sr = &services_[service->dependsOns[d]];
                if(sr->mandatoryNeighborhoodQtt > sr->unassignedProcessQtt)
                    return FALSE_;
            }
            return TRUE_;
        }

        inline bool compare(Id m1,Id m2){
            return ( machines_[m1].totalCost)
                   < (machines_[m2].totalCost);
        }
        inline bool compare2(Id m1, Id m2){
            if (machines_[m1].countAvaliable < machines_[m2].countAvaliable){
                return false;
            }
            if (machines_[m1].countAvaliable > machines_[m2].countAvaliable){
                return true;
            }
            return ( machines_[m1].totalCost)
                   < (machines_[m2].totalCost);
        }
        inline Cost machineProcessSatCost(Id m, Id p){
            Cost cost = 0;
            Process *process = &processes_[p];
            Machine *machine = &machines_[m];
            if (services_[process->serviceId].usedMachines[m]!=AVAILABLE_){
                cost = 99999999999;
                return cost;
            }

            //LoadCost_
            cost -= machine->loadCostMachine;
            Cost c;
            for (Id r=0; r<resourceQtt_; r++){
                c = machine->transitiveUsages[r] + machine->usages[r];
                c += (process->originalMachineId!=m)?process->requirements[r]:0;
                if (c > machine->capacities[r]){
                    cost = 99999999999;
                    return cost;
                }
                c = (machine->usages[r] + process->requirements[r] - machine->scapacities[r]);
                cost += c>0?c * resources_[r].weightloadCost:0;
            }

            //BalanceCost_
            Balance *balance;
            cost -= machine->balanceCostMachine;
            for (Id b=0; b<balanceQtt_; b++){
                balance = &balances_[b];
                Id r1 = balance->resourceId1;
                Id r2 = balance->resourceId2;
                Cost c = (balance->target
                        *(machine->capacities[r1]-machine->usages[r1]-process->requirements[r1]))
                        -(machine->capacities[r2]-machine->usages[r2]-process->requirements[r2]);
                cost += c > 0 ? c*balance->weightCost:0;
            }

            // Move cost
            if (process->originalMachineId!=m) {
                //ServiceMoveCost_
                Service *service = &services_[process->serviceId];
                if(service->movedProcessQtt==processesMovedInServiceMax_){
                    cost +=  weightServiceCost_;
                }
                //ProcessMoveCost_
                cost += process->moveCost * weightProcessCost_;
                //MachineMoveCost_
                cost += machines_[process->originalMachineId].moveCost[m] * weightMachineCost_;
            }

            return cost;
        }


    private:
        std::vector<Resource> resources_;
        std::vector<Machine> machines_;
        std::vector<Service> services_;
        std::vector<Process> processes_;
        std::vector<Balance> balances_;
        std::set<Id> usedMachines_;

        Qtt resourceQtt_        = 0;
        Qtt machineQtt_         = 0;
        Qtt serviceQtt_         = 0;
        Qtt processQtt_         = 0;
        Qtt balanceQtt_         = 0;
        Qtt neighborhoodQtt_    = 0;
        Qtt locationQtt_        = 0;
        Cost mmcmax_            = 0;
        Cost weightProcessCost_ = 0;
        Cost weightServiceCost_ = 0;
        Cost weightMachineCost_ = 0;
        Machine *machine_;
        Process *process_;

        bool checkCapacity      = true;

        Cost bestObjectiveCost_  = 0;
        Cost futureCost_         = 0;

        Qtt processesMovedInServiceMax_    = 0;
        Qtt processesMovedInServiceMaxQtt_ = 0;

        Cost totalLoadCost_        = 0;
        Cost totalBalanceCost_     = 0;
        Cost totalProcessMoveCost_ = 0;
        Cost totalServiceMoveCost_ = 0;
        Cost totalMachineMoveCost_ = 0;
    };

}
#endif //ROAED2012_INSTANCE_H
