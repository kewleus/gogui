#include "gui.h"

Gui::Gui()
{
	m_pSilverback = new Gorilla::Silverback();
}

Gui::~Gui()
{
	delete m_pSilverback;
}

Gorilla::Silverback* Gui::getSilverback()
{
	return m_pSilverback;
}

bool Gui::hasAtlas(Ogre::String name)
{
	for(unsigned int i = 0; i < m_vAtlas.size(); i++)
		if(m_vAtlas[i] == name)
			return true;
	return false;
}

void Gui::loadAtlas(Ogre::String name)
{
	m_pSilverback->loadAtlas(name);
	m_vAtlas.push_back(name);
}

Gorilla::Screen* Gui::getScreen(Ogre::String name)
{
	if(m_mScreens[name] != nullptr)
		return m_mScreens[name]->screen;
	return nullptr;
}

Gorilla::Screen* Gui::createScreen(Ogre::Viewport* vp, Ogre::String atlas, Ogre::String name)
{
	GScreen* scr = new GScreen();	
	if(!hasAtlas(atlas))
		loadAtlas(atlas);
		
	if(m_mScreens[name] == nullptr)
	{
		scr->screen	= m_pSilverback->createScreen(vp, atlas);
		m_mScreens[name] = scr;
	}
	
	return scr->screen;
}

Gorilla::Layer* Gui::getLayer(Ogre::String screen, Ogre::String layer)
{
	if(m_mScreens[screen] != nullptr)
		return m_mScreens[screen]->layers[layer];
	return nullptr;
}

Gorilla::Layer* Gui::getLayer(Gorilla::Screen* screen, Ogre::String layer)
{
	std::map<Ogre::String, GScreen*>::iterator i;
	for(i = m_mScreens.begin(); i != m_mScreens.end(); i++)
		return getLayer(i->first, layer);
	return nullptr;
}

Gorilla::Layer* Gui::createLayer(Ogre::String screen, Ogre::String layer)
{
	Gorilla::Layer* lyr = getLayer(screen, layer);
	if(lyr != nullptr)
		return lyr;

	if(getScreen(screen) != nullptr)
	{
		m_mScreens[screen]->layers[layer] = getScreen(screen)->createLayer(m_mScreens[screen]->layers.size());
		return m_mScreens[screen]->layers[layer];
	}
	return nullptr;
}

Gorilla::Layer* Gui::createLayer(Gorilla::Screen* screen, Ogre::String layer)
{
	Gorilla::Layer* lyr = getLayer(screen, layer);
	if(lyr != nullptr)
		return lyr;

		std::map<Ogre::String, GScreen*>::iterator i;
		for(i = m_mScreens.begin(); i != m_mScreens.end(); i++)
			if(i->second->screen == screen)
			{
				i->second->layers[layer] = i->second->screen->createLayer(i->second->layers.size());
				return i->second->layers[layer];
			}
	return nullptr;
}