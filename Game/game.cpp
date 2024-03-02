#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>
#include<windows.h>
#include"game (1).h"

//ทำเผื่อๆ

using namespace std;

int const scale = 4; // ขนาดของกระดาน(ลองเปลี่ยนได้)
int turn = 1; 

// <- Add header here! <game.h>

/////////////////////////////////////pond/////////////////////////////////////////////////////////
/////////////////////////////ของปอนด์เริ่มตรงนี้!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void manys(const wchar_t);
void many(const wchar_t);
void one(const wchar_t);
void display(Player, Player);
string toUpperStr(string);
void action(Player &, Deck);
void combat(Player &, Player &)
void win(string);

int main()
{
    string filename = "Namecard.txt";
    Deck imported("Namecard.txt");

    int turn = 1; 
    Player p1("P1", 10, imported), p2("P2", 10, imported);
    while(true){ 
        cout << "<<< Turn " << turn << " >>>\n";
        display(p1, p2);
        action(p1, imported);

        display(p1, p2);
        action(p2, imported);
        
        display(p1, p2);
        combat(p1, p2);
        cout << "\n";
        /////////////////////////////////////////////////////////////////////////
        if(p1.hp <= 0 || p2.hp <= 0) break;
        
        turn++;
    }
    if(p1.hp == p2.hp) win("Both");
    else if(p1.isDead()) win(" P1 ");
    else Win(" P2 ");
    //////////////////////////////////////// ของเวสป้าถึงตรงนี้ ///////////////////////////////
    return 0;
}

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

void display(Player left, Player right){ 
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
        
        string N1 = " ";
        string A1 = " ";
        string H1 = " ";
        
        if(left.slots[i] != NULL){
            N1 = left.slots[i].name;
            A1 = to_string(left.slots[i].atk);
            H1 = to_string(left.slots[i].hp);
        }
        
        string N2 = " ";
        string A2 = " ";
        string H2 = " ";
        
        if(right.slots[i] != NULL){
            N2 = right.slots[i].name;
            A2 = to_string(right.slots[i].atk);
            H2 = to_string(right.slots[i].hp);
        }
        
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
void action(Player &currP, Deck pile){
    string input;
    char format[] = "%d";
    int slot=0;
    
    cout << "[" << currP.name << "]: ";
    cin >> input;

     // if(turn == 1){
    //     two.importcard(filename,2);
    // }
    // else{
    //     one.importcard(filename,1);
    // }
    
    if(toUpperStr(input) == "SKIP") return;
    
    else if(toUpperStr(input) == "ADD"){
        cout << "[?] Which slots?(1-" << scale << "): ";
        cin >> input;

        if(input.empty() || cin.bad()){
            cout << "[!] Specify the slots, Please check your command.\n";
            action(currP, pile);
        }
        else if(slot > scale || slot < 1){
            cout << "[!] There are only " << scale << " slots. Please check your command.\n";
            action(currP, pile);
        }
        else{
            currP.slots[slot-1] = imported.random();
        }
    }
    
    else if(toUpperStr(input) == "END"){
        cout << "[i] Game ended by user.";
        exit(0);
    }
    
    else{
        cout << "[!] Invalid command. Write \"add\" to create a unit, \"skip\" to skip or \"End\" to to end the game.\n"; // สำหรับถ้าพิมพ์คำสั่งมาผิด
        action(currP, pile);
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

void win(string display){
    cout << endl;
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
    SetConsoleTextAttribute(Color,14);
    cout<<"||                                                                                                                                  ||"<<endl;
    cout<<"||                                                      !!! " << display << " win !!!!                                                           ||"<<endl;
    cout<<"||                                                                                                                                  ||"<<endl;
    SetConsoleTextAttribute(Color,5);
    cout<<"======================================================================================================================================";
    cout << endl;
}