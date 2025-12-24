#include "TalentTree.h"

int main()
{
    adrTree type;
    adrTree Tree;

    createTree(Tree);
    initializeTree(Tree);

    vector<adrPlayer> players;

    int pilihan;

    while(true){
        cout << "======Prominence IV: Nathadian Era======" << endl;
        cout << "1. Create Tree" << endl;
        cout << "2. View Talent Tree" << endl;
        cout << "3. Unlock Talent" << endl;
        cout << "4. View Player Profile" << endl;
        cout << "5. [DEV] Add New Talent" << endl;
        cout << "6. [DEV] Delete New Talent" << endl;
        cout << "0. Exit" << endl;

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
            break;
        }
        case 2:
            cout << "Displaying Talent Tree..." << endl;
            displayTree(Tree);
            break;
        
        case 3:
            cout << "Test Create Tree" << endl;
            break;
        
        case 4:{
            cout << "Displaying Player Profile..." << endl;
            cout << "Insert Player Name:" << endl;
            string pname;
            cin >> pname;

            adrPlayer player = nullptr;
            for(adrPlayer p : players){
                if(p->name == pname){
                    player = p;
                    break;
                }
            }

            if(player == nullptr){
                cout << "Player not found" << endl;
                break;
            }
            displayPlayer(Tree, player);
            break;
            }   
        case 5:
            cout << "Test Create Tree" << endl;
            break;
        
        case 6:
            cout << "Test Create Tree" << endl;
            break;
        break;
        case 0:
            cout << "Exiting Program..." << endl;
            return 0;
            break;
        
        default:
            cout << "Pilihan tidak tersedia! GUNAKAN MATAMU!" << endl;
            break;
        }
    }
    return 0;
}
