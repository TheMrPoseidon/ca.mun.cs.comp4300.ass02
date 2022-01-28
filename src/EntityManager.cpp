#include "EntityManager.hpp"

EntityManager::EntityManager() : m_totalEntities(0)
{
}

void EntityManager::update()
{
    removeDeadEntities(m_entities);

    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }

    for (auto & a: m_entitiesToAdd)
    {
        m_entities.push_back(a);
        m_entityMap[a->tag()].push_back(a);
    }
    m_entitiesToAdd.clear();
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    //source: https://www.techiedelight.com/remove-elements-vector-inside-loop-cpp/
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if(!it->get()->isActive())
        {
            vec.erase(it--);
        }
    }
    
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
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
    return m_entityMap[tag];
}