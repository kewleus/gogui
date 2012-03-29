#pragma once
#ifndef ITEMBOX_H
#define ITEMBOX_H

#include "gui.h"

//predefinition
enum ITEM_ID;

class ItemBox
{
public:
	ItemBox(Gui* pGui, ITEM_ID id, int capacity, Ogre::String baseImage, Ogre::String hoverImage);

	void			setPosition(Ogre::Vector2 pos);
	Ogre::Vector2	getPosition();
	void			setCaption(Ogre::String str);
	void			setCapacity(int capacity);
	void			alterCapacity(int relative);

	ITEM_ID			getItemID() { return m_ID; };
	void			setSelected(bool value);

	bool			isOver(const Ogre::Vector2& pos);
	bool			isEnabled() { return m_bEnabled; };
	void			setEnabled(bool value);
private:
	Gorilla::Screen*	m_pScreen;
	Gorilla::Layer*		m_pLayer;

	Gorilla::Caption*	m_pCaption;
	Gorilla::Rectangle* m_pBackground;
	Gorilla::Rectangle* m_pImage;
	Gorilla::Rectangle* m_pDisabled;

	bool			m_bEnabled;
	bool			m_bHovered;

	Ogre::String	m_sBaseImage;
	Ogre::String	m_sHoverImage;
	Ogre::Vector2	m_vPosition;
	Ogre::Vector2	m_vImageOffset;
	Ogre::Vector2	m_vCaptionOffset;
	Ogre::Vector2	m_vCaptionSize;

	int				m_iCapacity;

	std::string		m_sCaption;
	ITEM_ID			m_ID;
};

#endif // ITEMBOX_H