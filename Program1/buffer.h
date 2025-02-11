#pragma once
#include <mutex>
#include <condition_variable>

template<typename T>
class Buffer : private std::mutex, private std::condition_variable {

	T buffer;
	bool dataAvailable;

public:

	Buffer() {
		dataAvailable = false;
	}

	void writeData(T recvBuf) {
		std::unique_lock<std::mutex> lock(*this);
		buffer = std::move(recvBuf);
		dataAvailable = true;
		lock.unlock();
		notify_all();
	}

	T readData() {
		std::unique_lock<std::mutex> lock(*this);
		wait(lock, [this] { return dataAvailable; });
		T bufferData = std::move(buffer);
		buffer.clear();
		dataAvailable = false;
		lock.unlock();
		return bufferData;
	}
};