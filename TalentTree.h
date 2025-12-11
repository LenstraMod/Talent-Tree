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
adrTree createClass(Talent classes);
adrTree createSkill(Talent skills);
adrTree createStats(Talent stats);
adrPlayer createPlayer(adrPlayer player);
void insertTalent(adrTree& talent);
void deleteTalent(adrTree& talent);
bool unlocked(adrPlayer &p, adrTree q);
adrTree searchTalent(adrTree Tree, string name);
int countTalent(adrTree talent, string type);
void displayPlayer(adrTree talent);//Ini itu mengeprint semua talent dari player yang isUnlocked
void displayTree(adrTree Tree);
void resetTalent(adrTree& talent);

#endif // TALENTREE_H_INCLUDED
//Ketika Moves sudah mengisi semua stats, maka dianggap mastered. Mastered == Dapat memilih moves lain.
//Ketika Class sudah mengisi semua moves, maka dianggap completed. Completed == Dapat memilih class lain.
// struct TalentNode {
//     string key;             // Nama (Game/Class/Move/Stat) yang akan jadi kunci pengurutan
//     NodeType type;          // Penanda level (misal: CLASS, MOVE)
    
//     // Data Game RPG
//     bool isUnlocked;        // Status apakah sudah diambil
//     string description;     // Deskripsi tambahan (khusus untuk stats)

//     // Pointer BST
//     TalentNode* left;    // Anak Kiri (Nama lebih kecil / A-M)
//     TalentNode* right;   // Anak Kanan (Nama lebih besar / N-Z)
// };

// struct TalentTree {
//     TalentNode* root;    // Akar utama pohon
    
//     // Tracker Pemain
//     TalentNode* currentSelection; 
// };