/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates humanoid class for D&D game, Quest for Elgeon
 * Made 10/26/16
 * Updated 11/14/16
 * Humanoid Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _HUMANOIDH
#define _HUMANOIDH

#include <vector>
#include"cc4.h"
#include"voc.h"

using namespace std;
using namespace GameSpace;

class Humanoid: public CreatureClass{
public:
	///////////////////////////////////////////////
	//destructor//
	virtual ~Humanoid();
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//public methods//
    long XP() const;
    //Narrative: Returns the creature’s experience points 
    //Pre-condition: (none)  
    //Post-condition: returns XP as long
    
    long GP() const;
    //Narrative: Returns the creature’s gold points 
    //Pre-condition: (none) 
    //Post-condition: returns GP as long
	
	int Level() const;
    //Narrative: Returns the creature’s level within vocation 
    //Pre-condition (none) 
    //Post-condition: returns level as int 
	
	long UpdateGP(long value);
    //Narrative: Updates the creature’s GP by value.  Negative value will decrease GP and positive value will increase GP.  The updated GP is returned. 
    //Pre-condition: int value 
    //Post-condition: returns new GP 
    
    long UpdateXP(long value);
    //Narrative: Updates the creature’s XP by value.  A positive value will increase XP.  An increase in XP could cause a humanoid to be promoted to the next level within their vocation (each promotion will trigger a roll for HP).  If value is less than zero the XP is unchanged.   The updated XP is returned 
    //Pre-condition: int value 
    //Post-condition: returns new XP and changes level
	
	virtual void Write(ostream & out)const;
    //Narrative: Sets name based on parameter if its 10 or less characters 
    //Pre-condition: ostream & out 
    //Post-condition: outputs info and stats 
	
	int Voc() const;
    //Narrative: Returns the creature’s vocation 
    //Pre-condition: (none) 
    //Post-condition: returns vocation as enum (int)
	
	string Voc_Str() const;
    //Narrative: Returns the creature’s vocation as a string (“NNE” "BBN", "CLR","FTR", "ROG", "WIZ") 
    //Pre-condition: (none) 
    //Post-condition: returns string of vocation as string 
	
    virtual WeaponClass* FindWeapon (WeaponClass * wpn);
    //Narrative: Creature finds weapon on the ground.  If weapon is not NULL the weapon that is passed in replaces the weapon being carried.  The weapon replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found weapon and should return the weapon sent in. 
    //Pre-condition: WpnClass * wpn 
    //Post-condition: points to new weapon 
    
    virtual ArmorClass*  FindArmor (ArmorClass * armorGiven);
    //Narrative: Creature finds armor on the ground.  If armor is not NULL the armor that is passed in replaces the armor being worn.  The armor replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found armor and should return the armor sent in. 
    //Pre-condition: ArmorClass * armor 
    //Post-condition: points to new armor
	
	virtual EquipClass*  FindEquipment (EquipClass * equipGiven);
    //Narrative: Creature finds equip on the ground.  If equip is not NULL the equip that is passed in replaces the armor being worn.  The equip replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found equip and should return the equip sent in. 
    //Pre-condition: EquipClass * equipGiven
    //Post-condition: points to new equipment
	
	vector<string> Pack() const;
    //Narrative: returns pack in alphabetical order
    //Pre-condition: (none) 
    //Post-condition: pack as string is returned
	
	vector<string> EquipInventory() const;
	//Narrative: Returns the creature’s equipment by name.  Current weapon and armor should be included at the end of the equipment inventory list.
    //Pre-condition: (none) 
    //Post-condition: returns vector of strings of inventory
    
	virtual vector<string> EquipInitialList() const =0;
	//Narrative:Returns the creature’s initial list of equipment by name.  This is the initial list the player should start the game with.
    //Pre-condition: (none) 
    //Post-condition: finds function in lower class
    
	bool ChangeEquipment(string equipmentName);
	//Narrative: Creature changes equipment carried or worn with equipment in the pack.  The equipment that is passed in replaces the equipment being worn or carried if it is in the pack.  The equipment replaced is put back into the pack.  If the creature does not have the equipment in the pack then no change is made.  If the creature is carrying or wearing the requested equipment at the end of the function, return true, otherwise return false.  Creatures disabled or dying or dead cannot change equipment. 
    //Pre-condition: string equipmentName 
    //Post-condition: equipment is moved
    
