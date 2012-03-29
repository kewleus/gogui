void scene_initialization_function() {
	Gui* pGui = new Gui();
	pGui->createScreen(pViewport, "world", "WorldState");
	
	m_pItemBar = new ItemBar(pGui);
	m_pItemBar->addItem(new ItemBox(pGui, BALL, 25, "item_ball", "item_ball_hover"));
	m_pItemBar->addItem(new ItemBox(pGui, SMALLBALL, 25, "item_smallball", "item_smallball_hover"));
	m_pItemBar->addItem(new ItemBox(pGui, UNKNOWN, -1, "item_unknown", "item_unknown_hover"));
	
	m_pQuickMenu = new QuickMenu(pGui);
	m_pPopup = new PopUpBox(pGui);
}

void escape_key_press_function() {
	m_pQuickMenu->setVisible(true);
}

void exit_button_pressed_function() {
	m_pPopup->showMessage(0, "Are you sure?", this); 
	m_pPopup->dismiss();
}