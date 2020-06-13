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

#include "handle4.h"
#include <iostream>
#include <string>

using namespace std;
using namespace GameSpace;

const string Creature::RACE_STR[6] = {"HUMAN", "ELF","HALFELF","ORC","TROLL","OGRE"};
///////////////////////////////////////////////
//constructors//
Creature::~Creature(){
    if (ccPtr !=NULL){
		delete ccPtr;
	}
}

Creature::Creature(string nameGiven, RaceType raceGiven, VocRules::VocType vocGiven):ccPtr(NULL){
    switch(raceGiven){
        case HUMAN:
            ccPtr = new Human(nameGiven,vocGiven);
            break;
        case ELF:
            ccPtr = new Elf(nameGiven,vocGiven);
            break;
        case HALFELF:
            ccPtr = new HalfElf(nameGiven,vocGiven);
            break;
        case ORC:
            ccPtr = new Orc(nameGiven,vocGiven);
            break;
        case OGRE:
            ccPtr = new Ogre(nameGiven);
            break;
        case TROLL:
            ccPtr = new Troll(nameGiven);
            break;
        default:
            ccPtr = new Human(nameGiven,vocGiven);
    }
}

Creature::Creature(const Creature& c):ccPtr(NULL){
    CopyIntoMe(c);
}

Creature::Creature(CreatureClass* ptr):ccPtr(NULL){
    if (ptr){
        ccPtr = ptr-> Clone();
    }
}

Creature::Creature():ccPtr(NULL){
    
}

void Creature::CopyIntoMe(const Creature & c){
    if (c.ccPtr){
        ccPtr = c.ccPtr->Clone();
    }
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//


string Creature::Race_Str() const{
    string returnString = "";
    
    if(dynamic_cast<Human*>(ccPtr)){
        Human* h = dynamic_cast<Human*>(ccPtr);
        returnString =  h->Race_Str();
    }else if(dynamic_cast<Elf*>(ccPtr)){
        Elf* e = dynamic_cast<Elf*>(ccPtr);
        returnString = e->Race_Str();
    }else if(dynamic_cast<HalfElf*>(ccPtr)){
        HalfElf* he = dynamic_cast<HalfElf*>(ccPtr);
       returnString =  he->Race_Str();
    }else if(dynamic_cast<Orc*>(ccPtr)){
        Orc* o = dynamic_cast<Orc*>(ccPtr);
       returnString =  o->Race_Str();
    }else if(dynamic_cast<Ogre*>(ccPtr)){
        Ogre* og = dynamic_cast<Ogre*>(ccPtr);
       returnString =  og->Race_Str();
    }else if(dynamic_cast<Troll*>(ccPtr)){
        Troll* t = dynamic_cast<Troll*>(ccPtr);
       returnString =  t->Race_Str();
    }
    
    
    return returnString;
}

int Creature::Race() const{
    int returnInt = 0;
    
    for (int i = 0; i < 6; i++){
        if (Race_Str() == RACE_STR[i]){
            returnInt = i;
        }
    } 
    return returnInt;
}

bool Creature::IsHumanoid() const{
    bool returnBool = false;
    
    Humanoid * humanoidPtr = dynamic_cast<Humanoid*>(ccPtr);
    
    if (humanoidPtr) {
        returnBool = true;
    }
    
    return returnBool;
}

bool Creature::IsMonster()const{
    bool returnBool = false;
    
    Monster * monsterPtr = dynamic_cast<Monster*>(ccPtr);
    
    if (monsterPtr) {
        returnBool = true;
    }
    
    return returnBool;
}

string Creature::Name() const{
    if (ccPtr){
        return ccPtr->Name();
    }
    return "";
    
}


int Creature::Row() const{
    if (ccPtr){
        return ccPtr->Row();
    }
    return 0;
    
}


int Creature::Col() const{
    if (ccPtr){
        return ccPtr->Col();
    }
    return 0;
    
}


int Creature::HP() const{
    if (ccPtr){
        return ccPtr->HP();
    }
    return 0;
    
}

int Creature::Ability(CreatureClass::AbilityType givenAbility){
      if (ccPtr){
          return ccPtr->Ability(givenAbility);
      }
      return 0;
}


bool Creature::Active() const{
    if (ccPtr){
        return ccPtr->Active();
      }
    return false;
}


bool Creature::Dead() const{
    if (ccPtr){
        return ccPtr->Dead();
      }
    return false;
}


bool Creature::Dying() const{
    if (ccPtr){
        return ccPtr->Dying();
      }
    return false;
}


bool Creature::Disabled() const{
    if (ccPtr){
        return ccPtr->Disabled();
      }
    return false;
}


int Creature::AbilityMod(CreatureClass::AbilityType givenAbility) const{
    if (ccPtr){
        return ccPtr->AbilityMod(givenAbility);
    }
    return 0;
}


bool Creature::SetCell(int newRow, int newCol){
    if (ccPtr){
        return ccPtr->SetCell(newRow, newCol);
    }
    return false;
}


int Creature::UpdateHP(int modification){
    if (ccPtr){
        return ccPtr->UpdateHP(modification);
    }
    return 0;
}


void Creature::Write(ostream & out)const{
    if (ccPtr){
        return ccPtr->Write(out);
    }
    return;
}

  
long Creature::XP() const{
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->XP();
    }
    return 0;
}
  

long Creature::GP() const{
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->GP();
    }
    return 0;
}

