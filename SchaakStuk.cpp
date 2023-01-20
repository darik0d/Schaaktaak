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
        if(spb[index] == this){
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
        if(pos.first == 6 && !game.bezet(pos.first - 2, pos.second)){
                wow.push_back(make_pair(pos.first-2,pos.second));
        }
        // check if move one forward
        if(pos.first != 0 && !game.bezet(pos.first - 1, pos.second)){
                wow.push_back(make_pair(pos.first-1,pos.second));
        }
        // check if can attack
        if(pos.first != 0 && pos.second != 0 && game.bezet(pos.first - 1, pos.second - 1)){
            wow.push_back(make_pair(pos.first-1,pos.second - 1));
        }
        if(pos.first != 0 && pos.second != 7 && !game.bezet(pos.first - 1, pos.second + 1)){
            wow.push_back(make_pair(pos.first-1,pos.second+1));
        }
    }else{
        //copy white, but another indices
        // check if start position
        if(pos.first == 1 && !game.bezet(pos.first + 2, pos.second)){
            wow.push_back(make_pair(pos.first+2,pos.second));
        }
        // check if move one forward
        if(pos.first != 7 && !game.bezet(pos.first + 1, pos.second)){
            wow.push_back(make_pair(pos.first+1,pos.second));
        }
        // check if can attack
        if(pos.first != 7 && pos.second != 0 && game.bezet(pos.first + 1, pos.second - 1)){
            wow.push_back(make_pair(pos.first+1,pos.second - 1));
        }
        if(pos.first != 7 && pos.second != 7 && !game.bezet(pos.first + 1, pos.second + 1)){
            wow.push_back(make_pair(pos.first+1,pos.second+1));
        }
    }
}

vector<pair<int,int>> Toren::geldige_zetten(Game& game)const{

}
vector<pair<int,int>> Loper::geldige_zetten(Game& game)const{

}
vector<pair<int,int>> Paard::geldige_zetten(Game& game)const{

}
vector<pair<int,int>> Koningin::geldige_zetten(Game& game) const{

}
vector<pair<int,int>> Koning::geldige_zetten(Game& game) const{

}