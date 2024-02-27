#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>
#include<windows.h>
//ทำเผื่อๆ

using namespace std; 

int const scale = 4; // ขนาดของกระดาน(ลองเปลี่ยนได้)

class Unit{
    public:
        int hp = 0;
        int atk = 0;
        string txt = " x ";    // ค่าตัวอักษรที่แสดงใน terminal
        void txtUpdate();       // Update ตัวแปร txt อันด้านบน ↑
        void create(int, int); // Update ค่า stat ของ unit
        void damaged(int);    // ลดค่า hp ของ unit
};

class Random {
    string file;
    vector<string> names; 
    vector<int> atks;      
    vector<int> hps;
    string sum_name[5];
    int sum_atk[5];      
    int sum_hp[5];       
    
public:
    void importcard(const string filename);
    
};

void Random::importcard(const string filename) {
    ifstream text(filename);
    srand(time(NULL));
    
    while(getline(text, file)){
        char name[10]; 
        int attack, health;
        sscanf(file.c_str(), "%[^:]: %d %d", name, &attack, &health);
        names.push_back(name);
        atks.push_back(attack);
        hps.push_back(health);
    }
    int N = 3;
    for(int i = 0;i<N ;i++){
    int number1 = rand()% names.size();
    int *num = new int(number1);
    sum_name[i] = names[number1] ; 
    sum_atk[i] = atks[number1] ; 
    sum_hp[i] = hps[number1] ;

    delete num;
  }
  //ทดสอบระบบ/////////
    cout << sum_name[0] << "\n";
    cout << sum_atk[0] << "\n";
    cout << sum_hp[0] << "\n";
}
////////////New create//////////////////////////////ขอสไปรท์
// void importDataFromFile(const string filename,vector<string> &names,vector<int> &atk,vector<int> &hp){
//     ifstream text(filename);
//     string file;
//     char name[10];
//     int attack,health;
//     int receive;
//     while(getline(text,file)){
//         char format[] = "%[^:]: %d %d";
//         sscanf(file.c_str(),format,&name,&atk,&hp);
//         names.push_back(name);
//         atk.push_back(attack);
//         hp.push_back(health);
//     }
//     receive = rand()%9;

// };

////////////End//////////////////////////////ของสไปรท์ถึงนี่
void Unit::txtUpdate(){
    if(hp > 0) txt = "[" + to_string(atk) + "/" + to_string(hp) + "]"; // แสดงค่า stat ในรูปแบบ [atk/hp]
    else txt = " (x) "; // หากมีค่า hp เป็นศูนย์(unitตายหรือยังไม่ได้สร้าง) จะแสดง (x) แทน
}

void Unit::create(int attack, int health){
    atk = attack;
    hp = health;
    txtUpdate();
}

void Unit::damaged(int amount){
    hp -= amount;
    hp = (hp < 0) ? 0 : hp;         // เพื่อไม่ให้ hp เป็นจำนวนติดลบ
    txtUpdate();
}

class Player{
    public:
        int hp = 10;
        string name;                  // ชื่อไว้สำหรับแสดง
        Unit slots[scale];           // ← ค่า Unit ของแต่ละคนเก็บไว้ที่ตัวนี้
        void attack(Player &, int); // สั่งให้ unit ในช่องที่เลือกโจมตี unit ของฝ่ายตรงข้ามในช่องเดียวกัน
};

void Player::attack(Player &target, int num){
    if(slots[num].hp > 0){
        if(target.slots[num].hp <= 0) target.hp -= slots[num].atk; // ถ้าไม่มี unit กัน damage จะเข้า hp ของ player
        else target.slots[num].damaged(slots[num].atk);
    }
}
/////////////////////////////ของปอนด์เริ่มตรงนี้!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void many(const wchar_t specialChar) {
    for (int N=1; N<9; N++)
    wcout << specialChar;
}

