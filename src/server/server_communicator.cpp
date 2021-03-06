#include "server_communicator.h"
#include "server_room_manager.h"
#include "../common/common_error.h"
#define ERROR_CODE "8"

Communicator :: Communicator(SocketConnect socket,RoomManager *room_manager,
  ColaProtegida *events,std::string id) : protocol(std::move(socket)) {
    this->room_manager = room_manager;
    this->events = events;
    this->continue_running = true;
    this->is_valid = true;
    this->id = id;
    this->room = nullptr;
    this->thread_s_runnning = false;
}

Communicator::~Communicator() { 
    if (this->thread_s_runnning) {
        this->thread_s.join();
        this->thread_s_runnning = false;
    }
}

void Communicator :: endExecution() {
    this->continue_running = false;
    this->protocol.closeProtocol();
    if (this->thread_s_runnning) {
        this->thread_s.join();
        this->thread_s_runnning = false;
    }
}

void Communicator :: sendMessage() {
    try {
        this->thread_s_runnning = true;
        while (this->continue_running) {
            std::string message = this->room_sender->getMessageFor(this->player_name);
            if (!this->continue_running) break;
            this->protocol << message;
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }  catch (...) {
        std::cout << "Error inesperado(?)" << std::endl;
    }
}

void Communicator :: receiveMessage() {
    std::string name(this->player_name + "," + "join");
    this->room->addMessageToSend(name);
    while (this->continue_running) {
        std::string message;
        this->protocol >> message;
        if (message == "m") {
            this->protocol.closeProtocol();
            this->continue_running = false;
            continue;
        }
        message = this->player_name + "," + message;
        this->room->addMessageToSend(message);
    }
}

bool Communicator :: setInitialData(std::string &game_room,
  std::string &player_name) {
    std::string mode;
    this->protocol >> mode;
    this->protocol >> game_room;
    this->protocol >> player_name;
    this->player_name = player_name;
    std::string message = game_room+","+player_name+","+mode+","+this->id;
    this->events->push(message);
    if (!this->room_manager->idIsValid(this->id)) return false;
    this->room = this->room_manager->getCreatedRoom(game_room);
    this->room_sender = this->room->getSender();
    return true;
}

bool Communicator :: communicatorValid() {
    if (this->room != nullptr) {
        std::string room_name = this->room->getName();
        if (!this->room_manager->roomSenderIsClose(room_name)) return false;
    }
    return this->is_valid;
}

void Communicator :: run() {
    try {
        std::string game_room;
        std::string player_name;
        int initial_data_is_ok = this->setInitialData(game_room,player_name);
        if (!initial_data_is_ok) {
            std::string m = ERROR_CODE",Error al crear/unirse a la sala\n";
            this->protocol << m;
            this->is_valid = false;
        }
        if (this->is_valid) {
            this->thread_s = std::thread(&Communicator::sendMessage, this);
            this->receiveMessage();
            std::string msg(this->player_name+","+"disconnect");
            if (this->room != nullptr) this->room->addMessageToSend(msg);
            this->is_valid = false;
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        this->is_valid = false;
    } catch (...) {
        std::cout << "Error: unknown" << std::endl;
    }
}
