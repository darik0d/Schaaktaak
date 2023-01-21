//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
//class Game;
pair <int,int> SchaakStuk::getPosition(Game& game)const{
    int index = 0;
    vector<SchaakStuk*> spb = game.getSpeelbord();
    for(int i = 0; i < 64; i++){
        if(spb[i] == this){
            index = i;
        }
    }
    int row = index / 8;
    int col = index - (row*8);
    return make_pair(row,col);
}
vector<pair<int,int>> Pion::geldige_zetten(Game& game)const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    if(getKleur() == wit){
        // check if start position
        if(pos.first == 6 && game.bezet(pos.first - 2, pos.second) == nullptr){
                wow.push_back(make_pair(pos.first-2,pos.second));
        }
        // check if move one forward
        if(pos.first != 0 && game.bezet(pos.first - 1, pos.second) == nullptr){
                wow.push_back(make_pair(pos.first-1,pos.second));
        }
        // check if can attack
        if(pos.first != 0 && pos.second != 0 && game.bezet(pos.first - 1, pos.second - 1) != nullptr && game.bezet(pos.first - 1, pos.second - 1)->getKleur() == zwart){
            wow.push_back(make_pair(pos.first-1,pos.second - 1));
        }
        if(pos.first != 0 && pos.second != 7 && game.bezet(pos.first - 1, pos.second + 1) != nullptr && game.bezet(pos.first - 1, pos.second - 1)->getKleur() == zwart){
            wow.push_back(make_pair(pos.first-1,pos.second+1));
        }
    }else{
        //copy white, but another indices
        // check if start position
        if(pos.first == 1 && game.bezet(pos.first + 2, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first+2,pos.second));
        }
        // check if move one forward
        if(pos.first != 7 && game.bezet(pos.first + 1, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first+1,pos.second));
        }
        // check if can attack
        if(pos.first != 7 && pos.second != 0 && game.bezet(pos.first + 1, pos.second - 1) != nullptr && game.bezet(pos.first + 1, pos.second - 1)->getKleur() == wit){
            wow.push_back(make_pair(pos.first+1,pos.second - 1));
        }
        if(pos.first != 7 && pos.second != 7 && game.bezet(pos.first + 1, pos.second + 1)  != nullptr && game.bezet(pos.first + 1, pos.second + 1)->getKleur() == wit){
            wow.push_back(make_pair(pos.first+1,pos.second+1));
        }
    }
    return wow;
}

