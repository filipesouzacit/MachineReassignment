//
// Created by Filipe souza on 02/09/2020.
//

#pragma once
#include <iterator>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <functional>
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
#include<chrono>
//#define TRUE 1
//#define FALSE 0
//#define USED  2
//#define CANNOTBEUSED 1
//#define AVAILABLE 0
//#define UNASSIGNED 60000
//#define NONE 60000

namespace carSeq
{
    typedef int64_t Cost;
    typedef int32_t Id;
    typedef int64_t Qtt;
    typedef std::string Str;

    struct Param{
        Str name;
        Str value;
    };

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

    std::vector<Id> getArray(std::string line){
        std::vector<Id> intList;
        std::stringstream ss(line);
        std::string tmp;
        while (getline(ss, tmp, ',')) {
            intList.push_back((Id) std::stol(tmp));
        }
        return intList;
    }

    time_t startTime;
    int32_t runTime = 300;
    int32_t seed = 10;
    Qtt subProblemSizeInit = 4;
    Qtt subProblemSizeMax = 100;
    Qtt improvementThreshold = 50;
    Qtt improvementThresholdOF = 500;
    Qtt thresholdAltObjFunc = 20;
    double timeLimitAltObjFunc = 0;
    Qtt failuresMax = 400;
    Qtt failuresinitialMax = 31;
    double fatorFailuresMax = 1.5;
    double pctRandom = 0.2;
    Id AdaptSubProblemSize = 1;
    Id iterationToPrint = 0;
    Id selectProcesses = 1; // 1 - Random; 2 - MachineMaxCost ; 3 - ProcessMaxCost; 4 - UnblalancedMachines
    Id printFreq = 1000000;
    Str inst = "";
    Str testId = "000";
    std::string instancePath = "../data/model_";
    std::string inicSolutionPath  = "../data/assignment_";
    std::string solutionPath = "../solution/solution_";
    std::string dataPlotPath = "../solution/dataPlot_";
    std::string treeDataPlotPath = "../solution/tree_dataPlot_";
    std::string neighbourhoodPath = "../solution/neighbourhood_";
    std::mt19937 randNum;
    std::uniform_real_distribution<double> dis(0.0,1.0);

    bool TRUE_ = true;
    bool FALSE_ = false;
    Id USED_  = (Id)2;
    Id CANNOTBEUSED_ = (Id)1;
    Id AVAILABLE_ = (Id)0;
    Id UNASSIGNED_ = (Id)60000;
    Id NONE_ = (Id)60000;


    std::string getstring(std::vector<Id> vec){
        std::ostringstream vts;
        if (!vec.empty()){
            std::copy(vec.begin(), vec.end()-1,
                      std::ostream_iterator<Id>(vts, ", "));
            vts << vec.back();
        }
        return vts.str();
    }

    double totalTime(){
        return time(0) - startTime;
    }

    bool checkTime() {
        return runTime >= totalTime();
    }

    bool checkTimeObjFunc() {
        return (runTime*timeLimitAltObjFunc) >= totalTime();
    }


    void initSolver(){
        startTime = time(0);
    }
}
