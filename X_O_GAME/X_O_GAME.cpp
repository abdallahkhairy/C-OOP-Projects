#include <iostream>
#include "XOGame.h"

using namespace std;


int main() {
    XOGame game;
    char choice;

    game.setPlayersNames();
    game.displayScore();
    game.displayMatrix();

    do {
        game.play();
        
        // check if the game is over
        if (game.isGameEnded() ){
            game.displayScore();
            cout << endl <<"Enter [ Y ] To Play Another Game or [ N ] To End The Game : ";
            cin >> choice;
            while ((choice != 'Y') && (choice != 'y') && (choice != 'N') && (choice != 'n')){
                cout << endl << "Invalid Choice, Please Enter Y or N : ";
                cin >> choice;
            }
            if ((choice == 'Y') || (choice == 'y')) {
                game.reset_game();
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {/*  Nothing */ }

        }

    } while (true);

    return 0;
}
