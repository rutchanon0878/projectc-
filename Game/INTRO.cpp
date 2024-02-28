#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>
//ทำเผื่อๆ

using namespace std; 

int const scale = 5; // ขนาดของกระดาน(ลองเปลี่ยนได้)

class Unit{
    public:
        int hp = 0;
        int atk = 0;
        string txt = " (x) ";    // ค่าตัวอักษรที่แสดงใน terminal
        void txtUpdate();       // Update ตัวแปร txt อันด้านบน ↑
        void create(int, int); // Update ค่า stat ของ unit
        void damaged(int);    // ลดค่า hp ของ unit
};

class Player{
    public:
        int hp = 10;
        string name;                  // ชื่อไว้สำหรับแสดง
        Unit slots[scale];           // ← ค่า Unit ของแต่ละคนเก็บไว้ที่ตัวนี้
        void attack(Player &, int); // สั่งให้ unit ในช่องที่เลือกโจมตี unit ของฝ่ายตรงข้ามในช่องเดียวกัน
        bool isDead();
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

void Player::attack(Player &target, int num){
    if(slots[num].hp > 0){
        if(target.slots[num].hp <= 0) target.hp -= slots[num].atk; // ถ้าไม่มี unit กัน damage จะเข้า hp ของ player
        else target.slots[num].damaged(slots[num].atk);
    }
}

// แสดงกระดานใน terminal
void display(Player left, Player right){ 
    cout << "=================================\n";
    for(int i=0; i<scale; i++){
        cout << "|    " << left.slots[i].txt << "     <->     " << right.slots[i].txt << "    |\n"; // วนแสดง unit ที่อยู่ในแต่ละช่อง
    }
    cout << "_________________________________\n";
    cout << "|    " << left.name << "<" << left.hp << ">            " << right.name << "<" << right.hp << ">   |\n"; // บรรทัดสำหรับแสดงค่า hp
    cout << "=================================\n";
}

// การรับคำสั่งของผู้เล่น
void action(Player &currP){
    string input;
    int slot, attack, health;
    
    cout << "[" << currP.name << "]: ";
    cin >> input;
    
    if(input == "skip") return;
    else if(input == "add"){
        cout << "Choose a slot(1-" << scale << "): "; // ถามว่าจะใส่ช่องไหน
        cin >> slot;
        cout << "Enter your stat: "; // ถามว่าจะให้ stat เป็นเท่าไหร่ 
        cin >> attack >> health;
        currP.slots[slot-1].create(attack, health); // Update unit ในช่องนั้นให้มีค่าตามที่ใส่
    }
    else{
        cout << "[!] Invalid command. Write \"add\" to create a unit or \"skip\" to skip.\n"; // สำหรับถ้าพิมพ์คำสั่งมาผิด
        action(currP);
    }
    
    cout << "\n";
}

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
    cout<<"---------------------------------"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"|          P1 win!!!!          |"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"---------------------------------";
}

void p2Win(){
    cout<<"--------------------------------"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"|          P2 win!!!!          |"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"--------------------------------";
}

void bothwin(){
    cout<<"--------------------------------"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"|            Draw...          |"<<endl;
    for(int i = 0; i<1; i++) cout<<"|                              |"<<endl;
    cout<<"--------------------------------";
}
////////////////////////////////// ยังมีใน main อีก ///////////////////////////


int main()
{
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
        /////////////////////////////////////////////////////////////////////////
        if(p1.hp <= 0 || p2.hp <= 0) break;
        // วนลูปสลับไปเรื่อยๆยังไม่ได้เขียนโค้ดส่วนชนะ
    }
    if(p1.hp == p2.hp) bothwin();
    else if(p1.isDead()) p1Win();
    else p2Win();
    //////////////////////////////////////// ของเวสป้าถึงตรงนี้ ///////////////////////////////
    return 0;
}