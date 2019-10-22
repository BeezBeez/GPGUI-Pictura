#pragma once

#undef interface
#define interface class
#define events public
#define properties public

#define STATIC_PROPERTY(type, name)\
private: \
	static type _##name; \
public: \
	static type Get##name() { return _##name; } \
	static void Set##name(type value) { _##name = value; }


#define PROPERTY(type, name, defaultValue)\
private: \
	type _##name = defaultValue; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { _##name = value; }

#define READONLY_PROPERTY(type, name, defaultValue)\
private: \
	type _##name = defaultValue; \
public: \
	type Get##name() { return _##name; } \

#define NOTIFY_PROPERTY(type, name, onChanged, defaultValue)\
private: \
	type _##name = defaultValue; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { (onChanged)(_##name, value); _##name = value; }
