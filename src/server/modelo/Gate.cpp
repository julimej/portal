#include "Gate.h"
#include "Macros.h"
#define UP 0
#define DOWN 1
#define GATE_LARGE 2.0
#define GATE_WIDTH 1.0

Gate::Gate(World &world, float x_pos, float y_pos) : world(world){
    Filter_Data data(OTHER_BITS);
    data.addMaskBits(CHELL_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(ROCK_PORTAL_BITS);
    data.addMaskBits(BARRIER_BITS);
    gate = world.addPolygon(x_pos,y_pos,GATE_WIDTH/2,GATE_LARGE/2,true,data);
    gate->SetUserData(this);
    name = "Gate";
    sizes = b2Vec2(GATE_WIDTH,GATE_LARGE);
    contact = false;
    live = true;
    door_is_open = false;
}

const std::string& Gate::getEntityName() {
    return name;
}

bool Gate::lives() {
    return true;
}

void Gate::die() {
    live = false;
}

void Gate::startContact(b2Vec2) {
    contact = true;
}

void Gate::endContact() {
    contact = false;
}

bool Gate::setTransform(Entity *) {
    return true;
}

void Gate::changePosition() {
    bool state = true;
    for (auto button: buttons) {
      if (button.first->getStatus() != button.second) state = false;
    }
    door_is_open = state;
    gate->SetActive(!door_is_open);
}

b2Vec2 Gate::getPosition() {
    if (!live) return b2Vec2(0,0);
    return gate->GetPosition();
}

b2Vec2 Gate::getSizes() {
    return sizes;
}

void Gate::addButton(Button *button, int pos) {
    if (pos == UP) buttons.insert({button,true});
    if (pos == DOWN) buttons.insert({button,false});
}

bool Gate::isOpen(){
    if (door_is_open) return 1;
    else return 0;
}

void Gate::win(){}
