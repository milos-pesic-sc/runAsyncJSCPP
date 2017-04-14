#include "pch.h"
#include "Class1.h"
#include <iostream>
#include <chrono>

using namespace runner;
using namespace Platform;

Runner::Runner(Callback^ callbackInst) : callback(callbackInst), running(false)
{
}

Runner::~Runner() {
	destroy();
}

void Runner::init() {
	processor = std::make_unique<std::thread>([this]() {
		running = true;
		while (running) {
			std::cout << "Before RunAsync" << std::endl;
			enqueueForMainUIThread([this]() {
				callback->Invoke(1);
			});
			std::cout << "After RunAsync" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	});
}

void Runner::doSomethingHeavy() {
	std::cout << "Simulating long running task" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(30));
	std::cout << "Long running task completed" << std::endl;
}

void Runner::enqueueForMainUIThread(std::function<void(void)> function) {
	Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
		Windows::UI::Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler(function));
}

void Runner::destroy() {
	if (running) {
		running = false;
		processor->join();
	}

}