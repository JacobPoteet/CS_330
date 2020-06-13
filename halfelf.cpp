/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates HalfElf class for D&D game, Quest for Elgeon
 * Made 11/1/16
 * Updated 11/14/16
 * HalfElf Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
 
 #include "halfelf.h"
 #include<iostream>
 #include<string>
 
 using namespace std;
 using namespace GameSpace;
 
//////////////////////////////////////////////
//constants//
const string HalfElf::RACE = "HALFELF";
const int HalfElf::HUM_ABIL_COUNT/*=6*/;//declaration in .h
const int HalfElf::ABIL_ADJ[HUM_ABIL_COUNT] = {0,        0,       0,      0,      0,      0};
const VocRules::VocType HalfElf::VOC_DEFAULT = VocRules::ROG;
const int HalfElf::NUM_INIT_EQUIP/*=3*/;//declaration in .h
const string HalfElf::INIT_EQUIP[VocRules::VOC_MAX][NUM_INIT_EQUIP]={
   /*None*/    {""                    ,""               ,""},
   /*BARB*/    {"STUDDED LEATHER"     ,"DAGGER"         ,"SHORT BOW"},
   /*CLERIC*/  {"SMALL WOODED SHIELD" ,"LONG SWORD"     ,""},
   /*FIGHTER*/ {"SMALL WOODED SHIELD" ,"SWORD"          ,""},
   /*ROGUE*/   {"LEATHER JACKET"      ,"RAPIER"         ,"SHORT BOW"},
   /*WIZARD*/  {"CLUB"           ,"LIGHT CROSSBOW"      ,""}
};
//////////////////////////////////////////////

///////////////////////////////////////////////
//constructors//
HalfElf::HalfElf(string nameGiven, VocRules::VocType vocGiven):Humanoid(nameGiven,vocGiven,VOC_DEFAULT, ABIL_ADJ){
    
}
HalfElf::HalfElf():Humanoid(NAME_DEFAULT,VOC_DEFAULT,VOC_DEFAULT,ABIL_ADJ){

}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string HalfElf::Race_Str() const{
    return RACE;
}
vector<string> HalfElf::EquipInitialList() const{
    vector<string> returnList;
    
    for (int i = 0; (i <NUM_INIT_EQUIP); i++){
        if(INIT_EQUIP[Voc()][i] != ""){
        returnList.push_back(INIT_EQUIP[Voc()][i]);
        }
        
    }
    
    return returnList;
}
void HalfElf::Write(ostream & out)const{
    out << Race_Str() << DEL;
    Humanoid::Write(out);
    return;
}

HalfElf* HalfElf::Clone()const{
    return new HalfElf(*this);
}
///////////////////////////////////////////////
