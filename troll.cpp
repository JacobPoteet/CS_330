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

#include<iostream>
#include<string>
#include "troll.h"

using namespace std;
using namespace GameSpace;


///////////////////////////////////////////////
//constants//
const string Troll::RACE = "TROLL";
const int Troll::MON_ABILITY_COUNT/*= 6*/;//declared in .h
const int Troll::ABIL_ADJ[MON_ABILITY_COUNT] = {14,       23,      6,      6,      23,     9};
const int Troll::HIT_DIE[3]={6,8,36};
const int Troll::SAVE_THROW[3]={11,4,3};
const int Troll::BASE_ATT_BONUS[2]={9,1};
const string Troll::INIT_EQUIP[2]={"THICK SKIN","CLUB"};
const int Troll::NUM_INIT_SK/* = 2*/;
const string Troll::INIT_SKILLS [NUM_INIT_SK] ={"LISTEN"    ,"SPOT"};
///////////////////////////////////////////////

///////////////////////////////////////////////
//public constructors//
Troll::Troll(string nameGiven):Monster(nameGiven, ABIL_ADJ, HIT_DIE){
    vector<string> tmpVec;
    for(int i = 0; i < NUM_INIT_SK; i++)
        tmpVec.push_back(INIT_SKILLS[i]);
        
        InitSkills(tmpVec);
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string Troll::Race_Str() const{
    return RACE;
}
vector<string> Troll::EquipInitialList() const{
    vector<string> returnVec;
    int i =0;
    
    for (i =0; i < 2; i++){
        returnVec.push_back(INIT_EQUIP[i]);
    }
    GameSpace::Sort(returnVec);
    return returnVec;
}
int Troll::AttackRoll() const{

    return Monster::AttackRoll(BASE_ATT_BONUS);
}

int Troll::SavingThrow(SavingThrowType kind) const{
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

void Troll::Write(ostream & out)const{
    out << Race_Str()<< DEL;
    Monster::Write(out);
}

Troll* Troll::Clone() const{
    return new Troll(*this);
}
///////////////////////////////////////////////


///////////////////////////////////////////////
//private constructors//
Troll::Troll():Monster(NAME_DEFAULT, ABIL_ADJ, HIT_DIE){
    
}
///////////////////////////////////////////////
