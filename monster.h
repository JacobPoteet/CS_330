/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Monster class for D&D game, Quest for Elgeon
 * Made 10/26/16
 * Updated 11/14/16
 * Monster Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _MONSTERH
#define _MONSTERH

#include"cc4.h"

using namespace std;
using namespace GameSpace;

class Monster: public CreatureClass{
public:
	///////////////////////////////////////////////
	//destructor//
	~Monster();
    //Narrative: destrucs monster
    //Pre-condition: (none) 
    //Post-condition: monster is deleted
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//public methods//
	virtual void Write(ostream & out)const;
    //Narrative: Sets name based on parameter if its 10 or less characters 
    //Pre-condition: ostream & out 
    //Post-condition: outputs info and stats 
    
    virtual vector<string> EquipInitialList() const=0;
    //Narrative: equips initial list
    //Pre-condition: (none) 
    //Post-condition: Nothing. Pure Virtual
    
    virtual Monster* Clone() const = 0;

	///////////////////////////////////////////////
private:
	///////////////////////////////////////////////
	//constants//
	static const int MON_COUNT;
    static const int ABILITY_COUNT;
	///////////////////////////////////////////////
	
    
protected:
	///////////////////////////////////////////////
	//protected constuctors//
	Monster(const Monster & h);
    //Narrative: Copy constructor
    //Pre-condition: monster created
    //Post-condition: constructs copy of monster
    
    Monster(string nameGiven, int const AbilAdj[], int const hitDieGiven[]);
    //Narrative: constructs monster from parameters
    //Pre-condition: 2 arrays passed in
    //Post-condition: monster is created
	///////////////////////////////////////////////
    
    ///////////////////////////////////////////////
	//protected functions//
	virtual void InitAbilities(const int abilAdj[]);
    //Narrative: initalizes abilities from const array
    //Pre-condition: const int abilAdj[] 
    //Post-condition: abilities is initalized
    
    virtual int AttackRoll(const int attackBonus[])const;
    //Narrative:  calcutates attack roll
    //Pre-condition: attack bonus function and attackbonus array
    //Post-condition: attack roll is calculated
    
    int AttackBonus(int const baseAttBonus[]) const;
    //Narrative: calculates attack bonus for attack AttackRoll
    //Pre-condition: array for base attackBonus
    //Post-condition: attack bonus is calculates
	///////////////////////////////////////////////
	
    
};

#endif
///////////////////////////////////////////////
// //
///////////////////////////////////////////////
