#include "TalentTree.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main()
{
    adrTree type;
    adrTree Tree;

    createTree(Tree);
    initializeTree(Tree);

    vector<adrPlayer> players;

    int pilihan;

    while(true){
        clearScreen();
        cout << "======Talent Tree======" << endl;
        cout << "1. Create Player" << endl;
        cout << "2. View Talent Tree" << endl;
        cout << "3. Unlock Talent" << endl;
        cout << "4. View Player Profile" << endl;
        cout << "5. [DEV] Add New Talent" << endl;
        cout << "6. [DEV] Delete New Talent" << endl;
        cout << "7. Fight Monster" << endl;
        cout << "8. Reset Talent" << endl;
        cout << "0. Exit" << endl;

        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan){
        case 1:{
            cout << "Enter Player Name: ";
            string playerName;
            cin >> playerName;
            cout << "Creating Talent Tree for " << playerName << "..." << endl;
            adrPlayer player = createPlayer(playerName);
            players.push_back(player);
            cout << "Player " << playerName << " created successfully!" << endl;
            Sleep(2000);
            break;
        }
        case 2:
            cout << "Displaying Talent Tree..." << endl;
            displayTree(Tree);
            cout << "Type 0 then enter to continue..." << endl;
            int back;
            cin >> back;

            if(back == 0) break;
            
            Sleep(2000);
            break;
        
        case 3:{
            cout << "Unlocking Talent..." << endl;
            cout << "Insert Player Name:" << endl;
            string pname;
            cin >> pname;

            adrPlayer getPlayer = searchPlayer(players, pname);
            if(getPlayer == nullptr){
                cout << "Player not found" << endl;
                break;
            }

            cout << "Insert Talent Name:" << endl;
            string talentName;
            cin >> talentName;

            adrTree getTalent = searchTalent(Tree, talentName);
            if(getTalent == nullptr){
                cout << "Talent not found" << endl;

                break;
            }

            unlocked(getPlayer, getTalent);
            Sleep(2000);
            break;
            }
        case 4:{
            cout << "Displaying Player Profile..." << endl;
            cout << "Insert Player Name:" << endl;
            string pname;
            cin >> pname;

            adrPlayer getPlayer = searchPlayer(players, pname);
            if(getPlayer != nullptr){
                displayPlayer(Tree, getPlayer);
            }else{
                cout << "Player not found" << endl;
            }

            Sleep(4000);
            break;
            }   
        case 5:{
            cout << "[DEV MODE] - Insert New Talent" << endl;

            //Input data Parent (Induknya siapa?)
            cout << "Insert Parent Name (Target): ";
            string parentName;
            cin >> parentName; // Pastikan tidak ada spasi, atau gunakan getline

            //Input data Talent Baru
            cout << "New Talent Name: ";
            string name;
            cin >> name;
            cout << "Type (Class/Skill/Stats): ";
            string type;
            cin >> type;
            cout << "Description: ";
            string desc;
            cin.ignore(); // Membersihkan buffer sebelum getline
            getline(cin, desc); 
            cout << "Point Cost: ";
            int point;
            cin >> point;
            
            adrTree newOne = nullptr;

            if(type == "Class"){
                Talent newClass = {name, type, desc, point, false, false};
                newOne = createClass(newClass);
            } else if(type == "Skill"){
                Talent newSkill = {name, type, desc, point, false, false};
                newOne = createSkill(newSkill);
            } else if(type == "Stats"){
                Talent newStats = {name, type, desc, point, false, false};
                newOne = createStats(newStats);
            } else {
                cout << "Invalid type! Talent not created." << endl;
                break;
            }

            insertTalent(Tree, newOne, parentName);
            Sleep(2000);
            break;
            }
        case 6:{
            cout << "[DEV MODE] - Delete Talent" << endl;
            cout << "Insert Talent Name to Delete: ";
            string tname;
            cin >> tname;

            adrTree getTalent = searchTalent(Tree, tname);
            if(getTalent == nullptr){
                cout << "Talent not found." << endl;
                break;
            }else{
                deleteTalent(Tree, tname);
            }
            Sleep(2000);
            break;
            }
        case 7: {
            cout << "Insert Player Name: " << endl;
            string pname;
            cin >> pname;

            adrPlayer getPlayer = searchPlayer(players, pname);
            if(getPlayer == nullptr){
                cout << "Player Doesnt Exist." << endl;
            } 

            fightMonster(getPlayer);
            Sleep(2000);
            break;
        }
        case 8:{
            cout << "Insert Player Name: " << endl;
            string pname;
            cin >> pname;

            adrPlayer getPlayer = searchPlayer(players, pname);
            if(getPlayer == nullptr){
                cout << "Player Doesnt Exist." << endl;
                break;
            } 

            resetTalent(Tree, getPlayer);
            cout << "All talents have been reset for " << getPlayer->name << "." << endl;
            Sleep(2000);
            break;
        }
        case 0:{
            cout << "Exiting the program. Goodbye!" << endl;
            Sleep(1000);
            return 0;
        }
        default:
            cout << "Pilihan tidak tersedia! GUNAKAN MATAMU!" << endl;
            break;
        }
    }
    return 0;
}
