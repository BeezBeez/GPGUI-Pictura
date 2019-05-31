#pragma once

#include <list>
#include <utility>

namespace Pictura::Events
{
	template<typename T>
	class PICTURA_API EventHandlerImplBase
	{
	public:
		EventHandlerImplBase() {}
		virtual ~EventHandlerImplBase() {} 
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>*) =0; 

		bool IsSametype(EventHandlerImplBase<T>* pHandler2)
		{
			if( !pHandler2 || typeid(*this) != typeid(*pHandler2) )
			{
				return false;
			}

			return true;
		}
	};

	template<typename T>
	class PICTURA_API EventHandlerImpl: public EventHandlerImplBase<T>
	{
	public:
		virtual void OnEvent(T&) =0;
	};
	template<typename T>
	class PICTURA_API EventHandlerImplForNonMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)(T&))
			: m_pFunctionToCall(functionToCall)
		{
		}
		virtual void OnEvent(T& evt)
		{
				m_pFunctionToCall(evt);
		}
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2)
		{
			if( ! IsSametype(pHandler2))
			{
				return false;
			}
			EventHandlerImplForNonMemberFunction<T>* pHandlerCasted= dynamic_cast<EventHandlerImplForNonMemberFunction<T>* >(pHandler2);
			if( ! pHandlerCasted)
			{
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)(T&);
	};
	template<typename T, typename U>
	class PICTURA_API EventHandlerImplForMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::*memberFunctionToCall)(T&), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}
		virtual void OnEvent(T& evt)
		{
			if(m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)(evt);
			}
		}

		bool IsSametype(EventHandlerImplBase<T>* pHandler2)
		{
			if (!pHandler2 || typeid(*this) != typeid(*pHandler2))
			{
				return false;
			}

			return true;
		}

		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2)
		{	
			if(!IsSametype(pHandler2))
			{
				return false;
			}
			EventHandlerImplForMemberFunction<T,U>* pHandlerCasted= dynamic_cast<EventHandlerImplForMemberFunction<T,U>* >(pHandler2);
			if( ! pHandlerCasted)
			{
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;
		void(U::*m_pMemberFunction)(T&);
	};
	template<>
	class PICTURA_API EventHandlerImpl<void>: public EventHandlerImplBase<void>
	{
	public:
		virtual void OnEvent() =0;
	};
	template<>
	class PICTURA_API EventHandlerImplForNonMemberFunction<void> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)())
			: m_pFunctionToCall(functionToCall)
		{
		}
		virtual void OnEvent()
		{
				m_pFunctionToCall();
		}
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2)
		{
			if( ! IsSametype(pHandler2))
			{
				return false;
			}
			EventHandlerImplForNonMemberFunction<void>* pHandlerCasted= dynamic_cast<EventHandlerImplForNonMemberFunction<void>* >(pHandler2);
			if( ! pHandlerCasted)
			{
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)();
	};
	template<typename U>
	class PICTURA_API EventHandlerImplForMemberFunction<void, U> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::*memberFunctionToCall)(), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}
		virtual void OnEvent()
		{
			if(m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)();
			}
		}
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2)
		{
			if( ! IsSametype(pHandler2))
			{
				return false;
			}
			EventHandlerImplForMemberFunction<void,U>* pHandlerCasted= dynamic_cast<EventHandlerImplForMemberFunction<void,U>* >(pHandler2);
			if( ! pHandlerCasted)
			{
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;
		void(U::*m_pMemberFunction)();
	};
	class PICTURA_API EventHandler
	{
	public:
		template<typename T>
		static EventHandlerImpl<T>* Bind(void(*nonMemberFunctionToCall)(T&))
		{
			return new EventHandlerImplForNonMemberFunction<T>(nonMemberFunctionToCall);
		}
		template<typename T, typename U>
		static EventHandlerImpl<T>* Bind(void(U::*memberFunctionToCall)(T&), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<T,U>(memberFunctionToCall, thisPtr);
		}
		static EventHandlerImpl<void>* Bind(void(*nonMemberFunctionToCall)())
		{
			return new EventHandlerImplForNonMemberFunction<void>(nonMemberFunctionToCall);
		}
		template<typename U>
		static EventHandlerImpl<void>* Bind(void(U::*memberFunctionToCall)(), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<void,U>(memberFunctionToCall, thisPtr);
		}

	private:
		EventHandler();
	};
	template<typename T>
	class PICTURA_API EventBase
	{
	public:
		EventBase() {}
		virtual ~EventBase()
		{
			for(auto iter= m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler= *iter;
				if(pHandler)
				{
					delete pHandler;
					pHandler= 0;
				}
			}
			m_eventHandlers.clear();
		}
		EventBase<T>& operator += (EventHandlerImpl<T>* pHandlerToAdd)
		{

			if(pHandlerToAdd)
			{
				m_eventHandlers.push_back(pHandlerToAdd);
			}

			return *this;
		}
		EventBase<T>& operator -= (EventHandlerImpl<T>* pHandlerToRemove)
		{
			if( ! pHandlerToRemove)
			{
				return *this;
			}

			for(auto iter= m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler= *iter;
				if( pHandlerToRemove->IsBindedToSameFunctionAs(pHandler))
				{
					EventHandlerImpl<T>* pFoundHandler= *iter;
					if( pFoundHandler)
					{
						delete pFoundHandler;
						pFoundHandler= 0;
					}
					m_eventHandlers.erase(iter);
					break;
				}
			}
			if( pHandlerToRemove)
			{
				delete pHandlerToRemove;
				pHandlerToRemove= 0;
			}
			
			return *this;
		}

	private:
		EventBase(const EventBase&);
		EventBase& operator=(const EventBase&);

	public:
		std::list< EventHandlerImpl<T>* > m_eventHandlers;
	};
	template<typename T>
	class PICTURA_API Event : public EventBase<T>
	{
	public:
		std::list< EventHandlerImpl<T>* > m_eventHandlers;

		void operator()(T& eventData)
		{
			for(auto iter= m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler= *iter;
				if(pHandler)
				{
					pHandler->OnEvent(eventData);
				}
			}
		}
	};
	template<>
	class PICTURA_API Event<void> : public EventBase<void>
	{
	public:
		std::list< EventHandlerImpl<void>* > m_eventHandlers;

		void operator()()
		{
			for(auto iter= m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<void>* pHandler= *iter;
				if(pHandler)
				{
					pHandler->OnEvent();
				}
			}
		}
	};
}