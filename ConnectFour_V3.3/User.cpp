#include "User.h"

User::User() {
    username[0] = 'N';
    username[1] = 'U';
    username[2] = 'L';
    username[3] = 'L';
    username[4] = '\0';

    for (int i = 0; i < 3; i++) {
        gameResult[i] = -1;
        winLoss[i] = 0;
        for (int c = 0; c < 7; c++) {
            for (int r = 0; r < 6; r++) {
                game[i][c][r] = 0;
            }
        }
    }
}

void User::reset() {
    username[0] = 'N';
    username[1] = 'U';
    username[2] = 'L';
    username[3] = 'L';
    username[4] = '\0';

    for (int i = 0; i < 3; i++) {
        gameResult[i] = -1;
        winLoss[i] = 0;
        for (int c = 0; c < 7; c++) {
            for (int r = 0; r < 6; r++) {
                game[i][c][r] = 0;
            }
        }
    }
}

void User::setUsername(string s) {
    for (int i = 0; i < s.length(); i++) {
        username[i] = s[i];
    }
    username[s.length()] = '\0';
}

void User::addResult(int **gameB, int result) {

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            game[2][i][j] = game[1][i][j];
            game[1][i][j] = game[0][i][j];
            game[0][i][j] = gameB[i][j];
        }
    }

    gameResult[2] = gameResult[1];
    gameResult[1] = gameResult[0];
    gameResult[0] = result;

    switch (result) {
        case 1:
            winLoss[0]++;
            break;
        case 2:
            winLoss[1]++;
            break;
        case 3:
            winLoss[2]++;
            break;
    }

}

void User::print() {
    cout << endl << username << "'s stats" << endl;
    cout << "--------------------------" << endl;

    cout << "Wins vs. Losses: " << winLoss[0] << "-" <<
            winLoss[1] << "-" <<
            winLoss[2] << endl << endl;

    if (gameResult[0] == -1) {
        cout << "No previous games." << endl;
    } else {
        cout << "Previous Game Results" << endl;
        cout << "----------------" << endl;
        int i = 0;

        //While there are more games saved
        while (gameResult[i] != -1 && i < 3) {
            cout << "Game " << i + 1 << endl;

            //Print winner
            switch (gameResult[i]) {
                case 1:
                    cout << "You won this game!" << endl;
                    break;
                case 2:
                    cout << "You lost this game!" << endl;
                    break;
                case 3:
                    cout << "You tied this game!" << endl;
                    break;
            }

            //Print board
            for (int r = 0; r < 6; r++) {
                cout << endl;
                for (int c = 0; c < 7; c++) {
                    cout << game[i][r][c] << " ";
                }
            }
            cout << endl;
            i++;
        }

    }

}