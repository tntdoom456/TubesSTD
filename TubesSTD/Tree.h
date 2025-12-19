#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <string>
using namespace std;

struct SkillNode {
    string name;
    int cost;
    int reqStr;
    int reqInt;
    bool unlocked;

    SkillNode* left;
    SkillNode* right;
    SkillNode* parent;
};

SkillNode* createSkill(string name, int cost = 0, int reqStr = 0, int reqInt = 0);
int getDepth(SkillNode* node);

// otomatis menentukan posisi & stats
SkillNode* addChildAuto(SkillNode* parent, string name, string role);

bool canUnlock(SkillNode* p, int skillPoints, int STR, int INT);
void showUnlockable(SkillNode* root, int skillPoints, int STR, int INT);


// Tambahkan enum atau parameter string untuk tipe scaling
SkillNode* addChildAuto(SkillNode* parent, string name, string role, char primaryStat);

void deleteTree(SkillNode* root);
bool unlockSkill(SkillNode* node, int &skillPoints, int STR, int INT);


// --- CRUD HELPER ---
SkillNode* findNode(SkillNode* root, string name); // Penting untuk mencari node yg mau diedit/hapus
void printTree(SkillNode* root, int level = 0);    // READ (Visualisasi seluruh tree)
void updateSkill(SkillNode* target, string newName, int newCost, int newStr, int newInt); // UPDATE
void deleteSubtree(SkillNode* target);             // DELETE (Hapus node & anak-anaknya)

#endif
