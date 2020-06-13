/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 5
 * Creates handle class for D&D game, Quest for Elgeon
 * Made 12/1/16
 * Updated 12/7/16
 * Database Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _DBH
#define _DBH

#include "p4.h"
#include "handle4.h"
#include <map>
#include <algorithm>
#include <utility>

using namespace std;
using namespace GameSpace;

class CreatureDB{
public:
    
    enum ExceptionType{BELOW_VALID_INDEX, ABOVE_VALID_INDEX};
    
    
    static CreatureDB * GetDB();
    static void DeleteDB();
    bool LoadDB(istream & inStream);
    bool DumpDB (ostream & outStream) const; 
    bool Add(const Creature& Creature); 
    bool Remove(const string& CreatureName); 
    bool Retrieve(const string & CreatureName, /*out*/ Creature& Creature) const;
    void MakeEmpty();
    bool IsEmpty() const;
    int HumanoidCount() const;
    int MonsterCount() const;
    int EquipCount() const;
    vector<string> SortByName() const;
    vector<string> SortByXP() const;
    vector<string> SortByHP() const;
    const pair<const string, Creature>& operator[ ] (int index) const;
    void Write(ostream & out)const;
    
    
private:
    
    CreatureDB();
    ~CreatureDB();
    /*pair<const string, Creature>& operator=(const pair<const string, Creature>)*/;
    static bool IfHumanoidLoad(char typeGiven);
	static bool IfMonsterLoad(char typeGiven);
	VocRules::VocType CharToVoc(char vocGiven);
    static char StrToType(string typeGiven);
    static void SetCreatureStats(Creature & creatureGiven);
	Creature HumanoidLoad(char typeGiven, VocRules::VocType vocGiven, string nameGiven,int hpGiven, int xpGiven);
	Creature MonsterLoad(char typeGiven, string nameGiven, int hpGiven);
    
    map<string,Creature> cMap;
    static CreatureDB * cPtr;
    
};

ostream& operator<<(ostream& out, const CreatureDB* db);


#endif
