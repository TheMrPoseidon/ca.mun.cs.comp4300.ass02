#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <fmt/format.h>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::init(const std::string &path)
{
    std::ifstream fin(path);

    while (fin)
    {
        std::string type;
        fin >> type;

        if (type == "Window")
        {
            unsigned int width, height, fps, fullscreen;
            fin >> width >> height >> fps >> fullscreen;

            // Set up default window parameters
            m_window.create(sf::VideoMode(width, height), "Assignment 2");
            m_window.setFramerateLimit(fps);
        }

        else if (type == "Font")
        {
            std::string fontfile;
            uint16_t fontsize, r, g, b;
            fin >> fontfile >> fontsize >> r >> g >> b;

            if (!m_font.loadFromFile(fontfile))
            {
                m_running = false;
                exit(1);
            }

            m_text.setFont(m_font);
            m_text.setCharacterSize(fontsize);
            m_text.setFillColor(sf::Color(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)));
        }

        else if (type == "Player")
        {
            fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
        }

        else if (type == "Enemy")
        {
            fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
        }

        else if (type == "Bullet")
        {
            fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
        }
    }

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

        if (!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sLifespan();
        }
        sUserInput();
        sInterface();
        sRender();

        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{
    m_paused = paused;
}

void Game::spawnPlayer()
{
    auto size = m_window.getSize();
    auto center = Vec2(size.x / 2.0f, size.y / 2.0f);

    auto entity = m_entities.addEntity("player");
    entity->cTransform = std::make_shared<CTransform>(center, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
    entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
    entity->cInput = std::make_shared<CInput>();
    entity->cScore = std::make_shared<CScore>(0);
    m_player = entity;
}

void Game::spawnEnemy()
{
    // TODO
    // make sure the enemy is spawned properly with there config variables
    // must be spawned completely within the bounds of the window

    m_lastEnemySpawnTime = m_currentFrame;
    auto size = m_window.getSize();

    auto pos = Vec2();
    pos.x = m_enemyConfig.SR + rand() % (size.x - m_enemyConfig.SR + 1 - m_enemyConfig.SR);
    pos.y = m_enemyConfig.SR + rand() % (size.y - m_enemyConfig.SR + 1 - m_enemyConfig.SR);

    auto enemy = m_entities.addEntity("enemy");
    auto vertices = m_enemyConfig.VMIN + rand() % (m_enemyConfig.VMAX + 1 - m_enemyConfig.VMIN);
    auto angle = rand() % 360;;
    auto speed = m_enemyConfig.SMIN + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (m_enemyConfig.SMAX + 1 - m_enemyConfig.SMIN);
    auto velocity = Vec2(sin(angle) * speed, cos(angle) * speed);


    enemy->cTransform = std::make_shared<CTransform>(pos, velocity, Vec2(1.0, 1.0f), 0.0f);
    enemy->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(rand() % 255, rand() % 255, rand() % 255), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_playerConfig.OT);
    enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
    enemy->cScore = std::make_shared<CScore>(vertices*100);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    // TODO
    // spawn small enemies at the location of the input enemy entity
    // when we create the smaller enemy, we have to read the values of the original enemy
    //   number of small enemies is equal to the verticies
    //   same color and half the size of original
    //   worth double points of original

    
    int vertices = entity->cShape->circle.getPointCount();

    for (int i = 0; i < vertices; i++)

    {
        auto smallEnemy = m_entities.addEntity("small");
        smallEnemy->cScore = std::make_shared<CScore>(entity->cScore->score * 2);
    }
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

void Game::sInterface()
{
    m_text.setString(fmt::format("Score: {} ({})", m_score, m_paused ? "paused" : "running"));
    m_text.setPosition(0, 0);
}

void Game::sMovement()
{
    // TODO
    // Implement all entity movement in this function
    // should read the m_player->cInput comp to determine if entity is moving

    Vec2 playerVelocity;
    if (m_player->cInput->left)
    {
        playerVelocity.x -= m_playerConfig.S;
    }

    if (m_player->cInput->right)
    {
        playerVelocity.x += m_playerConfig.S;
    }

    if (m_player->cInput->up)
    {
        playerVelocity.y -= m_playerConfig.S;
    }

    if (m_player->cInput->down)
    {
        playerVelocity.y += m_playerConfig.S;
    }

    m_player->cTransform->velocity = playerVelocity;

    for(auto & enemy : m_entities.getEntities())
    {
        if(enemy->cTransform)
        {
            enemy->cTransform->pos += enemy->cTransform->velocity;
            enemy->cTransform->angle -= 1.0;
        }
    }
}

void Game::sLifespan()
{
    for (auto &e : m_entities.getEntities())
    {
        if (!e->cLifespan)
        {
            continue;
        }

        e->cLifespan->remaining -= 1;
        
        if (e->cLifespan->remaining <= 0)
        {
            e->destroy();
            continue;
        }

        int alpha = e->cLifespan->remaining / static_cast<float>(e->cLifespan->total) * 255;

        auto ocolor = e->cShape->circle.getOutlineColor();
        ocolor.a = alpha;
        e->cShape->circle.setOutlineColor(ocolor);

        auto fcolor = e->cShape->circle.getFillColor();
        fcolor.a = alpha;
        e->cShape->circle.setFillColor(fcolor);
    }
}

void Game::sCollision()
{
    auto windowBorder = m_window.getSize();
    for (auto & entity: m_entities.getEntities())
    {
        if(entity->cCollision && entity->cTransform)
        {
            if (entity->cTransform->pos.x - entity->cCollision->radius < 0 || entity->cTransform->pos.x + entity->cCollision->radius > windowBorder.x)
            {
                entity->cTransform->velocity.x *= -1;
            }

            if (entity->cTransform->pos.y - entity->cCollision->radius < 0 || entity->cTransform->pos.y + entity->cCollision->radius > windowBorder.y)
            {
                entity->cTransform->velocity.y *= -1;
            }
        }
    }
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
    if (m_currentFrame >= m_lastEnemySpawnTime + m_enemyConfig.SI)
    {
        spawnEnemy();
    }
}

void Game::sRender()
{
    m_window.clear();

    for(auto & e: m_entities.getEntities()) {
        if(e->cShape)
        {
            if(e->cTransform)
            {
                e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
            }
            e->cShape->circle.setRotation(e->cTransform->angle);
            m_window.draw(e->cShape->circle);
        }
    }

    // Draw Interface above
    m_window.draw(m_text);
    m_window.display();
}

void Game::sUserInput()
{
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
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->up = true;
                }
                break;
            case sf::Keyboard::A:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->left = true;
                }
                break;
            case sf::Keyboard::S:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->down = true;
                }
                break;
            case sf::Keyboard::D:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->right = true;
                }
                break;
            case sf::Keyboard::P:
                m_paused = !m_paused;
                break;
            case sf::Keyboard::Escape:
                m_running = false;
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
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->up = false;
                }
                break;
            case sf::Keyboard::A:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->left = false;
                }
                break;
            case sf::Keyboard::S:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->down = false;
                }
                break;
            case sf::Keyboard::D:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->right = false;
                }
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->shoot = true;
                }
                break;

            case sf::Mouse::Right:
                for (auto &e : m_entities.getEntities("player"))
                {
                    e->cInput->special = true;
                }
                break;

            default:
                break;
            }
        }
    }
}