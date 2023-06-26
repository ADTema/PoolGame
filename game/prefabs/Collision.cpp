#include "Collision.h"
#include <math.h>

#include "../../headers/GameObject.h"
#include "glm/gtx/norm.hpp"
#define SCALE 30

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
    body->SetLinearDamping(0.6f);
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

    bodyDef->angle = -wall->getRotation().z*(static_cast<float>(M_PI)/180);

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
    world.Step(0.02f, 10, 5);

    for (auto& m_hol : m_hols) {
        for (auto IBall = m_balls.begin(); IBall != m_balls.end(); IBall++) {
            if ((*IBall)) {
                if (glm::distance(m_hol->getPosition(),
                                  (*IBall)->getPosition()) < (Hole::RADIUS)) {
                    if ((*IBall)->number != 0 && (*IBall)->number != 8) {
                        world.DestroyBody((*IBall)->m_body);
                        (*IBall)->destroy();
                        IBall = m_balls.erase(IBall);
                    }
                }
            }
        }
    }
}
