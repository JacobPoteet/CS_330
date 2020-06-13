/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates human class for D&D game, Quest for Elgeon
 * Made 11/1/16
 * Updated 11/14/16
 * Human Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */

#include "monster.h"
#include<iostream>
#include<string>

using namespace std;
using namespace GameSpace;

//////////////////////////////////////////////
//constants//
const int Monster::MON_COUNT = 2;
const int Monster::ABILITY_COUNT = 6;
///////////////////////////////////////////////

Monster::~Monster(){
    
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
void Monster::Write(ostream & out)const{
    CreatureClass::Write(out);
}

///////////////////////////////////////////////

///////////////////////////////////////////////
//protected constuctors//
Monster::Monster(const Monster & h):CreatureClass(h){
    CreatureClass::CopyIntoMe(h);
}
Monster::Monster(string nameGiven, int const abilAdj[], int const hitDieGiven[]):CreatureClass(nameGiven){
    InitAbilities(abilAdj);
    InitHP(Dice::Roll(Name(), GameSpace::HP, hitDieGiven[0], hitDieGiven[1]) + hitDieGiven[2]);
}

void Monster::InitAbilities(const int abilAdj[]){
    CreatureClass::InitAbil(abilAdj);
    return;
    
}
int Monster::AttackRoll(const int attackBonus[])const{
    int returnInt=0;
    
    returnInt = Dice::Roll(Name(), GameSpace::ATT, 1, 20) + AttackBonus(attackBonus);
    
    
    return returnInt;
    
}
int Monster::AttackBonus(const int baseAttBonus[]) const{
    int returnInt = 0;
    
    
    if (WeaponClass::IsMelee(Weapon())){
        returnInt = baseAttBonus[0] + AbilityMod(STR);
        
    }else if(WeaponClass::IsRange(Weapon())){
        returnInt = baseAttBonus[1] + AbilityMod(DEX);
    }else{
        returnInt += AbilityMod(STR);
    }
    
    return returnInt;
}

///////////////////////////////////////////////
