#pragma once
#include "Core/Core.h"
#include "Core/CoreException.h"
#include "Maths/Convert.h"

namespace Pictura::Threading
{
	class PICTURA_API Thread
	{
	public:
		enum class ThreadPriority
		{
			Low = -2,
			BelowNormal = -1,
			Normal = 0,
			AboveNormal = 1,
			High = 2
		};

	public:
		template <typename... _Args>
		Thread(void(*function)(_Args...), _Args ...args)
		{
			if (function != nullptr)
			{
				threadObj = new std::thread(function, args...);
				ThreadId = std::hash<std::thread::id>{}(threadObj->get_id());
				ThreadName = "THREAD_" + Types::ToString(Maths::Convert::ToHexadecimal(ThreadId));
				threadObj->detach();

				Debug::Log::Trace("Creating thread [" + ThreadName + "]");
			}
		}

		template <typename U, typename... _Args>
		Thread(void(U:: * function)(_Args...), U * thisPtr, _Args ...args)
		{
			if (function != nullptr)
			{
				threadObj = Types::MakeUnique<std::thread>(function, thisPtr, args...);

				ThreadId = std::hash<std::thread::id>{}(threadObj->get_id());
				ThreadName = "THREAD_" + Types::ToString(Maths::Convert::ToHexadecimal(ThreadId));
				threadObj->detach();

				ThreadStack.push_back(Types::MakeTuple(ThreadId, this));

				Debug::Log::Trace("Creating thread [" + ThreadName + "]");
			}
		}

		~Thread()
		{
			if (threadObj != nullptr)
			{
				threadObj.reset();
				Debug::Log::Trace("Stopping thread [" + ThreadName + "]");
			}
			else
			{
				Debug::Log::Warning("Thread [" + ThreadName + "] was stopped but not correctly...");
				Debug::Log::Warning("A memory leak is possible !");
			}
		}

		void StopThread();

	public:
		static void Delay(int milliseconds);
		static void SetPriority(Thread &thread, ThreadPriority priority);
		static Thread* CurrentThread();

	public:
		PString ThreadName;
		
	private:
		PUniquePtr<std::thread> threadObj;
		uint64 ThreadId;
		PMutex ThreadLock;

		static PVector<PTuple<uint64, Thread*>> ThreadStack;
	};	
}

