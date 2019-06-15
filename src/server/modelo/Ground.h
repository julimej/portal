#ifndef TP4_GROUND_H
#define TP4_GROUND_H

#include "World.h"

class Ground : public Entity{
    b2Body* ground;
    b2Vec2 sizes;
    std::string name;
public:

    //Contructor de la clase Ground. Hay que pasarle la mitad de largo y la mitad de la altura
    Ground(World &world,float x_pos, float y_pos,  float width, float high);
    const std::string& getEntityName() override;
    void startContact(b2Vec2) override;
    void endContact() override;
    void die() override;
    bool lives() override;
    bool setTransform(Entity *) override;
    void changePosition() override;
    void startBouncing() override ;
    void win();
    b2Vec2 getSizes();
    b2Vec2 getPosition();
    float getAngle();
    ~Ground() = default;
};


#endif //TP4_GROUND_H
