#include "Game.hpp"

const unsigned int Game::DEFAULT_WIN_SIZE_X = 720U;
const unsigned int Game::DEFAULT_WIN_SIZE_Y = 1024U;
const float Game::DEFAULT_GAMEENGINE_RATIO_X = 1.0f;
const float Game::DEFAULT_GAMEENGINE_RATIO_Y = 1.0f;

const float Game::DEFAULT_BGM_VOLUME = 100.0f;
const float Game::DEFAULT_SFX_VOLUME = 100.0f;

const int Game::DEFAULT_DIFFICULTY = 3;

using std::ofstream;
using std::ifstream;

Game::Game(sf::RenderWindow * window)
{
	mWin = window;
	mBgmVolume = DEFAULT_BGM_VOLUME, mSfxVolume = DEFAULT_SFX_VOLUME;
	mGE.setDifficulty(DEFAULT_DIFFICULTY);
}
Game::~Game() {
}

Game::ErrorCode Game::init() {
	if (mWin == nullptr)
		return ErrorCode::NULLPTR_WIN;

	if (!mHpFont.loadFromFile("hennypenny-regular.ttf"))
		return ErrorCode::MISS_HP_FONT;

	if (!mTetrisTheme.openFromFile("tetris.ogg"))
		return ErrorCode::MISS_TETRIS_THEME;

	if (!mBlockTexture.loadFromFile("block.png"))
		return ErrorCode::MISS_BLOCK_TEXTURE;

	bool settingsRead = readSettings();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	mWin->create(sf::VideoMode(mWinSize.x, mWinSize.y), "Tetris 2.0", sf::Style::Titlebar | sf::Style::Close, settings);
	mWin->setFramerateLimit(60);
	mWin->setVerticalSyncEnabled(false);
	mWin->setKeyRepeatEnabled(true);

	mTetrisTheme.setLoop(true);
	mTetrisTheme.setVolume(mBgmVolume);
	mTetrisTheme.play();

	mMainMenu.setFont(mHpFont);
	mMainMenu.setMenuSize(sf::Vector2f((float)mWinSize.x, (float)mWinSize.y));
	mMainMenu.setSelection(0);

	mOptionsMenu.setFont(mHpFont);
	mOptionsMenu.setMenuSize(sf::Vector2f((float)mWinSize.x, (float)mWinSize.y));
	mOptionsMenu.setSelection(0);
	mOptionsMenu.setDifficultyValue(mGE.getDifficulty());
	mOptionsMenu.setBgmVolumeValue(mBgmVolume);
	mOptionsMenu.setSfxVolumeValue(mSfxVolume);

	mPauseMenu.setFont(mHpFont);
	mPauseMenu.setMenuSize(sf::Vector2f((float)mWinSize.x / 1.5f, (float)mWinSize.y / 1.5f));
	mPauseMenu.setSelection(0);
	mPauseMenu.setPosition(mWinSize.x / 6.0f, mWinSize.y / 6.0f);

	mGameOverMenu.setFont(mHpFont);
	mGameOverMenu.setMenuSize(sf::Vector2f((float)mWinSize.x, (float)mWinSize.y));
	mGameOverMenu.setSelection(0);

	setGameState(GameState::MAIN_MENU);

	if (!settingsRead)
		return ErrorCode::MISS_SETTINGS_INI;
	else
		return ErrorCode::NO_ERROR;
}

void Game::begin() {
	while (mWin->isOpen()) {
		// On gere les events
		processEvents();

		sf::Time elapsed = mClockGame.restart();
		mWin->clear(sf::Color::White);

		sf::RectangleShape fond;
		// On dessine en fonction du GameState
		switch (mGameState) {
		case GameState::MAIN_MENU:
			mWin->draw(mMainMenu);
			break;

		case GameState::OPTIONS_MENU:
			mWin->draw(mOptionsMenu);
			break;

		case GameState::PLAYING:
			mGE.updateGame(elapsed);
			mWin->draw(mGE);

			if (mGE.isGameOver())
				setGameState(GameState::GAME_OVER);

			break;

		case GameState::PAUSED:
			// Permet de voir le jeu en transparence
			mWin->draw(mGE);
			fond.setSize(sf::Vector2f((float)mWinSize.x, (float)mWinSize.y));
			fond.setFillColor(sf::Color(0, 0, 0, 150));
			mWin->draw(fond);

			mWin->draw(mPauseMenu);

			break;

		case GameState::GAME_OVER:
			mWin->draw(mGameOverMenu);
			break;
		default:
			break;
		}

		mWin->display();
	}
}
void Game::close() {
	writeSettings();
	mWin->close();
}

