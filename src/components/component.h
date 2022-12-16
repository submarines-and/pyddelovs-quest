#pragma once
#include <cstddef>

using ComponentId = std::size_t;
class Entity;

/** Return next id? */
inline ComponentId generateComponentId()
{
    static ComponentId lastId = 0u;
    return lastId++;
}

/**

The template function getComponentID  is instantiated per component type. Each such template function instance is like a completely separate function that has a local static variable defined in it. We have as many local static ID variables as we have have different instantiations of the function template. Each of them is incremented only when the corresponding template function instantiation is called. Hope this helps, if not, i can code a small example.

always return the same value if the type name is the same for example getComponentID<Position> would always return 0 or something like that.

*/
template <typename T>
inline ComponentId getComponentId() noexcept
{
    static ComponentId typeId = generateComponentId();
    return typeId;
}

class Component {
public:
    Entity* entity;
    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
};