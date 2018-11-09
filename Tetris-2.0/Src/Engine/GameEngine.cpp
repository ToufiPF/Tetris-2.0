#include "GameEngine.hpp"

const sf::Vector2f GameEngine::POSITION = sf::Vector2f(0, 0);
const sf::Vector2f GameEngine::SIZE = sf::Vector2f(TILE_SIZE * COUNT_TILES_WIDTH, TILE_SIZE * COUNT_TILES_HEIGHT);

GameEngine::GameEngine()
	: sf::Drawable(), sf::Transformable(), mActivePiece(nullptr), mNextPiece(nullptr)
{
	srand((unsigned int)time(nullptr));

	setPosition(POSITION);

	mScore = 0;
	mDifficulty = 1;
	mIsGameOver = false;

	mStrafeLeft = mStrafeRight = false;
	mRotateLeft = mRotateRight = false;
	mAccelerateDown = mInstantDown = false;

	mFond.setPosition(0, 0);
	mFond.setSize(SIZE);
	mFond.setFillColor(sf::Color(55, 55, 55));
}
GameEngine::~GameEngine() {
}

bool GameEngine::init(sf::Texture *textureBlock) {
	if (textureBlock == nullptr)
		return false;

	mTextureBlock = textureBlock;

	srand((unsigned int)time(nullptr));

	mScore = 0;
	mIsGameOver = false;

	mStrafeLeft = mStrafeRight = false;
	mRotateLeft = mRotateRight = false;
	mAccelerateDown = mInstantDown = false;

	mElapsedSinceLastFrame = sf::Time::Zero;
	mElapsedTotal = sf::Time::Zero;

	mTileMap.resize(COUNT_TILES_WIDTH);
	for (unsigned int i = 0; i < mTileMap.size(); ++i)
		mTileMap[i].resize(COUNT_TILES_HEIGHT, Piece::BlockType::Void);

	mVArray.setPrimitiveType(sf::PrimitiveType::Quads);
	mVArray.resize(COUNT_TILES_WIDTH * COUNT_TILES_HEIGHT * 4);

	sf::Vertex *vertex = nullptr;
	for (unsigned int x = 0; x < COUNT_TILES_WIDTH; x++) {
		for (unsigned int y = 0; y < COUNT_TILES_HEIGHT; y++) {
			mTileMap[x][y] = Piece::BlockType::Void;
			vertex = &mVArray[(x + y * COUNT_TILES_WIDTH) * 4];
			vertex[0].position = sf::Vector2f((float)x * TILE_SIZE, (float)y * TILE_SIZE);
			vertex[1].position = sf::Vector2f((float)(x + 1) * TILE_SIZE, (float)y * TILE_SIZE);
			vertex[2].position = sf::Vector2f((float)(x + 1) * TILE_SIZE, (float)(y + 1) * TILE_SIZE);
			vertex[3].position = sf::Vector2f((float)x * TILE_SIZE, (float)(y + 1) * TILE_SIZE);

			vertex[0].texCoords = sf::Vector2f(0, 0);
			vertex[1].texCoords = sf::Vector2f(TILE_SIZE, 0);
			vertex[2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE);
			vertex[3].texCoords = sf::Vector2f(0, TILE_SIZE);

			vertex[0].color = sf::Color::Transparent;
			vertex[1].color = sf::Color::Transparent;
			vertex[2].color = sf::Color::Transparent;
			vertex[3].color = sf::Color::Transparent;
		}
	}

	generateNextBlock();

	return true;
}

