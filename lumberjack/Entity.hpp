//
// Entity.hpp
// 2018-06-28
//
#pragma once

#include <iostream>
#include <vector>

#include "Action.hpp"

short last_used_id = 0;

class Entity
{
public:

    short id;
    std::vector<Action>behavior_list;

    Entity()
    {
        id = last_used_id++;
    }

    void execute_behavior_list()
    {
        for (auto& action : behavior_list)
        {
            if (action.func)
                action.func();
        }
    }

    virtual void iteration()
    {
        std::cout << "entity iteration" << std::endl;
        execute_behavior_list();
    }
};