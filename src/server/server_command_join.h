#ifndef COMMAND_JOIN_H
#define COMMAND_JOIN_H
#include <string>
#include "server_command.h"

/* 
* Comando para unir un jugador a la partida
*/


class CommandJoin : public Command {
private:
    Model *model;
    std::string player;

public:
    CommandJoin(Model *model,std::string &player);
    ~CommandJoin() = default;
    void execute() override;
};

#endif