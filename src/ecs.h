#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

/** Return next id? */
inline ComponentId getNewComponentTypeId()
{
    static ComponentId lastId = 0u;
    return lastId++;
}

/**

The template function getComponentID  is instantiated per component type. Each such template function instance is like a completely separate function that has a local static variable defined in it. We have as many local static ID variables as we have have different instantiations of the function template. Each of them is incremented only when the corresponding template function instantiation is called. Hope this helps, if not, i can code a small example.

always return the same value if the type name is the same for example getComponentID<Position> would always return 0 or something like that.

*/
template <typename T>
inline ComponentId getComponentTypeId() noexcept
{
    static ComponentId typeId = getNewComponentTypeId();
    return typeId;
}

/** Max components */
constexpr ComponentId maxComponents = 32;
constexpr Group maxGroups = 32;

/** ??? */
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

/** Base component class*/
class Component {
public:
    /** Owner*/
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}
};

/** Entity class consists of multiple components (behaviours, e.g. destructible) */
class Entity {

private:
    Manager& manager;
    /** Remove from game if false*/
    bool active = true;

    /** All active components for entity */
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;

    /** The Bitset stores true and false value, for example, if the position component is added it would set the value of the componentID inside bitset to true, then it would become much easier to get components and refactor their values. The array is used to store components. */
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager& man) : manager(man) {}

    void update()
    {
        for (auto& c : components)
            c->update();
    }

    void render()
    {
        for (auto& c : components)
            c->render();
    }

    /** Is this entity still active*/
    bool isActive() const { return active; }

    /** Call entity destroy function to remove from the game */
    void destroy() { active = false; }

    bool hasGroup(Group g)
    {
        return groupBitSet[g];
    }

    void addGroup(Group g);
    void deleteGroup(Group g)
    {
        groupBitSet[g] = false;
    }

    /** Is component still attached? */
    template <typename T>
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeId<T>()];
    }

    /** Returns reference to T (so it can be added to array)*/
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        // forward args
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;

        // std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        // always place new component in same position of array
        componentArray[getComponentTypeId<T>()] = c;
        componentBitSet[getComponentTypeId<T>()] = true;

        // init component
        // has refs to other components if we need them
        c->init();

        return *c;
    }

    template <typename T>
    T& getComponent()
    {
        // set ptr to position in component array
        auto ptr(componentArray[getComponentTypeId<T>()]);

        return *static_cast<T*>(ptr);
    }
};

/** Manager keeps track of all entities*/
class Manager {
private:
    /** All entities in manager*/
    std::vector<std::unique_ptr<Entity>> entities;

    /** All groups in manager */
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    /** Update all entities*/
    void update()
    {
        for (auto& e : entities)
            e->update();
    }

    /** Render all entities */
    void render()
    {
        for (auto& e : entities)
            e->render();
    }

    /** Remove dead entities*/
    void refresh()
    {
        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupedEntities[i]);

            // clear group
            v.erase(std::remove_if(
                        std::begin(v),
                        std::end(v),
                        [i](Entity* e) { return !e->isActive() || !e->hasGroup(i); }),
                    std::end(v));
        }

        // loop through all and delete non-active
        entities.erase(std::remove_if(
                           std::begin(entities),
                           std::end(entities),
                           [](const std::unique_ptr<Entity>& e) { return !e->isActive(); }),
                       std::end(entities));
    }

    /** Add new entity to group */
    void addToGroup(Entity* e, Group g)
    {
        groupedEntities[g].emplace_back(e);
    }

    std::vector<Entity*>& getGroup(Group g) { return groupedEntities[g]; }

    /** Add entity to world*/
    Entity& addEntity()
    {
        // ptr to entity
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};

        // add to list
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};