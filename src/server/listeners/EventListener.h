//
// EventListener.
// abstract Class that has notify function.
//

#ifndef EX1_EVENTLISTENER_H
#define EX1_EVENTLISTENER_H


class EventListener {

public:
    ~EventListener() {};

    virtual void notify() = 0;
};


#endif //EX1_EVENTLISTENER_H