void one(const wchar_t specialChar) {
    wcout << specialChar;
}
//  ____________
// ┇✖  Gula   ✖┇
// ┇ ╔╧╧╧╧╧╧╧╧╗ ┇
// ┇⚔️ -<3>- ⚔️┇
// ┇❤️️ -<4>- ❤️️┇
// ┇ ╚╤╤╤╤╤╤╤╤╝ ┇
// ┇____________┇
// แสดงกระดานใน terminal
void display(Player left, Player right){ 
    
        HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Color,14);
        cout << "Check" << endl;

    wchar_t F = L'\u00CF'; // ใช้รหัส Unicode
    wchar_t G = L'\u00D1';
    wchar_t A = L'\u00C9';
    wchar_t B = L'\u00BB';
    wchar_t C = L'\u00C8';
    wchar_t D = L'\u00BC';


    // one(A);
    // many(F);
    // one(B);
    // cout << "\n\n\n\n";
    // one(C);
    // many(G);
    // one(D);
    cout << endl;
    cout << "====================================================================================================================================\n";
    SetConsoleTextAttribute(Color,3);
    for(int i=0; i<scale; i++){
        // cout << "|    " << left.slots[i].txt << "     <->     " << right.slots[i].txt << "    |\n"; // วนแสดง unit ที่อยู่ในแต่ละช่อง
        cout << "          ";
        cout <<             " ____________" << "                                                                                        " << "____________";
        cout << "\n          |     ZX     |" << "                                                                                      " << "|            |";
        cout << "\n          | ";
        one(A);
        many(F);
        one(B);
        cout << " |" << "                                                                                      " << "| ";
        one(A);
        many(F);
        one(B);
        cout << " |";
        cout << "\n          |            |" << "                                                                                      " << "|            |";
        cout << "\n          |            |" << "                                                                                      " << "|            |";
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
    cout << "_________________________________\n";
    cout << "|    " << left.name << "<" << left.hp << ">            " << right.name << "<" << right.hp << ">   |\n"; // บรรทัดสำหรับแสดงค่า hp
    SetConsoleTextAttribute(Color,14);
    cout << "====================================================================================================================================\n";

}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

// การรับคำสั่งของผู้เล่น

// string toUpperStr(string x){
//     string y = x;
//     for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
//     return y;
// }
///////////////////////////////////////////ของฟิว
void action(Player &currP){
    string input;
    int slot, attack, health;
    
    cout << "[" << currP.name << "]: ";
    cin >> input;
    
    if(toUpperStr(input) == "SKIP") return;
    else if(toUpperStr(input) == "ADD"){
        cout << "Choose a slot(1-" << scale << "): "; // ถามว่าจะใส่ช่องไหน
        cin >> slot;
        while(slot<=0 || slot>5 ){
            cout << "[!] Invalid command.\nPlease choose a slot(1-" << scale << "): ";
            cin >> slot;

        }
        cout << "Enter your stat: "; // ถามว่าจะให้ stat เป็นเท่าไหร่ 
        cin >> attack >> health;
        currP.slots[slot-1].create(attack, health); // Update unit ในช่องนั้นให้มีค่าตามที่ใส่

    }
    else if(toUpperStr(input) == "EXIT") return;
    else{
        cout << "[!] Invalid command. Write \"add\" to create a unit or \"skip\" to skip or \"End\" to to end the game.\n"; // สำหรับถ้าพิมพ์คำสั่งมาผิด
        action(currP);
    }
    cout << "\n";
}
///////////////////////////////////////////////ของฟิวถึงนี่
// สั่งให้ unit ทุกช่องสู้กัน
void combat(Player &first, Player &second){
    for(int i=0; i<scale; i++){
        first.attack(second, i);
        second.attack(first, i);
    }
}

int main()
{

    string filename = "Namecard";
    vector<string> nameVector;
    vector<int> atkVector,hpVector;
    Random random;
    random.importcard(filename);
    
    
    int turn = 1;
    Player p1, p2;
    p1.name = "P1"; p2.name = "P2"; // กำหนดค่า name สำหรับเอาไว้แสดง
    while(true){ 
        cout << "<<< Turn " << turn << " >>>\n";
        display(p1, p2);
        action(p1);
        display(p1, p2);
        action(p2);
        display(p1, p2);
        combat(p1, p2);
        cout << "\n";
        turn++;
        // วนลูปสลับไปเรื่อยๆยังไม่ได้เขียนโค้ดส่วนชนะ
    }
    return 0;
}