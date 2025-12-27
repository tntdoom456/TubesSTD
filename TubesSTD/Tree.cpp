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

int getDepth(SkillNode* node) {
    int d = 0;
    while (node->parent != nullptr) {
        node = node->parent;
        d++;
    }
    return d;
}

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

    if (role == "attack" || role == "magic-attack") {
        parent->left = child;
    } else {
        parent->right = child;
    }

    child->parent = parent;
    return child;
}

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

SkillNode* addChildAuto(SkillNode* parent, string name, string role, char primaryStat) {
    if (!parent) return nullptr;

    int depth = getDepth(parent) + 1;
    int cost = depth;
    int reqStr = 0, reqInt = 0;

    if (primaryStat == 'S') {
        reqStr = 5 + depth * 3;
        if (role == "defense") reqInt = 2 + depth;
    } else if (primaryStat == 'I') {
        reqInt = 5 + depth * 3;
        if (role == "magic-support") reqStr = 2;
    }

    SkillNode* child = createSkill(name, cost, reqStr, reqInt);

    if (!parent->left) parent->left = child;
    else parent->right = child;

    child->parent = parent;
    return child;
}

bool unlockSkill(SkillNode* node, int &skillPoints, int STR, int INT) {
    if (canUnlock(node, skillPoints, STR, INT)) {
        node->unlocked = true;
        skillPoints -= node->cost;
        cout << "Sukses membuka skill: " << node->name << endl;
        return true;
    }
    cout << "Gagal membuka skill (Syarat tidak terpenuhi)." << endl;
    return false;
}

void deleteTree(SkillNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

SkillNode* findNode(SkillNode* root, string name) {
    if (root == nullptr) return nullptr;
    if (root->name == name) return root;

    SkillNode* foundNode = findNode(root->left, name);
    if (foundNode) return foundNode;

    return findNode(root->right, name);
}

void printTree(SkillNode* root, int level) {
    if (!root) return;

    for (int i = 0; i < level; i++) cout << "    ";

    cout << "|-- " << root->name;
    if (root->unlocked) cout << " [UNLOCKED]";
    else cout << " (Locked | Cost: " << root->cost << ")";
    cout << endl;

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

void updateSkill(SkillNode* target, string newName, int newCost, int newStr, int newInt) {
    if (!target) return;
    target->name = newName;
    target->cost = newCost;
    target->reqStr = newStr;
    target->reqInt = newInt;
    cout << "Skill berhasil diupdate!\n";
}

void deleteSubtree(SkillNode* target) {
    if (!target) return;

    if (target->parent) {
        if (target->parent->left == target) {
            target->parent->left = nullptr;
        } else if (target->parent->right == target) {
            target->parent->right = nullptr;
        }
    }

    deleteTree(target);
    cout << "Branch berhasil dihapus.\n";
}


void traversalPreOrder(SkillNode* root) {
    if (!root) return;
    cout << root->name << " -> ";
    traversalPreOrder(root->left);
    traversalPreOrder(root->right);
}

void traversalInOrder(SkillNode* root) {
    if (!root) return;
    traversalInOrder(root->left);
    cout << root->name << " -> ";
    traversalInOrder(root->right);
}

void traversalPostOrder(SkillNode* root) {
    if (!root) return;
    traversalPostOrder(root->left);
    traversalPostOrder(root->right);
    cout << root->name << " -> ";
}
