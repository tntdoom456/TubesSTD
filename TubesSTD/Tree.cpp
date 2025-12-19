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

SkillNode* addChildAuto(SkillNode* parent, string name, string role, char primaryStat) {
    if (!parent) return nullptr;

    int depth = getDepth(parent) + 1;
    int cost = depth;
    int reqStr = 0, reqInt = 0;

    // Logika umum: Stat utama naik tinggi, stat sekunder naik sedikit
    if (primaryStat == 'S') { // Strength based
        reqStr = 5 + depth * 3;
        if (role == "defense") reqInt = 2 + depth;
    } else if (primaryStat == 'I') { // Int based
        reqInt = 5 + depth * 3;
        if (role == "magic-support") reqStr = 2;
    }

    SkillNode* child = createSkill(name, cost, reqStr, reqInt);

    // Assign posisi
    if (!parent->left) parent->left = child;
    else parent->right = child; // Isi kanan jika kiri penuh

    child->parent = parent;
    return child;
}

bool unlockSkill(SkillNode* node, int &skillPoints, int STR, int INT) {
    if (canUnlock(node, skillPoints, STR, INT)) {
        node->unlocked = true;
        skillPoints -= node->cost; // Kurangi poin user
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
    delete root; // Hapus node saat ini setelah anak-anaknya dihapus
}


// 1. SEARCH (Pencarian Rekursif)
// Berguna untuk menemukan pointer node hanya berdasarkan nama string dari input user
SkillNode* findNode(SkillNode* root, string name) {
    if (root == nullptr) return nullptr;
    if (root->name == name) return root;

    // Cari di kiri
    SkillNode* foundNode = findNode(root->left, name);
    if (foundNode) return foundNode;

    // Cari di kanan
    return findNode(root->right, name);
}

// 2. READ (Visualisasi Tree)
void printTree(SkillNode* root, int level) {
    if (!root) return;

    // Print indentasi (spasi) sesuai level kedalaman
    for (int i = 0; i < level; i++) cout << "    ";

    cout << "|-- " << root->name;
    if (root->unlocked) cout << " [UNLOCKED]";
    else cout << " (Locked | Cost: " << root->cost << ")";
    cout << endl;

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

// 3. UPDATE
void updateSkill(SkillNode* target, string newName, int newCost, int newStr, int newInt) {
    if (!target) return;
    target->name = newName;
    target->cost = newCost;
    target->reqStr = newStr;
    target->reqInt = newInt;
    cout << "Skill berhasil diupdate!\n";
}

// 4. DELETE
// Menghapus node target beserta semua anaknya (pruning)
void deleteSubtree(SkillNode* target) {
    if (!target) return;

    // Putuskan hubungan dengan parent terlebih dahulu
    if (target->parent) {
        if (target->parent->left == target) {
            target->parent->left = nullptr;
        } else if (target->parent->right == target) {
            target->parent->right = nullptr;
        }
    }

    // Hapus memori secara rekursif menggunakan fungsi yang sudah kamu buat sebelumnya
    deleteTree(target);
    cout << "Branch berhasil dihapus.\n";
}
