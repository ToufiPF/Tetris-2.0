#pragma once

#include <SFML/Graphics.hpp>
#include "../main.hpp"
#include "AbstractMenu.hpp"

class MainMenu : public AbstractMenu
{
public:
	enum MainSelection {
		NEW_GAME = 0, OPTIONS, QUIT, MainCount
	};

public:
	MainMenu();
	~MainMenu();

	void setSelection(int sel);
	void setFont(sf::Font const& f);
	void setMenuSize(sf::Vector2f const& size);

protected:
	sf::Text mTitleTxt, mNewGameTxt, mOptionsTxt, mQuitTxt;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
