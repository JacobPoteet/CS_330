/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates Orc class for D&D game, Quest for Elgeon
 * Made 11/1/16
 * Updated 11/14/16
 * Orc Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 */
 
 #include "orc.h"
 #include<iostream>
 #include<string>
 
 using namespace std;
 using namespace GameSpace;
 
//////////////////////////////////////////////
//constants//
const string Orc::RACE = "ORC";
const int Orc::HUM_ABIL_COUNT/*=6*/;//declaration in .h
const int Orc::ABIL_ADJ[HUM_ABIL_COUNT] = {0,        0,      -2,     -2,     +2,     -1};
const VocRules::VocType Orc::VOC_DEFAULT = VocRules::BBN;
const int Orc::NUM_INIT_EQUIP/*=4*/;//declaration in .h
const string Orc::INIT_EQUIP[VocRules::VOC_MAX][NUM_INIT_EQUIP]={
   /*None*/    {""                    ,""               ,""         , ""},
   /*BARB*/    {"STUDDED LEATHER"     ,"DAGGER"         ,"GREAT AXE","SHORT BOW"},
   /*CLERIC*/  {"CROSSBOW"            ,"SHORT SPEAR"    ,""         ,""},
   /*FIGHTER*/ {"LARGE WOODED SHIELD" ,"SWORD"          ,""         ,""},
   /*ROGUE*/   {"LEATHER"             ,"RAPIER"         ,"SHORT BOW",""},
   /*WIZARD*/  {"CLUB"           ,"LIGHT CROSSBOW"      ,""         ,""}
};
//////////////////////////////////////////////

///////////////////////////////////////////////
//constructors//
Orc::Orc(string nameGiven, VocRules::VocType vocGiven):Humanoid(nameGiven,vocGiven,VOC_DEFAULT, ABIL_ADJ){    
    return;
}
Orc::Orc():Humanoid(NAME_DEFAULT,VOC_DEFAULT,VOC_DEFAULT,ABIL_ADJ){
    return;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
string Orc::Race_Str() const{
    return RACE;
}
vector<string> Orc::EquipInitialList() const{
    vector<string> returnList;
    
    for (int i = 0; (i <NUM_INIT_EQUIP) ; i++){
        if(INIT_EQUIP[Voc()][i] != ""){
            returnList.push_back(INIT_EQUIP[Voc()][i]);
        }
        
    }
    
    return returnList;
}
void Orc::Write(ostream & out)const{
    out << Race_Str() << DEL;
    Humanoid::Write(out);
    return;
}

Orc * Orc::Clone() const{
    return new Orc(*this);
}
///////////////////////////////////////////////
