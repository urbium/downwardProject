#ifndef SEARCH_ALGORITHMS_DELETE_RELAXED_SEARCH_H
#define SEARCH_ALGORITHMS_DELETE_RELAXED_SEARCH_H

#include "../open_list.h"
#include "../search_algorithm.h"
#include "../heuristics/additive_heuristic.h"

#include <memory>
#include <vector>

class Evaluator;
class PruningMethod;

namespace plugins {
class Feature;
}

namespace deleterelaxed_search {
class DeleteRelaxedSearch : public SearchAlgorithm {

    std::shared_ptr<Evaluator> del_rel_heuristic;


protected:
    virtual void initialize() override;
    virtual SearchStatus step() override;

public:
    explicit DeleteRelaxedSearch(const plugins::Options &opts);
    virtual ~DeleteRelaxedSearch() = default;

    virtual void print_statistics() const override;
};

extern void add_options_to_feature(plugins::Feature &feature);
}

#endif
