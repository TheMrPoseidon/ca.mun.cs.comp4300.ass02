#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "EntityManager.hpp"

struct PlayerConfig
{
    //  ShapeRadius, CollisionRadius
    int SR, CR;
    // FillColor(R,G,B)
    int FR, FG, FB;
    // OutlineColor(R,G,B)
    int OR, OG, OB;
    // OutlineThickness, ShapeVertices
    int OT, V;
    // Speed
    float S;
};
struct EnemyConfig
{
    //  ShapeRadius, CollisionRadius
    int SR, CR;
    // OutlineColor(R,G,B)
    int OR, OG, OB;
    // OutlineThickness, ShapeVerticesMin, ShapeVerticesMax, LifespanOfSmall, SpawnInterval
    int OT, VMIN, VMAX, L, SI;
    // SpeedMin, SpeedMax
    float SMIN, SMAX;
};
struct BulletConfig
{
    //  ShapeRadius, CollisionRadius
    int SR, CR;
    // FillColor(R,G,B)
    int FR, FG, FB;
    // OutlineColor(R,G,B)
    int OR, OG, OB;
    // OutlineThickness, ShapeVertices, Lifespan
    int OT, V, L;
    // Speed
    float S;
};

class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string &config);
    void setPaused(bool paused);

    // Systems
    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();
    void sInterface();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string &config);

    void run();
};