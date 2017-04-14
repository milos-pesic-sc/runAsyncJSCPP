#pragma once

#include <thread>
#include <memory>
#include <atomic>
#include <functional>

namespace runner
{

	public delegate void Callback(int event);

    public ref class Runner sealed
    {
    public:
        Runner(Callback^ callback);
		virtual ~Runner();
		void init();
		void doSomethingHeavy();
	private:
		void enqueueForMainUIThread(std::function<void(void)> function);
		void destroy();

		Callback^ callback;
		std::unique_ptr<std::thread> processor;
		std::atomic_bool running;
    };
}
