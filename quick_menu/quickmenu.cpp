#include "quickmenu.h"

QuickMenu::QuickMenu(Gui* pGui)
{
	if(!pGui) return;
	m_pScreen = pGui->getScreen("WorldState");
	m_pLayer = pGui->createLayer(m_pScreen, "QuickMenu");
	
	m_vSize = Ogre::Vector2(400,400);
	m_vPosition = Ogre::Vector2(m_pScreen->getWidth()/2 - m_vSize.x/2, m_pScreen->getHeight()/2 - m_vSize.y/2);
	m_vButtonOffset = Ogre::Vector2(60,135);
	m_vButtonSize = Ogre::Vector2(275,60);
	
	m_pBackground = m_pLayer->createRectangle(m_vPosition, m_vSize);
	m_pBackground->background_image("quickmenu_bg");

	m_pOptions = new GButton();
	m_pOptions->Background = m_pLayer->createRectangle(m_vPosition + m_vButtonOffset, m_vButtonSize);
	m_pOptions->BaseImage = "quickmenu_options";
	m_pOptions->HoverImage = "quickmenu_options_hover";
	m_pOptions->Hover(false);
	
	m_pRestart = new GButton();
	m_pRestart->Background = m_pLayer->createRectangle(m_vPosition + m_vButtonOffset + Ogre::Vector2(0,m_vButtonSize.y), m_vButtonSize);
	m_pRestart->BaseImage = "quickmenu_restart";
	m_pRestart->HoverImage = "quickmenu_restart_hover";
	m_pRestart->Hover(false);
	
	m_pExit = new GButton();
	m_pExit->Background = m_pLayer->createRectangle(m_vPosition + m_vButtonOffset + Ogre::Vector2(0,m_vButtonSize.y)*2, m_vButtonSize);
	m_pExit->BaseImage = "quickmenu_exit";
	m_pExit->HoverImage = "quickmenu_exit_hover";
	m_pExit->Hover(false);

	setVisible(false);
}

void QuickMenu::setVisible(bool value)
{
	m_pLayer->setVisible(value);
	m_bVisible = value;
}

bool QuickMenu::mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	if(m_pBackground->intersects(Ogre::Vector2(x, y)) && isVisible())
		return false;
	return true;
}
bool QuickMenu::mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left && isVisible())
	{
		if(isOver(Ogre::Vector2(x,y), m_pExit))
		{
			if(m_pListener != nullptr)
				m_pListener->QuickMenuExit();
			return false;
		}
		if(isOver(Ogre::Vector2(x, y), m_pOptions))
		{
			if(m_pListener != nullptr)
				m_pListener->QuickMenuOptions();
			return false;
		}
		if(isOver(Ogre::Vector2(x, y), m_pRestart))
		{
			if(m_pListener != nullptr)
				m_pListener->QuickMenuRestart();
			return false;
		}
	}
	if(m_pBackground->intersects(Ogre::Vector2(x, y)) && isVisible())
		return false;
	return true;
}
void QuickMenu::mouseMoved(unsigned int x, unsigned int y)
{
	isOver(Ogre::Vector2(x, y), m_pOptions);
	isOver(Ogre::Vector2(x, y), m_pRestart);
	isOver(Ogre::Vector2(x, y), m_pExit);	
}

bool QuickMenu::isOver(Ogre::Vector2 pos, GButton *button)
{
	bool result = button->Background->intersects(pos);
	button->Hover(result);
	return result;
}