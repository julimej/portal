#include "Portal.h"
#include "Macros.h"
#include "Metal_Block.h"
#include "Ground.h"
#include "Macros.h"

#define PI 3.14159265359
#define PORTAL_HIGH 1.0
#define PORTAL_WIDTH 0.4
#define PORTAL_WORLD_WIDTH 0.01
#define BALL 0.5

Portal::Portal(World& world, float x_pos, float y_pos): world(world) {
    Filter_Data data(ROCK_PORTAL_BITS);
    data.addMaskBits(OTHER_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(BALL_BITS);
    portal = world.addCircle(x_pos,y_pos,BALL,false,data,true);
    portal->SetGravityScale(ZERO);
    portal->SetUserData(this);
    contact = false;
    have_partner = false;
    name = "Portal";
    live = true;
    ball = true;
    send_it = false;
    position = portal->GetPosition();
    radius = BALL;
    sizes = b2Vec2(PORTAL_WIDTH,PORTAL_HIGH + 0.2);
    orientation = 0;
    normal = b2Vec2(0,0);

}

bool Portal::Move(float x_pos, float y_pos){
    b2Vec2 position = portal->GetPosition();

    b2Vec2 velocity(0,0);

    float angle = atan2((-y_pos) - position.y, x_pos - position.x);

    float force =  15.f;

    velocity = b2Vec2(force * cos(angle), force * sin(angle));

    portal->SetLinearVelocity(velocity);
    return true;
}

void Portal::changePosition() {
    if(!contact) return;
    if(contact){
        float x_subtraction = abs(body_pos.x) - abs(position.x);
        float y_subtraction = abs(body_pos.y) - abs(position.y);

        std::cout << "Resta: "<<x_subtraction<<"  "<<y_subtraction<<std::endl;

        b2Vec2 delta = b2Vec2(0,0);
        if(x_subtraction == 0 && angle == 90){

            orientation = 0;

            if(body_pos.y < position.y) normal = b2Vec2(0.f,1.f);
            if(body_pos.y > position.y) normal = b2Vec2(0.f,-1.f);
        } else if(y_subtraction == 0 && angle == 90){

            orientation = 2;

            if(body_pos.x < position.x) normal = b2Vec2(1.f,0.f);
            if(body_pos.x > position.x) normal = b2Vec2(-1.f,0.f);
        }else{
            if (angle == 45) {
                if (x_subtraction == 0 && y_subtraction == 0){
                    orientation = 3;
                    normal = b2Vec2(-1.f, 1.f);
                } else if (x_subtraction != 0 && y_subtraction == 0){
                    orientation = 2;
                    normal = b2Vec2(1.f,0.f);
                } else if (x_subtraction == 0 && y_subtraction != 0) {
                    orientation = 0;
                    normal = b2Vec2(0.f, -1.f);
                }
            } else if (angle == 135) {
                if (x_subtraction == 0 && y_subtraction == 0){
                    orientation = 1;
                    normal = b2Vec2(1.f, 1.f);
                } else if (x_subtraction != 0 && y_subtraction == 0){
                    orientation = 2;
                    normal = b2Vec2(-1.f,0.f);
                } else if (x_subtraction == 0 && y_subtraction != 0){
                    orientation = 0;
                    normal = b2Vec2(0.f,-1.f);
                }
            } else if (angle == 225) {
                if (x_subtraction == 0 && y_subtraction == 0){
                    orientation = 3;
                    normal = b2Vec2(1.f, -1.f);
                } else if (x_subtraction != 0 && y_subtraction == 0){
                    orientation = 2;
                    normal = b2Vec2(-1.f,0.f);
                } else if (x_subtraction == 0 && y_subtraction != 0){
                    orientation = 0;
                    normal = b2Vec2(0.f,1.f);
                }
            } else if (angle == 315) {
                if (x_subtraction == 0 && y_subtraction == 0){
                    orientation = 1;
                    normal = b2Vec2(-1.f, -1.f);
                } else if (x_subtraction != 0 && y_subtraction == 0){
                    orientation = 2;
                    normal = b2Vec2(1.f,0.f);
                } else if (x_subtraction == 0 && y_subtraction != 0){
                    orientation = 0;
                    normal = b2Vec2(0.f,-1.f);
                }
            }
        }

        Filter_Data data(ROCK_PORTAL_BITS);
        data.addMaskBits(OTHER_BITS);
        data.addMaskBits(CHELL_BITS);
        data.addMaskBits(ROCK_PORTAL_BITS);
        data.addMaskBits(BALL_BITS);
        if(orientation == 2){
            world.eraseBody(portal);
            portal = world.addPolygon(position.x,position.y,PORTAL_WORLD_WIDTH ,PORTAL_HIGH/2.f,true,data);
        }else if (orientation == 0) {
            world.eraseBody(portal);
            portal = world.addPolygon(position.x,position.y,PORTAL_HIGH/2.f,PORTAL_WORLD_WIDTH,true,data);
        } else{
            world.eraseBody(portal);
            portal = world.addPolygon(position.x - DELTA_POSITION + delta.x,position.y - DELTA_POSITION + delta.y,PORTAL_HIGH/2.f,PORTAL_WORLD_WIDTH,true,data);
            portal->SetTransform(portal->GetPosition(),angle * (PI/180));
        }
        portal->SetUserData(this);
        contact = false;
        ball = false;
        send_it = false;
        live = true;
    }
    portal->SetLinearVelocity(b2Vec2(0,0));
}

b2Vec2 Portal::getPosition(){
    if(!live) return b2Vec2(0,0);
    return portal->GetPosition();
}

bool Portal::isValid() {
    bool result = !ball;
    return result;
}

int Portal::getOrientation() {
    return orientation;
}

b2Vec2 Portal::getNormal() {
    return normal;
}

float Portal::getAngle() {
    if(!live) return 0;
    return portal->GetAngle();
}

void Portal::startContact(b2Vec2 pos) {
    contact = true;
    position = pos;
    portal->SetLinearVelocity(b2Vec2(0,0));
}

void Portal::endContact() {
    contact = false;
}

const std::string& Portal::getEntityName() {
    return name;
}

void Portal::die() {
    live = false;
}

bool Portal::lives(){
    return live;
}

bool Portal::setPartner(Portal *portal_partner) {
    partner = portal_partner;
    have_partner = true;
    return true;
}

Portal * Portal::getPartnerPortal() {
    if(!partner) return nullptr;
    if(partner->isABall()) return nullptr;
    return partner;
}

bool Portal::changePortalPosition(float x_pos, float y_pos) {
    if(!world.validPosition(x_pos,y_pos)) return false;
    if(live)world.eraseBody(portal);
    Filter_Data data(ROCK_PORTAL_BITS);
    data.addMaskBits(OTHER_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(BALL_BITS);
    portal = world.addCircle(x_pos,y_pos,BALL,false,data,true);
    portal->SetGravityScale(ZERO);
    portal->SetUserData(this);
    contact = false;
    ball = true;
    send_it = true;
    live = true;
    return true;
}

bool Portal::havePartner() {
    return have_partner;
}

float Portal::getradius() {
    return radius;
}

b2Vec2 Portal::getSizes() {
    return sizes;
}

bool Portal::setTransform(Entity * body){

    if(body->getEntityName() == "Metal_Block"){
        body_pos = dynamic_cast<Metal_Block *>(body)->getPosition();
        angle = dynamic_cast<Metal_Block *>(body)->getAngle();
        b2Vec2 body_sizes = dynamic_cast<Metal_Block *>(body)->getSizes();
        sizes = b2Vec2(PORTAL_WIDTH * body_sizes.x, PORTAL_HIGH);
    }

    if(body->getEntityName() == "Ground"){
        body_pos = b2Vec2(portal->GetPosition().x,dynamic_cast<Ground *>(body)->getPosition().y);
        angle = 90;
    }
    return true;
}


void Portal::win(){}

bool Portal::isABall() {
    return ball;
}