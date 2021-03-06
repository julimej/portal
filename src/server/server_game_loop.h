#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#define PLAYER_CODE 1
#define BLOCK_CODE 2
#define GATE_CODE 3
#define BUTTON_CODE 4
#define ACID_CODE 5
#define PORTAL_CODE 6
#define POWERBALL_CODE 7
#define ROCK_CODE 8
#define ENERGY_BARRIER_CODE 9

#include <iostream>
#include <string>
#include <time.h>
#include <map>
#include "../common/Thread.h"
#include "server_sender.h"
#include "Protected_Data_Base.h"
#include "Encoder.h"


class GameLoop : public Thread {
    private:
        int time;
        bool continue_running;
        std::string getFormat(int time);
        World* world;
        Encoder encoder;
        ProtectedDataBase *data_base;
        int next_scenario;
        int number_of_levels;

        //Devuelve un booleano indicando si el nivel
        //fue completado
        bool checkLevelComplete();

        //Espera la proxima accion del cliente para luego
        //indicar como debe continuar el gameloop
        void waitNextAction(int level_number);

    public:
        GameLoop(World* world,Sender *sender,ProtectedDataBase *data_base);
        ~GameLoop() = default;
        std::string getTime();
        void endGameLoop();
        bool gameLoopStarted();
        bool continueRunning();
        void setNumberOfLevels(int n);
        void run() override;
        void step();
        void sendInitialData();
        void sendDynamicData();
        void resetGameLoop();
        void sendInfoPlayers();
        void setNextScenario(int action,World* world=nullptr);
};

#endif
