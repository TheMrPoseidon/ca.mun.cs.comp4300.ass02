#include "EntityManager.hpp"

EntityManager::EntityManager() : m_totalEntities(0)
{
}

void EntityManager::update()
{
    // TODO:
    // add entities form m_entitiesToAdd to the proper location
    // add them to the vecotr of all entities
    // add them to the vecotr inside the map, with the tag as a key

    removeDeadEntities(m_entities);

    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    // TODO:
    // remove all dead entites form the vector
    // called by the update() function
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // TODO:
    // Implement this function so that entities are added tot he m_entititesToAdd vector here
    // Add them to the proper locations in the update() function

    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(entity);

    return entity;
}

const EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec & EntityManager::getEntities(const std::string & tag)
{
    // TODO:
    // return the correct vector form the map
    return m_entities;
}