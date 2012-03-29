#include "itembox.h"

ItemBox::ItemBox(Gui* pGui, ITEM_ID id, int capacity, Ogre::String baseImage, Ogre::String hoverImage)
{
	if(!pGui) return;
	m_vImageOffset = Ogre::Vector2(23,21);
	m_vCaptionOffset = Ogre::Vector2(23, 80);
	m_vCaptionSize = Ogre::Vector2(205, 30);

	m_bEnabled = true;
	m_bHovered = false;

	m_sBaseImage = baseImage;
	m_sHoverImage = hoverImage;
	m_ID = id;

	m_pScreen = pGui->getScreen("WorldState");
	m_pLayer = pGui->getLayer("WorldState", "ItemBar");

	// background / encapsulation
	m_pBackground = m_pLayer->createRectangle(Ogre::Vector2(0,0), Ogre::Vector2(250, 175));
	m_pBackground->background_image("itembox");

	// item image
	m_pImage = m_pLayer->createRectangle(m_vImageOffset, Ogre::Vector2(205, 133));
	m_pImage->background_image(baseImage);

	// disabled overlay
	m_pDisabled = m_pLayer->createRectangle(m_vImageOffset, Ogre::Vector2(205, 133));
	m_pDisabled->no_background();

	// caption
	m_pCaption = m_pLayer->createCaption(14, m_vCaptionOffset.x, m_vCaptionOffset.y, m_sCaption);
	m_pCaption->size(m_vCaptionSize.x, m_vCaptionSize.y);
	m_pCaption->align(Gorilla::TextAlign_Centre);
	m_pCaption->vertical_align(Gorilla::VerticalAlign_Middle);
	m_pCaption->background(Ogre::ColourValue(0.6f,0.6f,0.6f,0.4f));

	setCapacity(capacity);
}

void ItemBox::setPosition(Ogre::Vector2 pos)
{
	m_vPosition = pos;
	m_pBackground->position(pos);
	m_pDisabled->position(pos + m_vImageOffset);
	m_pImage->position(pos + m_vImageOffset);
	
	// no caption move have to recreate
	m_pLayer->destroyCaption(m_pCaption);
	m_pCaption = m_pLayer->createCaption(14, pos.x + m_vCaptionOffset.x, pos.y + m_vCaptionOffset.y, m_sCaption);
	m_pCaption->size(m_vCaptionSize.x, m_vCaptionSize.y);
	m_pCaption->align(Gorilla::TextAlign_Centre);
	m_pCaption->vertical_align(Gorilla::VerticalAlign_Middle);
	m_pCaption->background(Ogre::ColourValue(0.6f,0.6f,0.6f,0.4f));
}

Ogre::Vector2 ItemBox::getPosition()
{
	return m_vPosition;
}

void ItemBox::setEnabled(bool value)
{
	m_bEnabled = value;
	if(value)
		m_pDisabled->no_background();
	else
		m_pDisabled->background_colour(Ogre::ColourValue(0.4f, 0.4f, 0.4f, 0.4f));
}

bool ItemBox::isOver(const Ogre::Vector2& pos)
{
	if(!m_bEnabled)
		return false;

	bool result = m_pImage->intersects(pos);
	
	if(result && !m_bHovered)
	{
		m_pImage->background_image(m_sHoverImage);
		m_pCaption->background(Ogre::ColourValue(0.6f,0.6f,0.6f,0.6f));
	}
	else if(!result && m_bHovered)
	{
		m_pImage->background_image(m_sBaseImage);
		m_pCaption->background(Ogre::ColourValue(0.6f,0.6f,0.6f,0.4f));
	}

	m_bHovered = result;
	return result;
}

void ItemBox::setSelected(bool value)
{
	if(value)
		m_pImage->border(3, Ogre::ColourValue(0,0.7f,0,1));
	else
		m_pImage->border(0, Ogre::ColourValue(0,0.7f,0,0));
}

void  ItemBox::setCaption(Ogre::String str)
{
	m_sCaption = str;
	m_pCaption->text(m_sCaption);
}

void ItemBox::setCapacity(int capacity)
{
	m_iCapacity = capacity;

	if(m_iCapacity == 0)
		setEnabled(false);

	if(m_iCapacity == -1)
		setCaption("Infinite");
	else
		setCaption(Ogre::StringConverter().toString(m_iCapacity));
}

void ItemBox::alterCapacity(int relative)
{
	if(m_iCapacity > 0)
		m_iCapacity += relative;

	if(m_iCapacity == 0)
		setEnabled(false);

	if(m_iCapacity == -1)
		setCaption("Infinite");
	else
		setCaption(Ogre::StringConverter().toString(m_iCapacity));
}