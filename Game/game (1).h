////////////New create//////////////////////////////ขอสไปรท์////////////////////////////////////////

//เหลือสร้างclassเก็บค่าที่สุ่มออกมา
class Deck{
    string file;
    vector<string> names; 
    vector<int> atks;      
    vector<int> hps;     
    
    public:
        void Deck(const string filename);
        Unit random();
};

void Deck::Deck(const string filename) {
    ifstream text(filename);
    
    while(getline(text, file)){
        char name[10]; 
        int attack, health;
        sscanf(file.c_str(), "%[^:]: %d %d", name, &attack, &health);
        names.push_back(name);
        atks.push_back(attack);
        hps.push_back(health);
    }
}

Unit Deck::random(){
    srand(time(NULL));
    int num = rand()% names.size();
    
    string _name = names[num] ; 
    int _atk = atks[num] ; 
    int _hp = hps[num] ;
    
    Unit _unit(_name, _atk, _hp); 
    return _unit;
}

////////////End//////////////////////////////ของสไปรท์ถึงนี่////////////////////////////////////////////////

class Unit{
    public:
        int hp;
        int atk;
        string name;
        
        void Unit(string, int, int);
        void damaged(int);    // ลดค่า hp ของ unit
        void ru_Ok();
};

void Unit::Unit(string title, int attack, int health){
    atk = attack;
    hp = health;
    name = title;
}

void Unit::damaged(int amount){
    hp -= amount;
    hp = (hp < 0) ? 0 : hp;         // เพื่อไม่ให้ hp เป็นจำนวนติดลบ
}

void Unit::ru_Ok(){
    if(hp <= 0) delete this;
}

class Player{
    public:
        string name;                  // ชื่อไว้สำหรับแสดง
        int hp = 10;
        Unit slots[scale];           // ← ค่า Unit ของแต่ละคนเก็บไว้ที่ตัวนี้
        
        void Player(string, int, Deck);
        void battle(Player &, int); // สั่งให้ unit ในช่องที่เลือกโจมตี unit ของฝ่ายตรงข้ามในช่องเดียวกัน
        bool isDead();
};

void Player::Player(string title, int health, Deck pile){
    name = title;
    hp = health;
    for(int i=0; i<2; i++) slots[i] = pile.random();
}

void Player::battle(Player &target, int num){
    if(slots[num].hp != NULL){
        if(target.slots[num].hp != NULL){
            target.slots[num].damaged(slots[num].atk);
            slots[num].damaged
        }
        else target.hp -= slots[num].atk;
    }
    else if(target.slots[num != NULL) hp -= target.slots[num].atk;
    
    slots[num].ru_Ok();
    target.slots[num].ru_Ok();
}

bool Player::isDead(){
    if(hp <= 0) return true;
    else false;
}