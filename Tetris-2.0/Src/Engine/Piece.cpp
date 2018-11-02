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
	// On definit la taille de la matrice en fonction du type
	switch (mPieceType) {
	case BlockType::Cube:
		MATRICE_SIZE = 2;
		break;
	case BlockType::Line:
		MATRICE_SIZE = 4;
		break;
	case BlockType::T:
		MATRICE_SIZE = 3;
		break;
	case BlockType::L:
		MATRICE_SIZE = 3;
		break;
	case BlockType::ReversedL:
		MATRICE_SIZE = 3;
		break;
	case BlockType::Stairs:
		MATRICE_SIZE = 3;
		break;
	case BlockType::ReversedStairs:
		MATRICE_SIZE = 3;
		break;
	default:
		break;
	}

	mMatrice.resize(MATRICE_SIZE);
	for (int i = 0; i < MATRICE_SIZE; i++)
		mMatrice[i].resize(MATRICE_SIZE, BlockType::Void);

	// On dessine les pieces dans la matrice
	switch (mPieceType) {
	case BlockType::Cube:
		mMatrice[0][0] = BlockType::Cube;
		mMatrice[1][0] = BlockType::Cube;
		mMatrice[1][1] = BlockType::Cube;
		mMatrice[0][1] = BlockType::Cube;
		break;
	case BlockType::Line:
		mMatrice[0][0] = BlockType::Line;
		mMatrice[0][1] = BlockType::Line;
		mMatrice[0][2] = BlockType::Line;
		mMatrice[0][3] = BlockType::Line;
		break;
	case BlockType::T:
		mMatrice[0][0] = BlockType::T;
		mMatrice[1][0] = BlockType::T;
		mMatrice[2][0] = BlockType::T;
		mMatrice[1][1] = BlockType::T;
		break;
	case BlockType::L:
		mMatrice[0][0] = BlockType::L;
		mMatrice[1][0] = BlockType::L;
		mMatrice[2][0] = BlockType::L;
		mMatrice[0][1] = BlockType::L;
		break;
	case BlockType::ReversedL:
		mMatrice[0][0] = BlockType::ReversedL;
		mMatrice[1][0] = BlockType::ReversedL;
		mMatrice[2][0] = BlockType::ReversedL;
		mMatrice[2][1] = BlockType::ReversedL;
		break;
	case BlockType::Stairs:
		mMatrice[1][0] = BlockType::Stairs;
		mMatrice[2][0] = BlockType::Stairs;
		mMatrice[0][1] = BlockType::Stairs;
		mMatrice[1][1] = BlockType::Stairs;
		break;
	case BlockType::ReversedStairs:
		mMatrice[0][0] = BlockType::ReversedStairs;
		mMatrice[1][0] = BlockType::ReversedStairs;
		mMatrice[1][1] = BlockType::ReversedStairs;
		mMatrice[2][1] = BlockType::ReversedStairs;
		break;
	default:
		break;
	}
}
Piece::~Piece() {
}

vector<sf::Vector2i> Piece::getTilesLocalCoords() {
	std::vector<sf::Vector2i> solidTiles;
	for (int x = 0; x < MATRICE_SIZE; x++)
		for (int y = 0; y < MATRICE_SIZE; y++)
			if (mMatrice[x][y] != BlockType::Void)
				solidTiles.push_back(sf::Vector2i(x, y));

	return solidTiles;
}
vector<sf::Vector2i> Piece::getTilesGlobalCoords() {
	std::vector<sf::Vector2i> solidTiles(getTilesLocalCoords());
	for (unsigned int i = 0; i < solidTiles.size(); i++) {
		solidTiles[i].x += mTopLeftPos.x;
		solidTiles[i].y += mTopLeftPos.y;
	}

	return solidTiles;
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
	BlockType buffer[4][4];

	for (int i = 0; i < MATRICE_SIZE; i++)
		for (int j = 0; j < MATRICE_SIZE; j++)
			buffer[MATRICE_SIZE - 1 - i][j] = mMatrice[j][i];

	for (int i = 0; i < MATRICE_SIZE; i++)
		for (int j = 0; j < MATRICE_SIZE; j++)
			mMatrice[i][j] = buffer[i][j];
}
void Piece::rotateRight() {
	BlockType buffer[4][4];

	for (int i = 0; i < MATRICE_SIZE; i++)
		for (int j = 0; j < MATRICE_SIZE; j++)
			buffer[j][MATRICE_SIZE - 1 - i] = mMatrice[i][j];

	for (int i = 0; i < MATRICE_SIZE; i++)
		for (int j = 0; j < MATRICE_SIZE; j++)
			mMatrice[i][j] = buffer[i][j];
}