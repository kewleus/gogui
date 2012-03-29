#pragma once
#ifndef GUI_H
#define GUI_H

#include <map>
#include <vector>
#include "gorilla.h"

typedef struct GScreen
{
	Gorilla::Screen* screen;
	std::map<Ogre::String, Gorilla::Layer*> layers;
} GScreen;


typedef struct GButton
{
	Gorilla::Rectangle* Background;
	Ogre::String		BaseImage;
	Ogre::String		HoverImage;

public:
	void Hover(bool value) 
	{
		if(value)
		{
			Background->background_image(HoverImage);
		}
		else
		{
			Background->background_image(BaseImage);
		}
	};
} GButton;

class Gui
{
public:
	Gui();
	~Gui();

	Gorilla::Silverback*	getSilverback();
	
	// this is done automatically when creating a screen, but leaving option to do it elsewhere
	void					loadAtlas(Ogre::String name); 
	bool					hasAtlas(Ogre::String name);
			
	Gorilla::Screen*		getScreen(Ogre::String name);
	Gorilla::Screen*		createScreen(Ogre::Viewport* vp, Ogre::String atlas, Ogre::String name);

	Gorilla::Layer*			getLayer(Ogre::String screen, Ogre::String layer);
	Gorilla::Layer*			getLayer(Gorilla::Screen* screen, Ogre::String layer);
	Gorilla::Layer*			createLayer(Ogre::String screen, Ogre::String layer);
	Gorilla::Layer*			createLayer(Gorilla::Screen* Screen, Ogre::String layer);

private:
	Gorilla::Silverback*				m_pSilverback;
	std::vector<Ogre::String>			m_vAtlas;
	std::map<Ogre::String, GScreen*>	m_mScreens;
};

#endif //GUI_H