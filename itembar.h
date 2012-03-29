#pragma once
#ifndef ITEMBAR_H
#define ITEMBAR_H

#include "gui.h"
#include "itembox.h"
#include <map>
#include <vector>

enum ITEM_ID {
	UNKNOWN = -1,
	BALL,
	SMALLBALL
};

class ItemBar
{
public:
	ItemBar(Gui* pGui);
	
	// return true for clickthrough allowed, false to disallow clickthrough
	bool mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	bool mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id);
	void mouseMoved(unsigned int x, unsigned int y);

	void		addItem(ItemBox* item);
	ItemBox*	getItem(ITEM_ID id);

	ITEM_ID		getSelectedItem() { return m_ItemSelected; };
	void		setSelectedItem(ITEM_ID id);

private:
	Gorilla::Layer*			m_pLayer;
	Gorilla::Rectangle*		m_pBackground;

	Gorilla::Rectangle*		m_pScrollRight;
	Gorilla::Rectangle*		m_pScrollLeft;

	std::map<ITEM_ID, ItemBox*> m_mItems;
	std::vector<ItemBox*>		m_vOrderedItems;
	int							m_iLeftIndex;

	Ogre::Vector2			m_vPosition;
	Ogre::Vector2			m_vItemOffset;

	ITEM_ID					m_ItemSelected;
};

#endif //ITEMBAR_H