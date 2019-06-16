#define HOUR 3600000
#define MINUTE 60000
#define SECOND 1000
#define STEP_DURATION 40
#include "server_game_loop.h"
#include "modelo/Macros.h"
#include <chrono>

GameLoop ::GameLoop(World *world, Sender *sender,
    ProtectedDataBase *data_base) : encoder(data_base,sender) {
    this->time = 0;
    this->continue_running = true;
    this->world = world;
}

void GameLoop :: sendInfoPlayers() {
    if (!this->gameLoopStarted())
        this->encoder.sendPlayersName();
}

void GameLoop :: sendInfoRooms() {
    //if (!this->gameLoopStarted())
        //this->encoder.sendRoomsName(); no esta implementado todavia
}

void GameLoop :: sendInitialData() {
    this->encoder.sendPlayersPositions();
    this->encoder.sendPlayerIds();
    this->encoder.sendWorldSizes();
    this->encoder.sendMetalBlocks();
    this->encoder.sendButtons();    
    this->encoder.sendEnergyBalls();
    this->encoder.sendRocks();
    this->encoder.sendStoneBlocks();
    this->encoder.sendAcids();
    this->encoder.sendGates();
    this->encoder.sendBarriers();
    this->encoder.sendEndMap();
}

void GameLoop :: sendDynamicData() { //aca va todo lo que se mueve
    this->encoder.sendPlayersPositions();
    this->encoder.sendPortals();
    this->encoder.sendRocks();
    //this->encoder.sendEnergyBalls();
    this->encoder.sendGates(); 
    this->encoder.sendEmitters();
}

void GameLoop :: run() {
    this->sendInitialData();
    while (this->continue_running) {
        auto t_start = std::chrono::high_resolution_clock::now();
        world->Step();
        this->sendDynamicData();
        auto t_end = std::chrono::high_resolution_clock::now();
        int delta_time = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        int wait_time = STEP_DURATION-delta_time; //deberia chequear que es mayor a 0
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        this->time += STEP_DURATION;
    }
}

void GameLoop ::endGameLoop() {
    this->continue_running = false;
    this->encoder.sendEndGame();
}

//void GameLoop::resetGameLoop() {
//    this->encoder.sendEndLevel();
//    this->time = 0;
//    this->continue_running = false;
//    //reseteo el mundo
//}

std::string GameLoop ::getFormat(int time) {
    std::string time_s = std::to_string(time);
    if (time_s.size() == 1)
    {
        time_s = "0" + time_s;
    }
    return time_s;
}

std::string GameLoop ::getTime() {
    if (this->time == 0)
        return "NULL";
    int hours = int(this->time / HOUR);
    int minutes = int(this->time % HOUR / MINUTE);
    int seconds = int(this->time % HOUR % MINUTE / SECOND);
    return getFormat(hours) + ":" + getFormat(minutes) + ":" + getFormat(seconds);
}

bool GameLoop ::gameLoopStarted() {
    return this->time != 0;
}
