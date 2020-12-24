#include "Player.hh"
#include <SFML/Graphics.hpp>

Player::Player()
{
}

Player::Player(Dresseur &dresseur) : _dresseur(&dresseur),
                                     _pokeball("Images/pokeball.png"),
                                     _accepted(true),
                                     _first_on_arene(true)
{
    //this->IP = sf::IpAddress::getLocalAddress();
    this->IP = "109.0.200.98";
}

Player::Player(Player const &P) : IP(P.IP),
                                  _dresseur(P._dresseur),
                                  _pokeball(P._pokeball),
                                  _accepted(true),
                                  _first_on_arene(true)
{
    short int port = 30000;

    // Le client se connecte au port avec son IP a condition que le serveur ai deja été lancé
    if (this->socket.connect(IP, port) == sf::Socket::Done)
    {
        std::cout << "Tentative de connexion au serveur..." << std::endl;
        sf::Packet sendPacket;
        // On charge le pseudo dans le paquet a envoyer au serveur
        sendPacket << this->get_dresseur()->get_nom();
        // On envoie
        socket.send(sendPacket);
        sf::Packet receivePacket;
        // Le joueur a t il ete accepter par le serveur ?
        if (socket.receive(receivePacket) == sf::Socket::Done)
            receivePacket >> _accepted;
        // Non
        if (!_accepted)
        {
            std::cout << "Deconnecte du serveur car un joueur possède déjà ce personage!" << std::endl;
            this->socket.disconnect();
            this->_accepted = false;
        }
        // Oui
        else
        {
            std::cout << "Connexion reussi" << std::endl;
        }
    }
    else
    {
        std::cout << "Serveur pas encore crée, lancez le dans un autre terminal !" << std::endl;
        exit(0);
    }
    // Afin de ne pas bloquer le programme quand on attend une socket
    this->socket.setBlocking(false);
}

Player::~Player()
{
}
// Fonction ajoutée pour le bruit des pas
// elle evite de faire les 4 conditions a chaque fois
bool Player::is_moving()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return true;

    return false;
}

void Player::set_covidmon(Covidmon &pok)
{
    this->_covidmon.push_back(&pok);
}

Dresseur *Player::get_dresseur() const
{
    return this->_dresseur;
}

std::vector<Covidmon*> Player::get_covidmon() const
{
    return this->_covidmon;
}

bool Player::get_first_on_arene() const
{
    return this->_first_on_arene;
}

void Player::pop_pokeball(sf::RenderWindow &window)
{
    this->_pokeball.set_position_x(this->_dresseur->get_position_x() + SIZE_WIDTH_PERSO / 2 - SIZE_BLOCK_POKEBALL / 2);
    this->_pokeball.set_position_y(this->_dresseur->get_position_y() - SIZE_BLOCK_POKEBALL / 2);
    this->_pokeball.draw(window);
}

void Player::receive(std::vector<Dresseur> &dresseurs)
{
    sf::Packet receivePacket;
    if (socket.receive(receivePacket) == sf::Socket::Done)
    {
        sf::Uint16 x, y, animation;
        int dir, bg;
        Direction d;
        std::string nom;
        Bg current_bg;
        receivePacket >> nom >> dir >> animation >> x >> y >> bg;
        if (dir == 0)
            d = Down;
        if (dir == 1)
            d = Left;
        if (dir == 2)
            d = Right;
        if (dir == 3)
            d = Up;

        if (bg == 0)
            current_bg = intro;
        if (bg == 1)
            current_bg = menu;
        if (bg == 2)
            current_bg = choix_personnage;
        if (bg == 3)
            current_bg = choix_covidmon;
        if (bg == 4)
            current_bg = arene;

        if (current_bg == arene && get_dresseur()->get_current_bg() != arene && _first_on_arene)
        {
            _first_on_arene = false;
        }

        /*std::cout << "current_bg : " << current_bg << std::endl;
        std::cout << "animation : " << animation << std::endl;
        std::cout << "x : " << x << std::endl;
        std::cout << "y : " << y << std::endl;*/

        for (auto it = dresseurs.begin(); it != dresseurs.end(); it++)
        {
            if (it->get_nom() == nom)
            {
                it->set_position_x(x);
                it->set_position_y(y);
                it->set_direction(d);
                it->set_animation(animation);
                it->set_current_bg(current_bg);
            }
        }
    }
}

