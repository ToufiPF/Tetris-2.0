#include "Piece.hpp"

const sf::Uint8 ALPHA = sf::Uint8(200);

sf::Color Piece::getColorByBlockType(BlockType const& type) {
	switch (type) {
	case BlockType::Cube:
		return sf::Color(55, 85, 255, ALPHA);
	case BlockType::Line:
		return sf::Color(230, 65, 170, ALPHA);
	case BlockType::T:
		return sf::Color(225, 230, 25, ALPHA);
	case BlockType::L:
		return sf::Color(255, 15, 50, ALPHA);
	case BlockType::ReversedL:
		return sf::Color(80, 255, 30, ALPHA);
	case BlockType::Stairs:
		return sf::Color(15, 205, 235, ALPHA);
	case BlockType::ReversedStairs:
		return sf::Color(255, 170, 5, ALPHA);
	default:
		return sf::Color::Transparent;
	}
}

Piece::Piece(BlockType const& type)
	: mPieceType(type)
{
	// On construit la piece selon son type
	switch (mPieceType) {
	case BlockType::Cube:
		mPosRelativeCentreRot[0] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[1] = sf::Vector2i(1, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(0, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(1, 1);

		mCentreRotPos.x = 0;
		mCentreRotPos.y = 0;
		break;
	case BlockType::Line:
		mPosRelativeCentreRot[0] = sf::Vector2i(0, -1);
		mPosRelativeCentreRot[1] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(0, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(0, 2);

		mCentreRotPos.x = 0;
		mCentreRotPos.y = 1;
		break;
	case BlockType::T:
		mPosRelativeCentreRot[0] = sf::Vector2i(-1, 0);
		mPosRelativeCentreRot[1] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(1, 0);
		mPosRelativeCentreRot[3] = sf::Vector2i(0, 1);

		mCentreRotPos.x = 1;
		mCentreRotPos.y = 0;
		break;
	case BlockType::L:
		mPosRelativeCentreRot[0] = sf::Vector2i(0, -1);
		mPosRelativeCentreRot[1] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(0, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(1, 1);

		mCentreRotPos.x = 0;
		mCentreRotPos.y = 1;
		break;
	case BlockType::ReversedL:
		mPosRelativeCentreRot[0] = sf::Vector2i(1, -1);
		mPosRelativeCentreRot[1] = sf::Vector2i(1, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(0, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(1, 1);

		mCentreRotPos.x = 0;
		mCentreRotPos.y = 1;
		break;
	case BlockType::Stairs:
		mPosRelativeCentreRot[0] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[1] = sf::Vector2i(1, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(-1, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(0, 1);

		mCentreRotPos.x = 1;
		mCentreRotPos.y = 0;
		break;
	case BlockType::ReversedStairs:
		mPosRelativeCentreRot[0] = sf::Vector2i(-1, 0);
		mPosRelativeCentreRot[1] = sf::Vector2i(0, 0);
		mPosRelativeCentreRot[2] = sf::Vector2i(0, 1);
		mPosRelativeCentreRot[3] = sf::Vector2i(1, 1);

		mCentreRotPos.x = 1;
		mCentreRotPos.y = 0;
		break;
	default:
		break;
	}
}
Piece::~Piece() {
}

vector<sf::Vector2i> Piece::getTilesLocalCoords() {
	vector<sf::Vector2i> tiles;
	for (int i = 0; i < COUNT_TILES; ++i)
		tiles.push_back(sf::Vector2i(mPosRelativeCentreRot[i].x + mCentreRotPos.x, mPosRelativeCentreRot[i].y + mCentreRotPos.y));

	return tiles;
}
vector<sf::Vector2i> Piece::getTilesGlobalCoords() {
	std::vector<sf::Vector2i> tiles(getTilesLocalCoords());
	for (unsigned int i = 0; i < tiles.size(); ++i) {
		tiles[i].x += mTopLeftPos.x;
		tiles[i].y += mTopLeftPos.y;
	}

	return tiles;
}

void Piece::setLeftTopPosition(int x, int y) {
	mTopLeftPos.x = x;
	mTopLeftPos.y = y;
}

void Piece::move(int x, int y) {
	mTopLeftPos.x += x;
	mTopLeftPos.y += y;
}

void Piece::rotateLeft() {
	if (mPieceType == BlockType::Cube)
		return;

	// On applique la matrice de rotation
	// | 0  1|   |x|   | y|
	// |-1  0| * |y| = |-x|
	int tmp = 0;
	for (int i = 0; i < COUNT_TILES; ++i) {
		tmp = mPosRelativeCentreRot[i].x;
		mPosRelativeCentreRot[i].x = mPosRelativeCentreRot[i].y;
		mPosRelativeCentreRot[i].y = -1 * tmp;
	}
}
void Piece::rotateRight() {
	if (mPieceType == BlockType::Cube)
		return;

	// On applique la matrice de rotation
	// | 0 -1|   |x|   |-y|
	// | 1  0| * |y| = | x|
	int tmp = 0;
	for (int i = 0; i < COUNT_TILES; ++i) {
		tmp = mPosRelativeCentreRot[i].x;
		mPosRelativeCentreRot[i].x = -1 * mPosRelativeCentreRot[i].y;
		mPosRelativeCentreRot[i].y = tmp;
	}
}
