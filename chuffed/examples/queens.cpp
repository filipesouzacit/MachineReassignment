#include <cstdio>
#include <cassert>
#include <chuffed/core/engine.h>
#include <chuffed/core/propagator.h>
#include <chuffed/branching/branching.h>
#include <chuffed/vars/modelling.h>
#include <chuffed/ldsb/ldsb.h>

class Queens : public Problem {
public:
	int const n;
	vec<IntVar*> x;                             // placement of queens

	Queens(int _n) : n(_n) {

		createVars(x, n, 1, n);

		vec<int> a, b;
		for (int i = 0; i < n; i++) {
			a.push(i);
			b.push(-i);
		}

		all_different(x);
		all_different_offset(a, x);
		all_different_offset(b, x);

		branch(x, VAR_INORDER, VAL_MIN);
//		branch(x, VAR_SIZE_MIN, VAL_MIN);

		output_vars(x);

		if (so.ldsb) {
			// horizontal flip 
			vec<IntVar*> sym1;

			for (int i = 0; i < n/2; i++) {
				sym1.push(x[i]);
			}
			for (int i = 0; i < n/2; i++) {
				sym1.push(x[n-i-1]);
			}

			var_seq_sym_ldsb(2, n/2, sym1);

			// vertical flip sym

			vec<int> sym2;
			for (int i = 0; i < n; i++) sym2.push(i+1);
			for (int i = 0; i < n; i++) sym2.push(n-i);

			val_seq_sym_ldsb(2, n, x, sym2);

		} else if (so.sym_static) {

			int_rel(x[0], IRT_LT, x[n-1]);
			int_rel(x[0], IRT_LE, (n+1)/2);
			IntVar* t = newIntVar(1,n+1);
			int_plus(x[0], x[n-1], t);

		}
	}

  void print(std::ostream& os) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
        os << ((x[i]->getVal()-1 == j) ? 1 : 0) << ", ";
			}
			os << "\n";
		}
		os << "\n";
	}

};

int main(int argc, char** argv) {
	parseOptions(argc, argv);

	int n;

	assert(argc == 2);
	n = atoi(argv[1]);

	engine.solve(new Queens(n));

	return 0;
}



