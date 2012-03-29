#pragma once
#ifndef POPUPBOX_H
#define POPUPBOX_H

#include "gui.h"

class PopUpBoxListener
{
public:
	virtual void PopUpOk(int messageID) = 0;
	virtual void PopUpCancel(int messageID) = 0;
};

typedef struct PopUpMessage
{
	int	ID;
	Ogre::String Message;
	PopUpBoxListener* Listener;
} PopUpMessage;

class PopUpBox : public Ogre::Singleton<PopUpBox>
{
public:
	PopUpBox(Gui* pGui);

	void showMessage(int id, Ogre::String message, PopUpBoxListener* listener);
	bool isVisible() { return m_bVisible; };
	void dismiss();
	
	// return true for clickthrough allowed, false to disallow clickthrough
	bool mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	bool mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	void mouseMoved(unsigned int x, unsigned int y);
private:
	bool isOver(Ogre::Vector2 pos, GButton* button);

	Gorilla::Layer*		m_pLayer;
	Gorilla::Rectangle* m_pBackground;
	Gorilla::Caption*	m_pCaption;
	GButton*			m_pOk;
	GButton*			m_pCancel;

	Ogre::Vector2		m_vPosition;
	Ogre::Vector2		m_vSize;
	Ogre::Vector2		m_vButtonOffset;
	Ogre::Vector2		m_vButtonSize;

	std::vector<PopUpMessage>	m_vMessageStack;
	bool						m_bVisible;
};

#endif //POPUPBOX_H