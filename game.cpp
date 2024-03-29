//  Student: Daria Matviichuk
//  Rolnummer: s0221485
//  Opmerkingen: In SchaakGUI.cpp kunt u kiezen voor welke kleur AI speelt
//  (daarvoor moet u de inhoud van ai_kleur aanpassen, zie lijn 10)
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
    // Maak een leeg bord aan
    speelbord.clear();
    for(int i = 0; i < 64; i++){
        speelbord.push_back(nullptr);
    }
    // Zet alle zwarte schaakstukken
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
    // Zet alle witte schaakstukken
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

}
// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    if(s == nullptr) return false; // Een leeg schaakstuk kan niet worden verplaatst

    pair<int,int> pos = make_pair(r,k);
    // Verzamel alle mogelijke zetten (zonder na te gaan of er een schaak is)
    vector<pair<int,int>> mog = s->geldige_zetten(*this);
    // Ga na of de zet mogelijk is
    if(find(mog.begin(), mog.end(), pos) != mog.end()){
        pair <int,int> old_pos = s->getPosition(*this);
        int old_r = old_pos.first;
        int old_k = old_pos.second;
        SchaakStuk* old_piece = getPiece(r,k);
        setPiece(r,k,s);
        deletePiece(old_r, old_k);
        // Als de zet tot de schaak van eigen kleur leidt, is de zet onmogelijk
        if(schaak(s->getKleur())){
            setPiece(old_r, old_k, s);
            setPiece(r,k,old_piece);
            return false;
        }
        return true;
    }
    else return false;
}


// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    // Check alle geldige zetten voor figuren van de tegengestelde kleur
    vector<pair<int,int>> gevaar;
    for(auto figuur: speelbord){
        if(figuur != nullptr){
            if(figuur->getKleur() != kleur) {
                vector<pair<int, int>> to_add = figuur->geldige_zetten(*this);
                gevaar.reserve(gevaar.size() + to_add.size());
                gevaar.insert(gevaar.end(), to_add.begin(), to_add.end());
            }
        }
    }
    // Neem positie van de koning
    pair<int,int> pos = kleur == wit ? wk_pos : zk_pos;
    // Als positie van de koning zit in deze vector, return true
    if(find(gevaar.begin(), gevaar.end(), pos) != gevaar.end()) return true;
    else return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    if(schaak(kleur)) {
    // Bereken alle geldige zetten voor kleur
    vector<pair<SchaakStuk*, vector<pair<int,int>>>> zetten; // Vector van SchaakStuk + mogelijke zetten daarvan
    for(auto figuur: speelbord){
        if(figuur != nullptr){
            if(figuur->getKleur() == kleur){
                vector<pair<int,int>> to_add_dummy = figuur->geldige_zetten(*this);
                vector<pair<SchaakStuk*, vector<pair<int,int>>>> to_add;
                to_add.push_back(make_pair(figuur,to_add_dummy));
                zetten.reserve(zetten.size() + to_add.size());
                zetten.insert(zetten.end(), to_add.begin(), to_add.end());
            }
        }
    }
    // Controleer alle zetten
    for(auto check: zetten){
        for(auto pos: check.second){
            pair<int,int> old_pos = check.first->getPosition(*this);
            SchaakStuk* old_fig = getPiece(pos.first, pos.second);
            if(move(check.first, pos.first, pos.second)) {
                // Zet alles terug
                setPiece(old_pos.first, old_pos.second, check.first);
                setPiece(pos.first, pos.second, old_fig);
                return false;
            }
        }
    }
        //cout << "Schaakmat!!!" << endl;
        return true;
    }
    else return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    // Bereken alle geldige zetten voor kleur
    vector<pair<SchaakStuk*, vector<pair<int,int>>>> zetten; //vector van SchaakStuk + mogelijke zetten daarvan
    for(auto figuur: speelbord){
        if(figuur != nullptr){
            if(figuur->getKleur() == kleur){
                vector<pair<int,int>> to_add_dummy = figuur->geldige_zetten(*this);
                vector<pair<SchaakStuk*, vector<pair<int,int>>>> to_add;
                to_add.push_back(make_pair(figuur,to_add_dummy));
                zetten.reserve(zetten.size() + to_add.size());
                zetten.insert(zetten.end(), to_add.begin(), to_add.end());
            }
        }
    }
    if(zetten.empty()) return true;
    else {
        // Controleer alle zetten
        for(auto check: zetten){
            for(auto pos: check.second){
                pair<int,int> old_pos = check.first->getPosition(*this);
                SchaakStuk* old_fig = getPiece(pos.first, pos.second);
                if(move(check.first, pos.first, pos.second)) {
                    // Zet alles terug
                    setPiece(old_pos.first, old_pos.second, check.first);
                    setPiece(pos.first, pos.second, old_fig);
                    return false;
                }
            }
        }
        //cout << "Pat!!!" << endl;
        return true;
    }
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
    //check if koning()
    if(s != nullptr) {
        if (typeid(*s) == typeid(Koning)) {
            if (s->getKleur() == wit) wk_pos = make_pair(r, k);
            else zk_pos = make_pair(r, k);
        }
    }
    // Hier komt jouw code om een stuk neer te zetten op het bord
}

