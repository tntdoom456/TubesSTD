#include <iostream>
#include <string>
#include <limits>
#include "Tree.h"

using namespace std;

// --- FUNGSI TAMBAHAN UNTUK VALIDASI INPUT ---
int getValidInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Input Error! Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void pause() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer
    cin.get();
}
void cleanBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    int STR, INT, skillPoints;

    cout << "=== SETUP KARAKTER ===\n";
    STR = getValidInt("Masukkan STR Awal: ");
    INT = getValidInt("Masukkan INT Awal: ");
    skillPoints = getValidInt("Masukkan Skill Points: ");

    // --- INISIALISASI TREE OTOMATIS ---
    SkillNode* root = createSkill("Novice");
    root->unlocked = true;

    SkillNode* warrior = createSkill("Warrior", 1, 5, 0);
    warrior->parent = root;
    root->left = warrior;

    SkillNode* mage = createSkill("Mage", 1, 0, 5);
    mage->parent = root;
    root->right = mage;

    SkillNode* fighter = createSkill("Fighter", 2, 10, 0);
    fighter->parent = warrior;
    warrior->left = fighter;

    SkillNode* shielder = createSkill("Shielder", 2, 8, 2);
    shielder->parent = warrior;
    warrior->right = shielder;

    SkillNode* fireball = createSkill("Fireball", 2, 0, 10);
    fireball->parent = mage;
    mage->left = fireball;

    SkillNode* iceWall = createSkill("IceWall", 2, 2, 8);
    iceWall->parent = mage;
    mage->right = iceWall;

    int choice;
    string pName, cName, role;
    int cost, rStr, rInt;
    char confirm;

    while (true) {
        cout << "\n====================================\n";
        cout << "      SKILL TREE MANAGER (BINARY)   \n";
        cout << "====================================\n";
        cout << "Stats: STR=" << STR << " | INT=" << INT << " | SP=" << skillPoints << endl;
        cout << "------------------------------------\n";
        cout << "1. Tampilkan Tree & Traversal\n";
        cout << "2. Tambah Skill Manual\n";
        cout << "3. Tambah Skill Otomatis\n";
        cout << "4. Edit Skill\n";
        cout << "5. Hapus Skill/Branch\n";
        cout << "6. Unlock Skill (ACTION)\n";
        cout << "7. Lihat yang bisa di-Unlock\n";
        cout << "0. Keluar\n";

        choice = getValidInt("Pilihan: ");

        if (choice == 0) break;

        switch (choice) {
        case 1:
            cout << "\n[ Struktur Skill Tree ]\n";
            printTree(root);
            cout << "\n------------------------------------\n";
            cout << "[ Traversal Data ]\n";
            cout << "Pre-Order  : "; traversalPreOrder(root); cout << "END\n";
            cout << "In-Order   : "; traversalInOrder(root); cout << "END\n";
            cout << "Post-Order : "; traversalPostOrder(root); cout << "END\n";
            pause();
            break;

        case 2:
            cout << "Masukkan nama Parent node: ";
            cleanBuffer(); getline(cin, pName);
            {
                SkillNode* p = findNode(root, pName);
                if (p) {
                    if (p->left && p->right) {
                        cout << "Gagal: Node " << pName << " sudah penuh (Max 2 cabang)!\n";
                    } else {
                        cout << "Nama Skill Baru: "; getline(cin, cName);
                        cost = getValidInt("Cost: ");
                        rStr = getValidInt("Req STR: ");
                        rInt = getValidInt("Req INT: ");

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
            pause();
            break;

        case 3:
            cout << "Masukkan nama Parent node: ";
            cleanBuffer(); getline(cin, pName);
            {
                SkillNode* p = findNode(root, pName);
                if (p) {
                    if (p->left && p->right) {
                        cout << "Gagal: Node penuh!\n";
                    } else {
                        cout << "Nama Skill Baru: "; getline(cin, cName);
                        cout << "Role (attack/defense/magic-attack/magic-support): ";
                        cin >> role;

                        char primary;
                        cout << "Primary Stat (S for Warrior / I for Mage): ";
                        cin >> primary;

                        addChildAuto(p, cName, role, primary);
                        cout << "Skill Auto berhasil dibuat!\n";
                    }
                } else {
                    cout << "Parent tidak ditemukan!\n";
                }
            }
            pause();
            break;

        case 4:
            cout << "Nama Skill yang mau diedit: ";
            cleanBuffer(); getline(cin, cName);
            {
                SkillNode* target = findNode(root, cName);
                if (target && target != root) {
                    cout << "--- Edit Data ---\n";
                    cout << "Nama Baru: "; getline(cin, pName);
                    cost = getValidInt("Cost Baru: ");
                    rStr = getValidInt("Req STR Baru: ");
                    rInt = getValidInt("Req INT Baru: ");
                    updateSkill(target, pName, cost, rStr, rInt);
                } else {
                    cout << "Node tidak ditemukan atau tidak boleh diedit.\n";
                }
            }
            pause();
            break;

        case 5:
            cout << "Nama Skill yang mau dihapus: ";
            cleanBuffer(); getline(cin, cName);
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
            pause();
            break;

        case 6:
            cout << "\n=== Daftar Skill yang BISA di-Unlock saat ini ===\n";
            showUnlockable(root, skillPoints, STR, INT);
            cout << "-------------------------------------------------\n";

            cout << "Nama Skill yang mau di-Unlock: ";
            cleanBuffer(); getline(cin, cName);
            {
                SkillNode* target = findNode(root, cName);
                if (target) {
                    unlockSkill(target, skillPoints, STR, INT);
                } else {
                    cout << "Skill tidak ditemukan atau nama salah.\n";
                }
            }
            pause();
            break;

        case 7:
            cout << "\n=== Skill yang TERSEDIA untuk dibuka ===\n";
            showUnlockable(root, skillPoints, STR, INT);

            cout << "\nApakah Anda ingin membuka salah satu skill di atas? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                cout << "Masukkan nama Skill: ";
                cleanBuffer(); getline(cin, cName);

                SkillNode* target = findNode(root, cName);
                if (target) {
                    unlockSkill(target, skillPoints, STR, INT);
                } else {
                    cout << "Skill tidak ditemukan atau nama salah.\n";
                }
            } else {
                cout << "Kembali ke menu utama.\n";
            }
            pause();
            break;

        default:
            cout << "Pilihan tidak valid.\n";
            pause();
        }
    }

    deleteTree(root);
    return 0;
}
