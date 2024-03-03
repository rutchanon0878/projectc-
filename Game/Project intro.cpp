#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void returnback() {
    cout << "Choose your input:\n";
    cout << "(1) Play , (2) Introduction , (3) How to play , (0) Exit \n";
}

void playGame() {
    cout << "Play\n";
    // Add your game logic here
}

void displayIntroduction() {
    cout << "In the realm of a dark and ominous card game filled with sin and hidden secrets, two castles stand side by side, imposing and grand. \nIt's an endless battle between the aspirations of the forlorn rulers and the power of darkness spreading its enchantment across the mesmerizing lands of the 7 Sins card game!\n";
    // Add the rest of the introduction
}

void displayHowToPlay() {
    cout << "1. Card Field: \n"<< "     -There are a total of 4 card fields available in each turn.\n";
    cout << "2.Adding Characters: \n" << "     -In the first turn, you can add 2 characters to the field.\n" << "     -After that, you can add one character to the field per turn.\n";
    cout << "3.Randomizing atk and hp values:\n" << "     -When you add a character to the field, the system will randomize the atk (attack) and hp (health) values for each character.\n";
    cout << "4.Attacking:\n" << "     -Every character will attack the opposing field each turn.\n";
    cout << "Adding Characters in the Next Turn:\n" << "     -In every subsequent turn, you can add one character to the field. (you can have a maximum of 3 cards on the field)\n";



    // Add the rest of the instructions
}

int main() {
    system("Color 0");
    cout << "Welcome to 7 sins\n";
    cout << "The world of darkness and sin!\n";

    int currentMenu = 0;

    do {
        if (currentMenu == 0) {
            cout << "Choose your input:\n";
            cout << "1. Play\n";
            cout << "2. Introduction\n";
            cout << "3. How to play\n";
            cout << "0. Exit\n";
        } else if (currentMenu == 1) {
            playGame();
            currentMenu = 0;
            continue;
        } else if (currentMenu == 2) {
            system("cls");
            displayIntroduction();
            returnback();
        } else if (currentMenu == 3) {
            system("cls");
            displayHowToPlay();
            returnback();
        }

        cout << "Press here: ";
        string userInput;
        cin >> userInput;

        if (userInput == "1") {
            currentMenu = 1;
        } else if (userInput == "2") {
            currentMenu = 2;
        } else if (userInput == "3") {
            currentMenu = 3;
        } else if (userInput == "0") {
            cout << "Thank you for using the service. Goodbye!\n";
            break;
        } else {
            cout << "Wrong input. Please try again.\n";
        }

    } while (true);

    return 0;
}
