#pragma once

#include "Entite.hh"
#include "Attaque_de_loin.hh"
#include "Attaque_de_pres.hh"

// Type des Covidmon : 4 possibles
// Utilisés dans les constructeurs
typedef enum Type
{
    Feu,
    Eau,
    Plante,
    Vol
} Type;

class Covidmon : public Entite
{
private:
    sf::Font _font;
    sf::Texture __texture_pv;
    sf::Sprite __sprite_pv;
    std::vector<sf::Clock> _delai_attaques;
    std::vector<sf::SoundBuffer> _buffer_attaques;
    std::vector<sf::Sound> _son_attaques; 

    Type _type;
    Attaque_de_loin _attaque_de_loin;
    Attaque_de_pres _attaque_de_pres;
    sf::Uint16 _pv_current;
    sf::Uint16 _pv_max;
    bool _est_vivant;
    int _bar;
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
    bool est_fort_contre(const Covidmon &) const;
    bool est_faible_contre(const Covidmon &) const;

public:
    Covidmon();
    Covidmon(std::string, std::string, Type);
    Covidmon(Covidmon const &);
    ~Covidmon();

    Type get_type() const;
    sf::Uint16 get_pv_max() const;
    sf::Uint16 get_pv_current() const;
    bool get_est_vivant() const;
    Attaque_de_loin &get_attaque_de_loin();
    Attaque_de_pres &get_attaque_de_pres();

    void set_type(Type t);
    void set_pv_max(sf::Uint16);
    void set_pv_current(sf::Uint16);
    void set_est_vivant(bool);

    void animate();
    void attaque_de_loin(sf::RenderWindow &, bool);
    void attaque_de_pres(sf::RenderWindow &, bool);

    void operator-=(sf::Uint16);
    void receive_degat(Covidmon &);    
    void collision_attaque(Covidmon &);
    void draw_pv(sf::RenderWindow &);
    void got_a_clic(sf::RenderWindow &);
    void print_name(sf::RenderWindow &);

};