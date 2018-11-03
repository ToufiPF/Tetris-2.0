#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "AbstractMenu.hpp"

class PauseMenu : public AbstractMenu
{
public:
	enum PauseSelection {
		RESUME = 0, MAINMENU, PauseCount
	};

public:
	PauseMenu();
	~PauseMenu();

	void setSelection(int sel);

	void setMenuSize(sf::Vector2f const & size);
	void setFont(sf::Font const& f);

protected:
	sf::Text mPausedTxt, mResumeTxt, /*mOptionsTxt,*/ mMainMenuTxt;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
