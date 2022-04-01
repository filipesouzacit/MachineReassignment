#include <iostream>
#include "class/Search.cpp"

int main() {

    MRBD::testId = "666";
    Qtt numRuns = 1;
    MRBD::typeSearch = 3; // 1 - systematic; 2 - Discrepancy Search; 3 - Random and Restart;
    MRBD::selectProcesses = 4; // 1 - Random; 2 - MachineMaxCost ; 3 - ProcessMaxCost; 4 - UnblalancedMachines
//    MRBD::machineMaxInit = 200;
//    MRBD::machineMaxSearch = 100;
    MRBD::subProblemSizeInit = 30;
    MRBD::subProblemSizeMax  = 30;
    MRBD::improvementThreshold = 9999999;
    MRBD::pctChangeMachine = 1;
    MRBD::pctRandom = 0.3;
    MRBD::runTime = 300;
    MRBD::failuresMax = 400;
    MRBD::fatorFailuresMax = 1.5;
    MRBD::failuresinitialMax = 10;
    MRBD::discrepancyMax = 2;
//    MRBD::iterationToPrint = 0;
    MRBD::printFreq = 1000;
    MRBD::topValueSeletion = 1;
    MRBD::topVariableSeletion = 2;

    MRBD::improvementThresholdOF = 1000;
    MRBD::thresholdAltObjFunc = 5;
    MRBD::timeLimitAltObjFunc = 0;
    MRBD::ObjetiveFunctions = {6,7};

    std::vector<std::string> test = {
                                 "a2_5" //,
                //                 "a1_2","a1_3","a1_4","a1_5"//,
                               //  "a2_1",
                                // "a2_2","a2_3","a2_4","a2_5",
                                // "b_1","b_2","b_3","b_4","b_5","b_6","b_7","b_8","b_9","b_10",
                                // "x_1","x_2","x_3","x_4","x_5","x_6","x_7","x_8",
                                // "x_9","x_10"
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
            MRBD::neighbourhoodPath = "../../result/solution/"+ testId +"/neighbourhood_";
            MRBD::instancePath.append(test[i]).append(".txt");
            MRBD::inicSolutionPath.append(test[i]).append(".txt");
            MRBD::solutionPath.append(ss).append(test[i]).append(".txt");
            MRBD::dataPlotPath.append(ss).append(test[i]).append(".txt");
            MRBD::treeDataPlotPath.append(ss).append(test[i]).append(".txt");
            MRBD::neighbourhoodPath.append(ss).append(test[i]).append(".csv");
            MRBD::inst = test[i];
            MRBD::seed = s;
            MRBD::randNum = std::mt19937(MRBD::seed);
            MRBD::Search search = MRBD::Search();
            MRBD::initSolver();
            search.start();
        }
    }
    return 0;
}
