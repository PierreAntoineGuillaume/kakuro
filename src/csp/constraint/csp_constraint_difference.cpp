//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "csp_constraint_difference.h"
csp::csp_constraint_difference::csp_constraint_difference(std::vector<csp::csp_variable *> &vector) : csp_constraint(
    vector)
{
    if (associated_variables.size()!=2){
        throw std::runtime_error("Not wrong number of variables");
    }
}
bool csp::csp_constraint_difference::run_constraint() const
{
    return associated_variables[0]->get_value() != associated_variables[1]->get_value();
}

csp::csp_variable * csp::csp_constraint_difference::run_fc_child(std::vector<csp::record> &history) const
{
    auto free = get_unvaluated_variable();
    for (auto i:associated_variables){
        if (i->is_valuated()){
            free->restrict(i->get_value(),history);
        }
    }
    return free;
}
