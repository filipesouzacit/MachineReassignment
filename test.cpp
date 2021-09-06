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


// C++ program to illustrate the passing
// of functions as an object parameter
#include <functional>
#include <iostream>
using namespace std;

// Define add and multiply to
// return respective values
int add(int x, int y)
{
    return x + y;
}
int multiply(int x, int y)
{
    return x * y;
}

// Function that accepts an object of
// type std::function<> as a parameter
// as well
int invoke(int x, int y,
           function<int(int, int)> func)
{
    return func(x, y);
}

// Driver code
int mainh()
{
    // Pass the required function as
    // parameter using its name
    cout << "Addition of 20 and 10 is ";
    cout << invoke(20, 10, &add)
         << '\n';

    cout << "Multiplication of 20"
         << " and 10 is ";
    cout << invoke(20, 10, &multiply)
         << '\n';

    return 0;
}