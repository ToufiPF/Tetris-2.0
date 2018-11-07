#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>

#include <map>
#include "../main.hpp"

class Piece
{
public:
	enum BlockType : short {
		Void = 0, Cube, Line, T, L, ReversedL, Stairs, ReversedStairs
	};

	static sf::Color getColorByBlockType(BlockType const& type);
	static const int COUNT_TILES = 4;

public:
	Piece(BlockType const& type = BlockType::Cube);
	~Piece();

	BlockType getBlockType() { return mPieceType; };

	vector<sf::Vector2i> getTilesLocalCoords();
	vector<sf::Vector2i> getTilesGlobalCoords();

	void setLeftTopPosition(int x, int y);
	void move(int x, int y);
	void rotateLeft();
	void rotateRight();

protected:
	BlockType mPieceType;

	sf::Vector2i mTopLeftPos;
	sf::Vector2i mCentreRotPos;
	sf::Vector2i mPosRelativeCentreRot[COUNT_TILES];
};

#endif
