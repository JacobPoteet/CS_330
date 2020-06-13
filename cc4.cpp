/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 2
 * Creates creature class for D&D game, Quest for Elgeon
 * Made 10/10/16
 * Updated 11/14/16
 * Creature Class C++ File
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */


#include "cc4.h"
#include <iostream>
#include <string>
#include <cmath>
#include "dice.h"
#include "gamespace.h"
#include "voc.h"

using namespace std;
using namespace GameSpace;

///////////////////////////////////////////////
//constants//
const string CreatureClass::NAME_DEFAULT = "DEFAULT";
const int CreatureClass::ROW_DEFAULT = -1;
const int CreatureClass::COL_DEFAULT = -1;
const int CreatureClass::ABIL_DEDUC=5;
const int CreatureClass::MIN_CON = 0;
//Number of races in game
const int CreatureClass::NUM_RACE = 6;
//number of abilities in game
const int CreatureClass::NUM_ABILITY = 6;
//max chars in name allowed
const int CreatureClass::MAX_CHAR = 10;
const int CreatureClass::MAX_SKILL = 6;

//hp needed to be considered dead
const int CreatureClass::DEAD = -10;
//hp needed to be considered disabled
const int CreatureClass::DISABLED = 0;
///////////////////////////////////////////////

vector<CreatureClass::SkillRec> CreatureClass::skillsFile;
// int hp;
// char * name;
// CellType cell;
// int ability[6];
// vector<string> skills;
// WeaponClass* weapon;
// ArmorClass* armor;
///////////////////////////////////////////////
//constructor//
CreatureClass::CreatureClass():name(NULL), weapon(NULL), armor(NULL){
}

CreatureClass::CreatureClass(string nameGiven):name(NULL), weapon(NULL), armor(NULL){
    if(nameGiven == ""){
        throw GameSpace::INVALID_NAME;
    }
    else{   
        SetName(nameGiven);
    }
    cell.row = ROW_DEFAULT;
    cell.col = COL_DEFAULT;
    hp=0;
    InitSkillsFile();
    
	return;
}

CreatureClass::~CreatureClass(){
    if(name != NULL){
        delete[] name;
    }
    if (armor != NULL){
        delete armor;
    }
    if (weapon != NULL){
        delete weapon;
    }
    return;
}
///////////////////////////////////////////////


///////////////////////////////////////////////
//copy constructor
CreatureClass::CreatureClass(const CreatureClass& c):name(NULL), weapon(NULL), armor(NULL){
    
    CopyIntoMe(c);
    
    return;
}
///////////////////////////////////////////////


///////////////////////////////////////////////
//public methods

//returns name
string CreatureClass::Name() const{
    string returnString;
    
    for (int i =0; i<strlen(name); i++){
        returnString += name[i];
    }
    
    return returnString;
}

// returns row
int CreatureClass::Row() const{
    return cell.row;
}

//returns col 
int CreatureClass::Col() const{
    return cell.col;
}

//returns creature hp
int CreatureClass::HP() const{
    return hp;
}


//returns creature ability
int CreatureClass::Ability(AbilityType givenAbility){
    if((givenAbility < 0) or (givenAbility > 5)){
        throw INVALID_ABILITY;
    }
    
    return ability[givenAbility];
}

// returns true if active
bool CreatureClass::Active() const{
	bool returnBool = false;
    if(!Dead() and !Disabled() and !Dying()){
        returnBool = true;
    }
    return returnBool;
}

//returns true if the creature is dead
bool CreatureClass::Dead() const{
    return(hp <=DEAD or ability[CON]== MIN_CON);
}

//returns true if the creature is dying
bool CreatureClass::Dying() const{
	bool returnBool;

   if (hp>DEAD and hp<DISABLED){
		if(ability[CON]>MIN_CON){
			returnBool  = true;
		}
	}else{
		returnBool = false;
	}
	return returnBool;
}

//returns true if the creature is disabled
bool CreatureClass::Disabled() const{
    bool returnBool = false;
    bool abilityDisabled=false;
    
    int i=0;
    while(i<NUM_ABILITY){
        if (ability[i]<=0){
            abilityDisabled = true;
        }
        i++;
    }
    
    if((hp <= DISABLED) or (abilityDisabled == true)){
        returnBool = true;
    }
    
    return (hp <= DISABLED);
}

//returns the calculated ability modifier based on the in-parameter
int CreatureClass::AbilityMod(AbilityType givenAbility) const{
    if((givenAbility < 0) or (givenAbility > 5)){
        throw INVALID_ABILITY;
    }
    return floor((ability[givenAbility]/2)  - ABIL_DEDUC);
}

