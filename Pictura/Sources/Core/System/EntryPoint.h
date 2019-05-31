#pragma once
#include "Core\Core.h"
#include "Application.h"

#if PLATFORM_WINDOWS == 1

#define APPLICATION(ClassName) \
Pictura::Application* Pictura::InitApplication() \
{ \
	return new ClassName##(); \
}

extern Pictura::Application* Pictura::InitApplication();

int main(int argc, char** argv)
{
	PVector<PString> args(argv, argv + argc);
	Pictura::Runtime::Arguments = args;

	auto app = Pictura::InitApplication();
	app->Run();
	delete app;
}

#endif