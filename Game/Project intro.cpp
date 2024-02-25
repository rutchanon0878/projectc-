#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    char userInput;
    system("Color 0"); //ยังไม่ได้แก้ตกแต่งหรือใส่สี
    cout << "Welcome to 7 sins\n";
    cout << "The world of darkness and sin!\n";
    cout << "Enter 'P' for Play \n";
    cout << "Enter 'I' for Introduction \n";
    cout << "Enter 'H' for How to play \n";
    cout << "Press here : ";
    cin >> userInput ;
    if (userInput == 'P' || userInput == 'p') {
        cout << "Play";
        // P play เพื่อคำสั่งเข้าไปในฟั่งชั่นเพื่อเริ่มเกม
    return 0; 
    }
    else if (userInput == 'I' || userInput == 'i') {
        // I intro , เกริ่นนำ
        cout << "In the realm of a dark and ominous card game filled with sin and hidden secrets, two castles stand side by side, imposing and grand. \nIt's an endless battle between the aspirations of the forlorn rulers and the power of darkness spreading its enchantment across the mesmerizing lands of the 7 Sins card game!\n";
        cout << "In this game, you take on the role of a castle controller, shrouded in the power of darkness. You must guide your team through the challenges and the captivating mysteries of the castles lost in fascination, \nready to face intense battles and conquer the unseen darkness.\n";
        cout << "With the 7 character cards prepared for the battlefield, each card possesses unique powers and abilities gained from the battles within the castles. \nChallenge your adversaries and explore the paths of various sins in each thrilling round!\n";
        cout << "Don't forget the field cards, playing a crucial role in crafting strategies and seizing control of the castles in the way you desire. \nWith diverse choices for players, all of these elements will lead you into the world of horror and suspense in the 7 Sins card game! \nGet ready to embrace the challenges and overcome the crises that await you in every round of this exciting card game!\n";
    }else if (userInput == 'H' || userInput == 'h') {
        // H , How to play เป็นการบอกวิธีเล่นแบบคร่าวๆ
        cout << "This game is a turn-based combat where players can create powerful units with unique attack (atk) and health (hp) values in each round. \n";
        cout << "Engage in thrilling battles as you strategically choose to attack, summon new units, or strategically skip a turn. \n";
    }
    else {
        cout << "Thank you for using the service. Goodbye!\n";
    }

    return 0;
}

