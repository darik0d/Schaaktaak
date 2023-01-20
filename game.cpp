//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    speelbord.clear();
    for(int i = 0; i < 64; i++){
        speelbord.push_back(nullptr);
    }
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    //maak een leeg bord aan
    //set witte schaakstukken
    for(int i = 0; i < 8; i++){
        setPiece(1, i, new Pion(wit));
    }
    setPiece(0, 0, new Toren(wit));
    setPiece(0, 7, new Toren(wit));
    setPiece(0, 1, new Paard(wit));
    setPiece(0, 6, new Paard(wit));
    setPiece(0, 2, new Loper(wit));
    setPiece(0, 5, new Loper(wit));
    setPiece(0, 3, new Koningin(wit));
    setPiece(0, 4, new Koning(wit));
    //set zwarte schaakstukken
    for(int i = 0; i < 8; i++){
        setPiece(6, i, new Pion(zwart));
    }
    setPiece(7, 0, new Toren(zwart));
    setPiece(7, 7, new Toren(zwart));
    setPiece(7, 1, new Paard(zwart));
    setPiece(7, 6, new Paard(zwart));
    setPiece(7, 2, new Loper(zwart));
    setPiece(7, 5, new Loper(zwart));
    setPiece(7, 3, new Koningin(zwart));
    setPiece(7, 4, new Koning(zwart));
}
// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    return true;
}


// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    if(r > 7 || k > 7) return nullptr;
    if(speelbord.empty()) return nullptr;
    int index = r*8 + k;
    return speelbord[index];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    int index = r*8 + k;
    speelbord[index] = s;
    // Hier komt jouw code om een stuk neer te zetten op het bord
}

const vector<SchaakStuk *> &Game::getSpeelbord() const {
    return speelbord;
}
