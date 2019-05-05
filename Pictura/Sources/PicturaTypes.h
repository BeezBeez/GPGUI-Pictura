#pragma once

#include "PicturaPCH.h"

#define TRUESTRING "true"
#define FALSESTRING "false"

typedef std::string PString;

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
	return static_cast<typename std::underlying_type<E>::type>(e);
}
