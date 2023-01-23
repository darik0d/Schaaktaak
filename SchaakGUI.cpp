//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
// voor time delay:
//#include <chrono>
#include <thread>

bool ai_aan = true;

zw ai_kleur[2] = {zwart,zwart};
//kies tussen {zwart, wit} (voor geen AI), {wit, wit}, {zwart,zwart} of {wit, zwart}

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    g.setStartBord();
    geschiedenis.push_back(g.getSpeelbord());
    zet_nummer++;
    update();
}

void SchaakGUI::updateBedreigd(){
    g.bedreigde_stukken.clear();
    g.mogelijke_zetten(wit);
    g.mogelijke_zetten(zwart);
    for(auto pos:g.bedreigde_stukken) setPieceThreat(pos.first, pos.second, displayThreats());
    update();
}
pair<SchaakStuk*, pair<int,int>> SchaakGUI::besteZet(zw kleur){
    pair<SchaakStuk*, pair<int,int>> to_return;
    int prev_coef = 0;
    int cur_coef = 0;
    for(auto m: g.mogelijke_zetten_met_figuren(kleur)) {
        //pair<SchaakStuk*, vector<pair<int,int>>>
        for(auto pos: m.second){
            //m.first is de stuk
            SchaakStuk* old_stuk = g.getPiece(pos.first, pos.second);
            pair<int,int> old_pos = m.first->getPosition(g);
//            g.setPiece(old_pos.first, old_pos.second, nullptr);
//            g.setPiece(pos.first, pos.second, m.first);
            if(g.move(m.first, pos.first, pos.second)){
                //evaluate pos
                cur_coef = g.evaluatePosition(kleur);
                //add schaakmat coef
                zw antikleur = kleur == wit ? zwart : wit;
                if(g.schaakmat(antikleur)) cur_coef += 3000;
                //add schaak coef
                if(g.schaak(antikleur)) cur_coef += 100;

                //compare and if better, change
                if(cur_coef >= prev_coef){
                    prev_coef = cur_coef;
                    to_return = make_pair(m.first, pos);
                }
                //return everything to the previous state
                g.setPiece(old_pos.first, old_pos.second, m.first);
                g.setPiece(pos.first, pos.second, old_stuk);
            }
        }
    }
    return to_return;
}
void SchaakGUI::aiStap(zw kleur){
    //pak een random figuur en maak een willekeurige zet
//    vector<pair<SchaakStuk*, vector<pair<int,int>>>> waarheen = g.mogelijke_zetten_met_figuren(kleur);
//    int move_number = rand() % waarheen.size();
//    pair<SchaakStuk*, vector<pair<int,int>>> element = waarheen[move_number];
//    while (element.second.empty()){
//        move_number = rand() % waarheen.size();
//        element = waarheen[move_number];
//    }
//    g.move(element.first, element.second[0].first, element.second[0].second);

    wit_aan_de_beurt = !wit_aan_de_beurt;
    pair<SchaakStuk*, pair<int,int>> beste_move = besteZet(kleur);
    g.move(beste_move.first, beste_move.second.first, beste_move.second.second);
    clearBoard();
    removeAllMarking();
    updateBedreigd();
    update();
}
// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    // Wat hier staat is slechts een voorbeeldje dat wordt afgespeeld ter illustratie.
    // Jouw code zal er helemaal anders uitzien en zal enkel de aanpassing in de spelpositie maken en er voor
    // zorgen dat de visualisatie (al dan niet via update) aangepast wordt.
    //this_thread::sleep_for(std::chrono::milliseconds(100));
    if(!second_click){
        //display all threatened figures
        if(g.bezet(r,k) == nullptr) return;
        removeAllMarking();
        if(g.bezet(r,k)->getKleur() == wit && wit_aan_de_beurt || g.bezet(r,k)->getKleur() == zwart && !wit_aan_de_beurt) {
            selected_figure = g.bezet(r, k);
            if (selected_figure != nullptr) {
                setTileSelect(r, k, true);
                vector<pair<int,int>> to_go = selected_figure->geldige_zetten(g);
                for(auto x: to_go){
                    setTileFocus(x.first, x.second, displayMoves());
                }
                g.bedreigde_stukken.clear();
                zw kleur = wit_aan_de_beurt ? zwart : wit;
                for(auto try_pos: to_go){
                    SchaakStuk* old_stuk = g.getPiece(try_pos.first, try_pos.second);
                    g.setPiece(try_pos.first, try_pos.second, selected_figure);
                    g.mogelijke_zetten(kleur);
                    g.setPiece(r, k, selected_figure);
                    g.setPiece(try_pos.first, try_pos.second, old_stuk);
                }
                vector<pair<int,int>> gevaar = g.bedreigde_stukken;
                for(auto a: to_go){
                    if(std::find(gevaar.begin(), gevaar.end(), a) != gevaar.end()) {
                        setTileFocus(a.first, a.second, displayKills());
                        setTileThreat(a.first, a.second, displayKills());
                    }
                }
                update();
                second_click = true;
            }
        } else{
            message("Sorry, nu is de beurt van de andere kleur");
            updateBedreigd();
        }
    }else{
        second_click = false;
        removeAllMarking();
        if(g.move(selected_figure, r, k)){
            g.move(selected_figure, r, k);
            clearBoard();
            update();
            wit_aan_de_beurt = !wit_aan_de_beurt;
            zw kleurtje = wit_aan_de_beurt ? wit : zwart;
            if(g.schaakmat(kleurtje)) {
                message("Schaakmat!");
            } else if(g.schaak(kleurtje)){
                message("Schaak!");
            }
            else if(g.pat(kleurtje)) message("Pat!");
            updateBedreigd();
            stepForward();
            update();
            if(ai_aan) aiStap(kleurtje);
        }else{
            message("Deze zet is ongeldig.");
            updateBedreigd();
        }
    }
}

void SchaakGUI::newGame(){
    clearBoard();
    removeAllMarking();
    g.setStartBord();
    geschiedenis.push_back(g.getSpeelbord());
    second_click = false;
    wit_aan_de_beurt = true;
    selected_figure = nullptr;
    update();
}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}


void SchaakGUI::undo() {
    if(zet_nummer < 2) {
        message("U kunt niet meer terug.");
        return;
    }
    --zet_nummer;
    g.setSpeelbord(geschiedenis[zet_nummer-1]);
    if(!ai_aan) wit_aan_de_beurt = !wit_aan_de_beurt;
    clearBoard();
    removeAllMarking();
    update();
}

void SchaakGUI::redo() {
    if(zet_nummer >= geschiedenis.size()){
        message("Dit is de laatste bewaarde zet");
        return;
    }
    zet_nummer++;
    g.setSpeelbord(geschiedenis[zet_nummer-1]);
    if(!ai_aan) wit_aan_de_beurt = !wit_aan_de_beurt;
    clearBoard();
    removeAllMarking();
    update();
}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    for(int r = 0; r < 8; r++){
        for(int k = 0; k < 8; k++){
            //vector<SchaakStuk*> wow = g.getSpeelbord();
            if(g.getPiece(r,k)!= nullptr) setItem(r, k, g.getPiece(r,k));
        }
    }
}

