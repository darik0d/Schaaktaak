//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
#include <chrono>
#include <thread>

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
            message("Sorry, nu is niet uw beurt.");
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
        }else{
            message("Deze zet is ongeldig.");
            updateBedreigd();
        }
    }
//    // Volgende schaakstukken worden aangemaakt om het voorbeeld te illustreren.
//    // In jouw geval zullen de stukken uit game g komen
//    SchaakStuk* p1=new Pion(zwart);
//    SchaakStuk* p2=new Pion(zwart);
//    SchaakStuk* Q=new Koningin(zwart);
//    SchaakStuk* K=new Koning(zwart);
//
//    SchaakStuk* p3=new Pion(wit);
//    SchaakStuk* P=new Paard(wit);
//    SchaakStuk* L=new Loper(wit);
//    SchaakStuk* Kw=new Koning(wit);
//
//
//    removeAllMarking();  // Alle markeringen weg
//    clearBoard();        // Alle stukken weg
//
//    // plaats alle stukken
//    setItem(3,0,P);
//    setItem(1,1,p1);
//    setItem(0,3,Q);
//    setItem(0,4,K);
//    setItem(2,4,p2);
//    setItem(3,3,p3);
//    setItem(2,7,L);
//    setItem(5,3,Kw);
//
//    if (displayKills()) {
//        // Markeer de stukken die je kan slaan
//        setPieceThreat(3,0,true);
//        setPieceThreat(3,3,true);
//    }
//    if (displayThreats()) {
//        // Markeer jouw bedreigde stukken
//        setPieceThreat(2,4,true);
//        setPieceThreat(1,1,true);
//    }
//
//    message("Illustratie voor click; zwart is aan de beurt");
//
//    removeAllPieceThreats();  // Eens een stuk gekozen is, worden alle bedreigde stukken niete langer gemarkeerd
//    setTileSelect(2,4,true);  // De geselecteerde positie wordt steeds gemarkeerd
//    if (displayMoves()) {
//        // Geef de mogelijke zetten weer
//        setTileFocus(3,3,true);
//        setTileFocus(3,4,true);
//    }
//
//    message("Illustratie na click; zwart kiest doelpositie");
//
//    clearBoard();
//    removeAllMarking();
//
//    setItem(3,0,P);
//    setItem(1,1,p1);
//    setItem(0,3,Q);
//    setItem(0,4,K);
//    setItem(2,7,L);
//    setItem(5,3,Kw);
//    setItem(3,3,p2);
//
//    if (displayKills()) {
//        setPieceThreat(2,4,true);
//        setPieceThreat(1,1,true);
//    }
//    if (displayThreats()) {
//        setPieceThreat(3,0,true);
//    }
//
//
//    message("Illustratie na doelpositie gekozen is; nu is wit aan de beurt");
//
//    removeAllPieceThreats();
//
//    setTileSelect(2,7,true);
//    if (displayMoves()) {
//        for (int r=0;r<8;r++) {
//            if (r==2) continue;
//            int c=7-abs(r-2);
//            setTileFocus(r,c,true);
//        }
//    }
//    if (displayThreats()) {
//        setTileThreat(0,5,true);
//        setTileThreat(3,6,true);
//    }
//
//    message("Wit stuk geselecteerd; wit moet nu een doelpositie kiezen");
//    removeAllMarking();
//    // etc. etc. ...
//
//    delete p1;
//    delete p2;
//    delete Q;
//    delete K;
//    delete p3;
//    delete P;
//    delete L;
//    delete Kw;
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
    wit_aan_de_beurt = !wit_aan_de_beurt;
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
    wit_aan_de_beurt = !wit_aan_de_beurt;
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

