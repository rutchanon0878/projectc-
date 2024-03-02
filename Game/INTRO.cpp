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
int turn = 1; 
////////////New create//////////////////////////////ขอสไปรท์////////////////////////////////////////
//เหลือสร้างclassเก็บค่าที่สุ่มออกมา
class Random {
    string file;
    vector<string> names; 
    vector<int> atks;      
    vector<int> hps;     
    
public:
    string sum_name1[scale]; 
    int sum_atk1[scale];      
    int sum_hp1[scale];
    
    string sum_name2[scale]; 
    int sum_atk2[scale];      
    int sum_hp2[scale];   
   
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
    if(turn == 1){
    for(int i = 0;i<2 ;i++){
    int number1 = rand()% names.size();
    int *num1 = new int(number1);
    sum_name1[i] = names[number1] ; 
    sum_atk1[i] = atks[number1] ; 
    sum_hp1[i] = hps[number1] ;
    }
    for(int i = 0;i<2 ;i++){
    int number2 = rand()% names.size();
    int *num2 = new int(number2);
    sum_name2[i] = names[number2] ; 
    sum_atk2[i] = atks[number2] ; 
    sum_hp2[i] = hps[number2] ;
    }
    for(int i = 0;i<4 ;i++){
    int number1 = rand()% names.size();
    int *num1 = new int(number1);
    sum_name1[i] = "----------" ; 
    sum_atk1[i] = 0 ; 
    sum_hp1[i] = 0 ;
    }
    for(int i = 0;i<4 ;i++){
    int number2 = rand()% names.size();
    int *num2 = new int(number2);
    sum_name2[i] = "----------" ; 
    sum_atk2[i] = 0 ; 
    sum_hp2[i] = 0 ;
    }
}
else{
    int N = 3;
    for(int i = 2;i<N ;i++){
    int number1 = rand()% names.size();
    int *num1 = new int(number1);
    sum_name1[i] = names[number1] ; 
    sum_atk1[i] = atks[number1] ; 
    sum_hp1[i] = hps[number1] ;
    }
    for(int i = 2;i<N ;i++){
    int number2 = rand()% names.size();
    int *num2 = new int(number2);
    sum_name2[i] = names[number2] ; 
    sum_atk2[i] = atks[number2] ; 
    sum_hp2[i] = hps[number2] ;
    }
}
}

////////////End//////////////////////////////ของสไปรท์ถึงนี่////////////////////////////////////////////////

class Unit{
    public:
        int hp = 0;
        int atk = 0;
        string txt = " (x) ";    // ค่าตัวอักษรที่แสดงใน terminal
        void txtUpdate();       // Update ตัวแปร txt อันด้านบน ↑
        void create(int, int); // Update ค่า stat ของ unit
        void damaged(int);    // ลดค่า hp ของ unit
};

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
        bool isDead();
};

void Player::attack(Player &target, int num){
    if(slots[num].hp > 0){
        if(target.slots[num].hp <= 0) target.hp -= slots[num].atk; // ถ้าไม่มี unit กัน damage จะเข้า hp ของ player
        else target.slots[num].damaged(slots[num].atk);
    }
}
/////////////////////////////////////pond/////////////////////////////////////////////////////////
/////////////////////////////ของปอนด์เริ่มตรงนี้!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void manys(const wchar_t specialChar) {
    for (int N=1; N<135; N++)
    wcout << specialChar;
}

void many(const wchar_t specialChar) {
    for (int N=1; N<9; N++)
    wcout << specialChar;
}

void one(const wchar_t specialChar) {
    wcout << specialChar;
}

