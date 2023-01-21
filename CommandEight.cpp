#include "CommandEight.h"

using namespace std;

/**
 * execute - emplmntation of command header.
*/
void CommandEight::execute() {
    close(dio->getClientSockfd());
}