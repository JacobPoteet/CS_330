/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 2
 * Creates creature class for D&D game, Quest for Elgeon
 * Made 10/10/16
 * Updated 11/14/16
 * Creature Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _CC4H
#define _CC4H

#include <iostream>
#include <string>
#include <cmath>
#include "dice.h"
#include "gamespace.h"
#include "voc.h"
#include "armor.h"
#include "wpn.h"
#include "equip.h"

using namespace std;
using namespace GameSpace;



class CreatureClass{
public:
    
    ///////////////////////////////////////////////
    //ENUMS//
    enum AbilityType {DEX, CON, INT, CHA, STR, WIS};
    
    ///////////////////////////////////////////////
    
    
    ///////////////////////////////////////////////
    //constructors//  
    virtual ~CreatureClass();
    //Narrative: destructor
    //Pre-condition: constructed creature 
    //Post-condition: all memory freed
    
    
    
    ///////////////////////////////////////////////
    
    
    ///////////////////////////////////////////////
    //public methods//
    string Name() const;
    //Narrative: Returns the creature’s name 
    //Pre-condition: (none) 
    //Post-condition: the creature’s name is returned as string 
    
    int Row() const;
    //Narrative: Return the creature’s row 
    //Pre-condition: (none) 
    //Post-condition: returns the row as int
    
    int Col() const;
    //Narrative: Returns the creature’s cell row 
    //Pre-condition: (none) 
    //Post-condition: returns the column as int  
       
    int HP() const;
    //Narrative: Returns the creature’s health points 
    //Pre-condition: (none) 
    //Post-condition: returns HP
    
    int Ability(AbilityType givenAbility);
    //Narrative: Returns the creature’s specific ability based on in-parameter 
    //Pre-condition: takes ability which is an AbilityType 
    //Post-condition: returns in of the ability given
	
    bool Active() const;
    //Narrative: Determines if creature is active.  Returns true if the creature is not dead, dying or disabled.  False if the creature is disabled, dying or dead.
    //Pre-condition: (none) 
    //Post-condition: bool if active returned
	
    bool Dead() const;
    //Narrative: Returns true if creature is dead, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: returns bool true if dead
    
    bool Dying() const;
    //Narrative: Returns true if creature is dying, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: returns true if creature is dying 
    
    bool Disabled() const;
    //Narrative: Returns true is creature is disables, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: returns true if creature is disabled
    
    int AbilityMod(AbilityType givenAbility) const;
    //Narrative: Returns the calculated ability modifier based on the in-parameter 
    //Pre-condition:ability AbilityType 
    //Post-condition: ability modification is returned
    
    bool SetCell(int newRow, int newCol);
    //Narrative: Updates the creature’s current coordinates regardless of other fields.  If both newRow and newCol > -1 then the coordinates are set.  If both newRow and newCol are -1 then coordinates are set (indicates creature not on board). In all other cases coordinates should not be set.  If coordinates are set the function returns true.  In all other cases the function returns false. 
    //Pre-condition: passed two ints for new cell 
    //Post-condition: cell is set and returned bool
    
    int UpdateHP(int modification);
    //Narrative: Updates the creature’s HP by modification. Negative modification will decrease HP and positive modification will increase HP. The modified HP is returned. 
    //Pre-condition: int modification 
    //Post-condition: returns new HP 
    
    virtual void Write(ostream & out)const;
    //Narrative: Sets name based on parameter if its 10 or less characters 
    //Pre-condition: ostream & out 
    //Post-condition: outputs info and stats 
    