	EquipClass* BuyEquipment(EquipClass* equipGiven);
	//Narrative:Creature can buy new equipment.  If equipment is not NULL and creature has enough GP then the creature will buy the equipment.   When a creature purchases equipment the GP is decreased by the cost and the equipment that is passed in replaces the equipment being worn or carried.  The equipment replaced is put back into the pack.  If the creature cannot buy the equipment then the equipment is returned.  If NULL is passed in or the equipment is purchased then NULL is returned.  Creatures disabled or dying or dead cannot buy equipment and should return the equipment sent in.
    //Pre-condition: equipGiven as Equipclass*
    //Post-condition: Equipment is bought
    
	EquipClass* SellEquipment(string equipGiven);
	//Narrative:Creature can sell equipment.  If equipment is not NULL and creature owns the equipment then the creature will sell it.   When a creature sells equipment the GP is increased by the cost of the equipment.  The creature will first sell it out of the pack.  If the creature is carrying or wearing the equipment and none is in the pack then they will go without (pointer in creature is set to NULL).  The equipment that is sold is returned.  If the creature cannot sell the equipment or NULL was sent in, then NULL is returned.  Creatures disabled or dying or dead cannot sell equipment and should return NULL.
    //Pre-condition: equipGiven as string
    //Post-condition: equipment is sold 
    
	virtual int AttackRoll() const;
	//Narrative:If the creature is active, calculate and return the Attack roll; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition: attack roll is returned
    
	virtual int SavingThrow(SavingThrowType KindofThrow) const;
    //Narrative: If the creature is active, calculate and return the Saving Throw; otherwise return 0.
    //Pre-condition: KindofThrow as SavingThrowType
    //Post-condition: Saving throw is returned
    
    virtual Humanoid * Clone() const = 0;
	// Narrative: Returns Humanoid pointer
	// Pre-condition: (none)
	// Post-condition: new humanoid is creatued

	
	///////////////////////////////////////////////
private:
	///////////////////////////////////////////////
	//constants//
	static const string HUM_SKILL_DEF[6][3];
	static const int XP_DEFAULT;
    //in update xp, the count of dice used in roll
	static const int UPDATE_XP_COUNT;
	static const int LEVEL_DEFAULT;
	static const VocRules::VocType VOC_DEFAULT;
    static const int HUM_DIE_COUNT;
    //number of faces for human ability rolls
    static const int HUM_DIE_FACE;
    //minimun value
    static const int MIN_VAL;
    
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//private methods//
	Humanoid();
	void SetVoc(VocRules::VocType vocGiven, VocRules::VocType const DEF_VOC);
    //Narrative: sets vocation from given parameter 
    //Pre-condition: VocType vocGiven & VocType const DEF_VOC
    //Post-condition: sets new voc 
	
    int AttackBonus() const;
    //Narrative: Calculates attack bonus
    //Pre-condition: none
    //Post-condition: Attack bonus is returned
    
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//variables//
	int level;
    long xp;
	long gp;
	VocRules::VocType voc;
	vector<EquipClass *> pack;
	///////////////////////////////////////////////
	
    
protected:
	///////////////////////////////////////////////
	//protected constuctors//
	Humanoid(string nameGiven, VocRules::VocType vocGiven, VocRules::VocType const DEF_VOC, int const abilAdj[]);
    //Narrative: creates humanoid from parameters
    //Pre-condition: can only be called from lower class
    //Post-condition: humanoid constructor was executed
    
	Humanoid(const Humanoid & h);
    //Narrative:  Copy constructor
    //Pre-condition: constructed humanoid
    //Post-condition: humanoid is constructed from copy
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////
	//protected functions//
	void SetSkills();
    //Narrative: Sets skills using table 
    //Pre-condition: (none) 
    //Post-condition: skills are set for creature
    
    void CopyIntoMe(const Humanoid & h);
    //Narrative: Helper function of copying function
    //Pre-condition: preconstruced humanoid
    //Post-condition: properties are copied
    
    void InitAbil(int const abilAdj[]);
    //Narrative: Sets skills using table 
    //Pre-condition: (none) 
    //Post-condition: skills are set for creature

	///////////////////////////////////////////////
    
    static const int SKILL_COUNT;
    
    Humanoid & operator= (const Humanoid& h);
};

#endif
///////////////////////////////////////////////
// //
///////////////////////////////////////////////
