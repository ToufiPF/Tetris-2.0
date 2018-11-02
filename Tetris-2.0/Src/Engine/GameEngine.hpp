#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "../main.hpp"
#include "Piece.hpp"

class GameEngine : public sf::Drawable, public sf::Transformable
{
public:
	GameEngine();
	~GameEngine();

	bool init(sf::Texture *textureBlock);

	void updateGame(sf::Time const& elapsed);
	void processKeyEvent(sf::Event const& e);

	void setDifficulty(int difficulty) {
		if (difficulty < 1)
			mDifficulty = 1;
		else if (difficulty > 10)
			mDifficulty = 10;
		else
			mDifficulty = difficulty;
	};
	int getDifficulty() const { return mDifficulty; };

	unsigned long int getScore() const { return mScore; };
	bool isGameOver() const { return mIsGameOver; };

protected:
	sf::Time computeFrameTime(sf::Time elapsedTotal, int difficulty);
	// Donne la couleur au vertexArray
	void paintLevel();
	// Donne la couleur a la piece active
	void paintActivePiece();

	// Dessine le vertexArray
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Efface les rows fournies, et decale le niveau vers le bas
	void clearCompletedRows(vector<int> &rowsToClear);

	// Genere un nouveau block actif
	// Renvoie false si game over
	bool generateNextBlock();

	bool isMoveLeftAllowed(Piece *piece) const;
	bool isMoveRightAllowed(Piece *piece) const;
	bool isMoveDownAllowed(Piece *piece) const;

	void rotateLeftIfAllowed(Piece *piece);
	void rotateRightIfAllowed(Piece *piece);

protected:
	sf::Vector2u mSize;

	vector< vector< Piece::BlockType > > mTileMap;
	sf::VertexArray mVArray;
	Piece *mActivePiece;
	Piece *mNextPiece;

	sf::Texture *mTextureBlock;

	unsigned long int mScore;
	int mDifficulty;
	sf::Time mFrameTime;
	sf::Time mElapsedSinceLastFrame;
	sf::Time mElapsedTotal;

	bool mIsGameOver;

	// Mouvements
	bool mStrafeLeft, mStrafeRight;
	bool mRotateLeft, mRotateRight;
	bool mAccelerateDown, mInstantDown;
};

#endif