void GameEngine::processKeyEvent(sf::Event const& e) {
	if (e.type == sf::Event::KeyPressed) {
		switch (e.key.code) {
		case sf::Keyboard::Q:
		case sf::Keyboard::Left:
			mStrafeLeft = true;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			mStrafeRight = true;
			break;

		case sf::Keyboard::A:
			mRotateLeft = true;
			break;
		case sf::Keyboard::E:
			mRotateRight = true;
			break;

		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			mAccelerateDown = true;
			break;
		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			mInstantDown = true;
			break;
		default:
			break;
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		switch (e.key.code) {
		case sf::Keyboard::Q:
		case sf::Keyboard::Left:
			mStrafeLeft = false;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			mStrafeRight = false;
			break;

		case sf::Keyboard::A:
			mRotateLeft = false;
			break;
		case sf::Keyboard::E:
			mRotateRight = false;
			break;

		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			mAccelerateDown = false;
			break;
		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			mInstantDown = false;
			break;
		default:
			break;
		}
	}
}

bool GameEngine::updateGame(sf::Time const& elapsed) {
	// Si il n'y a pas de bloc actif, c'est que l'on a pas commencé le jeu -> on quitte
	if (mActivePiece == nullptr)
		return false;

	bool piecePlacedInMap = false;

	mElapsedSinceLastFrame += elapsed;
	mElapsedTotal += elapsed;

	if (mInstantDown) {
		while (isMoveDownAllowed(mActivePiece)) {
			mActivePiece->move(0, 1);
		}
		mInstantDown = false;
		piecePlacedInMap = true;
		placeActivePieceInTileMap();
	}
	else {
		if (mStrafeLeft) {
			if (isMoveLeftAllowed(mActivePiece)) {
				mActivePiece->move(-1, 0);
				mStrafeLeft = false;
			}
		}
		else if (mStrafeRight) {
			if (isMoveRightAllowed(mActivePiece)) {
				mActivePiece->move(1, 0);
				mStrafeRight = false;
			}
		}

		if (mRotateLeft) {
			rotateLeftIfAllowed(mActivePiece);
		}
		else if (mRotateRight) {
			rotateRightIfAllowed(mActivePiece);
		}

		if (mAccelerateDown)
			mFrameTime = computeFrameTime(mElapsedTotal, mDifficulty) / sf::Int64(2);
		else
			mFrameTime = computeFrameTime(mElapsedTotal, mDifficulty);

		// On descend d'une case tous les ticks
		if (mElapsedSinceLastFrame > mFrameTime) {
			mElapsedSinceLastFrame = mElapsedSinceLastFrame % mFrameTime;

			// On vérifie si on peut descendre
			if (isMoveDownAllowed(mActivePiece))
				mActivePiece->move(0, 1);
			else {
				piecePlacedInMap = true;
				placeActivePieceInTileMap();
			}
		}
	}

	paintLevel();
	paintActivePiece();

	return piecePlacedInMap;
}

void GameEngine::increaseScore(sf::Uint32 s, float multiplicator) {
	mScore += (sf::Uint64) (s * multiplicator * mDifficulty);
}

void GameEngine::placeActivePieceInTileMap() {
	vector<sf::Vector2i> tilesBl(mActivePiece->getTilesGlobalCoords());

	std::set<int> listRows;
	vector<int> rowsToClear;

	// on écrit le bloc actif dans le level
	for (unsigned int i = 0; i < tilesBl.size(); i++) {
		mTileMap[tilesBl.at(i).x][tilesBl.at(i).y] = mActivePiece->getBlockType();

		listRows.insert(tilesBl.at(i).y);
	}

	// on vérifie si des lignes sont completes, en partant du bas.
	bool voidTileFound;
	for (std::set<int>::reverse_iterator it = listRows.rbegin(); it != listRows.rend(); it++) {
		voidTileFound = false;
		for (int x = 0; x < COUNT_TILES_WIDTH; x++) {
			if (getBlockAt(x, *it) == Piece::BlockType::Void) {
				voidTileFound = true;
				break;
			}
		}
		if (!voidTileFound)
			rowsToClear.push_back(*it);
	}
	increaseScore(100, (float)rowsToClear.size() * rowsToClear.size());

	// on nettoie les lignes completes
	clearCompletedRows(rowsToClear);

	// et on charge un nouveau bloc
	if (!generateNextBlock()) {
		//generateNewBlock renvoie false : c'est game over
		cout << endl << "FIN DU JEU" << endl;
		mIsGameOver = true;
	}
	increaseScore(10);
}
void GameEngine::clearCompletedRows(vector<int> &rowsToClear) {
	for (unsigned int i = 0; i < rowsToClear.size(); i++) {
		// on remplace les lignes inferieures par celles superieures
		for (int x = 0; x < COUNT_TILES_WIDTH; x++) {
			for (int y = rowsToClear.at(i); y >= 1; y--) {
				mTileMap[x][y] = mTileMap[x][y - 1];
			}
			// on n'oublie pas d'effacer celle du dessus
			mTileMap[x][0] = Piece::BlockType::Void;
		}

		// et on decale le reste des lignes a nettoyer
		for (unsigned int j = i + 1; j < rowsToClear.size(); j++) {
			rowsToClear[j]++;
		}
	}
}

bool GameEngine::generateNextBlock() {
	if (mActivePiece != nullptr) {
		delete mActivePiece;
		mActivePiece = nullptr;
	}

	int alea = 0;
	// Si il y a deja une nextPiece, on la rend active
	if (mNextPiece != nullptr) {
		mActivePiece = mNextPiece;
	}
	// Sinon, on cree l'active
	else {
		alea = rand() % 7 + 1;
		mActivePiece = new Piece((Piece::BlockType) alea);
	}

	mActivePiece->setLeftTopPosition(COUNT_TILES_WIDTH / 2 - 1, 0);

	// Puis on cree une nouvelle nextPiece
	alea = rand() % 7 + 1;
	mNextPiece = new Piece((Piece::BlockType) alea);

	for (unsigned int i = 0; i < mActivePiece->getTilesGlobalCoords().size(); i++)
		if (getBlockAt(mActivePiece->getTilesGlobalCoords().at(i).x, mActivePiece->getTilesGlobalCoords().at(i).y) != Piece::BlockType::Void)
			return false;

	return true;
}

bool GameEngine::isMoveLeftAllowed(Piece *piece) const {
	vector<sf::Vector2i> tiles(piece->getTilesGlobalCoords());

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i).x <= 0)
			return false;

		if (getBlockAt(tiles.at(i).x - 1, tiles.at(i).y) != Piece::BlockType::Void)
			return false;
	}
	return true;
}
bool GameEngine::isMoveRightAllowed(Piece *piece) const {
	vector<sf::Vector2i> tiles(piece->getTilesGlobalCoords());

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i).x >= COUNT_TILES_WIDTH - 1)
			return false;

		if (getBlockAt(tiles.at(i).x + 1, tiles.at(i).y) != Piece::BlockType::Void)
			return false;
	}
	return true;
}
bool GameEngine::isMoveDownAllowed(Piece *piece) const {
	vector<sf::Vector2i> tiles(piece->getTilesGlobalCoords());

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i).y >= COUNT_TILES_HEIGHT - 1)
			return false;

		if (getBlockAt(tiles.at(i).x, tiles.at(i).y + 1) != Piece::BlockType::Void)
			return false;
	}
	return true;
}

