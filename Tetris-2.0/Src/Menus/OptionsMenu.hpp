#ifndef OPTIONSMENU_HPP
#define OPTIONSMENU_HPP

#include "AbstractMenu.hpp"

class OptionsMenu : public AbstractMenu
{
public:
	enum OptionSelection {
		DIFFICULTY = 0, BGM_VOL, SFX_VOL, APPLY, OptionCount
	};

	static const float DIFFICULTY_BAR_WIDTH;
	static const float DIFFICULTY_BAR_HEIGHT;

	static const float VOLUME_BAR_MAX_WIDTH;
	static const float VOLUME_BAR_MIN_HEIGHT;
	static const float VOLUME_BAR_MAX_HEIGHT;

public:
	OptionsMenu();
	~OptionsMenu();

	void setDifficultyValue(int difficulty);
	void setBgmVolumeValue(float bgmVol);
	void setSfxVolumeValue(float sfxVol);

	void setSelection(int sel);
	void setFont(sf::Font const& f);
	void setMenuSize(sf::Vector2f const& size);

protected:
	sf::Text mDifficultyTxt, mBgmTxt, mSfxTxt, mSaveOptTxt;
	sf::VertexArray mDifficultyBar;
	sf::ConvexShape mBgmVolumeBar, mSfxVolumeBar;

	// Dessine une suite de rectangle pour la difficulte
	static sf::VertexArray createDifficultyBar(sf::Vector2f const& pos, int value, int min = 1, int max = 10);

	// Dessine un trapeze pour la barre de volume
	static sf::ConvexShape createVolumeBar(sf::Vector2f const& pos, float value, float min = 0.0f, float max = 100.0f);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
