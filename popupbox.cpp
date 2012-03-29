#include "popupbox.h"

/* Singleton is initialized */
template<> PopUpBox* Ogre::Singleton<PopUpBox>::ms_Singleton = 0;

PopUpBox::PopUpBox(Gui* pGui)
{
	if(!pGui) return;
	Gorilla::Screen* pScreen = pGui->getScreen("WorldState");
	m_pLayer = pGui->createLayer(pScreen, "PopUpBox");
	
	m_vSize = Ogre::Vector2(500,300);
	m_vPosition = Ogre::Vector2(
		pScreen->getWidth()/2 - m_vSize.x/2, 
		pScreen->getHeight()/2 - m_vSize.y/2
		);
	m_vButtonOffset = Ogre::Vector2(90,200);
	m_vButtonSize = Ogre::Vector2(160,40);
	
	m_pBackground = m_pLayer->createRectangle(m_vPosition, m_vSize);
	m_pBackground->background_image("popupbox_bg");

	m_pCaption = m_pLayer->createCaption(14, 80 + m_vPosition.x, 80 + m_vPosition.y, "");
	m_pCaption->size(340,90);
	m_pCaption->align(Gorilla::TextAlign_Centre);
	m_pCaption->vertical_align(Gorilla::VerticalAlign_Middle);

	m_pOk = new GButton();
	m_pOk->Background = m_pLayer->createRectangle(m_vPosition + m_vButtonOffset, m_vButtonSize);
	m_pOk->BaseImage = "popupbox_ok";
	m_pOk->HoverImage = "popupbox_ok_hover";
	m_pOk->Hover(false);
	
	m_pCancel = new GButton();
	m_pCancel->Background = m_pLayer->createRectangle(m_vPosition + m_vButtonOffset + Ogre::Vector2(m_vButtonSize.x,0), m_vButtonSize);
	m_pCancel->BaseImage = "popupbox_cancel";
	m_pCancel->HoverImage = "popupbox_cancel_hover";
	m_pCancel->Hover(false);

	dismiss();
}

void PopUpBox::dismiss()
{
	// pop message off of stack and hide the box
	if(m_vMessageStack.size() > 0)
		m_vMessageStack.pop_back();

	if(m_vMessageStack.size() == 0)
	{
		m_pLayer->setVisible(false);
		m_bVisible = false;
	}
	else
	{
		m_pCaption->text(m_vMessageStack.back().Message);
	}
}

void PopUpBox::showMessage(int id, Ogre::String message, PopUpBoxListener* listener)
{
	// push message onto stack and show the message
	PopUpMessage pum;
	pum.ID = id;
	pum.Message = message;
	pum.Listener = listener;

	m_vMessageStack.push_back(pum);
	m_pCaption->text(message);
	m_pLayer->setVisible(true);
	m_bVisible = true;
}

bool PopUpBox::mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	// don't let click through body
	if(m_pBackground->intersects(Ogre::Vector2(x, y)) && isVisible())
		return false;
	return true;
}
bool PopUpBox::mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	if(isVisible())
	{
		// detect button clicks & don't allow click through
		if(id == OIS::MB_Left)
		{
			if(isOver(Ogre::Vector2(x,y), m_pOk))
			{
				if(m_vMessageStack.back().Listener != nullptr)
					m_vMessageStack.back().Listener->PopUpOk(m_vMessageStack.back().ID);
				return false;
			}
			if(isOver(Ogre::Vector2(x, y), m_pCancel))
			{
				if(m_vMessageStack.back().Listener != nullptr)
					m_vMessageStack.back().Listener->PopUpCancel(m_vMessageStack.back().ID);
				return false;
			}
		}
	
		// dont allow click through the body of the messagebox
		if(m_pBackground->intersects(Ogre::Vector2(x, y)))
			return false;
	}
	return true;
}
void PopUpBox::mouseMoved(unsigned int x, unsigned int y)
{
	// no point in changing images if you can't see them
	if(isVisible())
	{
		isOver(Ogre::Vector2(x, y), m_pOk);
		isOver(Ogre::Vector2(x, y), m_pCancel);	
	}
}

bool PopUpBox::isOver(Ogre::Vector2 pos, GButton* pButton)
{
	bool result = pButton->Background->intersects(pos);
	pButton->Hover(result);
	return result;
}