#pragma once

#include "Entite.hh"
#include "Attaque_de_loin.hh"
#include "Attaque_de_pres.hh"

typedef enum Type{
    Feu,
    Eau,
    Plante,
    Vol
}Type;

class Pokemon : public Entite
{
private:
    sf::Font _font;
    Type _type;
    Attaque_de_loin  _attaque_de_loin;
    Attaque_de_pres  _attaque_de_pres;
    int _pv;
    
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
    Pokemon(std::string, std::string,Type);
    Pokemon(Pokemon const &);
    ~Pokemon();

    Type get_type();
    int get_pv();
    void set_type(Type t);
    void set_pv(int);
    void animate();
    void attaque_de_loin(sf::RenderWindow&);
    void attaque_de_pres(sf::RenderWindow&);
    void collision_attaque(Pokemon&);
    bool est_fort_contre(Pokemon&);
    bool est_faible_contre(Pokemon&);
    void receive_degat(Pokemon&);
    void got_a_clic(sf::RenderWindow &);
    void print_name(sf::RenderWindow &);
    //void attaque()
};