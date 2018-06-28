//
// main.cpp
// 2018-06-28
//
#include <iostream>
#include <memory>
#include <vector>

class Entity
{
public:
    Entity() {}

    virtual void iteration() 
    {
        std::cout << "entity iteration" << std::endl;
    }
};

class Tree: public Entity
{
public:

    int height = 0;

    void iteration()
    {
        std::cout << "tree iteration" << std::endl;
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

    for (int i = 0; i < 100; ++i)
    {
        global_iteration();
    }
    
    system("pause");
    return 0;
}

