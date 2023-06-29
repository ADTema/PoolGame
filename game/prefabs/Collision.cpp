#include "Collision.h"

#include <cmath>


#define SCALE 30

void Collision::start() {
    GameObject::start();

    tScore = new Score(0);
    tScore->setScore(0);
    tScore->setPosition({0, 320, 10});
    this->m_pScene->addObject(tScore);
}

void Collision::addBall(Ball* ball) {
    m_balls.push_back(ball);

    auto circle = new b2CircleShape();
    auto pos = ball->getPosition();
    circle->m_radius = static_cast<float>(Ball::RADIUS) / SCALE;

    auto bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(pos.x / SCALE, pos.y / SCALE);

    auto fixDef = new b2FixtureDef();
    fixDef->shape = circle;
    fixDef->friction = .0f;
    fixDef->density = .05f;
    fixDef->restitution = 1;

    b2Body* body = world.CreateBody(bodyDef);
    body->CreateFixture(fixDef);
    body->SetLinearDamping(0.75f);
    ball->m_body = body;
}
void Collision::addHole(Hole* hole) { m_hols.push_back((hole)); }
void Collision::addWall(Rectangle* wall) {
    m_walls.push_back(wall);

    auto box = new b2PolygonShape();
    auto pos = wall->getPosition();
    box->SetAsBox(wall->m_size.x / 2 / SCALE, wall->m_size.y / 2 / SCALE);

    auto bodyDef = new b2BodyDef();
    bodyDef->type = b2_staticBody;
    bodyDef->position.Set(pos.x / SCALE, pos.y / SCALE);

    bodyDef->angle = -wall->getRotation().z * (static_cast<float>(M_PI) / 180);

    auto fixDef = new b2FixtureDef();
    fixDef->shape = box;
    fixDef->friction = .0f;

    fixDef->restitution = 1.f;

    b2Body* body = world.CreateBody(bodyDef);
    body->CreateFixture(fixDef);
    wall->m_body = body;
}
void Collision::fixedUpdate() {
    GameObject::fixedUpdate();
    world.Step(0.02f, 10, 10);


        for (auto& m_hole : m_hols) {
            for (auto m_ball : m_balls) {
                if (m_ball) {
                    if (glm::distance(m_hole->getPosition(),
                                      m_ball->getPosition()) <
                        (Hole::RADIUS)) {
                        if (m_ball->number != 0 && m_ball->number != 8) {
                            score += m_hole->bonus * m_ball->number;

                            m_ball->m_body->SetLinearVelocity(b2Vec2(0, 0));
                            m_ball->setPosition(glm::vec3(-550 + 20*m_ball->number, -320, 0));
                            m_ball->m_body->SetTransform({(-500.f + 20*m_ball->number)/SCALE, -320.f/SCALE}, 0);
                            tScore->setScore(score);
                            break;
                        } else if (m_ball->number == 0) {
                            m_ball->setPosition(glm::vec3(0, 0, 5));
                            m_ball->m_body->SetTransform({0, 0}, 0);
                            m_ball->m_body->SetLinearVelocity(b2Vec2(0, 0));
                            score -= score/4;
                            tScore->setScore(score);
                            break;
                        } else if (m_ball->number == 8) {
                            m_ball->m_pScene->endGame();
                            break;
                        }
                    }
                }
            }
        }
    }

