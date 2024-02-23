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

////////////New create//////////////////////////////ขอสไปรท์
//เหลือสร้างclassเก็บค่าที่สุ่มออกมา
// class random{
//         public:
//                 int number1;
//                 int receive;
// };
void importDataFromFile(const string filename,vector<string> &names,vector<int> &atk,vector<int> &hp){
    ifstream text(filename);
    string file;
    char name[10];
    int attack,health;
    srand(time(NULL));
    while(getline(text,file)){
        char format[] = "%[^:]: %d %d";
        sscanf(file.c_str(),format,&name,&attack,&health);
        names.push_back(name);
        atk.push_back(attack);
        hp.push_back(health);
    }
    int N = 1;
    for(int i = 0;i<N ;i++){
    int number1 = rand()%10;
    int *num = new int(number1);
    cout << names[number1] << "\n";
    cout << atk[number1] << "\n";
    cout << hp[number1] << "\n";
    delete num;
  }
}

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
    if(slots[num].hp > 0 && target.slots[num].hp > 0){
        target.slots[num].damaged(slots[num].atk);
        slots[num].damaged(target.slots[num].atk);
    }
    else if(slots[num].hp > 0 && target.slots[num].hp == 0) target.hp -= slots[num].atk;
    else if(slots[num].hp == 0 && target.slots[num].hp > 0) hp -= target.slots[num].atk;
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

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}
///////////////////////////////////////////ของฟิว//////New create////
void action(Player &currP){
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
            action(currP);
        }
        else if(slot > scale || slot < 1){
            cout << "[!] There are only " << scale << " slots. Please check your command.\n";
            action(currP);
        }
        else if(health <= 0){
            cout << "[!] Health can't be zero or negative number. Please check your command.\n";
            action(currP);
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
        action(currP);
    }
    cout << "\n";
}
///////////////////////////////////////////////ของฟิวถึงนี่//////////////////
// สั่งให้ unit ทุกช่องสู้กัน
void combat(Player &first, Player &second){
    for(int i=0; i<scale; i++){
        first.attack(second, i);
    }
}

int main()
{
    string filename = "Namecard.txt";
    vector<string> names;
    vector<int> atks,hps;
    importDataFromFile(filename,names,atks,hps);

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