#include "PauseMenu.hpp"

PauseMenu::PauseMenu()
	: AbstractMenu()
{
	mPausedTxt.setString(" - Paused - ");
	mPausedTxt.setCharacterSize(32);
	mPausedTxt.setFillColor(sf::Color(120, 120, 120));

	mResumeTxt.setString("Resume Game");
	mResumeTxt.setCharacterSize(28);
	mResumeTxt.setFillColor(sf::Color(120, 120, 120));
	/*
	mOptionsTxt.setString("Options");
	mOptionsTxt.setCharacterSize(28);
	mOptionsTxt.setFillColor(sf::Color(120, 120, 120));
	*/
	mMainMenuTxt.setString("Main Menu");
	mMainMenuTxt.setCharacterSize(28);
	mMainMenuTxt.setFillColor(sf::Color(120, 120, 120));
}
PauseMenu::~PauseMenu() {
}

void PauseMenu::setSelection(int sel) {
	mSel = sel;

	if (mSel < 0)
		mSel = 0;
	else if (mSel >= PauseSelection::PauseCount)
		mSel = PauseCount - 1;

	switch (mSel)
	{
	case PauseSelection::RESUME:
		mTriangleSel.setPosition(mResumeTxt.getGlobalBounds().left - 20,
			mResumeTxt.getGlobalBounds().top + (mResumeTxt.getLocalBounds().height - mTriangleSel.getLocalBounds().height) / 2);
		break;
		/*
		case PauseSelection::OPTIONS:
			mTriangleSel.setPosition(mOptionsTxt.getGlobalBounds().left - 20,
				mOptionsTxt.getGlobalBounds().top + (mOptionsTxt.getLocalBounds().height - mTriangleSel.getLocalBounds().height) / 2);
			break;
		*/
	case PauseSelection::MAINMENU:
		mTriangleSel.setPosition(mMainMenuTxt.getGlobalBounds().left - 20,
			mMainMenuTxt.getGlobalBounds().top + (mMainMenuTxt.getLocalBounds().height - mTriangleSel.getLocalBounds().height) / 2);
		break;
	default:
		break;
	}
}

void PauseMenu::setMenuSize(sf::Vector2f const & size) {
	AbstractMenu::setMenuSize(size);

	mPausedTxt.setPosition(sf::Vector2f((mMenuFrame.getSize().x - mPausedTxt.getGlobalBounds().width) / 2, 100));
	mResumeTxt.setPosition(sf::Vector2f((mMenuFrame.getSize().x - mResumeTxt.getGlobalBounds().width) / 2, 200));
	//mOptionsTxt.setPosition(sf::Vector2f((mMenuFrame.getSize().x - mOptionsTxt.getGlobalBounds().width) / 2, 300));
	mMainMenuTxt.setPosition(sf::Vector2f((mMenuFrame.getSize().x - mMainMenuTxt.getGlobalBounds().width) / 2, 400));
}
void PauseMenu::setFont(sf::Font const& f) {
	mPausedTxt.setFont(f);
	mResumeTxt.setFont(f);
	//mOptionsTxt.setFont(f);
	mMainMenuTxt.setFont(f);
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mMenuFrame, states);

	target.draw(mPausedTxt, states);
	target.draw(mResumeTxt, states);
	//target.draw(mOptionsTxt, states);
	target.draw(mMainMenuTxt, states);

	target.draw(mTriangleSel, states);
}