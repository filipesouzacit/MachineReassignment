//
// Created by Filipe souza on 22/03/2021.
//
#include "Instance.h"
using namespace MRBD;

void Instance::resourceAdd(Str str) {
    std::vector<std::string> line = split(str);
    Resource resource;
    resource.id             = resources_.size();
    resource.transientUsage = (bool) std::stol(line[0]);
    resource.weightloadCost = (weight) std::stol(line[1]);
    resources_.push_back(resource);
}

void Instance::machineAdd(Str str){
    std::vector<std::string> line = split(str);
    Machine machine;
    machine.id           = machines_.size();
    machine.neighborhood = (Id) std::stol(line[0]);
    machine.location     = (Id) std::stol(line[1]);
    machine.n = 0;
    machine.size =0;
    machine.loadCostMachine = 0;  // New
    machine.balanceCostMachine = 0; // New
    if(neighborhoodQtt_ < machine.neighborhood)
        neighborhoodQtt_ = machine.neighborhood;
    if(locationQtt_ < machine.location)
        locationQtt_ = machine.location;
    for (int i = 2; i < resourceQtt_+2; i++) {
        machine.capacities.push_back((Capacity) std::stol(line[i]));
        machine.scapacities.push_back((Capacity) std::stol(line[i+resourceQtt_]));
        machine.usages.push_back(0);
        machine.avaliable.push_back(0);
        machine.transitiveUsages.push_back(0);
    }
    for (int i = resourceQtt_*2+2; i < resourceQtt_*2+2+machineQtt_; i++) {
        Cost mmc = (Cost) std::stol(line[i]);
        machine.moveCost.push_back(mmc);
        if(mmcmax_ < mmc)
            mmcmax_ = mmc;
    }
    machines_.push_back(machine);
}

void Instance::serviceAdd(Str str){
    std::vector<std::string> line = split(str);
    Service service;
    service.id                       = services_.size();
    service.usedLocationQtt          = 0;
    service.processQtt               = 0;
    service.movedProcessQtt          = 0;
    service.unassignedProcessQtt     = 0;
    service.usedMachineQtt           = 0;
    service.mandatoryNeighborhoodQtt = 0;
    service.neighborhoodQtt          = 0;
    service.availableMachineQtt      = machineQtt_;
    service.spreadMin                = (Qtt) std::stol(line[0]);
    service.dependsOnQtt             = (Qtt) std::stol(line[1]);
    for (int i=2; i<service.dependsOnQtt+2; i++) {
        service.dependsOns.push_back((Id) std::stol(line[i]));
    }
    for (int i=0; i<neighborhoodQtt_; i++) {
        service.usedNeighborhoods.push_back(0);
        service.mandatoryNeighborhoods.push_back(0);
    }
    for (int i=0; i<locationQtt_; i++) {
        service.usedLocations.push_back(0);
    }
    for (int i=0; i<machineQtt_; i++) {
        service.usedMachines.push_back(AVAILABLE_);
    }
    services_.push_back(service);
}

void Instance::processAdd(Str str){
    std::vector<std::string> line = split(str);
    Process process;
    process.id          = processes_.size();
    process.serviceId   = (Id) std::stol(line[0]);
    process.moveCost         = (Cost) std::stol(line[resourceQtt_+1]);
    process.requirement = 0;
    services_[process.serviceId].processQtt++;
    services_[process.serviceId].unassignedProcess.push_back(process.id);
    services_[process.serviceId].unassignedProcessQtt++;
    for (int i=1; i <= resourceQtt_;i++) {
        process.requirements.push_back((Cost) std::stol(line[i]));
        process.requirement += ((Cost)std::stol(line[i])*resources_[i-1].weightloadCost);
    }
    processes_.push_back(process);
}

void Instance::balanceAdd(Str str, Str str2){
    std::vector<std::string> line = split(str);
    Balance balance;
    balance.id          = balances_.size();
    balance.resourceId1 = (Id) std::stol(line[0]);
    balance.resourceId2 = (Id) std::stol(line[1]);
    balance.target      = (Cost) std::stol(line[2]);
    balance.weightCost  = (Cost) std::stol(str2);
    balances_.push_back(balance);
}

void Instance::weightAdd(Str str){
    std::vector<std::string> line = split(str);
    weightProcessCost_   = (Cost) std::stol(line[0]);
    weightServiceCost_   = (Cost) std::stol(line[1]);
    weightMachineCost_   = (Cost) std::stol(line[2]);
}

