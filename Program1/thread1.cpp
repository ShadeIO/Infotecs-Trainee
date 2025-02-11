#include "thread1.h"
#include "buffer.h"
#include "DynamicLib.h"

#include <iostream>
#include <string>
#include <algorithm>

Thread1::Thread1(Buffer<std::string>& buffer) : buffer(buffer) {}

void Thread1::dataInput() {
    while (true) {
        string input;
        getline(std::cin, input);

        if (!input.empty() && input.length() <= 64 && all_of(input.begin(), input.end(), ::isdigit))
        {
            insertKB(input);
            buffer.writeData(std::move(input));
        }
    }
}