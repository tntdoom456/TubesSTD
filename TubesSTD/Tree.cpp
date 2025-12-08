#include "Tree.h"
#include <iostream>
using namespace std;

SkillNode* createSkill(string name, int cost, int reqStr, int reqInt) {
    SkillNode* s = new SkillNode;
    s->name = name;
    s->cost = cost;
    s->reqStr = reqStr;
    s->reqInt = reqInt;
    s->unlocked = false;
    s->left = s->right = s->parent = nullptr;
    return s;
}

// -------------------- DEPTH CALCULATOR ----------------------
int getDepth(SkillNode* node) {
    int d = 0;
    while (node->parent != nullptr) {
        node = node->parent;
        d++;
    }
    return d;
}

// -------------------- AUTO BUILDER --------------------------
SkillNode* addChildAuto(SkillNode* parent, string name, string role) {
    if (!parent) return nullptr;

    int depth = getDepth(parent) + 1;

    int reqStr = 0;
    int reqInt = 0;
    int cost = depth;

    if (parent->name == "Warrior") {
        if (role == "attack") {
            reqStr = 5 + depth * 3;
        } else if (role == "defense") {
            reqStr = 4 + depth * 2;
            reqInt = 2 + depth;
        }
    }
    else if (parent->name == "Mage") {
        if (role == "magic-attack") {
            reqInt = 5 + depth * 3;
        } else if (role == "magic-support") {
            reqInt = 4 + depth * 2;
            reqStr = 2;
        }
    }

    SkillNode* child = createSkill(name, cost, reqStr, reqInt);

    // posisi otomatis kiri = attack, kanan = defense/support
    if (role == "attack" || role == "magic-attack") {
        parent->left = child;
    } else {
        parent->right = child;
    }

    child->parent = parent;
    return child;
}

// -------------------- LOGIC UNLOCK --------------------------
bool canUnlock(SkillNode* p, int skillPoints, int STR, int INT) {
    if (!p) return false;
    if (p->unlocked) return false;
    if (p->parent && !p->parent->unlocked) return false;
    if (skillPoints < p->cost) return false;
    if (STR < p->reqStr) return false;
    if (INT < p->reqInt) return false;
    return true;
}

void showUnlockable(SkillNode* root, int skillPoints, int STR, int INT) {
    if (!root) return;
    if (canUnlock(root, skillPoints, STR, INT)) {
        cout << "- " << root->name
            << " (Cost " << root->cost
            << ", STR " << root->reqStr
            << ", INT " << root->reqInt << ")\n";
    }
    showUnlockable(root->left, skillPoints, STR, INT);
    showUnlockable(root->right, skillPoints, STR, INT);
}
