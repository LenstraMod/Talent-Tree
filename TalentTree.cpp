#include <iostream>
#include "TalentTree.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>

using namespace std;

void clearScreen() {
    // This weird string tells the terminal: "Clear screen (2J) and move cursor to top-left (1;1H)"
   #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void createTree(adrTree& Tree){
    Tree = nullptr;   
    Tree = createNode("Root", "System", "This is the root of the talent tree", 0, false, false);
}
bool isEmptyPlayer(adrPlayer player){
   return (player == nullptr);

}

adrTree createNode(string name, string type, string description, int pointRequire, bool isUnlocked, bool isCompleted){
    adrTree p = new TreeNode;
    p->info.name = name;
    p->info.type = type;
    p->info.description = description;
    p->info.pointRequire = pointRequire;
    p->info.isUnlocked = isUnlocked;
    p->info.isCompleted = isCompleted;
    p->parent = nullptr;

    return p;
}

adrTree createClass(Talent classes){
    return createNode(classes.name, classes.type, classes.description, classes.pointRequire, classes.isUnlocked, classes.isCompleted);
}
adrTree createSkill(Talent skills){
    return createNode(skills.name, skills.type, skills.description, skills.pointRequire, skills.isUnlocked, skills.isCompleted);
}
adrTree createStats(Talent stats){
    return createNode(stats.name, stats.type, stats.description, stats.pointRequire, stats.isUnlocked, stats.isCompleted);
}
adrPlayer createPlayer(string playerName){
    adrPlayer p = new Player;
    p->name = playerName;
    p->availablePoint = 0;
    return p;
}
void addChild(adrTree& parent, adrTree& child){
    child->parent = parent;
    parent->children.push_back(child);
}
adrTree searchTalent(adrTree Tree, string name){
    if(Tree == nullptr){ return nullptr;}

    if(Tree->info.name == name){
        return Tree;
    }

    //DFS
    for(adrTree child : Tree->children){
        adrTree found = searchTalent(child, name);
        if (found != nullptr){ return found;}
    }

    return nullptr;
}

adrPlayer searchPlayer(vector<adrPlayer> players, string name){
    adrPlayer foundPlayer = nullptr;

    for(adrPlayer p : players){
        if(p->name == name){
            foundPlayer = p;
            break;
        }
    }

    return foundPlayer;
}
void insertTalent(adrTree& Tree,adrTree talent, string parentName){
    adrTree getParent = searchTalent(Tree, parentName);

    if(getParent != nullptr){
        addChild(getParent, talent);
        cout << "Successfully added " << talent->info.name << " under " << parentName << endl;
    }else{
        cout << "Parent not found" << endl;
    }
}
void deleteSubTree(adrTree talent){ //untuk menghapus seluruh cabang agar memory tidak melayang kemana mana waokowk
    if(talent == nullptr){return;}
    for (int i = 0; i < talent->children.size(); i++)
    {
        deleteSubTree(talent->children[i]);
    }
    delete talent;
}
void deleteTalent(adrTree& Tree, string type){
    if(Tree == nullptr) return;

    if(Tree->parent == nullptr && Tree->info.name == type){
        cout << "Cannot delete root talent" << endl;
        return;
    }

    for(int i = 0; i < Tree->children.size(); i++){
        if(Tree->children[i]->info.name == type){
            deleteSubTree(Tree->children[i]);
            Tree->children.erase(Tree->children.begin() + i);
            i--;
            cout << "Talent " << type << " and its subtree deleted." << endl;
        }else{
            deleteTalent(Tree->children[i], type);
        }
    }
}
bool unlocked(adrPlayer &p, adrTree q){
    if(q == nullptr) return false;

    if(q->info.isUnlocked == true){
        cout << "Talent already unlocked" << endl;
        return true;
    }

    if(q->parent != nullptr && !q->parent->info.isUnlocked){
        if(q->parent->info.type == "Class"){
            cout << "Parent class talent must be unlocked first" << endl;
            return false;
        }else if(q->parent->info.type == "Skill"){
            cout << "Parent skill talent must be unlocked first" << endl;
            return false;
        }else if(q->parent->info.type == "Stats"){
            cout << "Parent stats talent must be unlocked first" << endl;
            return false;
        }
    }

    if(p->availablePoint >= q->info.pointRequire){
        p->availablePoint -= q->info.pointRequire;
        q->info.isUnlocked = true;
        p->unlockedTalent.push_back(q->info);

        cout << "Successfully Unlocked " << q->info.name << endl;
        return true;
    }else{
        cout << "Not enough points to unlock " << q->info.name << endl;
        cout << "Required: " << q->info.pointRequire << ", Available: " << p->availablePoint << endl;
        return false;
    }
}
int countTalent(adrTree talent, string type){
    if(talent == nullptr){
        return 0;
    }
    
    int total = 0;

    if(talent->info.type == type){
        total = 1;
    }

    for (int i = 0; i < talent->children.size(); i++){
        total =+ countTalent(talent->children[i], type);
    }

    return total;
}

