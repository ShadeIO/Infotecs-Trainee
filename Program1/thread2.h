#pragma once
#include <iostream>
#include "buffer.h"
#include "server.h"

class Thread2
{
    Buffer<std::string>& buffer;

public:
    Thread2(Buffer<std::string>& buffer);

    void sendData(Server& server);
};