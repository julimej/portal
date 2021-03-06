#ifndef EVENT_HANDLER_THREAD_H
#define EVENT_HANDLER_THREAD_H

#include "../common/Thread.h"
#include "client_communicator.h"
#include "Event_handler.h"
#include "position_converter.h"

class EventHandlerThread : public Thread {
private:
    bool continue_running;
    EventHandler eventHandler;

public:
    EventHandlerThread(ClientCommunicator *client_communicator,
      PositionConverter &converter,LocalSceneLogic &local_scene_logic);
    ~EventHandlerThread() = default;
    virtual void run() override;
    void endExecution();
    void setSendDataLocally(bool send_locally);
};

#endif
