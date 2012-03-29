#pragma once
#ifndef QUICKMENU_H
#define QUICKMENU_H

#include "gui.h"
#include "messagebox.h"

class QuickMenuListener
{
public:
	virtual void QuickMenuExit() = 0;
	virtual void QuickMenuOptions() = 0;
	virtual void QuickMenuRestart() = 0;
};

class QuickMenu
{
public:
	QuickMenu(Gui* pGui);

	void setListener(QuickMenuListener* pListener) { m_pListener = pListener; };

	void setVisible(bool value);
	bool isVisible() { return m_bVisible; };
	
	// return true for clickthrough allowed, false to disallow clickthrough
	bool mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	bool mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	void mouseMoved(unsigned int x, unsigned int y);
private:
	bool isOver(Ogre::Vector2 pos, GButton *button);
private:
	Gorilla::Screen*	m_pScreen;
	Gorilla::Layer*		m_pLayer;
	Gorilla::Rectangle* m_pBackground;
	GButton*			m_pOptions;
	GButton*			m_pRestart;
	GButton*			m_pExit;

	Ogre::Vector2		m_vPosition;
	Ogre::Vector2		m_vSize;
	Ogre::Vector2		m_vButtonOffset;
	Ogre::Vector2		m_vButtonSize;

	QuickMenuListener*	m_pListener;

	bool				m_bVisible;
};

#endif //QUICKMENU_H