#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu()
	: AbstractMenu()
{
	mGameOverTxt.setString("Game Over !");
	mGameOverTxt.setCharacterSize(44);
	mGameOverTxt.setFillColor(sf::Color(200, 70, 70));

	mYourScoreTxt.setString("Your score is : ");
	mYourScoreTxt.setFillColor(sf::Color(200, 200, 200));

	mIntScoreTxt.setString("0");
	mIntScoreTxt.setFillColor(sf::Color(200, 200, 200));
}
GameOverMenu::~GameOverMenu() {
}

void GameOverMenu::setMenuSize(sf::Vector2f const & size) {
	AbstractMenu::setMenuSize(size);

	mGameOverTxt.setPosition((mMenuFrame.getSize().x - mGameOverTxt.getGlobalBounds().width) / 2, 250);
	mYourScoreTxt.setPosition((mMenuFrame.getSize().x - mYourScoreTxt.getGlobalBounds().width) / 2, 400);
	mIntScoreTxt.setPosition((mMenuFrame.getSize().x - mIntScoreTxt.getGlobalBounds().width) / 2, mYourScoreTxt.getGlobalBounds().top + mYourScoreTxt.getGlobalBounds().height + 20);
}
void GameOverMenu::setFont(sf::Font const& f) {
	mGameOverTxt.setFont(f);
	mYourScoreTxt.setFont(f);
	mIntScoreTxt.setFont(f);
}

void GameOverMenu::setScore(unsigned long score) {
	mIntScoreTxt.setString(std::to_string(score));
	mIntScoreTxt.setPosition((mMenuFrame.getSize().x - mIntScoreTxt.getGlobalBounds().width) / 2, mYourScoreTxt.getGlobalBounds().top + mYourScoreTxt.getGlobalBounds().height + 20);
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(mMenuFrame, states);

	target.draw(mGameOverTxt, states);
	target.draw(mYourScoreTxt, states);
	target.draw(mIntScoreTxt, states);
}
