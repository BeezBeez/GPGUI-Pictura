#pragma once
#include "PicturaPCH.h"

using PString = std::string;

template <typename T>
using PVector = std::vector<T>;

template <typename T, typename T2>
using PMap = std::map<T, T2>;

template <typename T>
using PUniquePtr = std::unique_ptr<T>;

template <typename T>
using PSharedPtr = std::shared_ptr<T>;

template <typename T>
using PWeakPtr = std::weak_ptr<T>;

template <typename T>
using PList = std::list<T>;

using PMutex = std::mutex;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

template <typename... A>
using PTuple = std::tuple<A...>;

template <typename T, typename... A>
auto GetTupleValue(std::tuple<A...> _tuple) {
	return std::get<T>(_tuple);
}

template <typename T, typename O>
constexpr T CastTo(O o) noexcept {
	return static_cast<T>(o);
}

template <typename T, typename O>
constexpr T DynamicCastTo(O o) noexcept {
	return dynamic_cast<T>(o);
}

template <typename T, typename O>
constexpr T ReinterpretCastTo(O o) noexcept {
	return reinterpret_cast<T>(o);
}

constexpr uint64_t UINT64_MAXVALUE = 0xffffffffffffffffULL;

namespace Pictura::Types
{
	template <class T>
	PString ToString(const T& t)
	{
		try
		{
			std::stringstream ss;
			ss << t;
			return ss.str();
		}
		catch (const std::exception&)
		{
			return "";
		}
	}

	template <typename E>
	constexpr typename std::underlying_type<E>::type ToUnderlying(E e) noexcept {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}

	template <typename T, typename... Args>
	PUniquePtr<T> MakeUnique(Args ...args)
	{
		return std::make_unique<T>(args...);
	}

	template <typename T, typename... Args>
	PSharedPtr<T> MakeShared(Args ...args)
	{
		return std::make_shared<T>(args...);
	}

	template <typename... A>
	PTuple<A...> MakeTuple(A ...types)
	{
		return std::make_tuple(types...);
	}

	template <class T>
	void Move(const T& a)
	{
		std::move(a);
	}

	namespace Vectors
	{
		template <typename T>
		void RemoveElement(PVector<T> &vector, T value)
		{
			std::vector<T>::iterator pos = std::find(vector.begin(), vector.end(), value);
			if (pos != vector.end()) {
				vector.erase(pos);
			} else {
				Debug::Log::Warning("Tried to remove a not found element of a PVector !");
			}
		}
	}

	namespace Lists
	{
		template <typename T>
		void RemoveElement(PList<T> &list, T value)
		{
			list.remove(value);
		}
	}
}
