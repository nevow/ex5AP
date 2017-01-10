//
// the main of the server.
//

#include <iostream>
#include "managment/MainFlow.h"

int main(int argc, char *argv[]) {
    MainFlow *mf = new MainFlow(atoi(argv[1]));
    mf->input();
    delete (mf);
    return 0;
}