//
// Created by toonc on 12/17/2021.
// en bewerkt door Daria op 25/01/2023

#ifndef SCHAKEN_SCHAAKGUI_H
#define SCHAKEN_SCHAAKGUI_H

#include "guicode/ChessWindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QAction>

class SchaakGUI:public ChessWindow {
public:
    SchaakGUI();

    void update();

private:
    Game g;
    bool second_click = false;
    bool wit_aan_de_beurt = true;
    SchaakStuk* selected_figure = nullptr;
    void clicked(int x, int y) override;
    void newGame() override;
    void open() override;
    void save() override;
    void undo() override;
    void redo() override;
    void updateBedreigd();
    void visualizationChange() override;
    pair<int, pair<SchaakStuk*, pair<int,int>>> besteZetDeelTwee(zw kleur);
    pair<int,pair<SchaakStuk*, pair<int,int>>> besteZetDeelDrie(zw kleur);
    pair<SchaakStuk*, pair<int,int>> besteZet(zw kleur);
    void aiStap(zw kleur);
    bool stepForward();
    int zet_nummer = 0;
    vector<vector<SchaakStuk*>> geschiedenis;

/*  Overgeerfde functies van ChessWindow:

    void removeAllMarking();
    void clearBoard();
    void setItem(int i,int j,SchaakStuk* p);
    void setPieceThreat(int i,int j,bool b);
    void removeAllPieceThreats();
    void setTileSelect(int i,int j,bool b);
    void setTileFocus(int i,int j,bool b);
    void setTileThreat(int i,int j,bool b);

    bool displayKills();
    bool displayMoves();
    bool displayThreats();
*/
};


#endif //SCHAKEN_SCHAAKGUI_H
