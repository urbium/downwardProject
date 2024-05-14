#include "deleterelaxed_search.h"
#include "search_common.h"

#include "../plugins/plugin.h"

using namespace std;

namespace plugin_deleterelaxed {
class DeleteRelaxedSearchFeature : public plugins::TypedFeature<SearchAlgorithm, deleterelaxed_search::DeleteRelaxedSearch> {
public:
    DeleteRelaxedSearchFeature() : TypedFeature("Evaluator") {
        document_title("Returns Evaluator value for initial state");
        document_synopsis("...");

        add_option<shared_ptr<Evaluator>>("eval", "evaluator for h-value");
        deleterelaxed_search::add_options_to_feature(*this);

    }

    virtual shared_ptr<deleterelaxed_search::DeleteRelaxedSearch> create_component(const plugins::Options &options, const utils::Context &) const override {
        plugins::Options options_copy(options);
        auto temp = search_common::create_astar_open_list_factory_and_f_eval(options);
        options_copy.set("open", temp.first);
        options_copy.set("f_eval", temp.second);
        options_copy.set("reopen_closed", true);
        vector<shared_ptr<Evaluator>> preferred_list;
        options_copy.set("preferred", preferred_list);
        return make_shared<deleterelaxed_search::DeleteRelaxedSearch>(options_copy);
    }
};

static plugins::FeaturePlugin<DeleteRelaxedSearchFeature> _plugin;
}
