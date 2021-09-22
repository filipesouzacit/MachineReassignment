#include <ctime>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <errno.h>

#include <utility>

// #define DUMP_ONLY

#include <chuffed/support/ParseUtils.h>
#include <chuffed/core/engine.h>
#include <chuffed/core/propagator.h>
#include <chuffed/branching/branching.h>
#include <chuffed/vars/modelling.h>
#include <chuffed/globals/mddglobals.h>
// #include <globals/circglobals.h>
#include <mdd/circ_fns.h>

#define HORIZON 28

template <class T>
T circ_gcc(T fff, vec< vec<T> >& xs, CardOp rel, const vec<int>& cards)
{
  assert(cards.size() > 0);

  vec< vec<T> > vals(cards.size());
  for(int ii = 0; ii < xs.size(); ii++)
  {
    assert(xs[ii].size() == cards.size());
    for(int jj = 0; jj < cards.size(); jj++)
    {
      vals[jj].push(xs[ii][jj]);
    }
  }

  T ret = card(fff, vals[0], rel, cards[0]);
  for(int jj = 1; jj < cards.size(); jj++)
  {
    assert(vals[jj].size() == xs.size());
    ret = ret&(card(fff,vals[jj],rel,cards[jj]));
  }
  return ret;
}

void mdd_gcc(vec<IntVar*>& vs, CardOp op, const vec<int>& cards)
{
  MDDTable tab(vs.size());
  
  vec< vec<MDD> > vars;
  for(int ii = 0; ii < vs.size(); ii++)
  {
    vars.push();
    for(int jj = 0; jj < cards.size(); jj++)
      vars.last().push(tab.vareq(ii,jj));
  }
  MDD ret(circ_gcc(tab.fff(), vars, op, cards));
  
  MDDOpts opts;
  addMDD(vs, ret, opts);
}

MDD multi_sequence(MDDTable& tab, int nDays, vec<int>& bmin, vec<int>& bmax, vec<int>& bsz)
{
  MDD seq = tab.ttt();

  for(int ii = 0; ii < bsz.size(); ii++)
  {
    vec<MDD> terms;
    for(int jj = 0; jj < nDays; jj++)
      terms.push(tab.vareq(jj, ii));
    seq = seq&(sequence(tab.fff(), terms, bmin[ii], bmax[ii], bsz[ii]));
  }
  return seq;
}

const char* shift_str[] = { "m", "a", "n", "r" };

class NurseSeq : public Problem {
public:
  class Opts
  {
    public:
      Opts()
        : model(1), gcard(false)
      { }
      
      int model;
      int gcard;
  };