bool Game::writeSettings() const {
	ofstream os("settings.ini", std::ios::out | std::ios::trunc);
	if (!os)
		return false;

	os << "winSize: " << mWinSize.x << " " << mWinSize.y << endl;
	os << "gameEngineRatio: " << mGameEngineRatio.x << " " << mGameEngineRatio.y << endl;

	os << "bgmVolume: " << mBgmVolume << endl;
	os << "sfxVolume: " << mSfxVolume << endl;

	os << "difficulty: " << mGE.getDifficulty() << endl;

	os.close();

	return true;
}
bool Game::readSettings() {
	// Parametres de base
	mWinSize.x = DEFAULT_WIN_SIZE_X;
	mWinSize.y = DEFAULT_WIN_SIZE_Y;

	mGameEngineRatio.x = DEFAULT_GAMEENGINE_RATIO_X;
	mGameEngineRatio.y = DEFAULT_GAMEENGINE_RATIO_Y;

	mBgmVolume = DEFAULT_BGM_VOLUME;
	mSfxVolume = DEFAULT_SFX_VOLUME;

	mGE.setDifficulty(DEFAULT_DIFFICULTY);

	ifstream is("settings.ini", std::ios::in);
	if (is) {
		string line, buff;
		std::stringstream ss;

		while (std::getline(is, line)) {
			ss << line;
			cout << line << endl;
			ss >> buff;

			if (buff == "winSize:") {
				ss >> mWinSize.x >> mWinSize.y;
				if (ss.fail()) {
					cerr << "Failed to read : winSize" << endl;
					mWinSize.x = DEFAULT_WIN_SIZE_X;
					mWinSize.y = DEFAULT_WIN_SIZE_Y;
				}
			}
			else if (buff == "gameEngineRatio:") {
				ss >> mGameEngineRatio.x >> mGameEngineRatio.y;
				if (ss.fail()) {
					cerr << "Failed to read : gameEngineRatio" << endl;
					mGameEngineRatio.x = DEFAULT_GAMEENGINE_RATIO_X;
					mGameEngineRatio.y = DEFAULT_GAMEENGINE_RATIO_Y;
				}
			}
			else if (buff == "bgmVolume:") {
				ss >> mBgmVolume;
				if (ss.fail()) {
					cerr << "Failed to read : bgmVolume" << endl;
					mBgmVolume = DEFAULT_BGM_VOLUME;
				}
			}
			else if (buff == "sfxVolume:") {
				ss >> mSfxVolume;
				if (ss.fail()) {
					cerr << "Failed to read : sfxVolume" << endl;
					mSfxVolume = DEFAULT_SFX_VOLUME;
				}
			}
			else if (buff == "difficulty:") {
				int diff;
				ss >> diff;
				mGE.setDifficulty(diff);
				if (ss.fail()) {
					cerr << "Failed to read : difficulty" << endl;
					mGE.setDifficulty(DEFAULT_DIFFICULTY);
				}
			}

			ss.clear();
			ss.str(string());
		}

		is.close();

		return true;
	}
	else
		return false;
}

void Game::setGameState(const GameState &state)
{
	switch (state) {
	case GameState::MAIN_MENU:
		if (mGameState != GameState::OPTIONS_MENU)
			mMainMenu.setSelection(0);
	case GameState::OPTIONS_MENU:
		mOptionsMenu.setSelection(0);
		break;
	case GameState::PLAYING:
		// Si on vient de lancer le jeu, on reinitiallise le gameEngine
		if (mGameState == GameState::MAIN_MENU)
			mGE.init(&mBlockTexture);
		break;
	case GameState::PAUSED:
		mPauseMenu.setSelection(0);
		break;
	case GameState::GAME_OVER:
		mGameOverMenu.setScore(mGE.getScore());
		break;
	default:
		break;
	}
	mGameState = state;
}

