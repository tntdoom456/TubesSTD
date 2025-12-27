#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

void clearScreen() {
    cout << string(5, '\n');
}

int main() {
    int STR, INT, skillPoints;

    cout << "=== SETUP KARAKTER ===\n";
    cout << "Masukkan STR Awal: "; cin >> STR;
    cout << "Masukkan INT Awal: "; cin >> INT;
    cout << "Masukkan Skill Points: "; cin >> skillPoints;

    // --- INISIALISASI TREE OTOMATIS ---
    // 1. Root
    SkillNode* root = createSkill("Novice");
    root->unlocked = true;

    // 2. Level 1: Warrior & Mage
    SkillNode* warrior = createSkill("Warrior", 1, 5, 0);
    warrior->parent = root;
    root->left = warrior;

    SkillNode* mage = createSkill("Mage", 1, 0, 5);
    mage->parent = root;
    root->right = mage;

    // 3. Level 2: Anak-anak Warrior
    SkillNode* fighter = createSkill("Fighter", 2, 10, 0); // Kiri Warrior
    fighter->parent = warrior;
    warrior->left = fighter;

    SkillNode* shielder = createSkill("Shielder", 2, 8, 2); // Kanan Warrior
    shielder->parent = warrior;
    warrior->right = shielder;

    // 4. Level 2: Anak-anak Mage
    SkillNode* fireball = createSkill("Fireball", 2, 0, 10); // Kiri Mage
    fireball->parent = mage;
    mage->left = fireball;

    SkillNode* iceWall = createSkill("IceWall", 2, 2, 8); // Kanan Mage
    iceWall->parent = mage;
    mage->right = iceWall;

    // -----------------------------------------------------------

    int choice;
    string pName, cName, role;
    int cost, rStr, rInt;

    while (true) {
        cout << "\n====================================\n";
        cout << "      SKILL TREE MANAGER (BINARY)   \n";
        cout << "====================================\n";
        cout << "Stats: STR=" << STR << " | INT=" << INT << " | SP=" << skillPoints << endl;
        cout << "------------------------------------\n";
        cout << "1. Tampilkan Tree & Traversal\n"; // Judul menu diupdate
        cout << "2. Tambah Skill Manual\n";
        cout << "3. Tambah Skill Otomatis\n";
        cout << "4. Edit Skill\n";
        cout << "5. Hapus Skill/Branch\n";
        cout << "6. Unlock Skill (ACTION)\n";
        cout << "7. Lihat yang bisa di-Unlock\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            // --- MENAMPILKAN STRUKTUR TREE ---
            cout << "\n[ Struktur Skill Tree ]\n";
            printTree(root);

            // --- MENAMPILKAN 3 TRAVERSAL ---
            cout << "\n------------------------------------\n";
            cout << "[ Traversal Data ]\n";
            cout << "Pre-Order  : "; traversalPreOrder(root); cout << "END\n";
            cout << "In-Order   : "; traversalInOrder(root); cout << "END\n";
            cout << "Post-Order : "; traversalPostOrder(root); cout << "END\n";
            break;

        case 2:
            cout << "Masukkan nama Parent node: ";
            cin.ignore(); getline(cin, pName);
            {
                SkillNode* p = findNode(root, pName);
                if (p) {
                    if (p->left && p->right) {
                        cout << "Gagal: Node " << pName << " sudah penuh (Max 2 cabang)!\n";
                    } else {
                        cout << "Nama Skill Baru: "; getline(cin, cName);
                        cout << "Cost: "; cin >> cost;
                        cout << "Req STR: "; cin >> rStr;
                        cout << "Req INT: "; cin >> rInt;

                        SkillNode* child = createSkill(cName, cost, rStr, rInt);
                        child->parent = p;

                        if (!p->left) p->left = child;
                        else p->right = child;

                        cout << "Skill berhasil ditambahkan!\n";
                    }
                } else {
                    cout << "Parent tidak ditemukan!\n";
                }
            }
            break;

        case 3:
            cout << "Masukkan nama Parent node: ";
            cin.ignore(); getline(cin, pName);
            {
                SkillNode* p = findNode(root, pName);
                if (p) {
                    if (p->left && p->right) {
                        cout << "Gagal: Node penuh!\n";
                    } else {
                        cout << "Nama Skill Baru: "; getline(cin, cName);
                        cout << "Role (attack/defense/magic-attack/magic-support): ";
                        cin >> role;

                        char primary = 'S';
                        cout << "Primary Stat (S for Warrior / I for Mage): ";
                        cin >> primary;

                        addChildAuto(p, cName, role, primary);
                        cout << "Skill Auto berhasil dibuat!\n";
                    }
                } else {
                    cout << "Parent tidak ditemukan!\n";
                }
            }
            break;

        case 4:
            cout << "Nama Skill yang mau diedit: ";
            cin.ignore(); getline(cin, cName);
            {
                SkillNode* target = findNode(root, cName);
                if (target && target != root) {
                    cout << "--- Edit Data ---\n";
                    cout << "Nama Baru: "; getline(cin, pName);
                    cout << "Cost Baru: "; cin >> cost;
                    cout << "Req STR Baru: "; cin >> rStr;
                    cout << "Req INT Baru: "; cin >> rInt;
                    updateSkill(target, pName, cost, rStr, rInt);
                } else {
                    cout << "Node tidak ditemukan atau tidak boleh diedit.\n";
                }
            }
            break;

        case 5:
            cout << "Nama Skill yang mau dihapus (Hati-hati, anak juga terhapus): ";
            cin.ignore(); getline(cin, cName);
            if (cName == "Novice") {
                cout << "Tidak bisa menghapus Root (Novice)!\n";
            } else {
                SkillNode* target = findNode(root, cName);
                if (target) {
                    deleteSubtree(target);
                } else {
                    cout << "Skill tidak ditemukan.\n";
                }
            }
            break;

        case 6:
            cout << "Nama Skill yang mau di-Unlock: ";
            cin.ignore(); getline(cin, cName);
            {
                SkillNode* target = findNode(root, cName);
                if (target) {
                    unlockSkill(target, skillPoints, STR, INT);
                } else {
                    cout << "Skill tidak ditemukan.\n";
                }
            }
            break;

        case 7:
            cout << "\n=== Skill yang TERSEDIA untuk dibuka ===\n";
            showUnlockable(root, skillPoints, STR, INT);
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }

    deleteTree(root);
    return 0;
}
