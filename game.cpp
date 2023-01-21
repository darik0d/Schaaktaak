//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
Game::Game() {

    for(int i = 0; i < 64; i++){
        speelbord.push_back(nullptr);
    }
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    //maak een leeg bord aan
    speelbord.clear();
    for(int i = 0; i < 64; i++){
        speelbord.push_back(nullptr);
    }
    //set zwarte schaakstukken
    for(int i = 0; i < 8; i++){
        setPiece(1, i, new Pion(zwart));
    }
    setPiece(0, 0, new Toren(zwart));
    setPiece(0, 7, new Toren(zwart));
    setPiece(0, 1, new Paard(zwart));
    setPiece(0, 6, new Paard(zwart));
    setPiece(0, 2, new Loper(zwart));
    setPiece(0, 5, new Loper(zwart));
    setPiece(0, 3, new Koningin(zwart));
    setPiece(0, 4, new Koning(zwart));
    //set witte schaakstukken
    for(int i = 0; i < 8; i++){
        setPiece(6, i, new Pion(wit));
    }
    setPiece(7, 0, new Toren(wit));
    setPiece(7, 7, new Toren(wit));
    setPiece(7, 1, new Paard(wit));
    setPiece(7, 6, new Paard(wit));
    setPiece(7, 2, new Loper(wit));
    setPiece(7, 5, new Loper(wit));
    setPiece(7, 3, new Koningin(wit));
    setPiece(7, 4, new Koning(wit));

    SchaakStuk* s= getPiece(1,0); // Zwarte pion
    vector<pair<int,int>> v=s->geldige_zetten(*this);
    move(s,2,0); // Geeft true; het stuk wordt verplaatst
    move(s,5,1);
}
// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    pair<int,int> pos = make_pair(r,k);
    vector<pair<int,int>> mog = s->geldige_zetten(*this);
    if(find(mog.begin(), mog.end(), pos) != mog.end()){
        pair <int,int> old_pos = s->getPosition(*this);
        int old_r = old_pos.first;
        int old_k = old_pos.second;
        setPiece(r,k,s);
        deletePiece(old_r, old_k);
        return true;
    }
    else return false;
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
void Game::deletePiece(int r, int k){
    if(0 < r < 8 && 0 < k < 8){
        int index = r*8 + k;
        speelbord[index] = nullptr;
    }
}
// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) const{
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
SchaakStuk* Game::bezet(int row, int col) const{
    int index = row*8 + col;
    if(speelbord[index] != nullptr) return speelbord[index];
    else return nullptr;
}
SchaakStuk* Game::bezet(int index) const{
    if(speelbord[index] != nullptr) return speelbord[index];
    else return nullptr;
}
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    int index = r*8 + k;
    speelbord[index] = s;
    // Hier komt jouw code om een stuk neer te zetten op het bord
}

const vector<SchaakStuk *> &Game::getSpeelbord() const {
    return speelbord;
}


