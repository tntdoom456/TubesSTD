#include <iostream>
#include "Tree.h" // Include header buatan sendiri

using namespace std;

int main() {
    SkillTree myGameSkills;
    int playerPoints = 15; // Contoh poin pemain

    myGameSkills.addSkill("Novice", "Bash", 5);
    myGameSkills.addSkill("Bash", "Stun", 8);

    myGameSkills.addSkill("Novice", "Heal", 5);
    myGameSkills.addSkill("Heal", "Revive", 10);

    myGameSkills.displayTree();
    cout << "\nPlayer Points: " << playerPoints << endl;

    cout << "\n1. Coba ambil Skill Level 2 (Stun) langsung (Harus Gagal):" << endl;
    myGameSkills.unlockSkill("Stun", playerPoints);

    cout << "\n2. Ambil Skill Level 1 (Bash) (Harus Sukses):" << endl;
    myGameSkills.unlockSkill("Bash", playerPoints);

    cout << "\n3. Ambil Skill Level 2 (Stun) sekarang (Harus Sukses):" << endl;
    myGameSkills.unlockSkill("Stun", playerPoints);

    myGameSkills.displayTree();

    return 0;
}
