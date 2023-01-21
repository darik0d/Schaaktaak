//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H
#include <iostream>

using namespace std;
#include "SchaakStuk.h"
class SchaakStuk;
class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();
    SchaakStuk* getPiece(int r, int k) const;
    const vector<SchaakStuk *> &getSpeelbord() const;
    void deletePiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);
    SchaakStuk* bezet(int row, int col) const;
    SchaakStuk* bezet(int index) const;
private:
    vector<SchaakStuk*> speelbord;
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
};


#endif //SCHAKEN_GAME_H
