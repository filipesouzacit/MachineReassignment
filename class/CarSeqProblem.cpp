//
// Created by Filipe De Souza on 01/04/2022.
//

#include "CarSeqProblem.h"
using namespace carSeq;
CarSeqProblem::CarSeqProblem(Str fileName){
    Str str;
    int i;
    std::ifstream itemStream(fileName);
    if (!itemStream.good()) {
        std::cerr << "ERROR - File not found \"" << fileName << "\"" << std::endl;
        return;
    }

    // Read file
    getline(itemStream, str);
    std::vector<Str> line = split(str);
    inst.qttCar = (Qtt) std::stoi(line[0]);
    inst.qttOption = (Qtt) std::stoi(line[1]);
    inst.qttClass = (Qtt) std::stoi(line[2]);

    // get capacity
    getline(itemStream, str);
    line = split(str);
    for(Id i=0;i<inst.qttOption;i++){
        inst.capacity.push_back((Qtt) std::stoi(line[i]));
    }

    // get windows
    getline(itemStream, str);
    line = split(str);
    for(Id i=0;i<inst.qttOption;i++){
        inst.windowSize.push_back((Qtt) std::stoi(line[i]));
    }

    // get windows
    Qtt carPerClass = 0;
    inst.TotalOptionDemand = 0;
    for(Id c=0;c<inst.qttClass;c++){
        inst.classes.push_back(c+1);
        getline(itemStream, str);
        line = split(str);
        carPerClass = (Qtt) std::stoi(line[1]);
        inst.carPerClass.push_back(carPerClass);
        std::vector<bool> temp = {};
        for(Id i=0;i<inst.qttOption;i++){
            temp.push_back((bool) std::stol(line[i]));
            inst.TotalOptionDemand+=(carPerClass*std::stoi(line[i]));
        }
        inst.optionsRequired.push_back(temp);
    }
};

void CarSeqProblem::InitSolution(){
    for(Id c=0;c<inst.qttCar;c++){
        sol.sequency.push_back(0);
    }
    sol.cost = inst.TotalOptionDemand;
}