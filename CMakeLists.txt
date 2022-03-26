cmake_minimum_required(VERSION 3.17)

project(ROAED2012)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# ------------- CP Profiler Integration -------------
include_directories(".")
include_directories(${CMAKE_BINARY_DIR})
#include_directories("/usr/local")
#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
#INCLUDE_DIRECTORIES("gecode/")
#FIND_PACKAGE(<gecode> )
# ------------- Main Chuffed Definition -------------

add_library(chuffed
        chuffed/vars/int-var.cpp
        chuffed/vars/int-var-el.cpp
        chuffed/vars/modelling.cpp
        chuffed/vars/int-var-sl.cpp
        chuffed/vars/bool-view.cpp
        chuffed/vars/int-var-ll.cpp
        chuffed/parallel/master.cpp
        chuffed/parallel/slave.cpp
        chuffed/ldsb/ldsb.cpp
        chuffed/globals/subcircuit.cpp
        chuffed/globals/mddglobals.cpp
        chuffed/globals/sym-break.cpp
        chuffed/globals/linear-bool.cpp
        chuffed/globals/linear-bool-decomp.cpp
        chuffed/globals/well-founded.cpp
        chuffed/globals/circuit.cpp
        chuffed/globals/minimum.cpp
        chuffed/globals/bool_arg_max.cpp
        chuffed/globals/alldiff.cpp
        chuffed/globals/template.cpp
        chuffed/globals/directives.cpp
        chuffed/globals/cumulative.cpp
        chuffed/globals/cumulativeCalendar.cpp
        chuffed/globals/disjunctive.cpp
        chuffed/globals/regular.cpp
        chuffed/globals/lex.cpp
        chuffed/globals/table.cpp
        chuffed/mdd/MDD.cpp
        chuffed/mdd/mdd_prop.cpp
        chuffed/mdd/mdd_to_lgraph.cpp
        chuffed/mdd/MurmurHash3.cpp
        chuffed/mdd/opcache.cpp
        chuffed/mdd/weighted_dfa.cpp
        chuffed/mdd/wmdd_prop.cpp
        chuffed/mip/mip.cpp
        chuffed/mip/recalc.cpp
        chuffed/mip/simplex.cpp
        chuffed/primitives/element.cpp
        chuffed/primitives/bool.cpp
        chuffed/primitives/linear.cpp
        chuffed/primitives/arithmetic.cpp
        chuffed/primitives/domain.cpp
        chuffed/primitives/binary.cpp
        chuffed/branching/branching.cpp
        chuffed/core/init.cpp
        chuffed/core/stats.cpp
        chuffed/core/engine.cpp
        chuffed/core/options.cpp
        chuffed/core/sat.cpp
        chuffed/core/conflict.cpp
        chuffed/vars/int-var.h
        chuffed/vars/vars.h
        chuffed/vars/int-var-sl.h
        chuffed/vars/int-var-ll.h
        chuffed/vars/int-view.h
        chuffed/vars/int-var-el.h
        chuffed/vars/modelling.h
        chuffed/vars/bool-view.h
        chuffed/parallel/parallel.h
        chuffed/support/BVec.h
        chuffed/support/ParseUtils.h
        chuffed/support/vec.h
        chuffed/support/misc.h
        chuffed/support/heap.h
        chuffed/support/sparse_set.h
        chuffed/ldsb/ldsb.h
        chuffed/globals/globals.h
        chuffed/globals/mddglobals.h
        chuffed/mdd/CFG.h
        chuffed/mdd/circ_fns.h
        chuffed/mdd/circutil.h
        chuffed/mdd/CYK.h
        chuffed/mdd/MDD.h
        chuffed/mdd/mdd_prop.h
        chuffed/mdd/mdd_to_lgraph.h
        chuffed/mdd/MurmurHash3.h
        chuffed/mdd/opcache.h
        chuffed/mdd/opts.h
        chuffed/mdd/sorters.h
        chuffed/mdd/weighted_dfa.h
        chuffed/mdd/wmdd_prop.h
        chuffed/mip/mip.h
        chuffed/mip/simplex.h
        chuffed/primitives/primitives.h
        chuffed/branching/branching.h
        chuffed/core/sat.h
        chuffed/core/engine.h
        chuffed/core/sat-types.h
        chuffed/core/options.h
        chuffed/core/propagator.h
        ${CHUFFED_PROFILER_SOURCES}
        class/SubProblem.cpp class/SubProblem.h)

# ------------- Chuffed Examples -------------
add_executable(ROAED2012 main1.cpp)

add_executable(main EXCLUDE_FROM_ALL main.cpp)
target_link_libraries(main chuffed ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(main gecode "/usr/local/lib")








