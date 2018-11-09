#include "SideBar.hpp"

const sf::Vector2f SideBar::POSITION = sf::Vector2f(1000, 0);
const sf::Vector2f SideBar::SIZE = sf::Vector2f(300, GameEngine::SIZE.y);

SideBar::SideBar()
	: sf::Drawable(), sf::Transformable(), mNextPieceVArray(sf::PrimitiveType::Quads, 4 * Piece::COUNT_TILES)
{
	setPosition(POSITION);

	mCadreNextPiece.setFillColor(sf::Color(240, 240, 240));
	mCadreNextPiece.setSize(sf::Vector2f(4 * TILE_SIZE + 5, 4 * TILE_SIZE + 5));
	mCadreNextPiece.setPosition((SIZE.x - mCadreNextPiece.getSize().x) / 2.f, 20);

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
	mTxtNextPiece.setCharacterSize(18);
	mTxtNextPiece.setFillColor(sf::Color(220, 220, 220));
	mTxtNextPiece.setPosition(50, mCadreNextPiece.getPosition().y + mCadreNextPiece.getSize().y + 10);

	mTxtScore.setString("Score : 0");
	mTxtScore.setCharacterSize(20);
	mTxtScore.setFillColor(sf::Color(220, 220, 220));
	mTxtScore.setPosition(20, SIZE.y * 0.7f);

	mTxtHighScore.setString("Meilleur Score : ");
	mTxtHighScore.setCharacterSize(18);
	mTxtHighScore.setFillColor(sf::Color(220, 220, 220));
	mTxtHighScore.setPosition(20, mTxtScore.getPosition().y + 60);
}
SideBar::~SideBar() { }

void SideBar::init(sf::Font const& font, sf::Texture* textureBlock) {
	mTxtNextPiece.setFont(font);
	mTxtScore.setFont(font);
	mTxtHighScore.setFont(font);

	mTextureBlock = textureBlock;
	setScore(0);
	setHighScore(0);
}

void SideBar::setScore(sf::Uint64 score) {
	mTxtScore.setString("Score : " + std::to_string(score));
}
void SideBar::setHighScore(sf::Uint64 hScore) {
	mTxtHighScore.setString("Meilleur Score : " + std::to_string(hScore));
}

void SideBar::setNextPieceType(Piece::BlockType type) {
	if (type == Piece::BlockType::Void)
		return;

	if (mNextPiece != nullptr)
		delete mNextPiece;

	mNextPiece = new Piece(type);
	sf::Color color = Piece::getColorByBlockType(type);
	vector<sf::Vector2i> vec(mNextPiece->getTilesLocalCoords());

	sf::Vertex *vertex = nullptr;
	for (int i = 0; i < Piece::COUNT_TILES; ++i) {
		vertex = &mNextPieceVArray[i * 4];

		vertex[0].position = sf::Vector2f((float)vec.at(i).x * TILE_SIZE, (float)vec.at(i).y * TILE_SIZE);
		vertex[1].position = sf::Vector2f((float)(vec.at(i).x + 1) * TILE_SIZE, (float)vec.at(i).y * TILE_SIZE);
		vertex[2].position = sf::Vector2f((float)(vec.at(i).x + 1) * TILE_SIZE, (float)(vec.at(i).y + 1) * TILE_SIZE);
		vertex[3].position = sf::Vector2f((float)vec.at(i).x * TILE_SIZE, (float)(vec.at(i).y + 1) * TILE_SIZE);

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

	sf::RenderStates stArray(states);
	sf::Transform tArray;
	tArray.translate(mCadreNextPiece.getPosition().x + 2.5f, mCadreNextPiece.getPosition().y + 2.5f);
	stArray.transform *= tArray;
	stArray.texture = mTextureBlock;
	target.draw(mNextPieceVArray, stArray);

	target.draw(mTxtScore, states);
	target.draw(mTxtHighScore, states);
}
