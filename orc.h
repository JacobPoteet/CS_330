/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Orc class for D&D game, Quest for Elgeon
 * Made 11/1/16
 * Updated 11/14/16
 * Orc Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _ORCH
#define _ORCH

#include "humanoid.h"
#include "voc.h"

using namespace std;
using namespace GameSpace;

class Orc:public Humanoid{
public:
	///////////////////////////////////////////////
	//public constructors//
	Orc(string name, VocRules::VocType voc =VOC_DEFAULT);
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//public methods//
	string Race_Str() const;
    //Narrative: Returns the creature’s race as a string (“HUMAN”, “ELF”, “HALFELF”, “ORC”, “TROLL”, “OGRE”) 
    //Pre-condition: (none) 
    //Post-condition: returns string of race
	
	vector<string> EquipInitialList() const;
    //Narrative: Returns the creature’s initial list of equipment by name.  This is the initial list the player should start the game with. 
    //Pre-condition: (none) 
    //Post-condition: returns vector of string
    
	virtual void Write(ostream & out)const;
    //Narrative: Outputs creature 
    //Pre-condition: out
    //Post-condition: creature is displayed
    
    Orc* Clone() const;
	///////////////////////////////////////////////
    
private:
	///////////////////////////////////////////////
	//private constructors//
	Orc();
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//constants//
	static const string RACE;
    static const int HUM_ABIL_COUNT=6;
    static const int ABIL_ADJ[HUM_ABIL_COUNT];
    static const VocRules::VocType VOC_DEFAULT;
    static const int NUM_INIT_EQUIP = 4;
    static const string INIT_EQUIP[VocRules::VOC_MAX][NUM_INIT_EQUIP];
	///////////////////////////////////////////////
    
    
};

#endif
