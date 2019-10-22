#pragma once
#include "Core/Core.h"
#include "Core/Debug/Log.h"
#include "Filesystem/File.h"
#include "Widgets/Window/Window.h"
#include "NanoVG/nanovg.h"

using namespace Pictura::Filesystem;
using namespace Pictura::Debug;
using namespace Pictura::Widgets;

namespace Pictura::Graphics::Text
{
	class PICTURA_API FontFamily
	{
	public:
		FontFamily(PString fontName, PVector<PString> fontWeight, Window& ownerWindow);
		~FontFamily();

		static FontFamily* LoadFontByName(PString fontName, PVector<PString> fontWeight, Window& ownerWindow);
		static int GetFont(PString fontName, PString fontWeight, Widget& owner);

	public:
		PString fontName;
		PMap<PString, int> fontHandles;

	public:
		static PMap<PString, FontFamily*> loadedFonts;

	private:

	};
}
