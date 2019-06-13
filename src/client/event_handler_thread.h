#ifndef EVENT_HANDLER_THREAD_H
#define EVENT_HANDLER_THREAD_H

#include "../common/Thread.h"
#include "client_communicator.h"
#include "vista/ModelFacade.h"
#include "client/Event_handler.h"
#include "client/Message_sender.h"

class EventHandlerThread : public Thread {
private:
    bool continue_running;
    ModelFacade *model_facade;

public:
    EventHandlerThread(MessageSender&sender,
      ModelFacade *model_facade);
    ~EventHandlerThread() = default;
    virtual void run() override;
    void endExecution();
    EventHandler eventHandler;
};

#endif