//Updates the creature’s current coordinates regardless of other fields.
bool CreatureClass::SetCell(int newRow, int newCol){
    bool returnBool;
	
    if (newRow > ROW_DEFAULT and newCol > COL_DEFAULT){
        cell.row=newRow;
        cell.col=newCol;
        returnBool = true;
    }else if(newRow == ROW_DEFAULT and newCol == COL_DEFAULT){
        cell.row=newRow;
        cell.col=newCol;
        returnBool = true;
    }
    else{ 
        returnBool = false;
    }

	
	return returnBool;
}
//sets creature name
void CreatureClass::SetName(string nameGiven){
    string trimGiven;
    string shortString;
    int len;
    int i;
    
    trimGiven = TrimStr(nameGiven);
    
    len = trimGiven.size();
    
    if (nameGiven == ""){
        name = new char[NAME_DEFAULT.size()+1];
        strcpy(name, NAME_DEFAULT.c_str());

    }else if ((trimGiven.size()>0) and (len <= MAX_CHAR)){
        name = new char[len+1];
        strcpy(name, trimGiven.c_str());
   
    }else if((trimGiven.size()>0) and (len > MAX_CHAR)){
        name = new char[MAX_CHAR+1];
        shortString = trimGiven.substr(0,10);
        strcpy(name, shortString.c_str());
    }
    return;
}

//updates hp
int CreatureClass::UpdateHP(int modification){
		hp = hp+modification;
    return hp;
}


//output function
void CreatureClass::Write(ostream & out)const{
    
    out << Name() << DEL 
    <<"(" << Row() << "," << Col() << ")" << DEL 
    << HP() << DEL << '[';
    
    for (int i=0; i<NUM_ABILITY; i++){
        if(i==NUM_ABILITY-1)
            out<<ability[i];
        else
            out<<ability[i]<<DEL;
    }
    out << ']' << DEL;
    
    //skills
    int len = skills.size();
    out << '(';
    for(int j=0; j< len; j++){
        out << (skills[j]);
        
         if (j != (len-1)){
                         
         out <<',';
         }
        
    }
    out << ')';
    
    out << DEL;
    
    
    //out armor
    if(armor != NULL){
        out << Armor()<< DEL;
    }else {
        out <<DEL;
    }
    
    //out weapon
    if(weapon != NULL){
        out << Weapon()<< DEL;
    }else {
        out <<DEL;
    }
    
    out << endl;
    
    return;
}

//returns weapon as string
string CreatureClass::Weapon ()const{
	string returnString = "";
    
    if (weapon != NULL){
       returnString = weapon -> Name();
    }
	return returnString;
}
//returns armor as string
string CreatureClass::Armor () const{
	string returnString = "";
    
    if (armor != NULL){
       returnString = armor -> Name();
    }
    
	return returnString;
}
//returns true if has a weapon
bool CreatureClass::HasWeapon () const{
	
	return (weapon != NULL);
}
//returns true is has armor
bool CreatureClass::HasArmor () const{
	
	return (armor != NULL);
}
//returns location of old weapon
WeaponClass * CreatureClass::FindWeapon (WeaponClass * wpn){
    WeaponClass * returnWeapon = NULL;
    
    if (Active() and (wpn != NULL)){
        returnWeapon = weapon;
        weapon = wpn;
    }else if (!Active()){
        returnWeapon = wpn;
    }

    return returnWeapon;
}
//returns location of old armor
ArmorClass*  CreatureClass::FindArmor (ArmorClass * armorGiven){
    ArmorClass * returnArmor = NULL;
    
    if (Active() and armorGiven!=NULL){
            returnArmor = armor;
            armor = armorGiven;
    }else if (!Active()){
        returnArmor = armorGiven;
    }
    
    return returnArmor;
}

