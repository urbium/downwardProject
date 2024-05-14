#include "deleterelaxed_search.h"

#include "../evaluation_context.h"
#include "../evaluator.h"
#include "../open_list_factory.h"
#include "../pruning_method.h"

#include "../algorithms/ordered_set.h"
#include "../plugins/options.h"
#include "../task_utils/successor_generator.h"
#include "../utils/logging.h"
#include "../heuristics/additive_heuristic.h"


#include <cassert>
#include <cstdlib>
#include <memory>
#include <optional>
#include <set>

using namespace std;

namespace deleterelaxed_search {
DeleteRelaxedSearch::DeleteRelaxedSearch(const plugins::Options &opts)
    : SearchAlgorithm(opts),
        del_rel_heuristic(opts.get<shared_ptr<Evaluator>>("eval", nullptr))

    {   
}

void DeleteRelaxedSearch::initialize() {

}

void DeleteRelaxedSearch::print_statistics() const {
    statistics.print_detailed_statistics();
    search_space.print_statistics();
}

SearchStatus DeleteRelaxedSearch::step() {
    State initial_state = state_registry.get_initial_state();
    del_rel_heuristic.get()->notify_initial_state(initial_state);

    EvaluationContext eval_context(initial_state); 
    EvaluationResult er = del_rel_heuristic.get()->compute_result(eval_context);
    del_rel_heuristic.get()->report_value_for_initial_state(er);

    if (!er.is_infinite()){
        set_plan(Plan());
    }
    return SOLVED;
}

void add_options_to_feature(plugins::Feature &feature) {
    SearchAlgorithm::add_pruning_option(feature);
    SearchAlgorithm::add_options_to_feature(feature);
}
}