int Creature::Level() const{
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->Level();
    }
    return 0;
}

long Creature::UpdateGP(long value){
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->UpdateGP(value);
    }
    return 0;
}


long Creature::UpdateXP(long value){
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->UpdateXP(value);
    }
    return 0;
}


string Creature::Weapon() const{
    if (ccPtr){
        return ccPtr->Weapon();
    }
    return "";
}

string Creature::Armor ()const{
    if (ccPtr){
        return ccPtr->Armor();
    }
    return "";
}

bool Creature::HasWeapon (){
    if (ccPtr){
        return ccPtr->HasWeapon();
    }
    return false;
}

bool Creature::HasArmor (){
    if (ccPtr){
        return ccPtr->HasArmor();
    }
    return false;
}

WeaponClass* Creature::FindWeapon (WeaponClass * wpn){

    if (ccPtr){
        return ccPtr->FindWeapon(wpn);
    }
    return wpn;
}

ArmorClass*  Creature::FindArmor (ArmorClass * armorGiven){
    if (ccPtr){
        return ccPtr->FindArmor(armorGiven);
    }
    return armorGiven;
}

EquipClass*  Creature::FindEquipment (EquipClass * equipGiven){
    if (ccPtr){
        return ccPtr->FindEquipment(equipGiven);
    }
    return equipGiven;
}

WeaponClass* Creature::LoseWeapon (){
    if (ccPtr){
        return ccPtr->LoseWeapon();
    }
    return NULL;
}

ArmorClass* Creature::LoseArmor (){
    
    if (ccPtr){
        return ccPtr->LoseArmor();
    }

    return NULL;
}

EquipClass * Creature::LoseEquipment(){
    if (ccPtr){
        return ccPtr->LoseEquipment();
    }
    return NULL;
}

bool Creature::AddSkill (string skill){
    if (ccPtr){
        return ccPtr->AddSkill(skill);
    }
    return false;
}

int Creature::SkillCheck (string skill){
    if (ccPtr){
        return ccPtr->SkillCheck(skill);
    }
    return 0;
}

void Creature::Amnesia (){
    if (ccPtr){
        return ccPtr->Amnesia();
    }
    return;
}

vector<string> Creature::Skills () const{
    vector<string> tmp;
    
    if (ccPtr){
        return ccPtr->Skills();
    }
    return tmp;
}

vector<int> Creature::Abilities ()const{
    vector<int> tmp;
	
	if (ccPtr){
        return ccPtr->Abilities();
    }
    return tmp;
}

vector<string> Creature::EquipInitialList() const{
    vector<string> tmp;
	
	if (ccPtr){
        return ccPtr->EquipInitialList();
    }
    return tmp;
}

int Creature::InitiativeCheck() const{
    if (ccPtr){
        return ccPtr->InitiativeCheck();
    }
    return 0;
}

int Creature::AttackRoll() const{
    if (ccPtr){
        return ccPtr->AttackRoll();
    }
    return 0;
}

int Creature::SavingThrow(GameSpace::SavingThrowType KindofThrow) const{
    if (ccPtr){
        return ccPtr->SavingThrow(KindofThrow);
    }
    return 0;
}

int Creature::Defense(){
    if (ccPtr){
        return ccPtr->Defense();
    }
    return 0;
}

int Creature::Damage(){
    if (ccPtr){
        return ccPtr->Damage();
    }
    return 0;
}

int Creature::Voc() const{
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->Voc();
    }
    return 0;
}

string Creature::Voc_Str() const{
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->Voc_Str();
    }
    return "";
}

vector<string> Creature::Pack() const{
    vector<string> tmp;
    
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->Pack();
    }
    return tmp;
}

vector<string> Creature::EquipInventory() const{
    vector<string> tmp;
    
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->EquipInventory();
    }
    return tmp;
}

bool Creature::ChangeEquipment(string equipmentName){
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->ChangeEquipment(equipmentName);
    }
    return false;
}


EquipClass* Creature::BuyEquipment(EquipClass* equipGiven){
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->BuyEquipment(equipGiven);
    }
    return equipGiven;
}

EquipClass* Creature::SellEquipment(string equipGiven){
    Humanoid* h;
    h = dynamic_cast<Humanoid*>(ccPtr);
    
    if (h){
        return h->SellEquipment(equipGiven);
    }
    return NULL;
}

///////////////////////////////////////////////

///////////////////////////////////////////////
//overloaded assignment operators in class//
bool Creature::operator== (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator==(*c.ccPtr);
    }
    return false;
}

bool Creature::operator!= (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator!=(*c.ccPtr);
    }
    return false;
}

bool Creature::operator< (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator<(*c.ccPtr);
    }
    return false;
}

bool Creature::operator<= (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator<=(*c.ccPtr);
    }
    return false;
}

bool Creature::operator> (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator>(*c.ccPtr);
    }
    return false;
}

bool Creature::operator>= (const Creature& c){
    if(ccPtr and c.ccPtr){
        return ccPtr -> operator>=(*c.ccPtr);
    }
    return false;
}

Creature & Creature::operator= (const Creature& c){
    if(this != &c){
        if(ccPtr != NULL){
            delete ccPtr;
            ccPtr=NULL;
        }
        if (c.ccPtr){
            ccPtr = c.ccPtr->Clone();
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, const Creature creatureGiven){
    creatureGiven.Write(out);
}


///////////////////////////////////////////////
