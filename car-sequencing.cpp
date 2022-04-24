/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Mikael Lagerkvist <lagerkvist@gecode.org>
 *
 *  Copyright:
 *     Mikael Lagerkvist, 2009
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <iomanip>

using namespace Gecode;

// Problems
namespace {
  // Problem data
  extern const int* problems[];
  // Number of problems
  extern const unsigned int n_problems;
}

namespace {
  /**
   * \brief %Options for car sequencing problems
   *
   * \relates CarSequence
   */
  class CarOptions : public SizeOptions {
  private:
    /// Max slack parameter
    Driver::UnsignedIntOption _maxstall;

  public:
    /// Initialize options for example with name \a s
    CarOptions(const char* s)
      : SizeOptions(s),
        _maxstall("maxstall", "Maximum numbere of stalls", 30)
    {
      // Add options
      add(_maxstall);
    }
    /// Parse options from arguments \a argv (number is \a argc)
    void parse(int& argc, char* argv[]) {
      SizeOptions::parse(argc,argv);
    }
    /// Get max stalls
    int maxstall(void) const { return _maxstall.value(); }
  };


  /**
   * \brief Propagator that pushes all occurences of a value to the end.
   *
   * This propagator uses a variable array \f$x=\langle
   * x_1,x_2,\ldots,x_n\rangle\f$, a variable \f$y\f$, and a value
   * \f$val\f$. It It makes sure that the last \f$y\f$ variables of
   * \f$x\f$ are assigned the value, and that the value does not
   * appear in the rest of the array. Furthermore, the constriant
   * ensure that \$fval\$f isnot adjacent to \$fval-1\$f.
   *
   * Since the propagator is custom-made for the car sequencing
   * example, it relies on the fact that the value will be equal to
   * the upper bound to speed up computation. For example, it can
   * safely rely on only subscribing to bound events.
   *
   * \relates CarSequence
   */
  template <class View>
  class PushToEnd : public NaryOnePropagator<View,Int::PC_INT_BND> {
  protected:
    using NaryOnePropagator<View,Int::PC_INT_BND>::x;
    using NaryOnePropagator<View,Int::PC_INT_BND>::y;
    int val;

    /// Constructor for cloning \a p
    PushToEnd(Space& home, PushToEnd& p);
    /// Constructor for posting
    PushToEnd(Space& home, ViewArray<View>& x0, View y0, int val0);
  public:
    /// Constructor for rewriting \a p during cloning
    PushToEnd(Space& home, Propagator& p,
              ViewArray<View>& x0, View y0, int val0);
    /// Copy propagator during cloning
    virtual Actor* copy(Space& home);
    /// Perform propagation
    virtual ExecStatus propagate(Space& home, const ModEventDelta& med);
    /// Post propagator
    static  ExecStatus post(Space& home,
                            ViewArray<View>& x0, View y0, int val0);
  };

  template <class View>
  inline
  PushToEnd<View>::PushToEnd(Space& home,
                             ViewArray<View>& x0, View y0, int val0)
    : NaryOnePropagator<View,Int::PC_INT_BND>(home,x0,y0), val(val0) {}

  template <class View>
  ExecStatus
  PushToEnd<View>::post(Space& home,
                        ViewArray<View>& x0, View y0, int val0) {
    (void) new (home) PushToEnd<View>(home,x0,y0,val0);
    return ES_OK;
  }

  template <class View>
  inline
  PushToEnd<View>::PushToEnd(Space& home, PushToEnd<View>& p)
    : NaryOnePropagator<View,Int::PC_INT_BND>(home,p), val(p.val) {}

  template <class View>
  inline
  PushToEnd<View>::PushToEnd(Space& home, Propagator& p,
                             ViewArray<View>& x0, View y0, int val0)
  : NaryOnePropagator<View,Int::PC_INT_BND>(home,p,x0,y0), val(val0) {}

  template <class View>
  Actor*
  PushToEnd<View>::copy(Space& home) {
    return new (home) PushToEnd<View>(home,*this);
  }

  template <class View>
  ExecStatus
  PushToEnd<View>::propagate(Space& home, const ModEventDelta&) {
    // Find number of required positions
    int min = 0;
    for (int i = x.size(); i-- && x[i].min() >= val-1; ) {
      ++min;
    }
    // Find number of possible positions
    int max = 0;
    {
      int i = x.size();
      while (i--) {
        if (x[i].max() != val) break;
        ++max;
        if (max >= y.max()) break;
      }
      // No variables later than max can have value val
      while (i--) {
        GECODE_ME_CHECK(x[i].le(home, val));
      }
    }

    // Constrain y to be in {min..max}
    GECODE_ME_CHECK(y.gq(home, min));
    GECODE_ME_CHECK(y.lq(home, max));

    // At least the y.min() last values have value val
    for (int i = 0, pos = x.size()-1; i < y.min(); ++i, --pos) {
      GECODE_ME_CHECK(x[pos].eq(home, val));
    }

    return y.assigned() ? home.ES_SUBSUMED(*this) : ES_FIX;
  }

