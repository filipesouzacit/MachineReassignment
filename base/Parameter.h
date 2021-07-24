//
// Created by Filipe souza on 02/09/2020.
//

#pragma once
#include <algorithm>
#include <sys/stat.h>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <iomanip>
#include <locale>
#include <set>
#include <random>
#include<string>
//#define TRUE 1
//#define FALSE 0
//#define USED  2
//#define CANNOTBEUSED 1
//#define AVAILABLE 0
//#define UNASSIGNED 60000
//#define NONE 60000

namespace MRBD
{
    typedef int64_t weight;
    typedef int64_t Size;
    typedef int64_t Capacity;
    typedef int64_t Cost;
    typedef int32_t Id;
    typedef int32_t Qtt;
    typedef std::string Str;

    struct Param{
        Str name;
        Str value;
    };

    std::vector<std::string> split(std::string line)
    {
        std::vector<std::string> v;
        std::stringstream ss(line);
        std::string tmp;
        while (getline(ss, tmp, ' ')) {
            v.push_back(tmp);
        }
        return v;
    }

    Param getParam(std::string line){
        std::vector<std::string> v;
        std::stringstream ss(line);
        std::string tmp;
        while (getline(ss, tmp, '=')) {
            v.push_back(tmp);
        }
        Param p;
        if(v.size()==2){
            p.name = v[0];
            p.value = v[1];
        }else{
            p.name = "None";
        }
        return p;
    }

    time_t startTime;
    int16_t runTime = 300;
    int32_t seed = 10;
    Qtt subProblemSizeInit = 4;
    Qtt subProblemSizeMax = 100;
    Qtt improvementThreshold = 50;
    Qtt failuresMax = 400;
    Qtt failuresinitialMax = 31;
    double fatorFailuresMax = 1.5;
    Qtt topVariableSeletion = 3;
    Qtt topValueSeletion = 3;
    Qtt discrepancyMax = 5;
    Qtt machineMaxInit = 200;
    Qtt machineMaxSearch = 100;
    double pctChangeMachine = 0.5;
    double pctRandom = 0.2;
    Id iterationToPrint = 0;
    Id typeSearch = 2; // 1 - systematic; 2 - Discrepancy Search; 3 - Random and Restart;
    Id selectProcesses = 4; // 1 - Random; 2 - MachineMaxCost ; 3 - ProcessMaxCost; 4 - UnblalancedMachines
    Id printFreq = 1000000;
    Str inst = "";
    Str testId = "000";
    std::string instancePath = "../data/model_";
    std::string inicSolutionPath  = "../data/assignment_";
    std::string solutionPath = "../solution/solution_";
    std::string dataPlotPath = "../solution/dataPlot_";
    std::string treeDataPlotPath = "../solution/tree_dataPlot_";
    std::default_random_engine seed_;

    bool TRUE_ = true;
    bool FALSE_ = false;
    Id USED_  = (Id)2;
    Id CANNOTBEUSED_ = (Id)1;
    Id AVAILABLE_ = (Id)0;
    Id UNASSIGNED_ = (Id)60000;
    Id NONE_ = (Id)60000;


    double totalTime(){
        return time(0) - startTime;
    }

    bool checkTime() {
        return runTime >= totalTime();
    }

    void initSolver(){
        startTime = time(0);
        seed_ = std::default_random_engine(seed);
  //      default_selection();
    }
}
