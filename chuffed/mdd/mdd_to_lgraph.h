#ifndef __MDD_TO_LAYERGRAPH_H__
#define __MDD_TO_LAYERGRAPH_H__
#include "../mdd/MDD.h"
#include "../mdd/weighted_dfa.h"

EVLayerGraph::NodeID mdd_to_layergraph(EVLayerGraph& graph, MDD& r, vec<int>& costs);

#endif
