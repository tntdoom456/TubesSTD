#include "Tree.h"

using namespace std;

SkillNode::SkillNode(string n, int c, SkillNode* p) {
    name = n;
    cost = c;
    isUnlocked = false;
    parent = p;
}

SkillTree::SkillTree() {
    root = new SkillNode("Novice", 0);
    root->isUnlocked = true;
}

SkillTree::~SkillTree() {
    deleteTree(root);
}

void SkillTree::deleteTree(SkillNode* node) {
    if (!node) return;
    for (SkillNode* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

SkillNode* SkillTree::findNode(SkillNode* node, string name) {
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;

    for (SkillNode* child : node->children) {
        SkillNode* result = findNode(child, name);
        if (result != nullptr) return result;
    }
    return nullptr;
}

void SkillTree::printTree(SkillNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) cout << "  ";

    cout << "- " << node->name;
    if (node->isUnlocked) cout << " [UNLOCKED]";
    else cout << " [LOCKED] (Cost: " << node->cost << ")";
    cout << endl;

    for (SkillNode* child : node->children) {
        printTree(child, level + 1);
    }
}

void SkillTree::addSkill(string parentName, string skillName, int cost) {
    SkillNode* parentNode = findNode(root, parentName);
    if (parentNode) {
        SkillNode* newSkill = new SkillNode(skillName, cost, parentNode);
        parentNode->children.push_back(newSkill);
    } else {
        cout << "[Error] Parent skill '" << parentName << "' tidak ditemukan!" << endl;
    }
}

bool SkillTree::checkRequirement(SkillNode* node, int playerPoints) {

    if (node->isUnlocked) {
        cout << "[Info] Skill '" << node->name << "' sudah terbuka." << endl;
        return false;
    }

    if (node->parent != nullptr && !node->parent->isUnlocked) {
        cout << "[Gagal] Syarat belum terpenuhi! Buka skill '" << node->parent->name << "' dulu." << endl;
        return false;
    }

    if (playerPoints < node->cost) {
        cout << "[Gagal] Poin kurang untuk '" << node->name << "'. Butuh: " << node->cost << ", Punya: " << playerPoints << endl;
        return false;
    }

    return true;
}

void SkillTree::unlockSkill(string skillName, int &playerPoints) {
    SkillNode* targetNode = findNode(root, skillName);

    if (!targetNode) {
        cout << "[Error] Skill '" << skillName << "' tidak ditemukan." << endl;
        return;
    }

    if (checkRequirement(targetNode, playerPoints)) {
        targetNode->isUnlocked = true;
        playerPoints -= targetNode->cost;
        cout << "[Sukses] Skill '" << targetNode->name << "' terbuka! Sisa Poin: " << playerPoints << endl;
    }
}

void SkillTree::displayTree() {
    cout << "\n--- Status Skill Tree ---" << endl;
    printTree(root, 0);
    cout << "-------------------------" << endl;
}
