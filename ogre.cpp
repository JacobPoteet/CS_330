/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Ogre class for D&D game, Quest for Elgeon
 * Made 10/26/16
 * Updated 11/14/16
 * Ogre Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */

#include<iostream>
#include<string>
#include "ogre.h"

using namespace std;
using namespace GameSpace;

///////////////////////////////////////////////
//constants//
const string Ogre::RACE = "OGRE";
const int Ogre::MON_ABILITY_COUNT/*= 6*/;//declared in .h
const int Ogre::ABIL_ADJ[MON_ABILITY_COUNT] = {8,        15,      6,      7,      21,    10};
const int Ogre::HIT_DIE[3]={4,8,8};
const int Ogre::SAVE_THROW[3]={6,0,1};
const int Ogre::BASE_ATT_BONUS[2]={8,1};
const string Ogre::INIT_EQUIP[2]={"SPIKED BANDS", "SPEAR"};
const int Ogre::NUM_INIT_SK /*= 3*/;
const string Ogre::INIT_SKILLS [NUM_INIT_SK] = {"INTIMIDATE" ,"LISTEN" ,"SPOT"};
///////////////////////////////////////////////

///////////////////////////////////////////////
//public constructors//
Ogre::Ogre(string nameGiven):Monster(nameGiven, ABIL_ADJ, HIT_DIE){
    vector<string> tmpVec;
    for(int i = 0; i < NUM_INIT_SK; i++)
        tmpVec.push_back(INIT_SKILLS[i]);
        
        InitSkills(tmpVec);
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string Ogre::Race_Str() const{
    return RACE;
}
vector<string> Ogre::EquipInitialList() const{
    vector<string> returnVec;
    int i =0;
    
    for (i =0; i < 2; i++){
        returnVec.push_back(INIT_EQUIP[i]);
    }
    GameSpace::Sort(returnVec);
    return returnVec;
}
int Ogre::AttackRoll() const{
    return Monster::AttackRoll(BASE_ATT_BONUS);
}
int Ogre::SavingThrow(SavingThrowType kind) const{
    int returnInt = 0;
    int saveBonus = 0;
    
    if(kind > WILL or kind < FORT)
            throw INVALID_SAVINGTHROW;
    
    if(Active()){
        
        saveBonus = Dice::Roll(Name(),GameSpace::SVTH,1,20); 
        switch(kind){
            case FORT:
                returnInt = saveBonus + SAVE_THROW[0]+AbilityMod(CON);
                break;
            case REFLEX:
                returnInt = saveBonus + SAVE_THROW[1]+AbilityMod(DEX);
                break;
            case WILL:
                returnInt = saveBonus + SAVE_THROW[2]+AbilityMod(WIS);
                break;
        };
    }
    
    return returnInt;
}

void Ogre::Write(ostream & out)const{
    out << Race_Str() << DEL;
    Monster::Write(out);
    return;
}

Ogre* Ogre::Clone() const{
    return new Ogre(*this);
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//private constructors//
Ogre::Ogre():Monster(NAME_DEFAULT, ABIL_ADJ, HIT_DIE){
    
}
///////////////////////////////////////////////

