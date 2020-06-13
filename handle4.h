/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 4
 * Creates handle class for D&D game, Quest for Elgeon
 * Made 11/17/16
 * Updated 11/21/16
 * Handle Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
#ifndef _HANDLE4H
#define _HANDLE4H

#include "p4.h"
#include "voc.h"

using namespace std;
using namespace GameSpace;

class Creature{
public:
    
    enum RaceType{HUMAN, ELF, HALFELF, ORC, TROLL, OGRE};
    
    ///////////////////////////////////////////////
    //public methods//
    ~Creature();
    Creature();
    Creature(string nameGiven, RaceType raceGiven = HUMAN, VocRules::VocType vocGiven = VocRules::NNE);
    Creature(const Creature& c);
    Creature(CreatureClass* ptr);
    
    string Race_Str() const;
    int Race() const;
    bool IsHumanoid() const;
    bool IsMonster() const ;
    
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
    
    int Ability(CreatureClass::AbilityType givenAbility);
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
    
    int AbilityMod(CreatureClass::AbilityType givenAbility) const;
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
    
    void Write(ostream & out)const;
    //Narrative: Sets name based on parameter if its 10 or less characters 
    //Pre-condition: ostream & out 
    //Post-condition: outputs info and stats 
	
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
	
	string Weapon ()const;
    //Narrative: Returns name of weapon in use, empty string returned if no weapon being carried 
    //Pre-condition: (none) 
    //Post-condition: weapon name is returned  
    
    string Armor ()const;
    //Narrative: Returns name of armor being worn, empty string returned if no armor worn. 
    //Pre-condition: (none) 
    //Post-condition: armor name is returned 
    
    bool HasWeapon ();
    //Narrative: Returns true if creature is carrying a weapon, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: return if creature has weapon  
    
    bool HasArmor ();
    //Narrative: Returns true if creature has armor on, false otherwise 
    //Pre-condition: (none) 
    //Post-condition: return if creature has weapon 
    
    WeaponClass* FindWeapon (WeaponClass * wpn);
    //Narrative: Creature finds weapon on the ground.  If weapon is not NULL the weapon that is passed in replaces the weapon being carried.  The weapon replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found weapon and should return the weapon sent in. 
    //Pre-condition: WpnClass * wpn 
    //Post-condition: points to new weapon 
    
    ArmorClass*  FindArmor (ArmorClass * armorGiven);
    //Narrative: Creature finds armor on the ground.  If armor is not NULL the armor that is passed in replaces the armor being worn.  The armor replaced is returned.  If NULL is passed in then NULL is returned.  Creatures disabled or dying or dead cannot use found armor and should return the armor sent in. 
    //Pre-condition: ArmorClass * armorGiven 
    //Post-condition: points to new armor  
	
	EquipClass*  FindEquipment (EquipClass * equipGiven);
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
    
    vector<string> EquipInitialList() const;
    //Returns the creature’s initial list of equipment by name.  This is the initial list the player should start the game with.
    //Pre-condition: (none) 
    //Post-condition:  Finds functions
    
    int InitiativeCheck() const;
    //Narrative: If creature is active, calculate and return initiative check; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition:  initiative check int is returned
    
    int AttackRoll() const;
    //Narrative: If the creature is active, calculate and return the Attack roll; otherwise return 0.
    //Pre-condition: (none) 
    //Post-condition: Nothing. Pure Virtual
    
    int SavingThrow(GameSpace::SavingThrowType KindofThrow) const; 
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
	
	int Voc() const;
    //Narrative: Returns the creature’s vocation 
    //Pre-condition: (none) 
    //Post-condition: returns vocation as enum (int)
	
	string Voc_Str() const;
    //Narrative: Returns the creature’s vocation as a string (“NNE” "BBN", "CLR","FTR", "ROG", "WIZ") 
    //Pre-condition: (none) 
    //Post-condition: returns string of vocation as string 
	
	vector<string> Pack() const;
    //Narrative: returns pack in alphabetical order
    //Pre-condition: (none) 
    //Post-condition: pack as string is returned
	
	vector<string> EquipInventory() const;
	//Narrative: Returns the creature’s equipment by name.  Current weapon and armor should be included at the end of the equipment inventory list.
    //Pre-condition: (none) 
    //Post-condition: returns vector of strings of inventory
    
	bool ChangeEquipment(string equipmentName);
	//Narrative: Creature changes equipment carried or worn with equipment in the pack.  The equipment that is passed in replaces the equipment being worn or carried if it is in the pack.  The equipment replaced is put back into the pack.  If the creature does not have the equipment in the pack then no change is made.  If the creature is carrying or wearing the requested equipment at the end of the function, return true, otherwise return false.  Creatures disabled or dying or dead cannot change equipment. 
    //Pre-condition: (none) 
    //Post-condition: equipment is moved
    
	EquipClass* BuyEquipment(EquipClass* equipGiven);
	//Narrative:Creature can buy new equipment.  If equipment is not NULL and creature has enough GP then the creature will buy the equipment.   When a creature purchases equipment the GP is decreased by the cost and the equipment that is passed in replaces the equipment being worn or carried.  The equipment replaced is put back into the pack.  If the creature cannot buy the equipment then the equipment is returned.  If NULL is passed in or the equipment is purchased then NULL is returned.  Creatures disabled or dying or dead cannot buy equipment and should return the equipment sent in.
    //Pre-condition: equipGiven as Equipclass*
    //Post-condition: Equipment is bought
    
	EquipClass* SellEquipment(string equipGiven);
	//Narrative:Creature can sell equipment.  If equipment is not NULL and creature owns the equipment then the creature will sell it.   When a creature sells equipment the GP is increased by the cost of the equipment.  The creature will first sell it out of the pack.  If the creature is carrying or wearing the equipment and none is in the pack then they will go without (pointer in creature is set to NULL).  The equipment that is sold is returned.  If the creature cannot sell the equipment or NULL was sent in, then NULL is returned.  Creatures disabled or dying or dead cannot sell equipment and should return NULL.
    //Pre-condition: equipGiven as string
    //Post-condition: equipment is sold 
    
    
    ///////////////////////////////////////////////
	
	///////////////////////////////////////////////
    //overloaded assignment operators in class//
    bool operator== (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true if the names are the same 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns true bool if names are equal
    
    bool operator!= (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true if the names are not equal 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns true bool if names are not equal
    
    bool operator< (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName < nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes 
    
    bool operator<= (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName <= nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes 
    
    bool operator> (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName > nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes
    
    bool operator>= (const Creature& c);
    //Narrative: Relational operator that compares obj by non-case sensitive name. Returns true ownName >= nameGiven 
    //Pre-condition: const creature class passed by reference called c 
    //Post-condition: returns bool for comparing two classes  
    
    Creature & operator= (const Creature& c);
    //Narrative: overloaded assignment operator
    //Pre-condition: constructed creatureclass
    //Post-condition: passed value is changed
    
    ///////////////////////////////////////////////
    
private:
    ///////////////////////////////////////////////
    //private functions//
    void CopyIntoMe(const Creature & c);
    ///////////////////////////////////////////////
    
    ///////////////////////////////////////////////
    //private constants//
    static const string RACE_STR[6];
    ///////////////////////////////////////////////
	
	///////////////////////////////////////////////
    //variables//
	CreatureClass * ccPtr;
	///////////////////////////////////////////////
};

ostream& operator<<(ostream& out, const Creature creatureGiven);

#endif
