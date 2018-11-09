#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include "SFML/Graphics.hpp"
#include "AbstractMenu.hpp"
#include "../main.hpp"

class GameOverMenu : public AbstractMenu
{
public:
	GameOverMenu();
	~GameOverMenu();

	void setMenuSize(sf::Vector2f const & size);
	void setFont(sf::Font const& f);

	void setScore(sf::Uint64 score);

protected:
	sf::Text mGameOverTxt, mYourScoreTxt, mIntScoreTxt;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
