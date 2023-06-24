#include "Collision.h"

#include "../../headers/GameObject.h"
#include "glm/gtx/norm.hpp"

void fixCollision(Ball* ball1, Ball* ball2) {
    glm::vec3 delta = ball2->getPosition() - ball1->getPosition();
    float distance = glm::length(delta);
    float overlap = (Ball::RADIUS * 2) - distance;

    if (overlap > 0) {
        glm::vec3 collisionNormal = glm::normalize(delta);
        glm::vec3 collisionVector = collisionNormal * overlap * 0.5f;

        ball1->setPosition(ball1->getPosition() - collisionVector);
        ball2->setPosition(ball2->getPosition() + collisionVector);
    }
}

std::pair<bool, glm::vec3> Collision::checkCollision( Ball* ball1,  Ball* ball2) {

    auto ball1Pos = ball1->getPosition();
    auto ball2Pos = ball2->getPosition();


    float distance = glm::distance(ball1Pos, ball2Pos);
    float sumRadii = Ball::RADIUS * 2;

    if (distance <= sumRadii) {
        float collisionDistance = (sumRadii - distance) / 2.0f;
        auto collisionPoint = ball1Pos + collisionDistance * glm::normalize(ball2Pos - ball1Pos);
        return {true, collisionPoint};
    }

    return {false, glm::vec3(0)};
}
std::pair<bool, glm::vec3> Collision::checkCollision( Ball* ball, Rectangle* wall) {

    auto ballPos = ball->getPosition();
    auto wallPos = wall->getPosition();


    glm::vec3 closestPoint = glm::clamp(ballPos, wallPos - glm::vec3(wall->m_size / 2.0f, 0), wallPos + glm::vec3(wall->m_size / 2.0f,0));
    float distanceSquared = glm::distance2(ballPos, closestPoint);

    if (distanceSquared <= Ball::RADIUS * Ball::RADIUS) {
        glm::vec3 collisionNormal = glm::normalize(ballPos - closestPoint);
        auto collisionPoint = closestPoint + collisionNormal * static_cast<float>(Ball::RADIUS);
        return {true, collisionPoint};
    }

    return {false, glm::vec3(0)};
}
void Collision::addBall(Ball* ball) {
    m_balls.push_back(ball);
}
void Collision::addWall(Rectangle* wall) {
    m_walls.push_back(wall);
}
void Collision::fixedUpdate() {
    GameObject::fixedUpdate();
    auto temp1 = m_balls.end();
    temp1--;
    for (auto ball1 = m_balls.begin(); ball1 != temp1; ball1++){
        auto temp = ball1;
        temp++;
        for (auto ball2 = temp; ball2 != m_balls.end(); ball2++){
            auto collision = checkCollision(*ball1, *ball2);
            if(collision.first){
                //fixCollision((*ball1), (*ball2));
                auto normal1 = glm::normalize((*ball1)->getPosition() - collision.second);
                auto normal2 = glm::normalize((*ball2)->getPosition() - collision.second);

                if((*ball1)->velocity == glm::vec2(0)){
                    (*ball1)->velocity = normal1;
                }
                else{
                    (*ball1)->velocity = glm::reflect((*ball1)->velocity, glm::vec2(normal1));
                }
                if((*ball2)->velocity == glm::vec2(0)){
                    (*ball2)->velocity = normal2;
                }
                else{
                    (*ball2)->velocity = glm::reflect((*ball2)->velocity, glm::vec2(normal2));
                }

                auto force = ((*ball1)->force + (*ball2)->force) / 2;

                (*ball2)->force = force;
                (*ball1)->force = force;

                float overlap = Ball::RADIUS * 2 - glm::distance((*ball1)->getPosition(), (*ball2)->getPosition()) + 0.1f;
                if (overlap > 0) {
                    glm::vec3 correction = glm::normalize((*ball1)->getPosition() - (*ball2)->getPosition()) * overlap * 0.5f;
                    (*ball1)->setPosition((*ball1)->getPosition() + correction);
                    (*ball2)->setPosition((*ball2)->getPosition() - correction);
                }
            }
        }
    }

}
