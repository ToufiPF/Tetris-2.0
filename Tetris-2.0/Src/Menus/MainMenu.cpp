#include "MainMenu.hpp"

MainMenu::MainMenu()
	: AbstractMenu()
{
	mTitleTxt.setString("Tetris !");
	mTitleTxt.setFillColor(sf::Color(180, 70, 70));
	mTitleTxt.setCharacterSize(72);

	mNewGameTxt.setString("Nouvelle Partie");
	mNewGameTxt.setFillColor(sf::Color(120, 120, 120));

	mOptionsTxt.setString("Options");
	mOptionsTxt.setFillColor(sf::Color(120, 120, 120));

	mQuitTxt.setString("Quitter");
	mQuitTxt.setFillColor(sf::Color(120, 120, 120));
}
MainMenu::~MainMenu()
{
}

void MainMenu::setSelection(int selec) {
	mSel = selec;

	if (mSel < 0)
		mSel = 0;
	if (mSel >= MainSelection::MainCount)
		mSel = MainSelection::MainCount - 1;

	const int OFFSET_TRIANGLE = -7;
	switch (mSel) {
	case MainSelection::NEW_GAME:
		mTriangleSel.setPosition(mNewGameTxt.getGlobalBounds().left - 20,
			mNewGameTxt.getGlobalBounds().top + (mNewGameTxt.getGlobalBounds().height - mTriangleSel.getLocalBounds().height) / 2 + OFFSET_TRIANGLE);
		break;

	case MainSelection::OPTIONS:
		mTriangleSel.setPosition(mOptionsTxt.getGlobalBounds().left - 20,
			mOptionsTxt.getGlobalBounds().top + (mOptionsTxt.getLocalBounds().height - mTriangleSel.getLocalBounds().height) / 2 + OFFSET_TRIANGLE);
		break;

	case MainSelection::QUIT:
		mTriangleSel.setPosition(mQuitTxt.getGlobalBounds().left - 20,
			mQuitTxt.getGlobalBounds().top + (mQuitTxt.getLocalBounds().height - mTriangleSel.getLocalBounds().height) / 2 + OFFSET_TRIANGLE);
		break;

	default:
		break;
	}
}

void MainMenu::setMenuSize(sf::Vector2f const & size)
{
	AbstractMenu::setMenuSize(size);

	mTitleTxt.setPosition((mMenuFrame.getSize().x - mTitleTxt.getLocalBounds().width) / 2, 50);
	mNewGameTxt.setPosition((mMenuFrame.getSize().x - mNewGameTxt.getLocalBounds().width) / 2, 200);
	mOptionsTxt.setPosition((mMenuFrame.getSize().x - mOptionsTxt.getLocalBounds().width) / 2, 300);
	mQuitTxt.setPosition((mMenuFrame.getSize().x - mQuitTxt.getLocalBounds().width) / 2, 400);
}

void MainMenu::setFont(sf::Font const& font) {
	mTitleTxt.setFont(font);
	mNewGameTxt.setFont(font);
	mOptionsTxt.setFont(font);
	mQuitTxt.setFont(font);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mMenuFrame, states);

	target.draw(mTitleTxt, states);
	target.draw(mNewGameTxt, states);
	target.draw(mOptionsTxt, states);
	target.draw(mQuitTxt, states);

	target.draw(mTriangleSel, states);
}