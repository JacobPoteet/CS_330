/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Elf class for D&D game, Quest for Elgeon
 * Made 11/1/16
 * Updated 11/14/16
 * Elf Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
 
 #include "elf.h"
 #include<iostream>
 #include<string>
 
 using namespace std;
 using namespace GameSpace;
 
//////////////////////////////////////////////
//constants//
const string Elf::RACE = "ELF";
const int Elf::HUM_ABIL_COUNT/*=6*/;//declaration in .h
const int Elf::ABIL_ADJ[HUM_ABIL_COUNT] = {2,       -2,       0,      0,      0,      0};
const VocRules::VocType Elf::VOC_DEFAULT = VocRules::WIZ;
const int Elf::NUM_INIT_EQUIP/*=3*/;//declaration in .h
const string Elf::INIT_EQUIP[VocRules::VOC_MAX][NUM_INIT_EQUIP]={
   /*None*/    {""                    ,""               ,""},
   /*BARB*/    {"STUDDED LEATHER"     ,"DAGGER"         ,"SHORT BOW"},
   /*CLERIC*/  {"LARGE WOODED SHIELD" ,"LONG SWORD"     ,"SHORT BOW"},
   /*FIGHTER*/ {"SMALL WOODED SHIELD" ,"SWORD"          ,""},
   /*ROGUE*/   {"LEATHER JACKET"      ,"RAPIER"         ,"SHORT BOW"},
   /*WIZARD*/  {"SHORT BOW"           ,"QUARTER STAFF"  ,""}
};
//////////////////////////////////////////////

///////////////////////////////////////////////
//constructors//
Elf::Elf(string nameGiven, VocRules::VocType vocGiven):Humanoid(nameGiven,vocGiven,VOC_DEFAULT, ABIL_ADJ){
    return;
}
Elf::Elf():Humanoid(NAME_DEFAULT,VOC_DEFAULT,VOC_DEFAULT,ABIL_ADJ){
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string Elf::Race_Str() const{
    return RACE;
}
vector<string> Elf::EquipInitialList() const{
    vector<string> returnList;
    
    for (int i = 0; (i <NUM_INIT_EQUIP) ; i++){
        if(INIT_EQUIP[Voc()][i] != ""){
        returnList.push_back(INIT_EQUIP[Voc()][i]);
        }
        
    }
    
    return returnList;
}
void Elf::Write(ostream & out)const{
    out << Race_Str() << DEL;
	Humanoid::Write(out);
    return;
}

Elf* Elf::Clone() const{
    return new Elf(*this);
}
///////////////////////////////////////////////
