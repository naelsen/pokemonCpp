#include "Game.hh"

Game::Game() : _current_background(intro),
			   _selec_dresseur(false),
			   _selec_pokemon(false),
			   _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRES ...")
{
	this->_font.loadFromFile("Images/arial.ttf");
    this->_text.setFont(this->_font);
    this->_text.setString("Choisissez un joueur \n   (avec la souris!)");
    this->_text.setCharacterSize(17);
    this->_text.setStyle(sf::Text::Bold);
    this->_text.setFillColor(sf::Color::Black);
    this->_text.setPosition(sf::Vector2f(245, 220));

	this->_backgrounds.insert(couple("intro", Image("Images/Backgrounds/intro3.png")));
	this->_backgrounds.insert(couple("menu", Image("Images/Backgrounds/menu.png")));
	this->_backgrounds.insert(couple("choix_personnage", Image("Images/Backgrounds/choix_personnage.png")));
	this->_backgrounds.insert(couple("choix_pokemon", Image("Images/Backgrounds/choix_pokemon.png")));
	this->_backgrounds.insert(couple("arene", Image("Images/Backgrounds/arene.png")));

	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_gaby.png", "Gaby"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_joelle.png", "Joelle"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_red.png", "Red"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_chauve.png", "Le gros crane"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_butch.png", "Butch"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cassidy.png", "Cassidy"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cyrus.png", "Cyrus"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_james.png", "James"));

	this->_pokemons.push_back(Pokemon("Images/Pokemons/articodin.png", "Articodin"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/canartichaud.png", "Canartichaud"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/darumaka.png", "Darumaka"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/feneukin.png", "Feneukin"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/galacvole.png", "Galacvole"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/galarian.png", "Galarian"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/gardevoir.png", "Gardevoir"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/gloupix.png", "Gloupix"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/lubegon.png", "Lubegon"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/mageau.png", "Mageau"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/mrmime.png", "Mrmime"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/noixbat.png", "NoixBat"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/oh-oh.png", "Oh-Oh"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/pandours.png", "Pandours"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/ponyta.png", "Ponyta"));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/skeleton.png", "Skeleton"));
	// Placement des personnages sur la carte
	sf::Uint16 i = 1;
	sf::Uint16 j = 1;
	for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		if (i <= 4)
		{
			it->set_position_x(i * WINDOW_WIDTH / 6);
			it->set_position_y(85.f);
			i++;
		}
		else
		{
			it->set_position_x(j * WINDOW_WIDTH / 6);
			it->set_position_y(620.f - SIZE_HEIGHT_PERSO);
			j++;
		}
	}
	//Placement des pokémons
	i = 1;
	j = 1;
	sf::Uint16 k = 1;
	sf::Uint16 l = 1;
	for (auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
	{
		if (i <= 4)
		{
			it->set_position_x(i * WINDOW_WIDTH / 6);
			it->set_position_y(25.f);
			i++;
		}
		else if (j <= 4)
		{
			it->set_position_x(j * WINDOW_WIDTH / 6);
			it->set_position_y(85.f);
			j++;
		}
		else if (k <= 4)
		{
			it->set_position_x(k * WINDOW_WIDTH / 6);
			it->set_position_y(620.f - SIZE_BLOCK_POKEMON);
			k++;
		}
		else if (l <= 4)
		{
			it->set_position_x(l * WINDOW_WIDTH / 6);
			it->set_position_y(690.f - SIZE_BLOCK_POKEMON);
			l++;
		}
	} 
	sf::Clock c1;
	sf::Clock c2;
	sf::Sound s1;
	sf::Sound s2;
	sf::SoundBuffer sb1;
	sf::SoundBuffer sb2;
	bool sound_switched1 = false;
	bool sound_switched2 = false;
	this->_clocks.push_back(c1);
	this->_clocks.push_back(c2);
	this->_sounds.push_back(s1);
	this->_sounds.push_back(s2);
	this->_buffers.push_back(sb1);
	this->_buffers.push_back(sb2);
	this->_sounds_switched.push_back(sound_switched1);
	this->_sounds_switched.push_back(sound_switched2);
	this->_clocks[0].restart();
	this->_clocks[1].restart();
	this->_window.setFramerateLimit(60);
}

Game::~Game()
{
}

Bg Game::_get_current_background() const
{
	return this->_current_background;
}

void Game::_set_current_background(Bg bg)
{
	this->_current_background = bg;
}

void Game::run()
{
	while (this->_window.isOpen())
	{
		// ==ON S'OCCUPE DE SAVOIR SI ON DOIT FERMER LA FENETRE
		while (this->_window.pollEvent(this->_event))
		{
			if (this->_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->_window.close();
			}
		}
		this->_choisir_dresseur();
		this->_choisir_pokemon();
		this->_manage();
		this->_draw();
		this->_window.display();
	}
}

// La fonction joue le son du fichier placé en paramètre
void Game::_switch_sound(std::size_t i, std::string fichier)
{
	if(i < _buffers.size())
	{
		if (!this->_buffers[i].loadFromFile(fichier))
			std::cout << "Erreur chargement son" << std::endl;
		this->_sounds[i].setBuffer(_buffers[i]);
	}
}

void Game::_draw()
{
	this->_draw_bg();
	this->_draw_dresseur();
	this->_draw_pokemon();
	if (this->_selec_pokemon)
		this->_players[0].pop_pokeball(this->_window);
}

