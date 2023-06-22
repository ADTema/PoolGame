#ifndef PONG_COMPONENT_H
#define PONG_COMPONENT_H

class GameObject;

class Component {
   public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
    GameObject *gameObject;
};

#endif  // PONG_COMPONENT_H
