#include "PROINTRO.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm> // เพิ่มไฟล์ header นี้
#include<windows.h>

using namespace std;

const int scale = 4;

int turn = 1;

void displayIntroduction();
void displayHowToPlay();
void returnback();
void playGame();

class Random;
void GetEnter();

class Unit
{
public:
    string namecard;
    int hp = 0;
    int atk = 0;
    // string txt = " (x) ";
    string Nametxt = "          ";
    string atktxt = " ";
    string hptxt = " ";

    void txtUpdate();
    void create(string, int, int);
    void damaged(int);
};

void Unit::txtUpdate()
{
    if (hp > 0){
        Nametxt = namecard;
        atktxt = ""+ to_string(atk) +"";
        hptxt = ""+ to_string(hp) +"";
        // txt = "[" + to_string(atk) + "/" + to_string(hp) + "]";
    }
    else{
        Nametxt = "          ";
        atktxt = " ";
        hptxt = " ";
    }
}

void Unit::create(string names,int attack, int health)
{   
    namecard = names;
    atk = attack;
    hp = health;
    txtUpdate();
}

void Unit::damaged(int amount)
{
    hp -= amount;
    hp = (hp < 0) ? 0 : hp;
    txtUpdate();
}

class Player
{
public:
    int hp = 20;
    string name;
    Unit slots[scale];

    void attack(Player &);
    bool isDead();
    void action(Random &, int turn);
    int getTotalHp(); // Calculate total HP of all slots
};

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

class Random
{
private:
    vector<string> names;
    vector<int> atks;
    vector<int> hps;

public:
    void importCard(const string filename);
    void dealCards(Player &, int index);
};

void Player::action(Random &random, int turn)
{
    bool action = true;
    string input;
    int cardsToAdd = (turn == 1) ? 3 : 2;
    int addCount = 0;

    while (action)
    {
        
        cout << "[" << name << "]: ";
        cout << " Your Action : ";
        cin >> input;

        if (toUpperStr(input) == "ADD")
        {
            if (cardsToAdd > 0 && addCount < 3)
            {
                string index;
                cout << "Where do you want to put the card (index 1-" << scale << "): ";
                cin >> index;

                try
                {
                    int indexValue = stoi(index);

                    if (indexValue >= 1 && indexValue <= scale)
                    {
                        random.dealCards(*this, indexValue - 1);
                        cardsToAdd--;
                        addCount++;
                    }
                    else
                    {
                        cout << "Invalid slot index. Please choose a slot index between 1 and " << scale << "." << endl;
                    }
                }
                catch (std::invalid_argument)
                {
                    cout << "Invalid input. Please enter a valid number." << endl;
                    // You might want to add additional error handling or re-prompt the user here
                }
            }
            else
            {
                cout << "You can't add more cards this turn!" << endl;
                continue;
            }
        }
        else if (toUpperStr(input) == "END")
        {
            cout << "Ending the game." << endl;
            // Add any necessary game-ending logic here (e.g., displaying final scores)
            action = false; // This will exit the loop and end the game in a controlled manner
        }
        else if (toUpperStr(input) == "SKIP")
        {
            action = false;
            cout << "Skipping turn for " << name << endl;
        }
        else
        {
            cout << "Invalid action! Please choose 'ADD', 'END', or 'SKIP'." << endl;
            cin.ignore();
            continue;
        }
    }
    // Additional cleanup or post-game logic can be added here
}


void Player::attack(Player &target)
{
    for (int i = 0; i < scale; ++i)
    {
        if (slots[i].hp <= target.slots[i].atk && slots[i].atk >= target.slots[i].hp)
        {
            slots[i].damaged(slots[i].hp);
            target.slots[i].damaged(target.slots[i].hp);
            // double death
        }
        else if (slots[i].hp > 0 && target.slots[i].hp > 0)
        // Check if both slots have monsters before attacking
        {
            int P1atk = slots[i].atk;
            int P2atk = target.slots[i].atk;
            slots[i].damaged(P2atk);
            target.slots[i].damaged(P1atk);
        }
        else
        {
            if (slots[i].hp > 0 && target.slots[i].hp <= 0)
            {
                target.hp -= slots[i].atk - target.slots[i].hp;
            }
            else if (slots[i].hp <= 0 && target.slots[i].hp > 0)
            {
                hp -= target.slots[i].atk - slots[i].hp;
            }
        }
    }
}

void Random::importCard(const string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            char name[20]; // Adjusted size to accommodate longer names
            int attack, health;
            sscanf(line.c_str(), "%[^:]: %d %d", name, &attack, &health);
            names.push_back(name);
            atks.push_back(attack);
            hps.push_back(health);
        }
    }

    file.close();
}

