#pragma once

#include "PicturaPCH.h"

#define TRUESTRING "true"
#define FALSESTRING "false"

typedef std::string PString;

template <typename T>
using PVector = std::vector<T, Alloc<T>>;

namespace Pictura::Types
{
	template <class T>
	inline PString ToString(const T& t)
	{
		try
		{
			std::stringstream ss;
			ss << t;
			return ss.str();
		}
		catch (const std::exception& e)
		{
			
		}
	}

	template <typename E>
	constexpr typename std::underlying_type<E>::type ToUnderlying(E e) noexcept {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}

	template <typename... T>
	constexpr auto MakeArray(T&& ... values) ->
		std::array<
		typename std::decay<
		typename std::common_type<T...>::type>::type,
		sizeof...(T)> {
		return std::array<
			typename std::decay<
			typename std::common_type<T...>::type>::type,
			sizeof...(T)>{std::forward<T>(values)...};
	}
}