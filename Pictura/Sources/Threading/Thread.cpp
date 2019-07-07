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
		delete this;
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
