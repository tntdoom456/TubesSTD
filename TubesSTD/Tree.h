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

#endif
