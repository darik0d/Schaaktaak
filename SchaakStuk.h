//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>
using namespace std;
class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Verander deze functie niet!
    virtual vector<pair<int,int>> geldige_zetten(Game& game) const=0;                                // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI
    pair <int,int> getPosition(Game& game)const;
    zw getKleur() const { return kleur; }
private:
    zw kleur;
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> geldige_zetten(Game& game) const;
};

#endif //SCHAKEN_SCHAAKSTUK_H
