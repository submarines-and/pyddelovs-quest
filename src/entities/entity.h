#pragma once
#include <vector>
#include <map>
#include <bitset>
#include "components/component.h"

class Entity {
private:
    std::map<ComponentId, Component*> components;
    std::bitset<32> componentBitset;

public:
    bool active = true;

    void update()
    {
        for (auto& c : components)
            c.second->update();
    }

    void render()
    {
        for (auto& c : components)
            c.second->render();
    }

    void destroy() { active = false; }

    template <typename T, typename... TArgs>
    void addComponent(TArgs&&... mArgs)
    {
        T* component(new T(std::forward<TArgs>(mArgs)...));
        component->entity = this;

        components.emplace(getComponentId<T>(), component);
        componentBitset[getComponentId<T>()] = true;

        component->init();
    }

    template <typename T>
    bool hasComponent()
    {
        return componentBitset[getComponentId<T>()];
    }

    template <typename T>
    T& getComponent()
    {
        auto ptr(components[getComponentId<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class EntityManager {
public:
    std::vector<Entity*> entities;

    void update()
    {

        entities.erase(std::remove_if(
                           std::begin(entities),
                           std::end(entities),
                           [](const Entity* e) { return !e->active; }),
                       std::end(entities));

        for (auto e : entities) {
            e->update();
        }
    }

    void render()
    {
        for (auto e : entities) {
            e->render();
        }
    }

    Entity& addEntity()
    {
        Entity* e = new Entity();
        entities.push_back(e);
        return *e;
    }
};