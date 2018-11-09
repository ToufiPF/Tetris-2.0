#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include <SFML/Graphics.hpp>
#include "Piece.hpp"
#include "GameEngine.hpp"

class SideBar : public sf::Drawable, public sf::Transformable
{
public:
	static const sf::Vector2f POSITION;
	static const sf::Vector2f SIZE;
public:
	SideBar();
	~SideBar();

	void init(sf::Font const& font, sf::Texture *textureBlock);

	void setNextPieceType(Piece::BlockType type);
	void setScore(sf::Uint64 score);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

	sf::RectangleShape mCadreNextPiece;
	sf::Text mTxtNextPiece;

	Piece* mNextPiece;
	sf::VertexArray mNextPieceVArray;
	sf::Texture* mTextureBlock;

	sf::Text mTxtScore;

	sf::Text mTxtHighScore;
};

#endif
