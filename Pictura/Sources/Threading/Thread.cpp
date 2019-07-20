#include "PicturaPCH.h"
#include "Thread.h"
#include "Core/Debug/Log.h"

namespace Pictura::Threading
{
	PVector<PTuple<uint64, Thread*>> Thread::ThreadStack = {};
#if PLATFORM_WINDOWS == 1
	void Thread::SetPriority(Thread &thread, ThreadPriority priority)
	{
		
	}

	void Thread::Delay(int milliseconds)
	{
		Sleep(milliseconds);
	}

	void Thread::StopThread()
	{
		if (threadObj != nullptr && isRunning)
		{
			threadObj = Types::MakeUnique<std::thread>([]() {});
			isRunning = false;
			if (threadObj->joinable())
			{
				threadObj->join();
			}

			threadObj.reset();
			Debug::Log::Trace("Stopping thread [" + ThreadName + "]");
		}
		else
		{
			Debug::Log::Warning("Thread [" + ThreadName + "] was stopped but not correctly...");
			Debug::Log::Warning("A memory leak is possible !");
		}
	}

	Thread* Thread::CurrentThread()
	{
		uint64 CTID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		for (auto &t : ThreadStack)
		{
			if (GetTupleValue<Thread*>(t)->ThreadId == CTID)
			{
				return GetTupleValue<Thread*>(t);
			}
		}
	}
#endif

#if PLATFORM_LINUX == 1 || PLATFORM_OSX == 1
	void Thread::SetPriority(Thread& thread, ThreadPriority priority)
	{

	}

	void Thread::Delay(int milliseconds)
	{
		nanosleep(milliseconds * 1000);
	}
#endif
}
