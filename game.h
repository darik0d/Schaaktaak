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
    vector<pair<int,int>> bedreigde_stukken;
    void setStartBord();
    SchaakStuk* getPiece(int r, int k) const;
    const vector<SchaakStuk *> &getSpeelbord() const;

    void setSpeelbord(const vector<SchaakStuk *> &speelbord);

    void deletePiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);
    SchaakStuk* bezet(int row, int col) const;
    SchaakStuk* bezet(int index) const;
    vector<pair<int,int>> mogelijke_zetten(zw kleur);
    vector<pair<int,int>> mogelijke_attack_zetten(zw kleur);

private:
    vector<SchaakStuk*> speelbord;
    pair<int,int> wk_pos;
    pair<int,int> zk_pos;
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
};


#endif //SCHAKEN_GAME_H