void GameEngine::rotateLeftIfAllowed(Piece *piece) {
	bool cancelRot = false;

	piece->rotateLeft();

	vector<sf::Vector2i> tilesBl(piece->getTilesGlobalCoords());

	for (unsigned int i = 0; i < tilesBl.size(); i++) {
		if (tilesBl.at(i).x < 0 || tilesBl.at(i).x >= COUNT_TILES_WIDTH) {
			cancelRot = true;
			break;
		}

		if (tilesBl.at(i).y < 0 || tilesBl.at(i).y >= COUNT_TILES_HEIGHT) {
			cancelRot = true;
			break;
		}

		if (getBlockAt(tilesBl.at(i).x, tilesBl.at(i).y) != Piece::BlockType::Void) {
			cancelRot = true;
			break;
		}
	}
	if (cancelRot)
		piece->rotateRight();
	else
		mRotateLeft = false;
}
void GameEngine::rotateRightIfAllowed(Piece *piece) {
	bool cancelRot = false;

	mActivePiece->rotateRight();

	vector<sf::Vector2i> tilesBl(piece->getTilesGlobalCoords());

	for (unsigned int i = 0; i < tilesBl.size(); i++) {
		if (tilesBl.at(i).x < 0 || tilesBl.at(i).x >= COUNT_TILES_WIDTH) {
			cancelRot = true;
			break;
		}

		if (tilesBl.at(i).y < 0 || tilesBl.at(i).y >= COUNT_TILES_HEIGHT) {
			cancelRot = true;
			break;
		}

		if (getBlockAt(tilesBl.at(i).x, tilesBl.at(i).y) != Piece::BlockType::Void) {
			cancelRot = true;
			break;
		}
	}
	if (cancelRot)
		mActivePiece->rotateLeft();
	else
		mRotateRight = false;
}

Piece::BlockType GameEngine::getBlockAt(int x, int y) const {
	return mTileMap.at(x).at(y);
}
Piece::BlockType GameEngine::getBlockAt(sf::Vector2i pos) const {
	return getBlockAt(pos.x, pos.y);
}

sf::Time GameEngine::computeFrameTime(sf::Time elapsedTotal, int difficulty) {
	float limFrame = 100.0f;

	double frameTime = limFrame + (limFrame + (15 - difficulty) * 20) * std::exp(-(difficulty + 10) / 2000.0f * elapsedTotal.asSeconds());
	return sf::microseconds((sf::Int64) (1000 * frameTime));
}

void GameEngine::paintLevel() {
	sf::Vertex *ver = nullptr;
	sf::Color color;
	for (int x = 0; x < COUNT_TILES_WIDTH; x++) {
		for (int y = 0; y < COUNT_TILES_HEIGHT; y++) {
			ver = &mVArray[(x + y * COUNT_TILES_WIDTH) * 4];
			color = Piece::getColorByBlockType(mTileMap.at(x).at(y));
			ver[0].color = color;
			ver[1].color = color;
			ver[2].color = color;
			ver[3].color = color;
		}
	}
}
void GameEngine::paintActivePiece() {
	sf::Vertex *ver = nullptr;
	sf::Color color;
	for (unsigned int i = 0; i < mActivePiece->getTilesLocalCoords().size(); i++) {
		ver = &mVArray[(mActivePiece->getTilesGlobalCoords()[i].x + mActivePiece->getTilesGlobalCoords()[i].y * COUNT_TILES_WIDTH) * 4];
		color = Piece::getColorByBlockType(mActivePiece->getBlockType());
		ver[0].color = color;
		ver[1].color = color;
		ver[2].color = color;
		ver[3].color = color;
	}
}

void GameEngine::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mFond, states);
	states.texture = mTextureBlock;
	target.draw(mVArray, states);
}