void initializeTree(adrTree& Tree){
   cout << "Initializing Game Data..." << endl;

    //Warrior
    Talent tWar = {"Warrior", "Class", "Melee Tank", 0};
    insertTalent(Tree, createClass(tWar), "Root");
    
    insertTalent(Tree, createSkill({"Slash", "Skill", "Basic Sword Attack", 5}), "Warrior");
    insertTalent(Tree, createStats({"SharpBlade", "Stats", "+5 Base Damage", 3}), "Slash");

    insertTalent(Tree, createSkill({"ShieldBash", "Skill", "Stun Enemy", 10}), "Warrior");
    insertTalent(Tree, createStats({"HeavyShield", "Stats", "+1s Stun Duration", 4}), "ShieldBash");

    //Mage
    Talent tMage = {"Mage", "Class", "Magic User", 0};
    insertTalent(Tree, createClass(tMage), "Root");

    insertTalent(Tree, createSkill({"Fireball", "Skill", "Burn Area", 5}), "Mage");
    insertTalent(Tree, createStats({"Ignite", "Stats", "Adds Burn Effect", 4}), "Fireball");

    insertTalent(Tree, createSkill({"IceSpike", "Skill", "Freeze Single Target", 8}), "Mage");
    insertTalent(Tree, createStats({"Permafrost", "Stats", "+10% Freeze Chance", 4}), "IceSpike");

    //Archer
    Talent tArch = {"Archer", "Class", "Ranged DPS", 0};
    insertTalent(Tree, createClass(tArch), "Root");

    insertTalent(Tree, createSkill({"DoubleShot", "Skill", "Shoot 2 Arrows", 6}), "Archer");
    insertTalent(Tree, createStats({"QuickDraw", "Stats", "-1s Cooldown", 3}), "DoubleShot");

    insertTalent(Tree, createSkill({"EagleEye", "Skill", "Increase Range", 5}), "Archer");
    insertTalent(Tree, createStats({"HawkVision", "Stats", "+2 Attack Range", 3}), "EagleEye");

    //Assasin
    Talent tAsn = {"Assassin", "Class", "Stealth Burst", 0};
    insertTalent(Tree, createClass(tAsn), "Root");

    insertTalent(Tree, createSkill({"Backstab", "Skill", "High Critical Dmg", 8}), "Assassin");
    insertTalent(Tree, createStats({"VitalPoint", "Stats", "+15% Crit Damage", 5}), "Backstab");

    insertTalent(Tree, createSkill({"SmokeBomb", "Skill", "Escape Combat", 10}), "Assassin");
    insertTalent(Tree, createStats({"ThickSmoke", "Stats", "+2s Invisibility", 4}), "SmokeBomb");
    
    cout << ">> [System]: Full Talent Tree (Classes, Skills, Stats) loaded!" << endl;
}

bool playerHasTalent(adrPlayer player, string talentName) {
   if(player == nullptr) return false;

   for(int i = 0; i < player->unlockedTalent.size(); i++){
        if(player->unlockedTalent[i].name == talentName){
            return true;
        }
   }

   return false;
}

void displayPlayer(adrTree Tree, adrPlayer player){

    if(Tree == nullptr || player == nullptr){
        cout << "Tree or Player is empty" << endl;
        return;
    }

    if(Tree->info.name == "Root"){
        cout << "Player Name: " << player->name << endl;
        cout << "Available Point: " << player->availablePoint << endl;
        cout << "Unlocked Talents: " << endl;
    }

    bool isOwned = Tree->info.name == "Root" || playerHasTalent(player, Tree->info.name);

    if(isOwned){
        if(Tree->info.name != "Root"){
            cout << "- " << Tree->info.name << " (" << Tree->info.type << "): " << Tree->info.description << endl;
        }

        for(int i = 0; i < Tree->children.size(); i++){
            displayPlayer(Tree->children[i],player);
        }
    }
}
void displayTree(adrTree Tree){
    if (Tree == nullptr) {
        return;
    }

    // 1. Handle ROOT (Don't print "Root", just show children)
    if (Tree->info.name == "Root") {
        cout << "=== WORLD TALENT MAP ===" << endl;
        for (int i = 0; i < Tree->children.size(); i++) {
            displayTree(Tree->children[i]);
            cout << "------------------------" << endl; // Separator between Classes
        }
        return; // Stop here for Root, don't run the code below
    }

    // 2. Custom Print Based on "TYPE"
    if (Tree->info.type == "Class") {
        cout << "Class : " << Tree->info.name << endl;
    } 
    else if (Tree->info.type == "Skill") {
        // Add a tab or spaces for indentation
        cout << "\tSkill : " << Tree->info.name << endl;
        cout << "\tPoint Require : " << Tree->info.pointRequire << endl;
    }
    else if (Tree->info.type == "Stats") {
        // Stats usually don't have names like "Strength", 
        // they have descriptions like "+5 Strength".
        // We print the DESCRIPTION here as per your request.
        cout << "\t\tStat Name : " << Tree->info.name << endl;
        cout << "\t\tStat Description : " << Tree->info.description << endl;
        cout << "\t\tStat Point Require : " << Tree->info.pointRequire << endl;
    } 
    else {
        // Fallback for unknown types
        cout << "- " << Tree->info.name << endl;
    }

    // 3. Recurse to Children
    for (int i = 0; i < Tree->children.size(); i++) {
        displayTree(Tree->children[i]);
    }
}
void resetTalent(adrTree talent, adrPlayer player){
    if(talent == nullptr || player == nullptr) return;

    for(int i = 0; i < talent->children.size(); i++){
        resetTalent(talent->children[i], player);
    }

    for(int i = 0; i < player->unlockedTalent.size(); i++){
        if(player->unlockedTalent[i].name == talent->info.name){
            player->availablePoint += talent->info.pointRequire;
            player->unlockedTalent.erase(player->unlockedTalent.begin() + i);
            talent->info.isUnlocked = false;
            cout << "Talent " << talent->info.name << " has been reset for " << player->name << "." << endl;
            break;
        }
    }
}
void fightMonster(adrPlayer& player){
    cout << player->name << " is fighting a monster!" << endl;

    Sleep(5000);

    int earnedPoints = 10; // Fixed points for simplicity
    player->availablePoint += earnedPoints;

    cout << "Monster defeated! " << player->name << " earned " << earnedPoints << " talent points." << endl;
}