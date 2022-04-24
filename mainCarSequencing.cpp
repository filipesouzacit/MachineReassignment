//
// Created by Filipe De Souza on 22/04/2022.
//
#include "class/carSequencing.cpp"

using namespace carSeq;
int main(int argc, char** argv) {
    Str fileName = "../dataCar/pb_400_10.txt";
    Param param;
    for (int i=1; i<argc; ++i){
        param = getParam(argv[i]);
        if(param.name=="file")
            fileName = (Id) std::stol(param.value);

    CarSeqProblem problem = CarSeqProblem(fileName);
    problem.InitSolution();

    std::cout << "The objective function is: " << problem.cost() << std::endl;


    // create model and search engine
    carSequencing* m = new carSequencing(problem.instance());
    DFS<carSequencing> e(m);
    delete m;
    // search and print all solutions
    while (carSequencing* s = e.next()) {
        s->print(); delete s;
    }

    return 0;
}
