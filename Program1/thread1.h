#pragma once
#include "thread1.h"
#include "buffer.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Thread1 {

    Buffer<std::string>& buffer;

public:
    Thread1(Buffer<std::string>& buffer);

    void dataInput();
};