vector<pair<int,int>> Toren::geldige_zetten(Game& game)const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    //geen verschil of dat wit of zwart is. Bij attack moeten de figuren wel verschillende kleuren hebben
    //loop over boven
    for(int i = 1; pos.first + i < 8;i++){
        if(game.bezet(pos.first+i, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second));
        }else{
            if(game.bezet(pos.first + i, pos.second)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i,pos.second));
            }
            break;
        }
    }
    //loop over beneden
    for(int i = 1; pos.first - i >= 0;i++){
        if(game.bezet(pos.first - i, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second));
        }else{
            if(game.bezet(pos.first - i, pos.second)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second));
            }
            break;
        }
    }
    //loop over rechts
    for(int i = 1; pos.second + i < 8;i++){
        if(game.bezet(pos.first, pos.second + i) == nullptr){
            wow.push_back(make_pair(pos.first,pos.second + i));
        }else{
            if(game.bezet(pos.first, pos.second + i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first,pos.second + i));
            }
            break;
        }
    }
    //loop naar links
    for(int i = 1; pos.second - i >= 0; i++){
        if(game.bezet(pos.first, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first,pos.second - i));
        }else{
            if(game.bezet(pos.first, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first, pos.second - i));
            }
            break;
        }
    }
    return wow;
}
vector<pair<int,int>> Loper::geldige_zetten(Game& game)const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    //geen verschil of dat wit of zwart is. Bij attack moeten de figuren wel verschillende kleuren hebben
    //loop over boven + rechts
    for(int i = 1; pos.first + i < 8 && pos.second + i < 8;i++){
        if(game.bezet(pos.first+i, pos.second+i) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second+i));
        }else{
            if(game.bezet(pos.first + i, pos.second+i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i,pos.second+i));
            }
            break;
        }
    }
    //loop over beneden - links
    for(int i = 1; pos.first - i >= 0 && pos.second - i >= 0;i++){
        if(game.bezet(pos.first - i, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second - i));
        }else{
            if(game.bezet(pos.first - i, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second - i));
            }
            break;
        }
    }
    //loop over beneden - rechts
    for(int i = 1; pos.first - i >= 0 && pos.second + i < 8;i++){
        if(game.bezet(pos.first - i, pos.second + i) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second + i));
        }else{
            if(game.bezet(pos.first - i, pos.second + i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second + i));
            }
            break;
        }
    }
    //loop naar boven - links
    for(int i = 1; pos.first + i < 8 && pos.second - i >= 0; i++){
        if(game.bezet(pos.first + i, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second - i));
        }else{
            if(game.bezet(pos.first + i, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i, pos.second - i));
            }
            break;
        }
    }
    return wow;
}
vector<pair<int,int>> Paard::geldige_zetten(Game& game)const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    //geen verschil of dat wit of zwart is. Bij attack moeten de figuren wel verschillende kleuren hebben
    // Г
    if(pos.first+2 < 8 && pos.second + 1 < 8 && (game.bezet(pos.first+2, pos.second+1) == nullptr || game.bezet(pos.first+2, pos.second+1)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first+2, pos.second+1));
    if(pos.first+2 < 8 && pos.second - 1 > -1 && (game.bezet(pos.first+2, pos.second-1) == nullptr || game.bezet(pos.first+2, pos.second-1)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first+2, pos.second-1));
    if(pos.first - 2 > -1 && pos.second + 1 < 8 && (game.bezet(pos.first-2, pos.second+1) == nullptr || game.bezet(pos.first-2, pos.second+1)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first-2, pos.second+1));
    if(pos.first - 2 > -1 && pos.second - 1 > -1 && (game.bezet(pos.first-2, pos.second-1) == nullptr || game.bezet(pos.first-2, pos.second-1)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first-2, pos.second-1));
    if(pos.first - 1 > -1 && pos.second + 2 < 8 && (game.bezet(pos.first-1, pos.second+2) == nullptr || game.bezet(pos.first-1, pos.second+2)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first-1, pos.second+2));
    if(pos.first + 1 < 8 && pos.second + 2 < 8 && (game.bezet(pos.first+1, pos.second+2) == nullptr || game.bezet(pos.first+1, pos.second+2)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first+1, pos.second+2));
    if(pos.first - 1 > -1 && pos.second - 2 > -1 && (game.bezet(pos.first-1, pos.second-2) == nullptr || game.bezet(pos.first-1, pos.second-2)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first-1, pos.second-2));
    if(pos.first + 1 < 8 && pos.second - 2 > -1 && (game.bezet(pos.first+1, pos.second-2) == nullptr || game.bezet(pos.first+1, pos.second-2)->getKleur() != getKleur())) wow.push_back(make_pair(pos.first+1, pos.second-2));
    return wow;
}
vector<pair<int,int>> Koningin::geldige_zetten(Game& game) const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    //geen verschil of dat wit of zwart is. Bij attack moeten de figuren wel verschillende kleuren hebben
    //loop over boven
    for(int i = 1; pos.first + i < 8;i++){
        if(game.bezet(pos.first+i, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second));
        }else{
            if(game.bezet(pos.first + i, pos.second)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i,pos.second));
            }
            break;
        }
    }
    //loop over beneden
    for(int i = 1; pos.first - i >= 0;i++){
        if(game.bezet(pos.first - i, pos.second) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second));
        }else{
            if(game.bezet(pos.first - i, pos.second)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second));
            }
            break;
        }
    }
    //loop over rechts
    for(int i = 1; pos.second + i < 8;i++){
        if(game.bezet(pos.first, pos.second + i) == nullptr){
            wow.push_back(make_pair(pos.first,pos.second + i));
        }else{
            if(game.bezet(pos.first, pos.second + i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first,pos.second + i));
            }
            break;
        }
    }
    //loop naar links
    for(int i = 1; pos.second - i >= 0; i++){
        if(game.bezet(pos.first, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first,pos.second - i));
        }else{
            if(game.bezet(pos.first, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first, pos.second - i));
            }
            break;
        }
    }
    //geen verschil of dat wit of zwart is. Bij attack moeten de figuren wel verschillende kleuren hebben
    //loop over boven + rechts
    for(int i = 1; pos.first + i < 8 && pos.second + i < 8;i++){
        if(game.bezet(pos.first+i, pos.second+i) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second+i));
        }else{
            if(game.bezet(pos.first + i, pos.second+i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i,pos.second+i));
            }
            break;
        }
    }
    //loop over beneden - links
    for(int i = 1; pos.first - i >= 0 && pos.second - i >= 0;i++){
        if(game.bezet(pos.first - i, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second - i));
        }else{
            if(game.bezet(pos.first - i, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second - i));
            }
            break;
        }
    }
    //loop over beneden - rechts
    for(int i = 1; pos.first - i >= 0 && pos.second + i < 8;i++){
        if(game.bezet(pos.first - i, pos.second + i) == nullptr){
            wow.push_back(make_pair(pos.first - i,pos.second + i));
        }else{
            if(game.bezet(pos.first - i, pos.second + i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first - i,pos.second + i));
            }
            break;
        }
    }
    //loop naar boven - links
    for(int i = 1; pos.first + i < 8 && pos.second - i >= 0; i++){
        if(game.bezet(pos.first + i, pos.second - i) == nullptr){
            wow.push_back(make_pair(pos.first + i,pos.second - i));
        }else{
            if(game.bezet(pos.first + i, pos.second - i)->getKleur() != getKleur()){
                wow.push_back(make_pair(pos.first + i, pos.second - i));
            }
            break;
        }
    }
    return wow;
}
vector<pair<int,int>> Koning::geldige_zetten(Game& game) const{
    vector<pair<int,int>> wow;
    pair<int,int> pos = getPosition(game);
    for(int i = -1; i < 2; i++){
        for(int k = -1; k < 2; k++){
            if(-1 < pos.first + i && pos.first + i < 8 && -1 < pos.second + k && pos.second + k < 8) {
                if(game.bezet(pos.first + i, pos.second + k) == nullptr) {
                    wow.push_back(make_pair(pos.first+i, pos.second+k));
                }
                else if(game.bezet(pos.first + i, pos.second + k)->getKleur() != getKleur()) {
                    wow.push_back(make_pair(pos.first+i, pos.second+k));
                }
            }
        }
    }
    return wow;
}