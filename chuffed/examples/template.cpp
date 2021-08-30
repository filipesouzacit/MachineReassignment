#include <cstdio>
#include <cassert>
#include "../core/engine.h"
#include "../core/propagator.h"
#include "../branching/branching.h"
#include "../vars/modelling.h"

class ProblemName : public Problem {
public:
	// Constants

	int n;                                          // size of problem

	// Core variables

	vec<IntVar*> x;                                 // some vars

	// Intermediate variables

	//...

	ProblemName(int _n) : n(_n) {

		// Create vars

		createVars(x, n, 1, n);

		// Post some constraints

		all_different(x);

		// Post some branchings

		branch(x, VAR_INORDER, VAL_MIN);

		// Declare output variables (optional)

		output_vars(x);

		// Declare symmetries (optional)

		var_sym_break(x);

	}

	// Function to print out solution

	void print() {
		for (int i = 0; i < n; i++) {
			printf("%d, ", x[i]->getVal());
		}
		printf("\n");
	}

};

int main(int argc, char** argv) {
	parseOptions(argc, argv);

	int n;

	assert(argc == 2);
	n = atoi(argv[1]);

	engine.solve(new ProblemName(n));

	return 0;
}



