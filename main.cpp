#include <iostream>
#include "class/Search.cpp"

int main() {

    MRBD::testId = "666";
    Qtt numRuns = 5;
    MRBD::typeSearch = 3; // 1 - systematic; 2 - Discrepancy Search; 3 - Random and Restart;
    MRBD::selectProcesses = 4; // 1 - Random; 2 - MachineMaxCost ; 3 - ProcessMaxCost; 4 - UnblalancedMachines
//    MRBD::machineMaxInit = 200;
//    MRBD::machineMaxSearch = 100;
    MRBD::subProblemSizeInit = 20;
    MRBD::subProblemSizeMax  = 20;
    MRBD::improvementThreshold = 9999999;
//    MRBD::pctChangeMachine = 0.2;
//    MRBD::pctRandom = 0.5;
    MRBD::runTime = 360;
    MRBD::failuresMax = 400;
    MRBD::fatorFailuresMax = 1.5;
    MRBD::failuresinitialMax = 31;
    MRBD::discrepancyMax = 5;
//    MRBD::iterationToPrint = 0;
    MRBD::printFreq = 20;
    MRBD::topValueSeletion = 1;
    MRBD::topVariableSeletion = 5;

    std::vector<std::string> test = {
                     //            "a1_1",
                                 "a1_2","a1_3","a1_4","a1_5",
                                 "a2_1"
                                 ,"a2_2","a2_3","a2_4","a2_5",
                                 "b_1","b_2","b_3","b_4","b_5","b_6","b_7","b_8","b_9","b_10",
                                 "x_1","x_2","x_3","x_4","x_5","x_6","x_7","x_8",
                                 "x_9","x_10"
                                 };
//                                 "a1_2",
//                                 "a2_1",
//                                 "a2_3"
//                                 ,"b_8",
//                                 "b_9",
//                                 "b_10"
//    };
    std::string stringpath = "../../result/solution/"+ testId +"/";
    int status = mkdir(stringpath.c_str(),0777);
    for (Id s=0;s<numRuns;s++) {
        std::string ss = std::to_string(s) + ".";
        for (Id i = 0; i < test.size(); i++) {
            MRBD::instancePath = "../data/model_";
            MRBD::inicSolutionPath = "../data/assignment_";
            MRBD::solutionPath = "../../result/solution/"+ testId +"/solution_";
            MRBD::dataPlotPath = "../../result/solution/"+ testId +"/dataPlot_";
            MRBD::treeDataPlotPath = "../../result/solution/"+ testId +"/tree_dataPlot_";
            MRBD::instancePath.append(test[i]).append(".txt");
            MRBD::inicSolutionPath.append(test[i]).append(".txt");
            MRBD::solutionPath.append(ss).append(test[i]).append(".txt");
            MRBD::dataPlotPath.append(ss).append(test[i]).append(".txt");
            MRBD::treeDataPlotPath.append(ss).append(test[i]).append(".txt");
            MRBD::inst = test[i];
            MRBD::seed = s;
            MRBD::randNum = std::mt19937(MRBD::seed);
            MRBD::Search search = MRBD::Search();
            MRBD::initSolver();
            search.lnsMachineSelection();
            search.printBestSolution();
            search.printLDS_RRS();
        }
    }
    return 0;
}
