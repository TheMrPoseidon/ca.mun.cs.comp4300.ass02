#include "Game.hpp"

#include <iostream>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::init(const std::string &path)
{
    // TODO:
    // Read in config file

    // Set up default window parameters
    m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::run()
{
    // TODO:
    // Add pause functionality in here
    // Some systems shouldn't work (movement / input)
    // while some of them should work while paused (rendering)

    while (m_running)
    {
        m_entities.update();

        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();

        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{
    // TODO
}

void Game::spawnPlayer()
{
    // TODO
    // Finish adding all properties of the player with the correct values form the config

    auto entity = m_entities.addEntity("player");
    entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity->cInput = std::make_shared<CInput>();
    m_player = entity;
}

void Game::spawnEnemy()
{
    // TODO
    // make sure the enemy is spawned properly with there config variables
    // must be spawned completely within the bounds of the window

    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO
    // spawn small enemies at the location of the input enemy e
    // when we create the smaller enemy, we have to read the values of the original enemy
    //   number of small enemies is equal to the verticies
    //   same color and half the size of original
    //   worth double points of original

    /*
    int vertices = e->cShape->circle.getPointCount();

    for (int i = 0; i < vertices; i++)

    {
        auto smallEnemy = m_entities.addEntity("small");
        smallEnemy->cScore = std::make_shared<CScore>(e->cScore->score * 2);
    }
    */
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target)
{
    // TODO
    // implement the spawning of a bullet which travels towards target
    //   bullet speed given as scalar speed
    //   velocity must be set by using formular in notes
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO
    // Implement your own special weapon
}

void Game::sMovement()
{
    // TODO
    // Implement all entity movement in this function
    // should read the m_player->cInput comp to determine if entity is moving

    /*
    Vec2 playerVelocity;
    if(m_player->cInput->left)
    {
        playerVelocity.x -= m_playerConfig.S;
    }

    if(m_player->cInput->right)
    {
        playerVelocity.x += m_playerConfig.S;
    }
    m_player->cTransform->velocity = playerVelocity;
    */

    // sample movement speed update
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sLifespan()
{
    // TODO:
    // Implement all lifespan functionallity
    // for all entities
    //   if entity has no lifespan component
    //     skip
    //   if entity has 0 > current lifespan, substract 1
    //   if entity has lifespan and is alive
    //     scale alpha channel properly
    //   if entity has lifespan and its time is up
    //     destroy

    /* 
    for(auto & e : m_entities.getEntities())
    {
        if(!e->cLifespan) { continue; }
    }

    */
}

void Game::sCollision()
{
    // TODO:
    // Implement all proper collisions between entities
    // be sure to use the collision radius

    /*
    for (auto p: m_entities.getEntities("player"))
    {
        for (auto e : m_entities.getEntities("enemy"))
        {
            float dist = p->cTransform->pos.dist(e->cTransform->pos);
            //compare dist with p->cCollision->radius
        }
    }

    for (auto b: m_entities.getEntities("bullet"))
    {
        for (auto e : m_entities.getEntities("enemy"))
        {
            float dist = b->cTransform->pos.dist(e->cTransform->pos);
            //compare dist with b->cCollision->radius
        }
    }
    */
}

void Game::sEnemySpawner()
{
    // TODO:
    // Implement enemy spawning here
    // use m_currentFrame and m_lastEnemySpawnTime to determine
    // how long it has been since last enemy spawned
}

void Game::sRender()
{
    // TODO:
    // Change the code below to draw all entities
    // Sample drawing of the player below
    m_window.clear();

    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);
    m_window.draw(m_player->cShape->circle);
    m_window.display();
}

void Game::sUserInput()
{
    // TODO:
    // Handle User inputs
    //   Only setting the players input component
    //   No moving logic here
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Pressed\n";
                break;
            case sf::Keyboard::A:
                break;
            case sf::Keyboard::S:
                break;
            case sf::Keyboard::D:
                break;

            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Released\n";
                break;
            case sf::Keyboard::A:
                break;
            case sf::Keyboard::S:
                break;
            case sf::Keyboard::D:
                break;

            default:
                break;
            }
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                std::cout << "Left Mouse Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
                break;
            
            default:
                break;
            }
        }
    }
}