#include "itembar.h"

ItemBar::ItemBar(Gui* pGui)
{
	if(!pGui) return;
	Gorilla::Screen* pScreen = pGui->getScreen("WorldState");
	m_pLayer = pGui->createLayer(pScreen, "ItemBar");

	m_vPosition = Ogre::Vector2(0, pScreen->getHeight() - 300);
	m_iLeftIndex = 0;
	m_vItemOffset = Ogre::Vector2(230, 0);

	m_pBackground = m_pLayer->createRectangle(m_vPosition.x, m_vPosition.y, pScreen->getWidth(), 300);
	m_pBackground->background_image("itembar");

	// special layer for scroll buttons so item buttons don't draw overtop
	Gorilla::Layer* scrolllayer = pGui->createLayer(pScreen, "ItemBarScroll");
	m_pScrollRight = scrolllayer->createRectangle(Ogre::Vector2(pScreen->getWidth() - 100, m_vPosition.y + 110), Ogre::Vector2(100, 175));
	m_pScrollRight->background_image("scrollright");

	m_pScrollLeft = scrolllayer->createRectangle(m_vPosition + Ogre::Vector2(0,110), Ogre::Vector2(100, 175));
	m_pScrollLeft->background_image("scrollleft");
}

void ItemBar::addItem(ItemBox* item)
{
	// add new item if an item with the same id doesnt exist
	if(!m_mItems[item->getItemID()])
	{
		m_mItems[item->getItemID()] = item;
		m_vOrderedItems.push_back(item);
		item->setPosition(m_vPosition + m_vItemOffset * (m_vOrderedItems.size()-1) + Ogre::Vector2(95, 110));

		if(m_vOrderedItems.size() == 1)
		{
			item->setSelected(true);
			m_ItemSelected = item->getItemID();
		}
	}
}

ItemBox* ItemBar::getItem(ITEM_ID id)
{
	return m_mItems[id];
}

void ItemBar::setSelectedItem(ITEM_ID id)
{
	m_mItems[m_ItemSelected]->setSelected(false);
	m_mItems[id]->setSelected(true);
	m_ItemSelected = id;
}

bool ItemBar::mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	// prevent click through
	if(m_pBackground->intersects(Ogre::Vector2(x, y)))
		return false;
	return true;
}

bool ItemBar::mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left)
	{
		// scroll items left
		if(m_pScrollLeft->intersects(Ogre::Vector2(x, y)))
		{
			if(m_iLeftIndex < 0)
			{
				for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
					m_vOrderedItems[i]->setPosition(m_vOrderedItems[i]->getPosition() + Ogre::Vector2(230, 0));
				++m_iLeftIndex;
			}
			return false;
		}
		
		// scroll items right
		if(m_pScrollRight->intersects(Ogre::Vector2(x, y)))
		{
			if(((int)m_vOrderedItems.size()) - 6 + m_iLeftIndex > 0)
			{
				for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
					m_vOrderedItems[i]->setPosition(m_vOrderedItems[i]->getPosition() - Ogre::Vector2(230, 0));
				--m_iLeftIndex;
			}
			return false;
		}

		// register item clicks and highlight selected item
		for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
			if(m_vOrderedItems[i]->isOver(Ogre::Vector2(x,y)))
			{
				setSelectedItem(m_vOrderedItems[i]->getItemID());
				return false;
			}
	}

	// prevent clickthrough
	if(m_pBackground->intersects(Ogre::Vector2(x, y)))
		return false;
	return true;
}

void ItemBar::mouseMoved(unsigned int x, unsigned int y)
{
	// show hover image
	for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
		m_vOrderedItems[i]->isOver(Ogre::Vector2(x,y));
}