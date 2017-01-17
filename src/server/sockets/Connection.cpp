//
// Connection.
//

#include "Connection.h"

extern int validateAllReceivedInfo;
extern int actionCount;
pthread_mutex_t global_validator_locker;

/**
 * struct has Connection and pointer to the option that been choosen
 */
struct threadData {
    Connection *con;
    int *option;
};

/*
 * @param option
 */
void Connection::setOption(int *option) {
    // initialize threadData struct
    threadData *td = new threadData;
    td->con = this;
    td->option = option;
    pthread_mutex_init(&global_validator_locker, 0);               // lock
    // create a thread and apply on it sendInfoToClient
    int status = pthread_create(&t, NULL, sendInfoToClient, td);
    // if the thread doesn't Succeeded - report
    if (status) {
        cout << "problem creating thread in connection" << endl;
    }
}

/**
 * @param data is the struct with the arguments to the function
 * @return null
 */
void *sendInfoToClient(void *data) {
    threadData *td = (threadData *) data;
    Connection *con = td->con;
    int *choice = td->option;
    int tempOption;
    char buffer[50];
    int count = 0;

    do {
        // get to the loop only if it's the time to get in and it's your first time
        if (actionCount > count) {
            tempOption = *choice;
            // if the 9 chosen, send it and confirm it
            if (tempOption == 9) {
                count++;
                con->send("9");
                con->receive(buffer, sizeof(buffer));
                pthread_mutex_lock(&global_validator_locker);    // lock
                validateAllReceivedInfo++;
                pthread_mutex_unlock(&global_validator_locker);  // unlock
                // if 7 chosen, sent it and confirm it
            } else if (tempOption == 7) {
                con->send("exit");
                con->receive(buffer, sizeof(buffer));
                pthread_mutex_lock(&global_validator_locker);    // lock
                validateAllReceivedInfo++;
                pthread_mutex_unlock(&global_validator_locker);  // unlock
                // if not 9 or 7, do not do anything and sleep
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

/**
 * @param c id the string to send
 */
void Connection::send(string c) {
    sock->sendData(c, descriptor);
}

/**
 * @param c is the place of the string to receive,
 * @param size of the string
 * @return the string to receive
 */
char *Connection::receive(char *c, int size) {
    sock->receiveData(c, size, descriptor);
}
