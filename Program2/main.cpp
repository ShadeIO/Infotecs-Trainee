#include "connect.h"
#include <iostream>

int main()
{
    Connect client("127.0.0.1", 8080);
    client.run();
    return 0;
}

