#include "OptionsMenu.hpp"

const float OptionsMenu::DIFFICULTY_BAR_WIDTH = 10.0f;
const float OptionsMenu::DIFFICULTY_BAR_HEIGHT = 40.0f;

const float OptionsMenu::VOLUME_BAR_MAX_WIDTH = 300.0f;
const float OptionsMenu::VOLUME_BAR_MIN_HEIGHT = 10.0f;
const float OptionsMenu::VOLUME_BAR_MAX_HEIGHT = 40.0f;

OptionsMenu::OptionsMenu()
	: AbstractMenu()
{
	mDifficultyTxt.setString("Difficulté : ");
	mDifficultyTxt.setFillColor(sf::Color(120, 120, 120));

	mBgmTxt.setString("BGM Volume : ");
	mBgmTxt.setFillColor(sf::Color(120, 120, 120));

	mSfxTxt.setString("SFX Volume : ");
	mSfxTxt.setFillColor(sf::Color(120, 120, 120));

	mSaveOptTxt.setString("Ok");
	mSaveOptTxt.setFillColor(sf::Color(120, 120, 120));
}
OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::setDifficultyValue(int difficulty) {
	mDifficultyBar = createDifficultyBar(
		sf::Vector2f(mDifficultyTxt.getGlobalBounds().left + mDifficultyTxt.getGlobalBounds().width + 20, mDifficultyTxt.getGlobalBounds().top),
		difficulty, 1, 10);
}
void OptionsMenu::setBgmVolumeValue(float bgmVol) {
	mBgmVolumeBar = createVolumeBar(
		sf::Vector2f(mBgmTxt.getGlobalBounds().left + mBgmTxt.getGlobalBounds().width + 20, mBgmTxt.getGlobalBounds().top + VOLUME_BAR_MAX_HEIGHT * .8f),
		bgmVol, 0.0f, 100.0f);
}
void OptionsMenu::setSfxVolumeValue(float sfxVol) {
	mSfxVolumeBar = createVolumeBar(
		sf::Vector2f(mSfxTxt.getGlobalBounds().left + mSfxTxt.getGlobalBounds().width + 20, mSfxTxt.getGlobalBounds().top + VOLUME_BAR_MAX_HEIGHT * .8f),
		sfxVol, 0.0f, 100.0f);
}

void OptionsMenu::setSelection(int sel) {
	mSel = sel;

	if (mSel < 0)
		mSel = 0;
	else if (mSel >= OptionSelection::OptionCount)
		mSel = OptionSelection::OptionCount - 1;

	switch (mSel) {
	case OptionSelection::DIFFICULTY:
		mTriangleSel.setPosition(mDifficultyTxt.getGlobalBounds().left - 20,
			mDifficultyTxt.getGlobalBounds().top + (mDifficultyTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	case OptionSelection::BGM_VOL:
		mTriangleSel.setPosition(mBgmTxt.getGlobalBounds().left - 20,
			mBgmTxt.getGlobalBounds().top + (mBgmTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	case  OptionSelection::SFX_VOL:
		mTriangleSel.setPosition(mSfxTxt.getGlobalBounds().left - 20,
			mSfxTxt.getGlobalBounds().top + (mSfxTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	case OptionSelection::APPLY:
		mTriangleSel.setPosition(mSaveOptTxt.getGlobalBounds().left - 20,
			mSaveOptTxt.getGlobalBounds().top + (mSaveOptTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	default:
		break;
	}
}
void OptionsMenu::setFont(sf::Font const& f) {
	mDifficultyTxt.setFont(f);
	mBgmTxt.setFont(f);
	mSfxTxt.setFont(f);
	mSaveOptTxt.setFont(f);
}
void OptionsMenu::setMenuSize(sf::Vector2f const& size) {
	AbstractMenu::setMenuSize(size);

	mDifficultyTxt.setPosition(50, 100);
	mBgmTxt.setPosition(50, 200);
	mSfxTxt.setPosition(50, 300);
	mSaveOptTxt.setPosition((mMenuFrame.getSize().x - mSaveOptTxt.getLocalBounds().width) / 2, 400);
}

sf::VertexArray OptionsMenu::createDifficultyBar(sf::Vector2f const & pos, int value, int min, int max)
{
	int barCount = value - min + 1;

	sf::VertexArray difficultyBar(sf::PrimitiveType::Quads, 4 * barCount);

	float posLeft = pos.x;

	for (int i = 0; i < barCount * 4; i += 4) {
		posLeft = pos.x + i * 0.5f * DIFFICULTY_BAR_WIDTH;

		difficultyBar[i].position = sf::Vector2f(posLeft, pos.y);
		difficultyBar[i + 1].position = sf::Vector2f(posLeft + DIFFICULTY_BAR_WIDTH, pos.y);
		difficultyBar[i + 2].position = sf::Vector2f(posLeft + DIFFICULTY_BAR_WIDTH, pos.y + DIFFICULTY_BAR_HEIGHT);
		difficultyBar[i + 3].position = sf::Vector2f(posLeft, pos.y + DIFFICULTY_BAR_HEIGHT);
	}

	return difficultyBar;
}

sf::ConvexShape OptionsMenu::createVolumeBar(sf::Vector2f const & pos, float value, float min, float max)
{
	if (max - min == 0)
		max++;

	float barWidth = (value - min) / (max - min) * VOLUME_BAR_MAX_WIDTH;
	//float barHeight = (value - min) / (max - min) * (VOLUME_BAR_MAX_HEIGHT - VOLUME_BAR_MIN_HEIGHT);
	float barHeight = VOLUME_BAR_MIN_HEIGHT + (value - min) / (max - min) * (VOLUME_BAR_MAX_HEIGHT - VOLUME_BAR_MIN_HEIGHT);

	sf::ConvexShape volumeBar(4);
	volumeBar.setFillColor(sf::Color(120, 120, 120));

	volumeBar.setPoint(0, sf::Vector2f(pos.x, pos.y));
	volumeBar.setPoint(1, sf::Vector2f(pos.x + barWidth, pos.y));
	volumeBar.setPoint(2, sf::Vector2f(pos.x + barWidth, pos.y - barHeight));
	volumeBar.setPoint(3, sf::Vector2f(pos.x, pos.y - VOLUME_BAR_MIN_HEIGHT));

	return volumeBar;
}

void OptionsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mMenuFrame, states);

	target.draw(mDifficultyTxt, states);
	target.draw(mDifficultyBar, states);
	target.draw(mBgmTxt, states);
	target.draw(mBgmVolumeBar, states);
	target.draw(mSfxTxt, states);
	target.draw(mSfxVolumeBar, states);
	target.draw(mSaveOptTxt, states);

	target.draw(mTriangleSel, states);
}