//returns address of old equipment
EquipClass*  CreatureClass::FindEquipment (EquipClass * equipGiven){
    
    WeaponClass * wpnTmp = NULL;
    ArmorClass * armorTmp = NULL;
    
    wpnTmp = dynamic_cast<WeaponClass*>(equipGiven);
    armorTmp = dynamic_cast<ArmorClass*>(equipGiven);
    
    if(equipGiven != NULL){
        if (WeaponClass::IsEquipment(equipGiven->Name())){
            return FindWeapon(wpnTmp);
        }
        if (ArmorClass::IsEquipment(equipGiven->Name())){
            return FindArmor(armorTmp);
        }
    }else{
        return NULL;
    }
    
}
//returns location of lost weapon
WeaponClass * CreatureClass::LoseWeapon (){
    WeaponClass * returnWeapon = NULL;
    
    if (weapon != NULL){
        returnWeapon = weapon;
        weapon = NULL;
    }
    return returnWeapon;
}
//returns location of lost armor
ArmorClass* CreatureClass::LoseArmor (){
    ArmorClass * returnArmor = NULL;
    
    if(armor != NULL){
        returnArmor = armor;
        armor = NULL;
    }
    return returnArmor;
}
//returns location of lost equipment
EquipClass * CreatureClass::LoseEquipment(){
    
    if(weapon != NULL){
        return LoseWeapon();
    }else if(armor != NULL){
        return LoseArmor();
    }else{
        return NULL;
    }
}

//adds skill to vector
bool CreatureClass::AddSkill (string skill){
    bool returnBool = false;
    bool inSkills = false;
    bool inVector = false;
    int i=0;
    string upperString;
    
    upperString = Ucase(skill);
    
    //for personal skills
    for (i=0; i<skills.size() and !inVector; i++){
        if(skills[i] == upperString){
            inVector = true;
        }
    }
    if(inVector)
        returnBool = true;
    
    else if(Active()){
        
        for (i=0; i<skillsFile.size() and !inSkills;i++){
            if(skillsFile[i].skill == upperString){
                inSkills=true;
                skills.push_back(skillsFile[i].skill);
                returnBool = true;
            }
        }
        
    }else{
        returnBool=false;
    }
    
    return returnBool;
    
}
//rolls dice for skillcheck
int CreatureClass::SkillCheck (string skill){
    int returnInt = 0;
    int i = 0;
    bool skillCheck=false;
    bool found = false;
    AbilityType abilType;
    string upperString;
    
    upperString = Ucase(skill);
    
    if (!Dead()){
        //check if in skills vetor
        for (i=0; i<skills.size(); i++){
            if(skills[i] == upperString)
                skillCheck = true;
        }
        if(skillCheck == true){
            //read file until read equal skillGiven
            for(i=0;i<skillsFile.size() and found == false; i++){
                if (skillsFile[i].skill == upperString){
                    abilType=skillsFile[i].abil;
                    found = true;
                    
                }
            }
            returnInt = Dice::Roll(Name(), GameSpace::SKCK,1,20) + AbilityMod(abilType);
            
            
        }else
            returnInt = 0;
        
        
    }else
        returnInt = 0;
    
    return returnInt;
}
//clears skills
void CreatureClass::Amnesia (){
    skills.clear();
    return;
}
//returns vector skills
vector<string> CreatureClass::Skills () const{
	return skills;
}
//returns ability
vector<int> CreatureClass::Abilities () const{
	vector<int> returnVec;
	
	for (int i=0; i<NUM_ABILITY; i++){
		returnVec.push_back(ability[i]);
	}
	
	return returnVec;
}
//upercase and trims given string
CreatureClass::AbilityType CreatureClass::StringToAbility(string abilityGiven){
	AbilityType returnAbility;
// 	DEX, CON, INT, CHA, STR, WIS
    
    if(abilityGiven == "DEX"){
        returnAbility = DEX;
    }else if(abilityGiven == "CON"){
        returnAbility = CON;
    }else if(abilityGiven == "INT"){
        returnAbility = INT;
    }else if(abilityGiven == "CHA"){
        returnAbility = CHA;
    }else if(abilityGiven == "STR"){
        returnAbility = STR;
    }else if(abilityGiven == "WIS"){
        returnAbility = WIS;
    }else{
        throw INVALID_ABILITY;
    }
    
    return returnAbility;
}

//calculates InitiativeCheck
int CreatureClass::InitiativeCheck() const{
    int returnInt=0;
    
    if(Active()){
        returnInt = Dice::Roll(Name(),GameSpace::INIT,1,20) + AbilityMod(DEX);
    }
    return returnInt;
}

//returns defense count
int CreatureClass::Defense(){
    int returnInt = 0;
    
    if (Active() and (armor!= NULL)){
        returnInt = 10 + AbilityMod(DEX) + armor ->Bonus();
    }else if(armor==NULL){ 
        returnInt = 10+ AbilityMod(DEX);
    }
    
    return returnInt;
    
}
//returns damage count
int CreatureClass::Damage(){
    int returnInt = 0;
    
    if (Active() and weapon!=NULL){
        if(weapon->IsMelee()){
            returnInt = weapon->Damage(Name())+ AbilityMod(STR);
        }else if(weapon->IsRange()){
            returnInt = weapon->Damage(Name());
        }
    }else if(Active() and weapon ==NULL){
        returnInt = AbilityMod(STR);
    }
    return returnInt;
}

