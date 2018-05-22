//
// Created by Pierre-Antoine on 19/05/2018.
//

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <algorithm>
#include "csp_variable.h"
#include <chrono>
#include <thread>
#include <cassert>
#include "algo/record.h"

csp::csp_variable::csp_variable(const std::size_t &s) : id(s), domain_start(0), valuated(false)
{
}

std::size_t csp::csp_variable::get_id() const
{
    return id;
}

std::size_t csp::csp_variable::get_value() const
{
    if (!is_valuated())
    {
        throw std::runtime_error("Empty Domain for variable " + std::to_string(get_id()) + " ");
    }
    return *(std::prev(domain.cend()));
}

bool csp::csp_variable::is_valuated() const
{

    return !has_empty_domain() && valuated;
}

void csp::csp_variable::restrict_first()
{
    if (domain_start == domain.size())
    {
        return;
    }
    domain_start += 1;
    if (has_empty_domain())
        valuated=false;
}

void csp::csp_variable::release_last()
{
    if (domain_start == 0)
    {
        return;
    }
    domain_start -= 1;
}

typename domain_t::iterator csp::csp_variable::get_free_iterator(const std::size_t &index)
{
    return std::find(std::next(domain.begin(), domain_start), domain.end(), index);
}

std::size_t csp::csp_variable::get_available_size() const
{
    return domain.size() - domain_start;
}

void csp::csp_variable::assign_first_element_as_value()
{
    if (has_empty_domain())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        throw std::runtime_error("Empty domain for variable " + std::to_string(get_id()));
    }
    std::iter_swap(std::next(domain.begin(),domain_start),std::prev(domain.end()));
    valuated = true;
}

void csp::csp_variable::release_all()
{
    domain_start = 0;
    valuated = false;
}

csp::csp_variable::csp_variable(const csp::csp_variable &other)
    : id(other.get_id()), domain_start(other.domain_start), valuated(other.valuated), constraint_count(0)
{

}

void csp::csp_variable::restrict(const std::size_t &index)
{

    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        //value is locked
        return;
    }
    auto d = std::next(domain.begin(), domain_start);
    if (it != d)
    {
        std::iter_swap(it, d);
    }
    restrict_first();
}

void csp::csp_variable::restrict_not(const std::size_t &index)
{
    auto it = get_free_iterator(index);
    auto correction = 1;
    if (it == domain.end())
    {
        correction = 0;
    }
    else
    {
        std::iter_swap(it, std::prev(domain.end()));
    }

    while (get_available_size() - correction)
    {
        restrict_first();
    }

}

bool csp::csp_variable::has_empty_domain() const
{
    return get_available_size() == 0;
}

typename domain_t::const_iterator csp::csp_variable::cbegin() const
{
    return std::next(domain.cbegin(), domain_start);
}

typename domain_t::const_iterator csp::csp_variable::cend() const
{
    return domain.cend();
}

void csp::csp_variable::reset()
{
    std::sort(domain.begin(), domain.end());
}

void csp::csp_variable::increment_constraint_count()
{
    constraint_count += 1;
}

std::size_t csp::csp_variable::get_constraint_count() const
{
    return constraint_count;
}

