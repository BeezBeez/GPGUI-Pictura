#pragma once
#include "Core/Core.h"
#include "Core/Debug/Log.h"
#include "Application.h"

#define APPLICATION(ClassName) \
Pictura::Application* Pictura::InitApplication() \
{ \
	return new ClassName##(); \
}

extern Pictura::Application* Pictura::InitApplication();

void InvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, uint32 Line, uint64 Reserved)
{
	PString ErrorMessage;
	ErrorMessage = "CRT INVALID PARAMETER.\nExpression : " + Pictura::Types::ToString(Expression ? Expression : L"Unknown") + "\nFunction : " + Pictura::Types::ToString(Function ? Function : L"Unknown") + "\nFile : " + Pictura::Types::ToString(File ? File : L"Unknown") + "\nLine : " + Pictura::Types::ToString(Line);
	Pictura::Debug::Log::Error(ErrorMessage);
	throw std::exception("FATAL EXCEPTION.");
}

void SetupEnvironment()
{
#if PLATFORM_WINDOWS
	_set_invalid_parameter_handler(InvalidParameterHandler);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_CrtSetDebugFillThreshold(0);
#endif

#if PLATFORM_LINUX
	
#endif
}

int main(int argc, char** argv)
{
	SetupEnvironment();
	const PVector<PString> args(argv, argv + argc);
	auto app = Pictura::InitApplication();

	app->Arguments = args;
	StartupEventArgs e = StartupEventArgs(app->Arguments);

	app->Init(e);

	while (app->ApplicationThread) {}

	delete app;
}