  NurseSeq(Opts& opts) {
    FILE* out = stdout;

    gzFile file(gzdopen(0, "rb"));
    Parse::StreamBuffer in(file);
    
    Parse::skipWhitespace(in);
    while( *in == '#' )
        Parse::skipLine(in);

    nNurses = Parse::parseInt(in);
    nDays   = Parse::parseInt(in);
    nShifts = Parse::parseInt(in);
    assert(nShifts == 4);
    
    nDays = nDays > HORIZON ? HORIZON : nDays;

    vec< vec<int> > coverage;
    int maxcov = 0;
    for( int j = 0; j < nDays; j++ )
    {
        int cov = 0;
        coverage.push();
        for( int i = 0; i < nShifts; i++ )
        {
            coverage.last().push(parseInt(in));
            cov += coverage.last().last();
        }
        if (cov > maxcov)
            maxcov = cov;
    }
    nNurses = 1.5*maxcov;

    // Structure:
    // Shifts:   n1 n2 n3 ... nN  n1 n2 ...   nN
    //          [      Day 1   ][      ....        ]
    createVars(xs, nNurses*nDays, 0, nShifts-1, true); // Eager literals
    assert(xs.size() == nNurses*nDays);

//    for(int xi = 0; xi < xs.size(); xi++)
//      fprintf(out, "var x%d %d %d\n", xs[xi]->var_id, xs[xi]->getMin(), xs[xi]->getMax());
 
    // FIXME: Check search strategy
    // sat_sets_mid_order(&S,nNurses*nDays,nShifts,tempvars,false);
    //
    // Coverage
    vec<int> cov_props; // Coverage propagator ids.
    for( int j = 0; j < nDays; j++ )
    {
        if( !opts.gcard )
        {
            for( int i = 0; i < nShifts; i++ )
            {
                // Required coverage for the day.
                int req = coverage[j][i];
                if( req == 0 )
                    continue;

              vec<BoolView> rostered;
              for(int k = 0; k < nNurses; k++)
                rostered.push(xs[(nNurses*j) + k]->getLit(i, 1)); // [[ nurse_shift = i ]]
              bool_linear_decomp(rostered, IRT_GE, req);
#if 0
              fprintf(out, "bool_linear_ge(["); 
              bool first = true;
              for(int xi = 0; xi < nNurses; xi++)
              {
                fprintf(out, "%sx%d=%d", first ? "" : ", ", xs[nNurses*j + xi]->var_id, i);
                first = false;
              }
              fprintf(out, "], %d)\n", req);
#endif
            }
        } else {
            vec<int> lbs;
            for( int i = 0; i < nShifts; i++ )
            {
              lbs.push(coverage[j][i]);
            }
            
            // Allocation for the current shift.
            vec<IntVar*> sv;
            for(int ww = 0; ww < nNurses; ww++)
            {
              sv.push(xs[nNurses*j + ww]);
            }

            mdd_gcc(sv, CARD_GE, lbs);
        }
    }

      vec<int> bmin;
      vec<int> bmax;
      vec<int> bsz;
      vec<int> domvec;
      for( int i = 0; i < nDays; i++ )
          domvec.push(nShifts);
      
      // Spacing
      /*
      vec<dfa_trans> spaceDFA;
      // dfa_trans : { src, value, dest }
      static const dfa_trans nurseSpace[] =
          { {0,0,0},
            {0,1,1},
            {0,2,2},
            {0,3,0},
            {1,0,3},
            {1,1,1},
            {1,2,2},
            {1,3,0},
            {2,0,3},
            {2,1,3},
            {2,2,2},
            {2,3,0} };

      for( unsigned int i = 0; i < (sizeof(nurseSpace)/sizeof(dfa_trans)); i++ )
          spaceDFA.push(nurseSpace[i]);
      */
      vec< vec<int> > trans; 
      trans.push(); trans.last().push(1); trans.last().push(2); trans.last().push(3); trans.last().push(1);
      trans.push(); trans.last().push(0); trans.last().push(2); trans.last().push(3); trans.last().push(1);
      trans.push(); trans.last().push(0); trans.last().push(0); trans.last().push(3); trans.last().push(1);
      trans.push(); trans.last().push(0); trans.last().push(0); trans.last().push(0); trans.last().push(0);

      vec<int> accepts;
      accepts.push(1); accepts.push(2); accepts.push(3);

      int nStates = 4;
      int q0 = 1;

      MDDTable tab(nDays);

      _MDD _spacing = fd_regular(tab, nDays, nStates, trans, q0, accepts, false);
      MDD spacing(&tab, _spacing);
      /* /
      MDD spacing = tab.ttt();
      / */
      
      if( opts.model == 1 )
      {
          // Model 1
          
          // Day
          bmin.push(1);
          bmax.push(5);
          bsz.push(7);
          
          // Evening
          bmin.push(1);
          bmax.push(2);
          bsz.push(7);
          
          // Night 
          bmin.push(1);
          bmax.push(2);
          bsz.push(7);

          // Off
          bmin.push(2);
          bmax.push(5);
          bsz.push(7);
      } else {
          // Model 2
          
          // Day
          bmin.push(0);
          bmax.push(7);
          bsz.push(7);
          
          // Evening
          bmin.push(0);
          bmax.push(7);
          bsz.push(7);
          
          // Night 
          bmin.push(1);
          bmax.push(2);
          bsz.push(7);

          // Off
          bmin.push(1);
          bmax.push(2);
          bsz.push(5);
      }


      MDD seq(multi_sequence(tab, nDays, bmin, bmax, bsz));
      MDD seqprop(seq&spacing);
//      MDD seqprop(spacing);

      MDDOpts mopts;
      vec<IntVar*> inst;
      for( int i = 0; i < nNurses; i++ )
      {
          // Multi-sequence constraint
          inst.clear();
          for( int j = 0; j < nDays; j++ )
            inst.push(xs[j*nNurses + i]);
          
          addMDD(inst, seqprop, mopts);
      }
      fprintf(out, "satisfy\n");
  }
  
  void print(std::ostream& os) {
    for(int ii = 0; ii < nDays; ii++)
    {
      bool first = true;
      os << "[";
      for(int jj = 0; jj < nNurses; jj++)
      {
        os << (first ? "" : ", ");
        os << shift_str[xs[ii*nNurses + jj]->getVal()];
        first = false;
      }
      os << "]\n";
    }
  }

protected:
  int nNurses; 
  int nDays;   // Horizon
  int nShifts; // Shifts per day

  // Variables
  vec<IntVar*> xs;
};

static char* hasPrefix(char* str, const char* prefix) {
	int len = strlen(prefix);
	if (strncmp(str, prefix, len) == 0) return str + len;
	else return NULL;
}

int main(int argc, char** argv) {
    NurseSeq::Opts opts;

    // Problem-specific options
    int         i, j;
 	  const char* value;
    for (i = j = 0; i < argc; i++){
      if ((value = hasPrefix(argv[i], "-model="))) {
        opts.model = atoi(value);
      } else if(strcmp(argv[i], "-gcc") == 0) {
        opts.gcard = true;
      } else 
        argv[j++] = argv[i];
    }
    argc = j;

    parseOptions(argc, argv);

    Problem* p = new NurseSeq(opts);
#ifdef DUMP_ONLY
    return 0;
#endif
    engine.solve(p);

    return 0;
}