void display(Player left, Player right,Random name1,Random attack1,Random health1,Random name2,Random attack2,Random health2){ 
        // cout << name1.sum_name1[0] << "\n";
        // cout << attack1.sum_atk1[0] << "\n";
        // cout << health1.sum_hp1[0] << "\n";

        // cout << name2.sum_name2[0] << "\n";
        // cout << attack2.sum_atk2[0] << "\n";
        // cout << health2.sum_hp2[0] << "\n";

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Color,5);
        cout << "Check" << endl;


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
    
    // one(A);
    // many(F);
    // one(B);
    // cout << "\n\n\n\n";
    // one(C);
    // many(G);
    // one(D);
    // one(HP);
    cout << endl;
    manys(I);
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    // cout << "====================================================================================================================================\n";
    for(int i=0; i<scale; i++){
        // cout << "|    " << left.slots[i].txt << "     <->     " << right.slots[i].txt << "    |\n"; // วนแสดง unit ที่อยู่ในแต่ละช่อง
        // cout << name1.sum_name[i]<< endl;
        // cout << attack1.sum_atk[i]<<endl;
        // cout << health1.sum_hp[i]<<endl;
        string N1 = name1.sum_name1[i];
        string N2 = name2.sum_name2[i];
        int A1 = attack1.sum_atk1[i];
        int A2 = attack2.sum_atk2[i];
        int H1 = health1.sum_hp1[0];
        int H2 = health2.sum_hp2[0];
        cout << "          ";
        cout <<             " ____________" << "                                                                                        " << "____________";
        cout << "\n          |";
        one(E);
        cout << N1;
        one(E);     
        cout << "|" << "                                                                                      " << "|";
        one(E);
        cout << N2;
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
        cout << "\n          |   -<" << A1 <<  ">-    |" << "                                                                                      " << "|   -<" << A2 <<  ">-    |";
        cout << "\n          |   -<" << H1 <<  ">-    |" << "                                                                                      " << "|   -<" << H2 <<  ">-    |";
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
    // cout << "_________________________________\n";
    cout << "|    " << left.name << "<" << left.hp << ">                                                                                                               " << right.name << "<" << right.hp << ">   |\n"; // บรรทัดสำหรับแสดงค่า hp
    cout << "======================================================================================================================================\n";
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}
///////////////////////////////////////////ของฟิว//////New create/////////////////////////////
void action(Player &currP,int &turn ,Random turnFunc){
    string input;
    char format[] = "%d %d %d";
    int slot=0, attack=0, health=0;
    
    cout << "[" << currP.name << "]: ";
    cin >> input;

    
    if(toUpperStr(input) == "SKIP") return;
    
    else if(toUpperStr(input) == "ADD"){
        cin.ignore();
        getline(cin, input);
        sscanf(input.c_str(), format, &slot, &attack, &health);
        if(input.empty() || cin.bad()){
            cout << "[!] \"add\" command requires you to enter all of the three inputs \"add (slot) (attack) (health)\". Please check your command.\n";
            action(currP,turn,turnFunc);
        }
        else if(slot > scale || slot < 1){
            cout << "[!] There are only " << scale << " slots. Please check your command.\n";
            action(currP,turn,turnFunc);
        }
        else if(health <= 0){
            cout << "[!] Health can't be zero or negative number. Please check your command.\n";
            action(currP,turn,turnFunc);
        }
        else{
            currP.slots[slot-1].create(attack, health);
        }
    }
    
    else if(toUpperStr(input) == "END"){
        cout << "[!] Game ended by user.";
        exit(0);
    }
    
    else{
        cout << "[!] Invalid command. Write \"add (slot) (attack) (health)\" to create a unit, \"skip\" to skip or \"End\" to to end the game.\n"; // สำหรับถ้าพิมพ์คำสั่งมาผิด
        action(currP,turn,turnFunc);
    }
    cout << "\n";
}
///////////////////////////////////////////////ของฟิวถึงนี่//////////////////////////////////////////////////
// สั่งให้ unit ทุกช่องสู้กัน
void combat(Player &first, Player &second){
    for(int i=0; i<scale; i++){
        first.attack(second, i);
        second.attack(first, i);
    }
}

////////////////////////////////// ของเวสป้า ///////////////////////////
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
////////////////////////////////// ยังมีใน main อีก ///////////////////////////

int main()
{
    string filename = "Namecard.txt";
    vector<string> nameVector;
    vector<int> atkVector,hpVector;
    Random random;
    Random name1, attack1, health1;
    Random name2, attack2, health2;
    Random turnFunc;
    random.importcard(filename);
    
    name1.importcard(filename);
    attack1.importcard(filename);
    health1.importcard(filename);

    name2.importcard(filename);
    attack2.importcard(filename);
    health2.importcard(filename);

    turnFunc.importcard(filename);

    int turn = 1; 
    Player p1, p2;
    p1.name = "P1"; p2.name = "P2"; // กำหนดค่า name สำหรับเอาไว้แสดง
    while(true){ 
        cout << "<<< Turn " << turn << " >>>\n";
        display(p1, p2, name1, attack1, health1, name2, attack2, health2);
        action(p1,turn,turnFunc);

        display(p1, p2, name1, attack1, health1, name2, attack2, health2);
        action(p2,turn,turnFunc);

        display(p1, p2, name1, attack1, health1, name2, attack2, health2);
        combat(p1, p2);
        cout << "\n";
        /////////////////////////////////////////////////////////////////////////
        if(p1.hp <= 0 || p2.hp <= 0) break;
        // วนลูปสลับไปเรื่อยๆยังไม่ได้เขียนโค้ดส่วนชนะ
        turn++;
    }
    if(p1.hp == p2.hp) bothwin();
    else if(p1.isDead()) p1Win();
    else p2Win();
    //////////////////////////////////////// ของเวสป้าถึงตรงนี้ ///////////////////////////////
    return 0;
}