  /** \brief Post PushToEnd propagator.
   */
  void pushtoend(Space& home, IntVarArgs x, IntVar y, int val) {
    ViewArray<Int::IntView> vx(home, x);
    Int::IntView vy(y);
    GECODE_ES_FAIL(PushToEnd<Int::IntView>::post(home, vx, vy, val));
  }

}


/**
 * \brief %Example: Car sequencing
 *
 * See problem 1 at http://www.csplib.org/.
 *
 * This model uses extra stall-slots instead of violations, as proposed
 * in "Combining Forces to Solve the Car Sequencing Problem", Perron
 * and Shaw, CPAIOR 2004.
 *
 * \ingroup Example
 */
class CarSequencing : public Script {
public:
  /// Branching variants
  enum {
    BRANCH_INORDER,  ///< Branch from left to right
    BRANCH_MIDDLE  ///< Branch from middle out
  };
  /// Propagation variants
  enum {
    PROP_REGULAR,  ///< Use regular constraints
    PROP_CUSTOM    ///< Use custom constraint
  };
protected:
  /// Problem number
  const int problem;
  /// Number of cars
  const int ncars;
  /// Number of options
  const int noptions;
  /// Number of classes
  const int nclasses;
  /// Maximum number of stalls
  const int maxstall;
  /// Stall number
  const int stallval;
  /// End number
  const int endval;
  /// Number of stalls (cost to minimize)
  IntVar nstall;
  /// Number of end markers
  IntVar nend;
  /// Sequence of cars produced
  IntVarArray s;
public:
  /// Initial model
  CarSequencing(const CarOptions& opt)
    : Script(opt),
      problem(opt.size()),
      ncars(problems[problem][0]),
      noptions(problems[problem][1]),
      nclasses(problems[problem][2]),
      maxstall(opt.maxstall()),
      stallval(nclasses),
      endval(nclasses+1),
      nstall(*this, 0, maxstall),
      nend(*this, 0, maxstall),
      s(*this, ncars+maxstall, 0, nclasses+1)
  {
    // Read problem
    const int* probit = problems[problem] + 3;

    // Sequence requirements for the options.
    IntArgs max(noptions), block(noptions);
    for (int i = 0; i < noptions; ++i ) {
      max[i] = *probit++;
    }
    for (int i = 0; i < noptions; ++i ) {
      block[i] = *probit++;
    }
    // Number of cars per class
    IntArgs ncc(nclasses);
    // What classes require an option
    IntSetArgs classes(noptions);
    int** cdata = new int*[noptions];
    for (int i = noptions; i--; ) cdata[i] = new int[nclasses];
    int* n = new int[noptions];
    for (int i = noptions; i--; ) n[i] = 0;
    // Read data
    for (int c = 0; c < nclasses; ++c) {
      probit++;
      ncc[c] = *probit++;
      for (int o = 0; o < noptions; ++o) {
        if (*probit++) {
          cdata[o][n[o]++] = c;
        }
      }
    }
    // Transfer specification data to int-sets
    for (int o = noptions; o--; ) {
      classes[o] = IntSet(cdata[o], n[o]);
      delete [] cdata[o];
    }
    delete [] cdata;
    delete [] n;

    // Count the cars
    {
      IntSetArgs c(nclasses+2);
      for (int i = nclasses; i--; ) {
        c[i] = IntSet(ncc[i], ncc[i]);
      }
      c[stallval] = IntSet(0, maxstall);
      c[  endval] = IntSet(0, maxstall);
      count(*this, s, c);
    }

    // Count number of end and stalls
    count(*this, s, stallval, IRT_EQ, nstall);
    count(*this, s,   endval, IRT_EQ,   nend);
    rel(*this, nstall+nend == maxstall);

    // Make sure nothing is overloaded
    IntSet one(1, 1);
    for (int o = noptions; o--; ) {
      // sb[i] reflects if car s[i] has option o
      BoolVarArgs sb(s.size());
      for (int i = s.size(); i--; ) {
        BoolVar b(*this, 0, 1);
        dom(*this, s[i], classes[o], b);
        sb[i] = b;
      }aaa
      sequence(*this, sb, one, block[o], 0, max[o]);
    }

    // End-markers located at end only
    switch (opt.propagation()) {
    case PROP_REGULAR: {
      IntArgs notend(nclasses), notstallend(nclasses+1);
      for (int i = nclasses; i--; ) {
        notend[i] = i;
        notstallend[i] = i;
      }
      notstallend[nclasses] = stallval;
      REG r = *REG(notend) + REG(notstallend) + *REG(endval);
      extensional(*this, s, r);
      for (int pos = s.size()-1, i = 0; i < maxstall; ++i, --pos) {
        rel(*this, (nend > i) >> (s[pos]==endval));
      }
    } break;
    case PROP_CUSTOM: {
      pushtoend(*this, s, nend, endval);
    } break;
    }


    // Branching
    switch (opt.branching()) {
    case BRANCH_INORDER:
      branch(*this, s, INT_VAR_NONE(), INT_VAL_MIN());
      break;
    case BRANCH_MIDDLE: {
      IntVarArgs m(s.size());
      int mid = s.size() / 2;
      int pos = 0;
      m[pos++] = s[mid];
      for (int i = 1; i <= m.size()/2; ++i) {
        if (mid-i >= 0)
          m[pos++] = s[mid-i];
        if (mid+i < s.size())
          m[pos++] = s[mid+i];
      }
      assert(pos == m.size());
      branch(*this, m, INT_VAR_NONE(), INT_VAL_MIN());
      break;
    }
    }
  }

