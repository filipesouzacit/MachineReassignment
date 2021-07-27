//
// Created by Filipe souza on 17/07/2021.
//
#include <iostream>
#include "class/Search.cpp"
using namespace std;

int main(int argc, char** argv){
    Str instance = "";
    MRBD::Param param;
    for (int i=1; i<argc; ++i){
        param = MRBD::getParam(argv[i]);
        if(param.name=="typeSearch")
            MRBD::typeSearch = (Id) std::stol(param.value);
        else if(param.name=="instance")
            instance = param.value;
        else if(param.name=="test")
            MRBD::testId = param.value;
        else if(param.name=="selectProcesses")
            MRBD::selectProcesses = (Id) std::stol(param.value);
        else if(param.name=="machineMaxInit")
            MRBD::machineMaxInit = (Id) std::stol(param.value);
        else if(param.name=="machineMaxSearch")
            MRBD::machineMaxSearch = (Id) std::stol(param.value);
        else if(param.name=="subProblemSizeInit")
            MRBD::subProblemSizeInit = (Id) std::stol(param.value);
        else if(param.name=="subProblemSizeMax")
            MRBD::subProblemSizeMax = (Id) std::stol(param.value);
        else if(param.name=="improvementThreshold")
            MRBD::improvementThreshold = (Id) std::stol(param.value);
        else if(param.name=="pctChangeMachine")
            MRBD::pctChangeMachine = (double) std::stod(param.value);
        else if(param.name=="pctRandom")
            MRBD::pctRandom = (double) std::stod(param.value);
        else if(param.name=="runTime")
            MRBD::runTime = (Id) std::stol(param.value);
        else if(param.name=="failuresMax")
            MRBD::failuresMax = (Id) std::stol(param.value);
        else if(param.name=="fatorFailuresMax")
            MRBD::fatorFailuresMax = (double) std::stod(param.value);
        else if(param.name=="failuresinitialMax")
            MRBD::failuresinitialMax = (Id) std::stol(param.value);
        else if(param.name=="discrepancyMax")
            MRBD::discrepancyMax = (Id) std::stol(param.value);
        else if(param.name=="iterationToPrint")
            MRBD::iterationToPrint = (Id) std::stol(param.value);
        else if(param.name=="printFreq")
            MRBD::printFreq = (Id) std::stol(param.value);
        else if(param.name=="topValueSeletion")
            MRBD::topValueSeletion = (Id) std::stol(param.value);
        else if(param.name=="topVariableSeletion")
            MRBD::topVariableSeletion = (Id) std::stol(param.value);
        else if(param.name=="seed")
            MRBD::seed = (Id) std::stol(param.value);
    }
    if (instance==""){
        cout << "Instance Not Found!!!";
        return 1;
    }
    Str sseed = to_string(MRBD::seed) + ".";
    Str stringpath = "../result/solution/"+ MRBD::testId +"/";
    int status = mkdir(stringpath.c_str(),0777);
    MRBD::inst = instance;
    MRBD::instancePath = "data/model_";
    MRBD::inicSolutionPath = "data/assignment_";
    MRBD::solutionPath = "../result/solution/"+ MRBD::testId +"/solution_";
    MRBD::dataPlotPath = "../result/solution/"+ MRBD::testId +"/dataPlot_";
    MRBD::treeDataPlotPath = "../result/solution/"+ MRBD::testId +"/tree_dataPlot_";
    MRBD::instancePath.append(instance).append(".txt");
    MRBD::inicSolutionPath.append(instance).append(".txt");
    MRBD::solutionPath.append(sseed).append(instance).append(".txt");
    MRBD::dataPlotPath.append(sseed).append(instance).append(".txt");
    MRBD::treeDataPlotPath.append(sseed).append(instance).append(".txt");
    MRBD::randNum = std::mt19937(MRBD::seed);
    MRBD::Search search = MRBD::Search();
    MRBD::initSolver();
    search.start();
    return 0;
}



