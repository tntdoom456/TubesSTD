#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <iostream>
#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <string>
#include <vector>
#include <iostream>

struct SkillNode {
    std::string name;
    int cost;
    bool isUnlocked;
    SkillNode* parent;
    std::vector<SkillNode*> children;

    SkillNode(std::string n, int c, SkillNode* p = nullptr);
};

class SkillTree {
private:
    SkillNode* root;

    SkillNode* findNode(SkillNode* node, std::string name);
    void printTree(SkillNode* node, int level);

    void deleteTree(SkillNode* node);

public:
    SkillTree();
    ~SkillTree();

    void addSkill(std::string parentName, std::string skillName, int cost);
    bool checkRequirement(SkillNode* node, int playerPoints);
    void unlockSkill(std::string skillName, int &playerPoints);
    void displayTree();
};

#endif



#endif
