#include "SideBar.hpp"

SideBar::SideBar()
	: sf::Drawable(), sf::Transformable(), mNextPieceVArray(sf::PrimitiveType::Quads, 4 * Piece::COUNT_TILES)
{
	mCadreNextPiece.setPosition(0, 0);

	sf::Vertex *vertex = nullptr;
	for (int i = 0; i < Piece::COUNT_TILES; ++i) {
		vertex = &mNextPieceVArray[i * 4];

		vertex[0].texCoords = sf::Vector2f(0, 0);
		vertex[1].texCoords = sf::Vector2f(TILE_SIZE, 0);
		vertex[2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE);
		vertex[3].texCoords = sf::Vector2f(0, TILE_SIZE);

		vertex[0].color = sf::Color::Transparent;
		vertex[1].color = sf::Color::Transparent;
		vertex[2].color = sf::Color::Transparent;
		vertex[3].color = sf::Color::Transparent;
	}

	mTxtNextPiece.setString("Prochaine Piece :");
	mTxtNextPiece.setCharacterSize(22);
	mTxtNextPiece.setFillColor(sf::Color(123, 123, 123));

	mTxtScore.setString("Score : ");
	mTxtScore.setCharacterSize(34);
	mTxtScore.setFillColor(sf::Color(123, 123, 123));

	mTxtHighScore.setString("Meilleur Score : ");
	mTxtHighScore.setCharacterSize(28);
	mTxtHighScore.setFillColor(sf::Color(123, 123, 123));
}
SideBar::~SideBar() { }

void SideBar::setFont(sf::Font const& font) {
	mTxtNextPiece.setFont(font);
	mTxtScore.setFont(font);
	mTxtHighScore.setFont(font);
}
void SideBar::setNextPiece(Piece *piece) {
	mNextPiece = piece;
	sf::Color color = Piece::getColorByBlockType(mNextPiece->getBlockType());
	vector<sf::Vector2i> vec(mNextPiece->getTilesLocalCoords());

	sf::Vertex *vertex = nullptr;
	for (int i = 0; i < Piece::COUNT_TILES; ++i) {
		vertex = &mNextPieceVArray[i * 4];

		vertex[0].position = sf::Vector2f(vec.at(i).x * TILE_SIZE, vec.at(i).y * TILE_SIZE);
		vertex[1].position = sf::Vector2f((vec.at(i).x + 1) * TILE_SIZE, vec.at(i).y * TILE_SIZE);
		vertex[2].position = sf::Vector2f((vec.at(i).x + 1) * TILE_SIZE, (vec.at(i).y + 1) * TILE_SIZE);
		vertex[3].position = sf::Vector2f(vec.at(i).x * TILE_SIZE, (vec.at(i).y + 1) * TILE_SIZE);

		vertex[0].color = color;
		vertex[1].color = color;
		vertex[2].color = color;
		vertex[3].color = color;
	}
}

void SideBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mCadreNextPiece, states);
	target.draw(mTxtNextPiece, states);
	target.draw(mNextPieceVArray, states);
	target.draw(mTxtScore, states);
	target.draw(mTxtHighScore, states);
}
