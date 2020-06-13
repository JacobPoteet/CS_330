/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Troll class for D&D game, Quest for Elgeon
 * Made 10/26/16
 * Updated 11/14/16
 * Troll Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _TROLLH
#define _TROLLH

#include "monster.h"

using namespace std;
using namespace GameSpace;

class Troll:public Monster{
public:
	///////////////////////////////////////////////
	//public constructors//
	Troll(string nameGiven);
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//public methods//
	string Race_Str() const;
    //Narrative: returns race as string
    //Pre-condition: (none)
    //Post-condition: string of race returned
    
	virtual vector<string> EquipInitialList() const;
    //Narrative: Returns the creature’s initial list of equipment by name.  This is the initial list the player should start the game with.
    //Pre-condition: (none)
    //Post-condition: string of vectors returned
    
	virtual int AttackRoll() const;
    //Narrative: If the creature is active, calculate and return the Attack roll; otherwise return 0.
    //Pre-condition: (none)
    //Post-condition: creature is output
    
	virtual int SavingThrow(SavingThrowType kind) const;
    //Narrative: If the creature is active, calculate and return the Saving Throw; otherwise return 0.
    //Pre-condition: SavingThrowType kind
    //Post-condition: SavingThrow int returned
	
	void Write(ostream & out)const;
    //Narrative: output creature 
    //Pre-condition: out ostream
    //Post-condition: creature is output
    
    Troll* Clone() const;
	///////////////////////////////////////////////
    
private:
	///////////////////////////////////////////////
	//private constructors//
	Troll();
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//constants//
	static const string RACE;
    static const int MON_ABILITY_COUNT = 6;
	static const int ABIL_ADJ[MON_ABILITY_COUNT];
	static const int HIT_DIE[3];
	static const int SAVE_THROW[3];
	static const int BASE_ATT_BONUS[2];
	static const string INIT_EQUIP[2];
	static const int NUM_INIT_SK=3;
	static const string INIT_SKILLS[NUM_INIT_SK];
	///////////////////////////////////////////////
    
    
};

#endif
