//
// Connection.
//

#include "Connection.h"

extern int validateAllReceivedInfo;
extern int actionCount;
pthread_mutex_t global_validator_locker;

int Connection::getDcc() {
    return this->descriptor;
}

struct threadData {
    Connection *con;
    int *option;
};

void Connection::setOption(int *option) {
    threadData *td = new threadData;
    td->con = this;
    td->option = option;
    pthread_mutex_init(&global_validator_locker, 0);
    int status = pthread_create(&t, NULL, sendInfoToClient, td);
    if (status) {
        cout << "problem creating thread in connection" << endl;
    }
}


void *sendInfoToClient(void *data) {
    threadData *td = (threadData *) data;
    Connection *con = td->con;
    int *choice = td->option;
    int tempOption;
    char buffer[50];
    int count = 0;
    do {
        if (actionCount > count) {
            tempOption = *choice;
            if (tempOption == 9) {
                count++;
                con->send("9");
                con->receive(buffer, sizeof(buffer));
                pthread_mutex_lock(&global_validator_locker);
                validateAllReceivedInfo++;
                pthread_mutex_unlock(&global_validator_locker);
            } else if (tempOption == 7) {
                con->send("exit");
                con->receive(buffer, sizeof(buffer));
                pthread_mutex_lock(&global_validator_locker);
                validateAllReceivedInfo++;
                pthread_mutex_unlock(&global_validator_locker);
            } else {
                sleep(1);
            }
        } else {
            tempOption = 0;
            sleep(1);
        }
    } while (tempOption != 7);
    delete td;
    return NULL;
}

void Connection::send(string c) {
    sock->sendData(c, descriptor);
}

char *Connection::receive(char *c, int size) {
    sock->receiveData(c, size, descriptor);
}
