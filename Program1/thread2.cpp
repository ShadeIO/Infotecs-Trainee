#include "thread2.h"
#include "DynamicLib.h"
#include "buffer.h"
#include "server.h"

#include <numeric>
#include <string>


Thread2::Thread2(Buffer<std::string>& buffer) :
    buffer(buffer) {}


void Thread2::sendData(Server& server)
{
    while (true) {
        std::string data = buffer.readData();
        std::cout << data << std::endl;
        int sum = sumString(std::move(data));
        server.send(std::move(std::to_string(sum)));
    }
}