const vector<SchaakStuk *> &Game::getSpeelbord() const {
    return speelbord;
}

vector<pair<int,int>> Game::mogelijke_zetten(zw kleur) {
    vector<pair<int,int>> zetten;
    for(SchaakStuk* stuk: speelbord){
        if(stuk != nullptr){
            if(stuk->getKleur() == kleur){
                vector<pair<int,int>> to_add = stuk->geldige_zetten(*this);
                zetten.reserve(zetten.size() + to_add.size());
                zetten.insert(zetten.end(),to_add.begin(),to_add.end());
            }
        }
    }
    return zetten;
}

vector<pair<SchaakStuk*, vector<pair<int,int>>>> Game::mogelijke_zetten_met_figuren(zw kleur){
    vector<pair<SchaakStuk*, vector<pair<int,int>>>> zetten;
    for(SchaakStuk* stuk: speelbord){
        if(stuk != nullptr){
            if(stuk->getKleur() == kleur){
                vector<pair<int,int>> to_add = stuk->geldige_zetten(*this);
                zetten.push_back(make_pair(stuk, to_add));
            }
        }
    }
    return zetten;
}

void Game::setSpeelbord(const vector<SchaakStuk *> &speelbord) {
    Game::speelbord = speelbord;
}

double Game::evaluatePosition(zw kleur){
    // Evalueer het bord aan de hand van aan-/afwezigheid van stukken en hun positie
    double to_return = 0;
    int coef = 0;
    for(auto figuur:speelbord){
        if(figuur != nullptr){
            if(figuur->getKleur() == kleur) coef = 1;
            else coef = -1;
            pair<int,int> pos = figuur->getPosition(*this);
            if(typeid(*figuur) == typeid(Pion)) {
                to_return += coef*10;
                if(figuur->getKleur() == wit) to_return += coef*pawnW[pos.first][pos.second];
                else to_return += coef*pawnZ[pos.first][pos.second];
            }
            else if(typeid(*figuur) == typeid(Paard)) {
                to_return += coef*30;
                if(figuur->getKleur() == wit) to_return += coef*paardW[pos.first][pos.second];
                else to_return += coef*paardZ[pos.first][pos.second];
            }
            else if(typeid(*figuur) == typeid(Loper)) {
                to_return += coef*30;
                if(figuur->getKleur() == wit) to_return += coef*loperW[pos.first][pos.second];
                else to_return += coef*loperZ[pos.first][pos.second];
            }
            else if(typeid(*figuur) == typeid(Toren)) {
                to_return += coef*50;
//                if(figuur->getKleur() == wit) to_return += coef*torenW[pos.first][pos.second];
//                else to_return += coef*torenZ[pos.first][pos.second];
            }
            else if(typeid(*figuur) == typeid(Koningin)) {
                to_return += coef*90;
//                if(figuur->getKleur() == wit) to_return += coef*koninginW[pos.first][pos.second];
//                else to_return += coef*koninginZ[pos.first][pos.second];
            }
            else if(typeid(*figuur) == typeid(Koning)) {
                to_return += coef*900;
//                if(figuur->getKleur() == wit) to_return += coef*koningW[pos.first][pos.second];
//                else to_return += coef*koningZ[pos.first][pos.second];
            }
        }
    }
    return to_return;
}

