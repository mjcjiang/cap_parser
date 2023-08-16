#include <iostream>
#include "cap_parser.h"

int main(int argc, char *argv[])
{
    CapParser parser("./files/nd_packet.cap");
    parser.processPackages();
    return 0;
}

