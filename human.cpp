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

#include "human.h"
#include <iostream>
#include <string>

using namespace std;
using namespace GameSpace;

//////////////////////////////////////////////
//constants//
const string Human::RACE = "HUMAN";
const int Human::HUM_ABIL_COUNT/*=6*/;//declaration in .h
const int Human::ABIL_ADJ[HUM_ABIL_COUNT] = {0,        0,       0,      0,      0,      0};
const VocRules::VocType Human::VOC_DEFAULT = VocRules::FTR;
const int Human::NUM_INIT_EQUIP;//declaration in .h
const string Human::INIT_EQUIP[VocRules::VOC_MAX][NUM_INIT_EQUIP] = {
    /*None*/    {""                    ,""               ,""},
    /*BARB*/    {"STUDDED LEATHER"     ,"DAGGER"         ,"SHORT BOW"},
    /*CLERIC*/  {"LARGE WOODED SHIELD" ,"CROSSBOW"       ,"MACE" },
    /*FIGHTER*/ {"LARGE WOODED SHIELD" ,"SWORD"          ,"" },
    /*ROGUE*/   {"LEATHER JACKET"      ,"RAPIER"         ,"SHORT BOW" },
    /*WIZARD*/  {"CLUB"                ,"DAGGER"         ,"LIGHT CROSSBOW"}
};

//////////////////////////////////////////////

///////////////////////////////////////////////
//constructors//
Human::Human(string nameGiven, VocRules::VocType vocGiven):Humanoid(nameGiven,vocGiven,VOC_DEFAULT, ABIL_ADJ){
    return;
}
Human::Human():Humanoid(NAME_DEFAULT,VOC_DEFAULT, VOC_DEFAULT, ABIL_ADJ){
    return;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string Human::Race_Str() const{
    return RACE;
}
vector<string> Human::EquipInitialList() const{
    vector<string> returnList;
    
    for (int i = 0; (i <NUM_INIT_EQUIP) ; i++){
        if(INIT_EQUIP[Voc()][i] != ""){
            returnList.push_back(INIT_EQUIP[Voc()][i]);
        }
        
    }
    
    return returnList;
}
void Human::Write(ostream & out)const{
    out << Race_Str() << DEL;
	Humanoid::Write(out);
    return;
}

Human* Human::Clone() const {
    return new Human(*this);
}
///////////////////////////////////////////////