void CreatureClass::InitSkillsFile(){
    if (skillsFile.size()== 0){
        fstream infile;
        string abilStr;
        string curLine;
        SkillRec tmpRec;
        RollType tmpRoll;
        
        infile.open("skills.in");
        
        //go through skills.in
        while(infile){
            getline(infile, curLine, DEL);
            getline(infile, abilStr);
            tmpRoll = GameSpace::StrToRoll(abilStr);
            curLine=Ucase(curLine);
            tmpRec.skill = curLine;
            tmpRec.abil = AbilityType(tmpRoll);
            
            skillsFile.push_back(tmpRec);
        }
        infile.close();
    }
    return;
}

//copy constructor
void CreatureClass::CopyIntoMe(const CreatureClass& c){
        if (c.name != NULL){
            int size = strlen(c.name);
            name = new char [MAX_CHAR+1];
            strcpy(name,c.name);
        }
        
        for (int i = 0; i < NUM_ABILITY; i++){
            ability[i] = c.ability[i];
        }
        
        skills.clear();
        for (int j = 0; j < c.skills.size(); j++){
            skills.push_back(c.skills[j]);
        }
        
        if (c.armor != NULL){
            armor = new ArmorClass(*c.armor);
        }
        
        if (c.weapon != NULL){
            weapon = new WeaponClass(*c.weapon);
        }
        cell.row = c.cell.row;
        cell.col = c.cell.col;
        hp = c.HP();
        
    return;
}
///////////////////////////////////////////////
//protected methods//
// void CreatureClass::HpRollXpUpdate(string nameGiven, int xpCount, int hitDieGiven){
// // 	int newHP = 0;
// //     newHP = UpdateHP(Dice::Roll(nameGiven, GameSpace::HP, xpCount, hitDieGiven)+ AbilityMod(CON));
// // 
// //     return;
// }
void CreatureClass::InitAbil(int const abilAdj[]){
    for(int i=0; i< NUM_ABILITY; i++){
        ability[i]=abilAdj[i];
    }
    return;
}

void CreatureClass::InitSkills(vector<string> skillsGiven){
    for(int i =0; (i < skillsGiven.size()) and skillsGiven[i]!=""; i++)
        skills.push_back(skillsGiven[i]);
    return;
}
void CreatureClass::InitHP(int initHP){
    if(initHP!=0)    
        hp=initHP;
    else
        hp=1;
    return;
}

///////////////////////////////////////////////

///////////////////////////////////////////////
//overloaded assignment operators in class//
//returns true if the name is =
bool CreatureClass::operator== (const CreatureClass& c){
    string ownName;
    string nameGiven;
	
    ownName = Ucase(Name());
    nameGiven = Ucase(c.Name());
	
	return (ownName == nameGiven);
}
//returns true if the names are !=
bool CreatureClass::operator!= (const CreatureClass& c){
	string ownName;
    string nameGiven;
    
    ownName = Ucase(Name());
    nameGiven = Ucase(c.Name());
	
	return (ownName != nameGiven);
}
//returns true if the names are <
bool CreatureClass::operator< (const CreatureClass& c){

    return (not Cmp(c.Name(),Name()));
}
//returns true if the names are <=
bool CreatureClass::operator<= (const CreatureClass& c){
   
    
    return (Cmp(Name(),c.Name()));
}
//returns true if the names are >
bool CreatureClass::operator> (const CreatureClass& c){
    
    return (not(Cmp(Name(),c.Name())));
    
}
//returns true if the names are >=
bool CreatureClass::operator>= (const CreatureClass& c){

    
    return (Cmp(c.Name(),Name()));
}
CreatureClass & CreatureClass::operator= (const CreatureClass& c){
    
    if(this != &c){
        if (name != NULL){
            delete[] name;
        }
        if (armor != NULL){
            delete armor;
        }
        if (weapon != NULL){
            delete weapon;
        }
        
        CopyIntoMe(c);
    }
    
    return *this;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//overloaded assignment operators outside of class/
ostream& operator << (ostream& out, const CreatureClass& c){
    c.Write(out);
    return out;
}
///////////////////////////////////////////////
