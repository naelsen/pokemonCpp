#include "Attaque_de_pres.hh"

Attaque_de_pres::Attaque_de_pres(std::string im) : Image(im),
                                                   _degats(36),
                                                   _animation(0),
                                                   _est_lancee(false),
                                                   _just_clicked(true)
{
}
Attaque_de_pres::Attaque_de_pres() : _degats(50)
{
}

Attaque_de_pres::Attaque_de_pres(Attaque_de_pres const &at) : Image(at),
                                                              _degats(at._degats),
                                                              _animation(at._animation),
                                                              _est_lancee(at._est_lancee),
                                                              _just_clicked(true)

{
}

Attaque_de_pres::~Attaque_de_pres()
{
}

int Attaque_de_pres::get_degats() const
{
    return this->_degats;
}

bool Attaque_de_pres::get_est_lancee() const
{
    return this->_est_lancee;
}

bool Attaque_de_pres::get_just_clicked() const
{
    return this->_just_clicked;
}

sf::Uint16 Attaque_de_pres::get_animation() const
{
    return this->_animation;
}

void Attaque_de_pres::set_degats(int d)
{
    this->_degats = d;
}

void Attaque_de_pres::set_est_lancee(bool e)
{
    this->_est_lancee = e;
}

void Attaque_de_pres::set_just_clicked(bool click)
{
    this->_just_clicked = click;
}

void Attaque_de_pres::set_animation(sf::Uint16 animation)
{
    this->_animation = animation;
}

void Attaque_de_pres::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    0,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

void Attaque_de_pres::lancement()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.05f)
    {
        if (this->_animation < 15)
            this->_animation++;
        else
        {
            this->_animation = 0;
            set_est_lancee(false);
            this->set_just_clicked(true);
            this->set_position_x(WINDOW_WIDTH);
        }
        this->_clock.restart();
    }
}