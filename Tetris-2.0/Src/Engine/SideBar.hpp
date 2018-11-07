#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include <SFML/Graphics.hpp>
#include "Piece.hpp"

class SideBar : public sf::Drawable, public sf::Transformable
{
public:
	SideBar();
	~SideBar();

	void setNextPiece(Piece *piece);
	void setFont(sf::Font const& font);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

	sf::RectangleShape mCadreNextPiece;
	sf::Text mTxtNextPiece;
	Piece* mNextPiece;
	sf::VertexArray mNextPieceVArray;

	sf::Text mTxtScore;

	sf::Text mTxtHighScore;
};

#endif
