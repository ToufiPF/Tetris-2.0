#include <SFML/Window.hpp>
#include "main.hpp"
#include "Game.hpp"

int main()
{
	sf::RenderWindow window;

	Game game(&window);

	switch (game.init()) {
	case Game::ErrorCode::MISS_SETTINGS_INI:
		cerr << "Fichier settings.ini manquant, paramêtres de base chargés.";
	case Game::ErrorCode::NO_ERROR:
		cout << "Jeu initialisé." << endl;
		break;

	case Game::ErrorCode::NULLPTR_WIN:
		cerr << "Fenêtre mal initialisée." << endl;
		return Game::ErrorCode::NULLPTR_WIN;

	case Game::ErrorCode::MISS_HP_FONT:
		cerr << "Police \"Hennypenny-regular.ttf\" manquante !" << endl;
		return Game::ErrorCode::MISS_HP_FONT;

	case Game::ErrorCode::MISS_BLOCK_TEXTURE:
		cerr << "Texture \"block.png\" manquante !" << endl;

	default: // (Game::ErrorCode::UNKNOWN)
		cerr << "Problème à inconnu lors de l'initialisation du moteur du jeu." << endl
			<< "Essayez de réinstaller le programme." << endl;
		return Game::ErrorCode::UNKNOWN;
	}

	game.begin();

	return 0;
}