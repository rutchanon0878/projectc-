#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void returnback() {
    cout << "Choose your input:\n";
    cout << "(1) Play , (2) Introduction , (3) How to play , (0) Exit \n";
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
