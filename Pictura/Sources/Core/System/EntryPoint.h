#pragma once
#include "Core/Core.h"
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
	const PVector<PString> args(argv, argv + argc);
	auto app = Pictura::InitApplication();

	app->Arguments = args;
	StartupEventArgs e = StartupEventArgs(app->Arguments);

	app->ApplicationStart(e);
	app->ApplicationClose();

	delete app;
}

#endif