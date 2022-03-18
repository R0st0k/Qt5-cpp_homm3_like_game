#include "../headers/heroes.h"

Heroes::Heroes(){
    allHeroes = new Hero [1];
    allHeroes[0].attack = 1;
    allHeroes[0].defense = 0;
    allHeroes[0].spellPower = 2;
    allHeroes[0].knowledge = 2;
    allHeroes[0].mana = allHeroes[0].knowledge*10;
    allHeroes[0].exp = 50;
    allHeroes[0].move = 1500;
    allHeroes[0].morality = 0;
    allHeroes[0].luck = 0;
    allHeroes[0].visibility = 5;
    allHeroes[0].color = 1;
}

Heroes::~Heroes(){
    delete[] allHeroes;
}
