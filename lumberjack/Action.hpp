//
// Action.hpp
// 2018-06-28
//
#pragma once

#include <functional>


struct Action
{
    std::function<void()> func;
};