void Player::receive(std::vector<Covidmon> &Covidmon, sf::RenderWindow& window)
{
    sf::Packet receivePacket;
    if (socket.receive(receivePacket) == sf::Socket::Done)
    {
        sf::Uint16 x, y, animation, pv_current;
        int dir, bg;
        bool is_attacking_near;
        bool is_attacking_far;
        Direction d;
        std::string nom;
        Bg current_bg;
        receivePacket >> nom >> dir >> animation >> x >> y >> bg >> pv_current >> is_attacking_near >> is_attacking_far;

        // On ajoute le covidmon si il est nouveau dans le vector de covidmon
        bool push = true;
        for(std::size_t it = 0; it < _covidmon.size(); it++)
        {
            if(_covidmon[it]->get_nom() == nom)
                push = false;
        }
        // Si aucun pokemon n'appartient a vector
        if(push)
        {
            for (auto it = Covidmon.begin(); it != Covidmon.end(); it++)
            {
                if (it->get_nom() == nom)
                {
                    std::cout << nom << " push" << std::endl;
                    set_covidmon(*it);
                }
            }
        }
        if(_covidmon.size() == 2)
        {
            if(is_attacking_far)
            {
                _covidmon[1]->get_attaque_de_loin().set_est_lancee(true);
            }
            if(is_attacking_near)
            {
                _covidmon[1]->get_attaque_de_pres().set_est_lancee(true);
            }
        }

        if (dir == 0)
            d = Down;
        if (dir == 1)
            d = Left;
        if (dir == 2)
            d = Right;
        if (dir == 3)
            d = Up;

        if (bg == 0)
            current_bg = intro;
        if (bg == 1)
            current_bg = menu;
        if (bg == 2)
            current_bg = choix_personnage;
        if (bg == 3)
            current_bg = choix_covidmon;
        if (bg == 4)
            current_bg = arene;

        /*std::cout << "current_bg : " << current_bg << std::endl;
        std::cout << "animation : " << animation << std::endl;
        std::cout << "x : " << x << std::endl;
        std::cout << "y : " << y << std::endl;*/

        for (auto it = Covidmon.begin(); it != Covidmon.end(); it++)
        {
            if (it->get_nom() == nom)
            {
                it->set_position_x(x);
                it->set_position_y(y);
                it->set_direction(d);
                it->set_animation(animation);
                it->set_current_bg(current_bg);
                it->set_pv_current(pv_current);
            }
        }
    }
}


void Player::send()
{
    sf::Packet sendPacket_type;
    sf::Packet sendPacket_data;
    sendPacket_type << "dresseur";
    sendPacket_data << this->_dresseur->get_nom() << this->_dresseur->get_direction() << this->get_dresseur()->get_animation() << this->_dresseur->get_position_x() << this->_dresseur->get_position_y() << this->_dresseur->get_current_bg();
    socket.send(sendPacket_type);
    socket.send(sendPacket_data);
}

void Player::send_covidmon()
{
    sf::Packet sendPacket_type;
    sf::Packet sendPacket_data;
    sendPacket_type << "covidmon";
    sendPacket_data << this->_covidmon[0]->get_nom() << this->_covidmon[0]->get_direction() << this->get_covidmon()[0]->get_animation() << this->_covidmon[0]->get_position_x() << this->_covidmon[0]->get_position_y() << this->_covidmon[0]->get_current_bg() << this->_covidmon[0]->get_pv_current() << this->_covidmon[0]->get_attaque_de_pres().get_est_lancee() << this->_covidmon[0]->get_attaque_de_loin().get_est_lancee();
    socket.send(sendPacket_type);
    socket.send(sendPacket_data);
}

bool Player::is_accepted()
{
    return this->_accepted;
}

void Player::disconnect()
{
    sf::Packet sendPacket;
    sendPacket << this->_dresseur->get_nom();
    this->socket.disconnect();
    std::cout << "Deconnexion du serveur !" << std::endl;
}

/*sf::Packet& operator <<(sf::Packet& packet, Direction dir)
{
    return packet << dir
}
*/
/*sf::Packet& operator <<(sf::Packet& packet, const Player& P)
{
    return packet << P.get_dresseur()->get_nom() << P.get_dresseur()->get_position_x() << P.get_dresseur()->get_position_y();
}

sf::Packet& operator >>(sf::Packet& packet, Player& P)
{
    return packet >> P.get_dresseur()->get_nom() >> P.get_dresseur()->get_position_x() >> P.get_dresseur()->get_position_y();
}*/