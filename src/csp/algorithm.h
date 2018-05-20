//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include <cstddef>
#include <memory>
#include <vector>

#include "csp_variable.h"
#include "csp_constraint.h"

namespace csp
{
    class algorithm
    {
    protected:
        void record_solution(std::vector<std::vector<std::size_t>> & affectations, const std::vector<csp::csp_variable> & variables) const;
    public:
        const std::string name;
        virtual std::vector<std::vector<size_t>> run(std::vector<csp::csp_variable> & variables, const std::vector<std::unique_ptr<csp::csp_constraint>>&constraints) const=0;
        explicit algorithm(std::string name);
    };
}

