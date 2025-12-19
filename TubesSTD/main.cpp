#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

// Fungsi bantuan untuk membersihkan layar (opsional)
void clearScreen() {
    // system("cls"); // windows
    // system("clear"); // linux/mac
    cout << string(5, '\n');
}

int main() {
    // 1. Inisialisasi Player Stats
    int STR, INT, skillPoints;
    cout << "=== SETUP KARAKTER ===\n";
    cout << "Masukkan STR Awal: "; cin >> STR;
    cout << "Masukkan INT Awal: "; cin >> INT;
    cout << "Masukkan Skill Points: "; cin >> skillPoints;

    // 2. Setup Root Tree (Novice)
    SkillNode* root = createSkill("Novice");
    root->unlocked = true; // Skill awal selalu terbuka

    // Data sementara untuk input user
    int choice;
    string pName, cName, role; // Parent Name, Child Name, Role
    int cost, rStr, rInt;      // Req vars

    while (true) {
        cout << "\n====================================\n";
        cout << "      SKILL TREE MANAGER (BINARY)   \n";
        cout << "====================================\n";
        cout << "Stats: STR=" << STR << " | INT=" << INT << " | SP=" << skillPoints << endl;
        cout << "------------------------------------\n";
        cout << "1. Tampilkan Tree (READ)\n";
        cout << "2. Tambah Skill Manual (CREATE)\n";
        cout << "3. Tambah Skill Otomatis (CREATE - Auto)\n";
        cout << "4. Edit Skill (UPDATE)\n";
        cout << "5. Hapus Skill/Branch (DELETE)\n";
        cout << "6. Unlock Skill (ACTION)\n";
        cout << "7. Lihat yang bisa di-Unlock (FILTER)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: // READ
            cout << "\n[ Struktur Skill Tree ]\n";
            printTree(root);
            break;

        case 2: // CREATE (Manual)
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

                        // Masukkan ke slot kosong
                        if (!p->left) p->left = child;
                        else p->right = child;

                        cout << "Skill berhasil ditambahkan!\n";
                    }
                } else {
                    cout << "Parent tidak ditemukan!\n";
                }
            }
            break;

        case 3: // CREATE (Auto Builder)
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

                        // Menentukan stat utama (S/I) berdasarkan parent
                        char primary = 'S'; // Default Strength
                        // Logika sederhana: kalau parentnya Mage/keturunannya, pakai Int
                        // (Di kode nyata, bisa cek parent name atau role recursive)
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

        case 4: // UPDATE
            cout << "Nama Skill yang mau diedit: ";
            cin.ignore(); getline(cin, cName);
            {
                SkillNode* target = findNode(root, cName);
                if (target && target != root) { // Jangan edit Novice sembarangan
                    cout << "--- Edit Data ---\n";
                    cout << "Nama Baru: "; getline(cin, pName); // pakai var pName utk temp
                    cout << "Cost Baru: "; cin >> cost;
                    cout << "Req STR Baru: "; cin >> rStr;
                    cout << "Req INT Baru: "; cin >> rInt;
                    updateSkill(target, pName, cost, rStr, rInt);
                } else {
                    cout << "Node tidak ditemukan atau tidak boleh diedit.\n";
                }
            }
            break;

        case 5: // DELETE
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

        case 6: // UNLOCK
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

        case 7: // FILTER / CHECK
            cout << "\n=== Skill yang TERSEDIA untuk dibuka ===\n";
            showUnlockable(root, skillPoints, STR, INT);
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }

    // Bersihkan memori sebelum keluar
    deleteTree(root);
    return 0;
}
