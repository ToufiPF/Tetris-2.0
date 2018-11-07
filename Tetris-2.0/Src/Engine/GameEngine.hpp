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

	sf::Uint64 getScore() const { return mScore; };
	bool isGameOver() const { return mIsGameOver; };

	// Retourne la taille du niveau de tetris
	static sf::Vector2f getLocalSize() { return sf::Vector2f(TILE_SIZE * COUNT_TILES_WIDTH, TILE_SIZE * COUNT_TILES_HEIGHT); }
	// Calcule le temps d'une frame en fonction du temps ecoule et de la difficulte
	static sf::Time computeFrameTime(sf::Time elapsedTotal, int difficulty);

protected:
	// Augmente le score de s * multiplicator * difficulty
	void increaseScore(sf::Uint32 s, float multiplicator = 1.f);

	// Donne la couleur au vertexArray
	void paintLevel();
	// Donne la couleur a la piece active
	void paintActivePiece();

	// Dessine le vertexArray
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Appele quand une piece touche le fond
	void placeActivePieceInTileMap();
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
	vector< vector< Piece::BlockType > > mTileMap;
	sf::VertexArray mVArray;
	Piece *mActivePiece;
	Piece *mNextPiece;

	sf::Texture *mTextureBlock;

	sf::Uint64 mScore;
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