    ///////////////////////////////////////////////
    
    
    ///////////////////////////////////////////////
    //overloaded assignment operators in class//
    bool operator== (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true if the names are the same 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns true bool if names are equal
    
    bool operator!= (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true if the names are not equal 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns true bool if names are not equal
    
    bool operator< (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName < nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes 
    
    bool operator<= (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName <= nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes 
    
    bool operator> (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName > nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes
    
    bool operator>= (const CreatureClass& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName >= nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes  
    
    
    
    ///////////////////////////////////////////////
    
    ////////////////////p2////////////////////
    
    string Weapon ()const;
    //Narrative: Returns name of weapon in use, empty string returned if no weapon being carried 
    //Pre-condition: (none) 
    //Post-condition: weapon name is returned  
    
    string Armor ()const;
    //Narrative: Returns name of armor being worn, empty string returned if no armor worn. 
    //Pre-condition: (none) 
    //Post-condition: armor name is returned 
    
    bool HasWeapon () const;
    //Narrative: Returns true if creature is carrying a weapon, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: return if creature has weapon  
    
    bool HasArmor () const;
    //Narrative: Returns true if creature has armor on, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: return if creature has weapon 
    
    virtual WeaponClass* FindWeapon (WeaponClass * wpn);
    //Narrative: Creature finds weapon on the ground.  If weapon is not NULL the weapon that is passed in replaces the weapon being carried.  The weapon replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found weapon and should return the weapon sent in. 
    //Pre-condition: WpnClass * wpn 
    //Post-condition: points to new weapon 
    
    virtual ArmorClass*  FindArmor (ArmorClass * armorGiven);
    //Narrative: Creature finds armor on the ground.  If armor is not NULL the armor that is passed in replaces the armor being worn.  The armor replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found armor and should return the armor sent in. 
    //Pre-condition: ArmorClass * armorGiven 
    //Post-condition: points to new armor  
	
	virtual EquipClass*  FindEquipment (EquipClass * equipGiven);
	//Narrative: Creature finds equipment on the ground.  If equipment is not NULL the equipment that is passed in replaces the equipment being worn or carried.  The equipment replaced is put back into the pack.  NULL is returned.  Creatures disabled or dying or dead cannot use found equipment and should return the equipment sent in.
    //Pre-condition: EquipClass * equipGiven 
    //Post-condition: points to new equipment 
    
    WeaponClass* LoseWeapon ();
    //Narrative: Weapon being carried is lost (could be dropped or taken).  Return the lost weapon, NULL returned if no weapon lost. 
    //Pre-condition: (none) 
    //Post-condition: pointer to old weapon is returned 
    
    ArmorClass* LoseArmor ();
    //Narrative: Armor being worn is lost (could be dropped or taken).  Return the lost armor, NULL returned if no armor lost. 
    //Pre-condition: (none) 
    //Post-condition: pointer to old armor is returned 
    
    EquipClass * LoseEquipment();
    //Narrative: Creature loses equipment on the ground.  If equipment is being carried (weapon) it is returned.  If nothing is being carried then what is worn (armor) is returned.  If neither of these then NULL is returned.  
    //Pre-condition: (none) 
    //Post-condition: pointer to old equipment
    
    bool AddSkill (string skill);
    //Narrative: Skill is added to list of skills (no duplicates in list) if valid skill based on skills.in file.  If skill added or already in skill list return true, otherwise return false.  Creatures disabled or dying or dead cannot add a new skill. 
    //Pre-condition: string skill 
    //Post-condition: returns true if you can add more to the vector 
    
    int SkillCheck (string skill);
    //Narrative: If skill is in creature’s skill list, calculate and return skill check; otherwise return 0.  Dead creatures cannot perform a skill check and must return zero. 
    //Pre-condition: (none) 
    //Post-condition: string skill 
    
    void Amnesia ();
    //Narrative: Remove all skills from skill list.  
    //Pre-condition: (none) 
    //Post-condition: vector of skills is cleared 
    
    vector<string> Skills () const;
    //Narrative: Returns the creature’s skill list as a vector of strings. 
    //Pre-condition: (none) 
    //Post-condition: skills vector is returned 
    
    
    vector<int> Abilities ()const;
    //Narrative: Returns the creature’s 6 abilities as a vector of integers. 
    //Pre-condition: (none) 
    //Post-condition: a vector of abilities is returned
    
    ////////////////////p3////////////////////
    
    virtual vector<string> EquipInitialList() const =0;
    //Returns the creature’s initial list of equipment by name.  This is the initial list the player should start the game with.
    //Pre-condition: (none) 
    //Post-condition:  Finds functions
    
    int InitiativeCheck() const;
    //Narrative: If creature is active, calculate and return initiative check; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition:  initiative check int is returned
    
    virtual int AttackRoll() const=0;
    //Narrative: If the creature is active, calculate and return the Attack roll; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition: Nothing. Pure Virtual
    
    virtual int SavingThrow(GameSpace::SavingThrowType KindofThrow) const=0; 
    //Narrative: If the creature is active, calculate and return the Saving Throw; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition:nothing. Pure virtual
    
    int Defense();
    //Narrative: If the creature is active, calculate and return the Defense roll; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition: defense int is retured
    
    int Damage();
    //Narrative: If the creature is active, calculate and return the Damage roll; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition: damage int is returned
    
    virtual CreatureClass* Clone() const = 0;
    
    
private:
    ///////////////////////////////////////////////
    //private constructor//
    static const int ROW_DEFAULT;
    static const int COL_DEFAULT;
    ///////////////////////////////////////////////

    ///////////////////////////////////////////////
    //private constructor//
    CreatureClass();
    //Narrative: Creates creature. 
    //Pre-condition:  (none) 
    //Post-condition: constructs creature class with no parameters
    ///////////////////////////////////////////////
    
    ///////////////////////////////////////////////
    //private methods//
    void SetName(string nameGiven);
    //Narrative: Sets name based on parameter if its 10 or less characters 
    //Pre-condition: nameGiven is a string 
    //Post-condition: sets the name
    
	AbilityType StringToAbility(string abilityGiven);
    //Narrative: helper function that changes string to ability type 
    //Pre-condition: string abilityGiven 
    //Post-condition: AbilityType is returned
    
    
    void InitSkillsFile();
    //Narrative: Initalizes skills.in file to vector
    //Pre-condition: (none) 
    //Post-condition: skillsFile is initalized
    
    
    ///////////////////////////////////////////////
    
    ///////////////////////////////////////////////
    //structs//
    struct CellType{
        int row;
        int col;
    };
    struct SkillRec{
        string skill;
        AbilityType abil;
    };
    
    ///////////////////////////////////////////////
    
    
    ///////////////////////////////////////////////
    //variables//
	int hp;
    char * name;
    CellType cell;
    int ability[6];
	vector<string> skills;
    static vector<SkillRec> skillsFile;
	WeaponClass* weapon;
	ArmorClass* armor;
    ///////////////////////////////////////////////
	
protected:
	///////////////////////////////////////////////
    //constructors//
	CreatureClass(string nameGiven);
	//Narrative: Creates creature. 
    //Pre-condition: name as string
    //Post-condition: constructs creature class with name
	
	CreatureClass(const CreatureClass& c);
    //Narrative: copy constructor
    //Pre-condition: pass constructed creature 
    //Post-condition: new creature is a copy  
	///////////////////////////////////////////////
    
    virtual void InitAbil(int const abilAdj[]);
//   //Narrative: 
    //Pre-condition: (none) 
    //Post-condition:  virtual void InitSkills(vector<string> skillsGiven);
    
    void CopyIntoMe (const CreatureClass& c);
    //Narrative: helper function used to copy creature data 
    //Pre-condition: const CreatureClass& c 
    //Post-condition: creature is copied 
    
    void InitSkills(vector<string> skillsGiven);
    //Narrative: Skills are initalized in given vector
    //Pre-condition: vector<string> skillsGiven
    //Post-condition: vector initalized
    
    void InitHP(int initHP);
    //Narrative: hp initalized
    //Pre-condition: int initHP
    //Post-condition: hp initalized
    
	///////////////////////////////////////////////
    //constants//
    
    //default stats for constructor
    static const string NAME_DEFAULT;
    static const int MAX_SKILL;
    //ability deduction
    static const int ABIL_DEDUC;
    //minimum constitution
    static const int MIN_CON;
    //number of die for human ability rolls

    //Number of races in game
    static const int NUM_RACE;
    //number of abilities in game
	static const int NUM_ABILITY;
    //max chars in name allowed
	static const int MAX_CHAR;
    //human skill default
    //hp needed to be considered dead
    static const int DEAD;
    //hp needed to be considered disabled
    static const int DISABLED;
    ///////////////////////////////////////////////
	
	CreatureClass & operator= (const CreatureClass& c);
    //Narrative: overloaded assignment operator
    //Pre-condition: constructed creatureclass
    //Post-condition: passed value is changed
	
};

///////////////////////////////////////////////
//overloaded assignment operators in the public space
ostream & operator<< (ostream & out, const CreatureClass & c);
//Narrative: couts creature properties 
//Pre-condition: CreatureClass c passed by refrence and out ostream passed by refrence 
//Post-condition: outputs creature data 
///////////////////////////////////////////////

#endif
