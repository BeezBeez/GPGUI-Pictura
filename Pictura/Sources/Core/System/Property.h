#pragma once

#define PROPERTY(type, name, defaultValue)\
private: \
	type _##name = defaultValue; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { _##name = value; }

#define NOTIFY_PROPERTY(type, name, onChanged, defaultValue)\
private: \
	type _##name = defaultValue; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { (onChanged)(_##name, value); _##name = value; }
