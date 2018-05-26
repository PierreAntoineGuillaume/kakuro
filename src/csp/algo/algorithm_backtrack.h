//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "../algorithm.h"
#include "../heuristic.h"
namespace csp
{
    class algorithm_backtrack : public algorithm
    {
    public:
        solution run(variable_vector &variables,
                     const constraint_vector &constraints,
                     heuristic heuristic) const override;
        explicit algorithm_backtrack(bool stop_at_first_result = true);
    };
}

