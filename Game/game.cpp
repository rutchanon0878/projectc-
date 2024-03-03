#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm> // เพิ่มไฟล์ header นี้

using namespace std;

const int scale = 4;

class Random;
void GetEnter();

class Unit
{
public:
    int hp = 0;
    int atk = 0;
    string txt = " (x) ";

    void txtUpdate();
    void create(int, int);
    void damaged(int);
};

void Unit::txtUpdate()
{
    if (hp > 0)
        txt = "[" + to_string(atk) + "/" + to_string(hp) + "]";
    else
        txt = " (x) ";
}

void Unit::create(int attack, int health)
{
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
    int hp = 10;
    string name;
    Unit slots[scale];

    void attack(Player &);
    bool isDead();
    void action(Random &, int turn);
    int getTotalHp(); // Calculate total HP of all slots
};

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
    int cardsToAdd = (turn == 1) ? 2 : 1; // Adjust cards to add based on turn number
    int addCount = 0;                     // Track the number of times "add" action is used
    while (action)
    {
        cout << "[" << name << "]: ";
        cout << " Your Action : ";
        cin >> input;
        // แปลง input เป็นตัวพิมพ์เล็กทั้งหมด
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "add")
        {
            if (cardsToAdd > 0 && addCount < 2) // Allow "add" action only if cardsToAdd > 0 and addCount < 2
            {
                int index;
                cout << "Where do you want to put the card (index 1-" << scale << "): ";
                cin >> index;
                if (index >= 1 && index <= scale)
                {

                    random.dealCards(*this, index - 1); // Deal card to the specified slot

                    cardsToAdd--;
                    addCount++;
                }
                else
                {
                    cout << "Invalid slot index. Please choose a slot index between 1 and " << scale << "." << endl;
                }
            }
            else
            {
                cout << "You can't add more cards this turn!" << endl;
                continue;
            }
        }
        else if (input == "skip")
        {
            action = false;
            cout << "Skipping turn for " << name << endl;
        }
        else
        {
            cout << "Invalid action! Please choose 'add' or 'skip'." << endl;
            cin.ignore();
            continue;
        }
    }
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

bool Player::isDead()
{
    return hp <= 0;
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
    if (player.slots[index].hp <= 0) // Check if the slot is empty
    {
        int cardIndex = rand() % names.size();                       // Choose a random card from the available ones
        player.slots[index].create(atks[cardIndex], hps[cardIndex]); // Assign the chosen card to the slot
    }
    else
    {
        cout << "Slot " << (index + 1) << " is already occupied. You cannot add a card to this slot." << endl;
        cout << "Where do you want to put the card (index 1-" << scale << "): ";
        int index;
        cin.ignore();
        cin >> index;
        dealCards(player, index - 1);
    }
}

void display(Player left, Player right)
{
    cout << left.name << " vs " << right.name << endl;
    for (int i = 0; i < scale; i++)
    {
        cout << "Slot " << setw(2) << (i + 1) << ": " << setw(10) << left.slots[i].txt << " - " << right.slots[i].txt << endl;
    }
    cout << "HP: " << left.name << " = " << left.hp << ", " << right.name << " = " << right.hp << endl;
}

int main()
{
    string filename = "Namecard.txt";
    Random random;
    random.importCard(filename);

    Player p1, p2;
    p1.name = "Player 1";
    p2.name = "Player 2";

    int turn = 1;
    while (!p1.isDead() && !p2.isDead()) // Continue the loop until one of the players is dead
    {
        cout << "Turn " << turn << endl;
        display(p1, p2);
        GetEnter();

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

        // Update player HP based on slot status

        // cout << "Player 1 HP: " << p1.hp << endl;
        // cout << "Player 2 HP: " << p2.hp << endl;
        GetEnter();
        system("cls");
        turn++;
    }

    // Determine the winner
    cout << "Game Over!" << endl;
    if (p1.isDead() && p2.isDead())
    {
        cout << "It's a tie!" << endl;
    }
    else if (p1.isDead())
    {
        cout << p2.name << " wins!" << endl;
    }
    else
    {
        cout << p1.name << " wins!" << endl;
    }

    return 0;
}

void GetEnter()
{
    cout << "Press Enter to continue" << endl;
    cin.get();
}