void Game::_draw_bg()
{
	switch (this->_current_background)
	{
	case intro:
		this->_backgrounds["intro"].draw(this->_window);
		break;
	case menu:
		this->_backgrounds["menu"].draw(this->_window);
		break;
	case choix_personnage:
		this->_backgrounds["choix_personnage"].draw(this->_window);
		if(this->_selec_dresseur == false)
			this->_window.draw(this->_text);
		break;
	case choix_pokemon:
		this->_backgrounds["choix_pokemon"].draw(this->_window);
		if(this->_selec_pokemon == false)
			this->_window.draw(this->_text);
		break;
	case arene:
		this->_backgrounds["arene"].draw(this->_window);
		break;
	default:
		break;
	}
}

void Game::_draw_dresseur()
{
	if (this->_current_background == choix_personnage)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
			}
			it->draw(this->_window);
			it->animate();
		}
	}
	if (this->_current_background == choix_pokemon)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
				it->draw(this->_window);
				it->animate();
			}
		}
	}
	if (this->_current_background == arene)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
				it->draw(this->_window);
				it->animate();
			}
		}
	}
}

void Game::_draw_pokemon()
{
	if (this->_current_background == choix_pokemon)
	{
		for (auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
		{
			if (!it->get_choisi())
			{
				it->draw(this->_window);
				it->animate();
			}
			else
				it->print_name(this->_window);
		}
	}
	if (this->_current_background == arene)
	{
		for (auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
				it->draw(this->_window);
				it->move();
				it->animate();
				// 30,30 ---  570,30 ---- 570,570 ------ 30, 600
			}
		}
	}
}
void Game::_manage()
{
	this->_manage_bg();
	this->_manage_sound();
	this->_manage_dresseur();
}
//Les sons se déclanchent que dans la deuxième fenetre

void Game::_back_sound()
{
	if (this->_current_background != arene)
	{
		if (this->_sounds_switched[1] == false)
		{
			this->_switch_sound(1,"Sons/musique.wav");
			this->_sounds_switched[1] = true;
			this->_clocks[1].restart();
			this->_sounds[1].play();
		}
		else if (this->_clocks[1].getElapsedTime().asMilliseconds() > 31300)
		{
			this->_clocks[1].restart();
			this->_sounds[1].play();
		}
	}
	else
	{
		if (this->_sounds_switched[1] == true)
		{
			this->_switch_sound(1,"Sons/musique_arene1.wav");
			this->_sounds_switched[1] = false;
			this->_clocks[1].restart();
			this->_sounds[1].play();
		}
		else if (this->_clocks[1].getElapsedTime().asMilliseconds() > 31300)
		{
			this->_clocks[1].restart();
			this->_sounds[1].play();
		}
	}
}

void Game::_front_sound()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background != arene && this->_clocks[0].getElapsedTime().asMilliseconds() > 200)
	{
		if (this->_sounds_switched[0] == false)
		{
			_switch_sound(0,"Sons/b.wav");
			this->_sounds_switched[0] = true;
			this->_clocks[0].restart();
			this->_sounds[0].play();
		}
	}
	else if (this->_players[0].is_moving() && this->_clocks[0].getElapsedTime().asMilliseconds() > 800)
	{
		if (this->_sounds_switched[0] == true)
		{
			this->_switch_sound(0,"Sons/footstep.wav");
			this->_sounds_switched[0] = false;
			this->_clocks[0].restart();
			this->_sounds[0].play();
		}
		else
		{
			this->_clocks[0].restart();
			this->_sounds[0].play();
		}
	}
}

void Game::_manage_sound()
{
	this->_back_sound();
	this->_front_sound();
}

void Game::_manage_bg()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == intro)
	{
		_set_current_background(menu);
		this->_clocks[0].restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == menu)
	{
		if (this->_clocks[0].getElapsedTime().asMilliseconds() > 200)
			_set_current_background(choix_personnage);
	}
	else if (this->_selec_dresseur)
	{
		if (this->_players[0].get_dresseur()->is_out())
		{
			if (this->_current_background == choix_personnage)
				_set_current_background(choix_pokemon);
			else if (this->_current_background == choix_pokemon)
				_set_current_background(arene);
			this->_players[0].get_dresseur()->set_position_x(0);
		}
	}
}

void Game::_manage_dresseur()
{
	if (this->_current_background == choix_personnage)
	{
		for (auto it = this->_players.begin(); it != this->_players.end(); it++)
		{
			it->send();
			it->receive(this->_dresseurs);
			it->get_dresseur()->move();
		}
	}
	if (this->_current_background == choix_pokemon)
	{
		this->_players[0].get_dresseur()->move();
	}
	if (this->_current_background == arene)
	{
		if (this->_players[0].get_dresseur()->get_position_y() != WINDOW_WIDTH / 2 - 100)
			this->_players[0].get_dresseur()->set_position_y(WINDOW_WIDTH / 2 - 100);
		if (this->_players[0].get_dresseur()->get_animation() != 0)
			this->_players[0].get_dresseur()->set_animation(0);
	}
}

void Game::_choisir_dresseur()
{
	if (!this->_selec_dresseur && this->_current_background == choix_personnage)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				Player P(*it);
				this->_players.push_back(P);
				if(_players[0].is_accepted())
				{
					this->_selec_dresseur = true;
					this->_text.setString("Choisissez un covidmon \n   (avec la souris!)");
				}
				else
				{
					_players.pop_back();
					it->set_choisi(false);
				}
				
			}
		}
	}
}

void Game::_choisir_pokemon()
{
	if (!this->_selec_pokemon && this->_current_background == choix_pokemon)
	{
		for (auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
		{
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				this->_players[0].set_pokemon(*it);
				this->_selec_pokemon = true;
			}
		}
	}
}