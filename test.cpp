//
// Created by Filipe souza on 27/07/2021.
//

#include <random>
#include <iostream>

using namespace std;

int main(int argc, char** argv){

    mt19937 gen((int) std::stol(argv[1]));
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < 5; ++i) {
        cout << gen() << " - " << dis(gen) << endl;
    }
    
}