#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
// voor time delay:
//#include <chrono>
#include <thread>

bool ai_aan = true;

zw ai_kleur[2] = {zwart, zwart}; //kies tussen {zwart, wit} (voor geen AI), {wit, wit} (AI speelt voot witte),
// {zwart,zwart} (AI speelt voor zwarte)  of {wit, zwart} (AI speelt met zichzelf. Elke zet gebeurt van een click)
int schaak_coef = 15; // Geef in hoe een schaak belangrijk is

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    g.setStartBord();
    geschiedenis.push_back(g.getSpeelbord());
    zet_nummer = 0;
    stepForward();
    if(ai_kleur[0] != ai_kleur[1]) ai_aan = false;
    if(ai_kleur[0] == wit and ai_kleur[1] != zwart) aiStap(wit);
    update();
}

void SchaakGUI::updateBedreigd(){
    g.bedreigde_stukken.clear();
    g.mogelijke_zetten(wit);
    g.mogelijke_zetten(zwart);
    for(auto pos:g.bedreigde_stukken) setPieceThreat(pos.first, pos.second, displayThreats());
    update();
}
pair<int,pair<SchaakStuk*, pair<int,int>>> SchaakGUI::besteZetDeelDrie(zw kleur){
    pair<SchaakStuk*, pair<int,int>> dummy_to_return;
    vector<pair<SchaakStuk*, pair<int,int>>> to_return;
    int prev_coef = 0;
    int cur_coef = 0;
    bool first_time = true;
    for(auto m: g.mogelijke_zetten_met_figuren(kleur)) {
        //pair<SchaakStuk*, vector<pair<int,int>>>
        for(auto pos: m.second){
            //m.first is het stuk
            SchaakStuk* old_stuk = g.getPiece(pos.first, pos.second);
            pair<int,int> old_pos = m.first->getPosition(g);
            if(g.move(m.first, pos.first, pos.second)){
                //evaluate pos
                cur_coef = g.evaluatePosition(kleur);
                //add schaakmat coef
                zw antikleur = kleur == wit ? zwart : wit;
                if(g.schaakmat(antikleur)) cur_coef += 3000;
                //add schaak coef
                if(g.schaak(antikleur)) cur_coef += schaak_coef;

                //compare and if better, change
                if(!first_time && m.first != nullptr){ //Controleer of dat is de eerste keer
                    //Bij de tweede en volgende keren moet je nagaan of dat een goede coef is
                    if(cur_coef == prev_coef){
                        prev_coef = cur_coef;
                        to_return.push_back(make_pair(m.first, pos));
                    }else if(cur_coef > prev_coef){
                        prev_coef = cur_coef;
                        to_return.clear();
                        to_return.push_back(make_pair(m.first, pos));
                    }
                } else{ // Als dat de eerste keer is, set prev_coef aan cur_coef + push de mogelijk aan de return
                    first_time = false;
                    prev_coef = cur_coef;
                    to_return.push_back(make_pair(m.first, pos));
                }
                //return everything to the previous state
                g.setPiece(old_pos.first, old_pos.second, m.first);
                g.setPiece(pos.first, pos.second, old_stuk);
            }
        }
    }
    if(to_return.empty()) return make_pair(-3000, dummy_to_return);
    return make_pair(prev_coef, to_return[rand() % to_return.size()]);
}
pair<int,pair<SchaakStuk*, pair<int,int>>> SchaakGUI::besteZetDeelTwee(zw kleur){
    pair<SchaakStuk*, pair<int,int>> dummy_to_return;
    vector<pair<SchaakStuk*, pair<int,int>>> to_return;
    int prev_coef = 0;
    int cur_coef = 0;
    bool first_time = true;
    for(auto m: g.mogelijke_zetten_met_figuren(kleur)) {
        //pair<SchaakStuk*, vector<pair<int,int>>>
        for(auto pos: m.second){
            //m.first is het stuk
            SchaakStuk* old_stuk = g.getPiece(pos.first, pos.second);
            pair<int,int> old_pos = m.first->getPosition(g);
            if(g.move(m.first, pos.first, pos.second)){
                //evaluate pos
                cur_coef = g.evaluatePosition(kleur);
                //add schaakmat coef
                zw antikleur = kleur == wit ? zwart : wit;
                if(g.schaakmat(antikleur)) cur_coef += 3000;
                //add schaak coef
                if(g.schaak(antikleur)) cur_coef += schaak_coef;

                //compare and if better, change
                if(!first_time && m.first != nullptr){ //Controleer of dat is de eerste keer
                    //Bij de tweede en volgende keren moet je nagaan of dat een goede coef is
                    if(cur_coef == prev_coef){
                        prev_coef = cur_coef;
                        to_return.push_back(make_pair(m.first, pos));
                    }else if(cur_coef > prev_coef){
                        prev_coef = cur_coef;
                        to_return.clear();
                        to_return.push_back(make_pair(m.first, pos));
                    }
                } else{ // Als dat de eerste keer is, set prev_coef aan cur_coef + push de mogelijk aan de return
                    first_time = false;
                    prev_coef = cur_coef;
                    to_return.push_back(make_pair(m.first, pos));
                }
                //return everything to the previous state
                g.setPiece(old_pos.first, old_pos.second, m.first);
                g.setPiece(pos.first, pos.second, old_stuk);
            }
        }
    }
    if(to_return.empty()) return make_pair(-3000, dummy_to_return);

    vector<pair<SchaakStuk*, pair<int,int>>> real_to_return;
    // Doe de laatste controle alleen voor de beste zetten:
    first_time = true;
    for(auto zet: to_return) {
        // Bewaar vorige figuren en positie
        SchaakStuk* old_stuk = g.getPiece(zet.second.first, zet.second.second);
        pair<int,int> old_pos = zet.first->getPosition(g);
        // Doe de move
        g.move(zet.first, zet.second.first, zet.second.second);
        // Evalueer positie
        cur_coef = g.evaluatePosition(kleur);
        // Vind be beste zet van ons
        zw antikleur = kleur == wit ? zwart : wit;
        int anti_coef = besteZetDeelDrie(antikleur).first;
        cur_coef -= anti_coef;

        // Vergelijk en als beter, verander
        if(!first_time && zet.first != nullptr){ //Controleer of dat is de eerste keer om toe te voegen
            //Bij de tweede en volgende keren moet je nagaan of dat een goede coef is
            if(cur_coef == prev_coef){
                prev_coef = cur_coef;
                real_to_return.push_back(make_pair(zet.first, zet.second));
            }else if(cur_coef > prev_coef){
                prev_coef = cur_coef;
                real_to_return.clear();
                real_to_return.push_back(make_pair(zet.first, zet.second));
            }
        } else{ // Als dat de eerste keer is, set prev_coef aan cur_coef + push de mogelijk aan de return
            first_time = false;
            prev_coef = cur_coef;
            real_to_return.push_back(make_pair(zet.first, zet.second));
        }
        //return everything to the previous state
        g.setPiece(old_pos.first, old_pos.second, zet.first);
        g.setPiece(zet.second.first, zet.second.second, old_stuk);
    }
    if(real_to_return.empty()) return make_pair(-3000, dummy_to_return);
    return make_pair(prev_coef, real_to_return[rand() % to_return.size()]);
}
pair<SchaakStuk*, pair<int,int>> SchaakGUI::besteZet(zw kleur){
    vector<pair<SchaakStuk*, pair<int,int>>> to_return;
    pair<SchaakStuk*, pair<int,int>> dummy_to_return;
    int prev_coef;
    bool first_time = true;
    int cur_coef = 0;
    vector<pair<SchaakStuk *, vector<pair<int, int>>>> mog_zetten = g.mogelijke_zetten_met_figuren(kleur);
    for(auto m: mog_zetten) {
        //pair<SchaakStuk*, vector<pair<int,int>>>
        for(auto pos: m.second){
            //m.first is de stuk
            SchaakStuk* old_stuk = g.getPiece(pos.first, pos.second);
            pair<int,int> old_pos = m.first->getPosition(g);
            if(g.move(m.first, pos.first, pos.second)){
                //evaluate pos
                cur_coef = g.evaluatePosition(kleur);
                //add schaakmat coef
                zw antikleur = kleur == wit ? zwart : wit;
                if(g.schaakmat(antikleur)) cur_coef += 3000;
                //add schaak coef
                if(g.schaak(antikleur)) cur_coef += schaak_coef;

                //get the best coef of the opposite
                int anti_coef = besteZetDeelTwee(antikleur).first;
                cur_coef -= anti_coef;

                //compare and if better, change
                if(!first_time && m.first != nullptr){ //Controleer of dat is de eerste keer
                    //Bij de tweede en volgende keren moet je nagaan of dat een goede coef is
                    if(cur_coef == prev_coef){
                        prev_coef = cur_coef;
                        to_return.push_back(make_pair(m.first, pos));
                    }else if(cur_coef > prev_coef){
                        prev_coef = cur_coef;
                        to_return.clear();
                        to_return.push_back(make_pair(m.first, pos));
                }
                } else{ // Als dat de eerste keer is, set prev_coef aan cur_coef + push de mogelijk aan de return
                    first_time = false;
                    prev_coef = cur_coef;
                    to_return.push_back(make_pair(m.first, pos));
                }
                //return everything to the previous state
                g.setPiece(old_pos.first, old_pos.second, m.first);
                g.setPiece(pos.first, pos.second, old_stuk);
            }
        }
    }

    if(to_return.empty()){ // Einde van het spel
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "Tot volgende keer!" << endl;
        return dummy_to_return;
    }
    return to_return[rand() % to_return.size()];
}
void SchaakGUI::aiStap(zw kleur){
    // Geïnspireerd door https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977/amp/
    removeAllMarking();
    wit_aan_de_beurt = !wit_aan_de_beurt;
    pair<SchaakStuk*, pair<int,int>> beste_move = besteZet(kleur);
    if(beste_move.first == nullptr) return; // Als er geen zet mogelijk is, stop
    g.move(beste_move.first, beste_move.second.first, beste_move.second.second);

    //check special cases:
    zw kleurtje = kleur == wit ? zwart : wit;
    if(g.schaakmat(kleurtje)) {
        message("Schaakmat!");
    } else if(g.schaak(kleurtje)){
        message("Schaak!");
    } else if(g.pat(kleurtje)) message("Pat!");
    clearBoard();
    updateBedreigd();
    update();
    stepForward();
}
// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {

    if(ai_kleur[0] == wit and ai_kleur[1] == zwart) { // Speelt AI met zichzelf nu?
        zw kleur = wit_aan_de_beurt ? wit : zwart;
        aiStap(kleur);
        stepForward();
        return;
    }
    if(!second_click){
        if(g.bezet(r,k) == nullptr) return;
        removeAllMarking();
        // Ga na of nu de beurt van de speler is
        if(g.bezet(r,k)->getKleur() == wit && wit_aan_de_beurt || g.bezet(r,k)->getKleur() == zwart && !wit_aan_de_beurt) {
            selected_figure = g.bezet(r, k);
            if (selected_figure != nullptr) {
                setTileSelect(r, k, true); // Kies het stuk
                vector<pair<int,int>> to_go = selected_figure->geldige_zetten(g);
                for(auto x: to_go){ // Toon alle mogelijke zetten voor dit stuk
                    setTileFocus(x.first, x.second, displayMoves());
                }
                // Verzamel de plaatsen waar het stuk kan geslagen worden
                g.bedreigde_stukken.clear();
                zw kleur = wit_aan_de_beurt ? zwart : wit;
                for(auto try_pos: to_go){
                    // Doe de (onvoorwaardelijke) zet
                    SchaakStuk* old_stuk = g.getPiece(try_pos.first, try_pos.second);
                    g.setPiece(r, k, nullptr);
                    g.setPiece(try_pos.first, try_pos.second, selected_figure);

                    // Probeer alle mogelijke zetten
                    g.mogelijke_zetten(kleur);

                    // Zet alles terug
                    g.setPiece(r, k, selected_figure);
                    g.setPiece(try_pos.first, try_pos.second, old_stuk);
                }
                // Toon de plaatsen waar het stuk kan geslagen worden
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
        // Als het de tweede click is:
        second_click = false;
        removeAllMarking();
        // Doe de zet als het mogelijk is
        if(g.move(selected_figure, r, k)){
            g.move(selected_figure, r, k);
            clearBoard();
            update();
            wit_aan_de_beurt = !wit_aan_de_beurt;

            // Ga na of dat er een speciaal geval gebeurt
            zw kleurtje = wit_aan_de_beurt ? wit : zwart;
            if(g.schaakmat(kleurtje)) {
                message("Schaakmat!");
            } else if(g.schaak(kleurtje)){
                message("Schaak!");
            }
            else if(g.pat(kleurtje)) message("Pat!");

            // Update alles
            updateBedreigd();
            stepForward();
            update();
            if(ai_aan) aiStap(kleurtje); // Doe AI stap als het aan is
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
    // Stel zet nummer = 0 als je geen undo van het nieuwe spel wil
    //zet_nummer = 0
    stepForward();
    if(ai_kleur[0] == zwart and ai_kleur[1] == wit) ai_aan = false;
    if(ai_kleur[0] == wit) aiStap(wit);
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
    zet_nummer--;
    if(!ai_aan  || (ai_kleur[0] == wit && ai_kleur[1] == zwart)) {
        wit_aan_de_beurt = !wit_aan_de_beurt;
    }
    else{ // Met AI doet de speler twee zetten in een keer
        zet_nummer--;
    }
    g.setSpeelbord(geschiedenis[zet_nummer-1]);
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
    if(!ai_aan || (ai_kleur[0] == wit && ai_kleur[1] == zwart)) {
        wit_aan_de_beurt = !wit_aan_de_beurt;
    }else{ // Met AI doet de speler twee zetten in een keer
        zet_nummer++;
    }
    g.setSpeelbord(geschiedenis[zet_nummer-1]);
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
            if(g.getPiece(r,k)!= nullptr) setItem(r, k, g.getPiece(r,k));
        }
    }
}

bool SchaakGUI::stepForward(){
    while(geschiedenis.size() != zet_nummer) geschiedenis.pop_back();
    zet_nummer ++;
    geschiedenis.push_back(g.getSpeelbord());
    return true;
}

