#pragma once

#define PROPERTY(type, name)\
private: \
	type _##name; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { _##name = value; }

#define NOTIFY_PROPERTY(type, name, onChanged)\
private: \
	type _##name; \
public: \
	type Get##name() { return _##name; } \
	void Set##name(type value) { (onChanged)(_##name, value); _##name = value; }
