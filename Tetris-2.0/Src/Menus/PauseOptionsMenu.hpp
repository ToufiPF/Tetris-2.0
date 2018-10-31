#ifndef PAUSEOPTIONSMENU_HPP
#define PAUSEOPTIONSMENU_HPP

#include "OptionsMenu.hpp"

class PauseOptionsMenu : public OptionsMenu
{
public:
	enum PauseOptionSelection {
		BGM_VOL = 0, SFX_VOL, APPLY, PauseOptionCount
	};
protected:
	OptionsMenu::OptionSelection;

public:
	PauseOptionsMenu();
	~PauseOptionsMenu();

	void setSelection(int sel);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif