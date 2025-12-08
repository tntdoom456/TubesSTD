#include <iostream>
#include "Tree.h"
using namespace std;

int main() {
    int STR, INT, skillPoints;

    cout << "Masukkan STR: ";  cin >> STR;
    cout << "Masukkan INT: ";  cin >> INT;
    cout << "Masukkan Skill Points: "; cin >> skillPoints;

    SkillNode* novice = createSkill("Novice");
    novice->unlocked = true;

    // Warrior & Mage sebagai template awal
    SkillNode* warrior = createSkill("Warrior");
    SkillNode* mage = createSkill("Mage");

    novice->left = warrior;
    warrior->parent = novice;

    novice->right = mage;
    mage->parent = novice;

    // AUTOMATIC BUILDER
    SkillNode* atk1 = addChildAuto(warrior, "Attacker Lv1", "attack");
    SkillNode* def1 = addChildAuto(warrior, "Defender Lv1", "defense");

    SkillNode* atk2 = addChildAuto(atk1, "Berserker", "attack");
    SkillNode* def2 = addChildAuto(def1, "Shield Master", "defense");

    SkillNode* mAtk1 = addChildAuto(mage, "Pyromancer", "magic-attack");
    SkillNode* mDef1 = addChildAuto(mage, "Cryomancer", "magic-support");

    SkillNode* mAtk2 = addChildAuto(mAtk1, "Inferno", "magic-attack");
    SkillNode* mDef2 = addChildAuto(mDef1, "Blizzard", "magic-support");

    cout << "\n=== Skill yang bisa kamu unlock ===\n";
    showUnlockable(novice, skillPoints, STR, INT);
}