void Instance::assignMachineToProcess(Id m, Id p){
    Process *process = &processes_[p];
    Machine *machine = &machines_[m];
    Service *service = &services_[process->serviceId];
    process->currentMachineId  = m;

    addProcessToMachine(m, p);
    incrementUsageOfMachine(m,p);

    addNeighborhoodToService(service, machine->neighborhood);
    addLocationToService(service, machine->location);
    addMachineToService(service, m);
    addProcessMoveToService(service, p);

    updateLoadAndBalanceCost(m);
    totalMachineMoveCost_ += machineMoveCost(p,TRUE_);
    totalProcessMoveCost_ += processMoveCost(p,TRUE_);
}

void Instance::printSolutionInFile(){
    std::ofstream fileOut{MRBD::solutionPath};
    if (!fileOut.good()) {
        std::cerr << "ERROR - File not found \"" << MRBD::solutionPath << "\"" << std::endl;
        return;
    }
    for (Id p=0; p < processQtt_; p++)
        fileOut << processes_[p].bestMachineIdFull << " ";
    fileOut.close();
}



Instance::Instance() {
    getObjectiveCost = &Instance::getObjectiveCostFull;
    Str str,str2;
    int i;
    std::ifstream itemStream(MRBD::instancePath);
    if (!itemStream.good()) {
        std::cerr << "ERROR - File not found \"" << MRBD::instancePath << "\"" << std::endl;
        return;
    }

    // Read Resources
    getline(itemStream, str);
    resourceQtt_ = (Qtt) std::stoi(str);
    for (i = 0; i < resourceQtt_; i++) {
        getline(itemStream, str);
        resourceAdd(str);
    }

    // Read Machines
    getline(itemStream, str);
    machineQtt_ = (Qtt) std::stoi(str);
    for (i = 0; i < machineQtt_; i++) {
        usedMachines_.insert(i);
        getline(itemStream, str);
        machineAdd(str);
    }
    locationQtt_ ++;
    neighborhoodQtt_ ++;

    // Read Service
    getline(itemStream, str);
    serviceQtt_ = (Qtt) std::stoi(str);
    for (i = 0; i < serviceQtt_; i++) {
        getline(itemStream, str);
        serviceAdd(str);
    }

    // Read Processes
    getline(itemStream, str);
    processQtt_ = (Qtt) std::stoi(str);
    for (i = 0; i < processQtt_; i++) {
        getline(itemStream, str);
        processAdd(str);
    }

    // Read Balances
    getline(itemStream, str);
    balanceQtt_ = (Qtt) std::stoi(str);
    for (i = 0; i < balanceQtt_; i++) {
        getline(itemStream, str);
        getline(itemStream, str2);
        balanceAdd(str,str2);
    }

    // Read weight
    getline(itemStream, str);
    weightAdd(str);

    // Read Solution
    processesMovedInServiceMax_ = 0;

    std::ifstream itemStreamSol(MRBD::inicSolutionPath);
    if (!itemStreamSol.good()) {
        std::cerr << "ERROR - File not found \"" << MRBD::inicSolutionPath << "\"" << std::endl;
        return;
    }

    for(Id m=0;m<qttMachines();m++){
        updateLoadAndBalanceCost(m);
    }

    getline(itemStreamSol, str);
    std::vector<std::string> line = split(str);
    Id machineId;
    for (Id p=0; p<processQtt_; p++) {
        machineId = (Id)std::stoi(line[p]);
        processes_[p].bestMachineId     = machineId;
        processes_[p].originalMachineId = machineId;
        processes_[p].lnsMachineId      = machineId;
        incrementTransitiveUsageOfOriginalMachine(p);
        assignMachineToProcess(machineId,p);
    }
    bestObjectiveCost_ = getObjectiveCostFull();
    bestObjectiveCostFull_ = bestObjectiveCost_;
}

bool Instance::machineSatisfyRequirementOfProcess(Id m, Id p){
    machine_ = &machines_[m];
    Process *P = &processes_[p];
    if (checkCapacity) {
        for (Id r = 0; r < resourceQtt_; r++) {
            if (tusages(r) + P->requirements[r] > machine_->capacities[r])
                return FALSE_;
        }
    }else{
        for (Id r = 0; r < resourceQtt_; r++) {
            if (tusages(r) > machine_->capacities[r])
                return FALSE_;
        }
    }
    return TRUE_;
}

void Instance::unassignProcess(Id p){
    Process *process = &processes_[p];
    Id m = process->currentMachineId;
    Id s = process->serviceId;
    Machine *machine = &machines_[m];
    Service *service = &services_[s];

    decrementUsageOfMachine(m,p);

    updateLoadAndBalanceCost(m);
    totalMachineMoveCost_ -= machineMoveCost(p,FALSE_);
    totalProcessMoveCost_ -= processMoveCost(p,FALSE_);

    removeProcessMoveToService(service,p);
    removeMachineFromService(service, m);
    removeLocationFromService(service, machine->location);
    removeNeighborhoodFromService(service, machine->neighborhood);
    removeProcessFromMachine(m, p);

    process->currentMachineId = UNASSIGNED_;

}