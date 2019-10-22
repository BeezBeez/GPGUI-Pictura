#include "PicturaPCH.h"
#include "FontFamily.h"

namespace Pictura::Graphics::Text
{
	PMap<PString, FontFamily*> FontFamily::loadedFonts = PMap<PString, FontFamily*>({ {"null1", nullptr}, {"null2", nullptr} });

	FontFamily::FontFamily(PString name, PVector<PString> weights, Window& ownerWindow) : fontName(name)
	{
		PString fontPathPrefix = weights[0] == "" ? "C:\\Windows\\Fonts\\" + name : "C:\\Windows\\Fonts\\" + name + "-";
		for (PString weight : weights)
		{
			DEBUG_SECTION(
			Log::Trace("Loading " + name + " [" + weight + "]...");
			)

			if (File::Exist((fontPathPrefix + weight + ".ttf").c_str()))
			{
				int handle = nvgCreateFont(ownerWindow.GetBrush(), (name + "-" + weight).c_str(), (fontPathPrefix + weight + ".ttf").c_str());
				fontHandles.insert_or_assign(PString(name + "_" + weight), handle);

				DEBUG_SECTION(
				Log::Success("Font " + fontName + " loaded !");
				)
			}
			else
			{
				DEBUG_SECTION(
				Log::Error("Font not found...");
				)
			}
		}		
	}

	FontFamily::~FontFamily()
	{

	}

	FontFamily* FontFamily::LoadFontByName(PString fontName, PVector<PString> fontWeight, Window& ownerWindow)
	{
		if (loadedFonts[fontName + "__" + Types::ToString(ownerWindow.GetHash())] == nullptr)
		{
			DEBUG_SECTION(
			Log::Trace("Initializing font with slot name > " + fontName + "__" + Types::ToString(ownerWindow.GetHash()));
			)
			FontFamily* result = new FontFamily(fontName, fontWeight, ownerWindow);
			loadedFonts.insert_or_assign(fontName + "__" + Types::ToString(ownerWindow.GetHash()), result);
			return result;
		}
		else
		{
			DEBUG_SECTION(
			Log::Trace("Loading already created fonts !");
			)
			return loadedFonts[fontName + "__" + Types::ToString(ownerWindow.GetHash())];
		}
	}

	int FontFamily::GetFont(PString fontName, PString fontWeight, Widget& owner)
	{
		if (loadedFonts[fontName + "__" + Types::ToString(owner.GetOwnerWindow()->GetHash())] == nullptr)
		{
			FontFamily* fnt = FontFamily::LoadFontByName(fontName, { fontWeight }, *(owner.GetOwnerWindow()));	
		}
		
		return loadedFonts[fontName + "__" + Types::ToString(owner.GetOwnerWindow()->GetHash())]->fontHandles[fontName + "_" + fontWeight];
	}
}