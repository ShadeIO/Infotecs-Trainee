#include <iostream>
#include <thread>

#include "server.h"
#include "buffer.h"
#include "thread1.h"
#include "thread2.h"

using namespace std;

int main()
{
    Buffer<std::string> buffer;

    Server server(8080);
    server.run();

    Thread1 input(buffer);
    Thread2 process(buffer);

    std::thread inputThread(&Thread1::dataInput, input);
    std::thread processingThread(&Thread2::sendData, process, std::ref(server));

    inputThread.join();
    processingThread.join();
}

