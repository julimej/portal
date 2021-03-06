#include "Stone_Block.h"
#include "Macros.h"


Stone_Block::Stone_Block(World &world,float x_pos, float y_pos,float size){
    Filter_Data data(OTHER_BITS);
    data.addMaskBits(CHELL_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(ROCK_PORTAL_BITS);
    data.addMaskBits(BALL_BITS);
    block = world.addBox(x_pos,y_pos,size/2.f,true,data);
    block->SetUserData(this);
    angle = 90;
    name = "Stone_Block";
    position = block->GetPosition();
    sizes = b2Vec2(size,size);
}

Stone_Block::Stone_Block(World &world,float x_pos, float y_pos,float size,int angle){
    Filter_Data data(OTHER_BITS);
    data.addMaskBits(CHELL_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(ROCK_PORTAL_BITS);
    data.addMaskBits(BALL_BITS);
    block = world.addTriangle(x_pos,y_pos,size,angle,true,data);
    position = b2Vec2(x_pos + DELTA_POSITION, y_pos + DELTA_POSITION);
    block->SetUserData(this);
    this->angle = angle;
    name = "Stone_Block";
    sizes = b2Vec2(size,size);
}

b2Vec2 Stone_Block::getPosition() {
    return position;
}

int Stone_Block::getAngle() {
    return angle;
}

b2Vec2 Stone_Block::getSizes() {
    return sizes;
}

const std::string& Stone_Block::getEntityName() {
    return name;
}

bool Stone_Block::lives() {
    return true;
}

void Stone_Block::die() {}

void Stone_Block::startContact(b2Vec2) {}

void Stone_Block::endContact() {}

bool Stone_Block::setTransform(Entity *) {
    return true;
}

void Stone_Block::changePosition() {}

void Stone_Block::win(){}