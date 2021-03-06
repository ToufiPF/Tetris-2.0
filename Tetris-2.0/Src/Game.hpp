#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "main.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/SideBar.hpp"

#include "Menus/MainMenu.hpp"
#include "Menus/OptionsMenu.hpp"
#include "Menus/PauseMenu.hpp"
#include "Menus/GameOverMenu.hpp"

class Game
{
public:
	enum ErrorCode : short {
		NO_ERROR = 0, NULLPTR_WIN, MISS_HP_FONT, MISS_BLOCK_TEXTURE, MISS_TETRIS_THEME, MISS_SETTINGS_INI, UNKNOWN = 100
	};
	enum GameState : short {
		MAIN_MENU = 0, OPTIONS_MENU, PLAYING, PAUSED, GAME_OVER
	};

	static const unsigned int MINIMUM_WIN_SIZE_X;
	static const unsigned int MINIMUM_WIN_SIZE_Y;

	static const float DEFAULT_BGM_VOLUME;
	static const float DEFAULT_SFX_VOLUME;

	static const int DEFAULT_DIFFICULTY;

public:
	Game(sf::RenderWindow *window = nullptr);
	~Game();

	// Charge les ressources, lit les options, cree la fenetre
	ErrorCode init();

	// Lance la boucle du menu
	void begin();

	// Ferme la fenetre et sauvegarde
	void close();

protected:
	// Lit et sauvegarde les options
	bool writeSettings() const;
	bool readSettings();

	// Change l'etat du jeu : mainMenu, optionsMenu, playing, paused, gameOver
	void setGameState(const GameState &state);

	// Dessine le jeu en fonction du gameState
	void draw();

	// Gere les events
	void processEvents();
	// Gere les events claviers selon l'etat du jeu
	void processKeyEvents(const sf::Event &e);
	// Gere les events resize
	void processResizeEvent(const sf::Event &e);

	// Redimensionne les vues
	void resizeViewPorts();

protected:
	sf::RenderWindow *mWin;

	sf::Font mHpFont;
	sf::Texture mBlockTexture;
	sf::Music mTetrisTheme;

	GameState mGameState;
	sf::View mViewMenus;
	sf::View mViewGE;
	sf::View mViewSideBar;

	GameEngine mGE;
	SideBar mSideBar;
	sf::Clock mClockGame;

	/* ---- Settings ---- */
	float mBgmVolume, mSfxVolume;

	/* ---- Menus ---- */
	MainMenu mMainMenu;
	OptionsMenu mOptionsMenu;
	PauseMenu mPauseMenu;
	GameOverMenu mGameOverMenu;
};

#endif
