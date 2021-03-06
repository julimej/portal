#ifndef OBJECT_GATE_H
#define OBJECT_GATE_H
#include <string>
#include "object.h"

class ObjectGate : public Object {
private:
    Model *model;
    float x_pos;
    float y_pos;
    int id;

public:
    ObjectGate(Model *model,float x_pos,float y_pos, int id);
    ~ObjectGate() = default;
    void aggregate() override;
};

#endif