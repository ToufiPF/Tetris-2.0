#include "SideBar.hpp"

SideBar::SideBar()
	: sf::Drawable(), sf::Transformable()
{
	mCadreNextPiece.setPosition(0, 0);

	mTxtNextPiece.setString("Prochaine Piece :");
	mTxtNextPiece.setCharacterSize(22);
	mTxtNextPiece.setColor(sf::Color(123, 123, 123));

	mTxtScore.setString("Score : ");
	mTxtScore.setCharacterSize(34);
	mTxtScore.setColor(sf::Color(123, 123, 123));

	mTxtHighScore.setString("Meilleur Score : ");
	mTxtHighScore.setCharacterSize(28);
	mTxtHighScore.setColor(sf::Color(123, 123, 123));
}
SideBar::~SideBar() { }

void SideBar::setFont(sf::Font const& font) {
	mTxtNextPiece.setFont(font);
	mTxtScore.setFont(font);
	mTxtHighScore.setFont(font);
}

void SideBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mCadreNextPiece, states);
	target.draw(mTxtNextPiece, states);
	//target.draw(mNextPiece, states);
	target.draw(mTxtScore, states);
	target.draw(mTxtHighScore, states);
}
