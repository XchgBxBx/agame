//
// main.cpp
// 2018-06-28
//
#include <iostream>
#include <memory>

#include "Variables.h"
#include "Entity.hpp"

class Tree: public Entity
{
public:
    int height;
    int it_to_grow;

    Tree()
    {
        height = 2;
        it_to_grow = 0;

        Action count_to_grow{
            [this]()
            {
                it_to_grow++;
            }
        };

        Action grow{
            [this]()
            {
                if (it_to_grow == TREE_ITERATIONS_PER_GROW)
                {
                    height++;
                    it_to_grow = 0;
                }

                // reached max height, no need for actions
                if (height == TREE_MAX_HEIGHT)
                    behavior_list.clear();
            }
        };

        behavior_list.push_back(count_to_grow);
        behavior_list.push_back(grow);
    }

    void iteration()
    {
        std::cout << "tree id" << id << " | height: " << height << std::endl;
        execute_behavior_list();
    }
};


std::vector<Entity*> entities;
int iterations = 0;


void initialize()
{
    entities.push_back(new Entity());
    entities.push_back(new Entity());
    entities.push_back(new Tree());
}

void global_iteration()
{
    std::cout << "\n>> iteration " << iterations << std::endl;

    for (auto& entity : entities)
    {
        entity->iteration();
    }

    ++iterations;
}

int main(int argc, char **argv)
{
    initialize();

    for (int i = 0; i < MAX_ITERATIONS; ++i)
    {
        global_iteration();
    }
    
    system("pause");
    return 0;
}

