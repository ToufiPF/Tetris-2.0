#include <SFML/Window.hpp>
#include "main.hpp"
#include "Game.hpp"

int main()
{
	sf::RenderWindow window;

	Game game(&window);

	switch (game.init()) {
	case Game::ErrorCode::MISS_SETTINGS_INI:
		cerr << "Fichier settings.ini manquant, parametres de base charges.";
	case Game::ErrorCode::NO_ERROR:
		cout << "Jeu initialise." << endl;
		break;

	case Game::ErrorCode::NULLPTR_WIN:
		cerr << "Fen�tre mal initialis�e." << endl;
		return Game::ErrorCode::NULLPTR_WIN;

	case Game::ErrorCode::MISS_HP_FONT:
		cerr << "Police \"Hennypenny-regular.ttf\" manquante !" << endl;
		return Game::ErrorCode::MISS_HP_FONT;

	case Game::ErrorCode::MISS_BLOCK_TEXTURE:
		cerr << "Texture \"block.png\" manquante !" << endl;
		return Game::ErrorCode::MISS_BLOCK_TEXTURE;

	case Game::ErrorCode::UNKNOWN:
	default:
		cerr << "Probl�me � inconnu lors de l'initialisation du moteur du jeu." << endl
			<< "Essayez de r�installer le programme." << endl;
		return Game::ErrorCode::UNKNOWN;
	}

	game.begin();

	return 0;
}