void Random::dealCards(Player &player, int index)
{
    srand(time(0));
    bool dealphase = true;

    while (true)
    {
        if (player.slots[index].hp <= 0) // Check if the slot is empty
        {
            int cardIndex = rand() % names.size(); // Choose a random card from the available ones
            player.slots[index].create(names[cardIndex], atks[cardIndex], hps[cardIndex]); // Assign the chosen card to the slot
            break; // Break out of the loop when successful
        }
        else
        {
            cout << "Slot " << (index + 1) << " is already occupied. You cannot add a card to this slot." << endl;
            cout << "Where do you want to put the card (index 1-" << scale << "): ";
            cin.ignore();

            string newIndex;
            cin >> newIndex;
            int NewindexValue = stoi(newIndex);
            // Check if input is not an integer
            while (!(cin >> NewindexValue) || NewindexValue < 1 || NewindexValue > scale)
            {
                cout << "Invalid input. Please enter a valid slot index between 1 and " << scale << ": ";
                cin.clear();  // Clear the error flag
                cin.ignore(); // Discard invalid input
            }

            index = NewindexValue - 1;
        }
    }
}

void manys(const wchar_t specialChar){
    for (int N=1; N<135; N++)
    wcout << specialChar;
}

void many(const wchar_t specialChar){
    for (int N=1; N<9; N++)
    wcout << specialChar;
}

void one(const wchar_t specialChar){
    wcout << specialChar;
}

void display(Player left, Player right){ 
    
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Color,14);
    wchar_t F = L'\u00CF'; // ใช้รหัส Unicode
    wchar_t G = L'\u00D1';
    wchar_t A = L'\u00C9';
    wchar_t B = L'\u00BB';
    wchar_t C = L'\u00C8';
    wchar_t D = L'\u00BC';
    wchar_t E = L'\u00ED';
    wchar_t I = L'\u00DF';
    wchar_t ATK = L'\u0041';
    wchar_t HP = L'\u2665';

    manys(I);
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    cout << "Turn " << turn << endl;
    cout << "=====================================================================================================================================\n";
    for(int i=0; i<scale; i++){
        cout << "          ";
        cout <<             " ____________" << "                                                                                        " << "____________";
        cout << "\n          |";
        one(E);
        cout << left.slots[i].Nametxt;
        one(E);     
        cout << "|" << "                                                                                      " << "|";
        one(E);
        cout << right.slots[i].Nametxt;
        one(E);
        cout << "|";
        cout << "\n          | ";
        one(A);
        many(F);
        one(B);
        cout << " |" << "                                                                                      " << "| ";
        one(A);
        many(F);
        one(B);
        cout << " |";
        cout << "\n          |   -<" << left.slots[i].atktxt <<  ">-    |" << "                                                                                      " << "|   -<" << right.slots[i].atktxt <<  ">-    |";
        cout << "\n          |   -<" << left.slots[i].hptxt <<  ">-    |" << "                                                                                      " << "|   -<" << right.slots[i].hptxt <<  ">-    |";
        cout << "\n          | ";
        one(C);
        many(G);
        one(D);
        cout << " |" << "                                                                                      " << "| ";
        one(C);
        many(G);
        one(D);
        cout << " |";
        cout << "\n          |____________|" << "                                                                                      " << "|____________|\n";


    }
    cout << endl;
    SetConsoleTextAttribute(Color,5);
    manys(I);
    cout << endl;
    cout << "|    " << left.name << "<" << left.hp << ">                                                                                                    " << right.name << "<" << right.hp << ">    |\n"; // บรรทัดสำหรับแสดงค่า hp
    cout << "======================================================================================================================================\n";
}

bool Player::isDead(){
    if(hp <= 0) return true;
    else false;
}

void p1Win(){
    cout << endl;
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    cout<<"||                                                                                                                                  ||"<<endl;
    cout<<"||                                                       !!! P1 win !!!!                                                            ||"<<endl;
    cout<<"||                                                                                                                                  ||"<<endl;
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
}

void p2Win(){
    cout << endl;
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    cout<<"||                                                                                                                                  ||"<<endl;
    cout<<"||                                                       !!! P2 win !!!!                                                            ||"<<endl;
    cout<<"||                                                                                                                                  ||"<<endl;
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
}

void bothwin(){
    cout << endl;
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    cout<<"||                                                                                                                                  ||"<<endl;
    cout<<"||                                                      !!! Both win !!!!                                                           ||"<<endl;
    cout<<"||                                                                                                                                  ||"<<endl;
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
}

int main()
{
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
            system("cls");
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
        system("Color 0");
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
            system("cls");
        }

    } while (true);
    return 0;
}
   
void GetEnter()
{
    cout << "Press Enter to continue" << endl;
    cin.get();
}

void playGame(){
    string filename = "Namecard.txt";
    Random random;
    random.importCard(filename);

    Player p1, p2;
    p1.name = "Player 1";
    p2.name = "Player 2";

    while (!p1.isDead() && !p2.isDead()) // Continue the loop until one of the players is dead
    {
        
        display(p1, p2);
        GetEnter();

        cout << endl;
        
        system("cls");
        display(p1, p2);

        p1.action(random, turn);
        GetEnter();
        system("cls");

        display(p1, p2);
        p2.action(random, turn);
        system("cls");

        display(p1, p2);
        cin.ignore();
        GetEnter();
        system("cls");
        cout << "Player combat:" << endl;
        p1.attack(p2);

        display(p1, p2);

        GetEnter();
        system("cls");
        if(p1.hp <= 0 || p2.hp <= 0) break;
        turn++;
    }
    if(p1.hp > p2.hp) p1Win();
    if(p1.hp < p2.hp) p2Win();
    if(p1.hp == p2.hp) bothwin();
   
}
