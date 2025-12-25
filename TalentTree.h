#ifndef TALENTREE_H_INCLUDED
#define TALENTREE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Talent{
    string name;
    string type; //"Class","Skill","Stats"
    string description;
    int pointRequire;
    bool isUnlocked;
    bool isCompleted;
    };

typedef struct TreeNode* adrTree;
typedef struct Player* adrPlayer;

struct TreeNode{
    Talent info;
    vector<TreeNode*> children; //ini tuh sebagai anak "Class"
    adrTree parent;
};

struct Player{
    string name;
    int availablePoint;
    vector<Talent> unlockedTalent;
};

void createTree(adrTree& Tree);
bool isEmptyPlayer(adrPlayer player);
adrTree createNode(string name, string type, string description, int pointRequire, bool isUnlocked, bool isCompleted);
adrTree createClass(Talent classes);
adrTree createSkill(Talent skills);
adrTree createStats(Talent stats);
adrPlayer createPlayer(string playerName);
void addChild(adrTree& parent, adrTree& child);
void insertTalent(adrTree& Tree,adrTree talent, string parentName);
void deleteSubTree(adrTree talent);
void deleteTalent(adrTree& talent, string type);
bool unlocked(adrPlayer &p, adrTree q);
adrTree searchTalent(adrTree Tree, string name);
adrPlayer searchPlayer(vector<adrPlayer> players, string name);
int countTalent(adrTree talent, string type);
void initializeTree(adrTree& Tree);
bool playerHasTalent(adrPlayer player, string talentName);
void displayPlayer(adrTree Tree, adrPlayer player);//Ini itu mengeprint semua talent dari player yang isUnlocked
void displayTree(adrTree Tree);
void resetTalent(adrTree talent, adrPlayer player);
void fightMonster(adrPlayer& player);
void clearScreen();

#endif 