void Game::processEvents() {
	sf::Event e;

	while (mWin->pollEvent(e)) {
		switch (e.type)
		{
		case sf::Event::EventType::Closed:
			close();
			break;

		case sf::Event::EventType::LostFocus:
			break;
		case sf::Event::EventType::GainedFocus:
			break;

		case sf::Event::EventType::KeyPressed:
			processKeyEvents(e);
			break;
		case sf::Event::EventType::KeyReleased:
			processKeyEvents(e);
			break;

		default:
			break;
		}
	}
}
void Game::processKeyEvents(const sf::Event &e) {
	if (mGameState == GameState::MAIN_MENU) {
		if (e.type != sf::Event::EventType::KeyPressed)
			return;

		switch (e.key.code) {
		case sf::Keyboard::Up:
		case sf::Keyboard::Z:
			mMainMenu.setSelection(mMainMenu.getSelection() - 1);
			break;

		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			mMainMenu.setSelection(mMainMenu.getSelection() + 1);
			break;

		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			if (mMainMenu.getSelection() == MainMenu::MainSelection::NEW_GAME) {
				setGameState(GameState::PLAYING);
			}
			else if (mMainMenu.getSelection() == MainMenu::MainSelection::OPTIONS) {
				setGameState(GameState::OPTIONS_MENU);
				mOptionsMenu.setSelection(0);
			}
			else if (mMainMenu.getSelection() == MainMenu::MainSelection::QUIT) {
				close();
			}
			break;

		case sf::Keyboard::Escape:
			close();
			break;
		default:
			break;
		}
	}
	else if (mGameState == GameState::OPTIONS_MENU) {
		if (e.type != sf::Event::EventType::KeyPressed)
			return;

		switch (e.key.code) {
		case sf::Keyboard::Up:
		case sf::Keyboard::Z:
			mOptionsMenu.setSelection(mOptionsMenu.getSelection() - 1);
			break;
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			mOptionsMenu.setSelection(mOptionsMenu.getSelection() + 1);
			break;

		case sf::Keyboard::Left:
		case sf::Keyboard::Q:

			switch (mOptionsMenu.getSelection()) {
			case OptionsMenu::OptionSelection::DIFFICULTY:
				mGE.setDifficulty(mGE.getDifficulty() - 1);
				mOptionsMenu.setDifficultyValue(mGE.getDifficulty());
				break;

			case OptionsMenu::OptionSelection::BGM_VOL:
				mBgmVolume -= 10.0f;
				if (mBgmVolume < 0.0f)
					mBgmVolume = 0.0f;

				mOptionsMenu.setBgmVolumeValue(mBgmVolume);
				mTetrisTheme.setVolume(mBgmVolume);
				break;

			case OptionsMenu::OptionSelection::SFX_VOL:
				mSfxVolume -= 10.0f;
				if (mSfxVolume < 0.0f)
					mSfxVolume = 0.0f;

				mOptionsMenu.setSfxVolumeValue(mSfxVolume);
				break;

			default:
				break;
			}
			break;
		case sf::Keyboard::Right:
		case sf::Keyboard::D:

			switch (mOptionsMenu.getSelection()) {
			case OptionsMenu::OptionSelection::DIFFICULTY:
				mGE.setDifficulty(mGE.getDifficulty() + 1);
				mOptionsMenu.setDifficultyValue(mGE.getDifficulty());
				break;

			case OptionsMenu::OptionSelection::BGM_VOL:
				mBgmVolume += 10.0f;
				if (mBgmVolume > 100.0f)
					mBgmVolume = 100.0f;

				mOptionsMenu.setBgmVolumeValue(mBgmVolume);
				mTetrisTheme.setVolume(mBgmVolume);
				break;

			case OptionsMenu::OptionSelection::SFX_VOL:
				mSfxVolume += 10.0f;
				if (mSfxVolume > 100.0f)
					mSfxVolume = 100.0f;

				mOptionsMenu.setSfxVolumeValue(mSfxVolume);
				break;

			default:
				break;
			}
			break;

		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			if (mOptionsMenu.getSelection() == OptionsMenu::OptionSelection::APPLY) {
				setGameState(GameState::MAIN_MENU);
				writeSettings();
			}
			break;

		case sf::Keyboard::Escape:
			setGameState(GameState::MAIN_MENU);
			writeSettings();
			break;
		default:
			break;
		}
	}
	else if (mGameState == GameState::PLAYING) {
		if (e.type == sf::Event::EventType::KeyReleased && e.key.code == sf::Keyboard::Escape) {
			setGameState(GameState::PAUSED);
		}
		mGE.processKeyEvent(e);
	}
	else if (mGameState == GameState::PAUSED) {
		if (e.type == sf::Event::EventType::KeyPressed) {
			switch (e.key.code) {
			case sf::Keyboard::Z:
			case sf::Keyboard::Up:
				mPauseMenu.setSelection(mPauseMenu.getSelection() - 1);
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				mPauseMenu.setSelection(mPauseMenu.getSelection() + 1);
				break;
			default:
				break;
			}
		}
		if (e.type == sf::Event::EventType::KeyReleased) {
			switch (e.key.code) {
			case sf::Keyboard::Escape:
				setGameState(GameState::PLAYING);
				break;

			case sf::Keyboard::Return:
			case sf::Keyboard::Space:

				if (mPauseMenu.getSelection() == PauseMenu::PauseSelection::RESUME)
					setGameState(GameState::PLAYING);
				else if (mPauseMenu.getSelection() == PauseMenu::PauseSelection::MAINMENU)
					setGameState(GameState::MAIN_MENU);

				break;

			default:
				break;
			}
		}
	}
	else if (mGameState == GameState::GAME_OVER) {
		if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Space)
				setGameState(GameState::MAIN_MENU);
		}
	}
}