  /// Return cost
  virtual void constrain(const Space& _best) {
    const CarSequencing& best = static_cast<const CarSequencing&>(_best);
    rel(*this, nstall, IRT_LE, best.nstall.val());
  }

  /// Print solution
  virtual void
  print(std::ostream& os) const {
    int width = nclasses > 9 ? 2 : 1;
    const char* space = nclasses > 9 ? " " : "";
    os << "Stall slots=" << nstall
       << ", End slots=" << nend << std::endl;
    int i = 0;
    for (; i < s.size(); ++i) {
      if (s[i].assigned()) {
        int v = s[i].val();
        if (v == endval) break;
        if (v == stallval) os << space << "_ ";
        else               os << std::setw(width) << v << " ";
      } else {
        os << space << "? ";
      }
      if ((i+1)%20 == 0) os << std::endl;
    }
    if (i%20)
      os << std::endl;
    os << std::endl;
  }

  /// Constructor for cloning \a s
  CarSequencing(CarSequencing& cs)
    : Script(cs),
      problem(cs.problem),
      ncars(cs.ncars),
      noptions(cs.noptions),
      nclasses(cs.nclasses),
      maxstall(cs.maxstall),
      stallval(cs.stallval),
      endval(cs.endval)
  {
    nstall.update(*this, cs.nstall);
    nend.update(*this, cs.nend);
    s.update(*this, cs.s);
  }
  /// Copy during cloning
  virtual Space*
  copy(void) {
    return new CarSequencing(*this);
  }
};

/** \brief Main-function
 *  \relates CarSequencing
 */
int
main(int argc, char* argv[]) {
  CarOptions opt("CarSequencing");
  opt.solutions(0);
  opt.size(0);
  opt.branching(CarSequencing::BRANCH_INORDER);
  opt.branching(CarSequencing::BRANCH_INORDER,  "inorder");
  opt.branching(CarSequencing::BRANCH_MIDDLE, "middle");
  opt.propagation(CarSequencing::PROP_CUSTOM);
  opt.propagation(CarSequencing::PROP_REGULAR, "regular");
  opt.propagation(CarSequencing::PROP_CUSTOM,  "custom");
  opt.parse(argc,argv);
  if (opt.size() >= n_problems) {
    std::cerr << "Error: size must be between 0 and "
              << n_problems-1 << std::endl;
    return 1;
  }

  Script::run<CarSequencing,BAB,CarOptions>(opt);
  return 0;
}


namespace {
  /// Problems from CSPLib
  // ----------------------------------
  //  Problem 19/71,  (Regin & Puget   // 4)
  // ----------------------------------
  const int p5[] = {
    100, 5, 23,
    1, 2, 1, 2, 1,
    2, 3, 3, 5, 5,
    0, 2, 0, 0, 0, 1, 1,
    1, 2, 0, 0, 1, 0, 1,
    2, 5, 0, 1, 1, 1, 0,
    3, 4, 0, 0, 0, 1, 0,
    4, 4, 0, 1, 0, 1, 0,
    5, 1, 1, 1, 0, 0, 1,
    6, 3, 1, 1, 1, 0, 1,
    7, 4, 0, 0, 1, 0, 0,
    8, 19, 0, 1, 0, 0, 0,
    9, 7, 1, 1, 0, 1, 0,
    10, 10, 1, 0, 0, 0, 0,
    11, 1, 0, 0, 1, 1, 0,
    12, 5, 1, 1, 1, 1, 0,
    13, 2, 1, 0, 1, 1, 0,
    14, 6, 1, 1, 0, 0, 0,
    15, 4, 1, 1, 1, 0, 0,
    16, 8, 1, 0, 0, 1, 0,
    17, 1, 1, 0, 0, 0, 1,
    18, 4, 0, 1, 1, 0, 0,
    19, 2, 0, 0, 0, 0, 1,
    20, 4, 0, 1, 0, 0, 1,
    21, 1, 1, 1, 0, 1, 1,
    22, 1, 0, 1, 1, 0, 1,
  };
};

// STATISTICS: example-any

