/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 3
 * Creates humanoid class for D&D game, Quest for Elgeon
 * Made 10/26/16
 * Updated 11/14/16
 * Humanoid Class header file
 * Help from: chris, austin, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, austin, adam, ben
 * Dan and i worked a lot on this file together. we tried to only share ideas but in some places its hard to get differnt code.
 */

#include <vector>
#include "cc4.h"
#include "humanoid.h"
#include "voc.h"

using namespace std;
using namespace GameSpace;

//for HUM_SKILL_DEF array declaration
const int Humanoid::SKILL_COUNT = 3;
///////////////////////////////////////////////
//constants//
const string Humanoid::HUM_SKILL_DEF[VocRules::VOC_MAX][SKILL_COUNT]= {
    /*None*/    {""            ,""                  ,""},
    /*BARB*/    {"CLIMB"        ,"LISTEN"            ,"SWIM"},
    /*CLERIC*/  {"HEAL"         ,"USE MAGIC DEVICES" , "" },
    /*FIGHTER*/ {"INTIMIDATE"   ,"SWIM"              ,"" },
    /*ROGUE*/   {"BLUFF"        ,"CLIMB"             ,"HIDE" },
    /*WIZARD*/  {"CONCENTRATION","HIDE"              ,"USE MAGIC DEVICES"}
};
const int Humanoid::XP_DEFAULT=0;
const int Humanoid::UPDATE_XP_COUNT=1;
const int Humanoid::LEVEL_DEFAULT=1;
const VocRules::VocType Humanoid::VOC_DEFAULT=VocRules::NNE;
const int Humanoid::HUM_DIE_COUNT = 3;
const int Humanoid::HUM_DIE_FACE = 6;
const int Humanoid::MIN_VAL = 0;
///////////////////////////////////////////////

///////////////////////////////////////////////
//destructor//
Humanoid::~Humanoid(){
    for (int i = 0; i < pack.size(); i++){
        delete pack[i];
        pack[i] =NULL;
    }
    pack.clear();
    return;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//public methods//
//returns creature xp
long Humanoid::XP() const{
    return xp;
}

//returns creature gp
long Humanoid::GP() const{
    return gp;
}

//returns creature level
int Humanoid::Level() const{
    return level;
}



//updates gp
long Humanoid::UpdateGP(long value){
    if((gp+value)>MIN_VAL){
        if (not CreatureClass::Dead()){
                gp = gp + value;
        }
    }
    return gp;
}


//updates xp and levels
long Humanoid::UpdateXP(long value){
    int hitDie=0;
    int throwHP = 0;
    
    VocRules *vrPtr = VocRules::GetVocRules( );
    
    
    if (not Dead() and (value >MIN_VAL)){
        xp = xp + value;
        while(xp >= VocRules::XPforPromotion(Level()+1) and (Level() < VocRules::LEVEL_MAX)){
            level++;
            hitDie=vrPtr->VocRules::HitDie(voc);
            throwHP = (Dice::Roll(Name(), GameSpace::HP, UPDATE_XP_COUNT, hitDie)+ AbilityMod(CON));
            if(throwHP < 1){
                throwHP = 1;
            }
            UpdateHP(throwHP);
        }
    }
    vrPtr->VocRules::DeleteVocRules();
    return xp;
}

//outputs
void Humanoid::Write(ostream & out)const{
    out << Voc_Str() << DEL;
    CreatureClass::Write(out);
    vector<string> sortedVec;
    
    out << '\t';
    
    out << Level() << DEL << XP() << DEL << GP() << DEL << '(';
    
    if(pack.size()>0){
        sortedVec = Pack();
        
        for (int l = 0; l < sortedVec.size()-1; l++){
            out << sortedVec[l];
            out << ',';
        }
        out <<sortedVec[sortedVec.size()-1];
    }
    out << ')' << DEL << endl;
    return;
}


//returns creature voc
int Humanoid::Voc() const{
    return voc;
}
//returns voc as string
string Humanoid::Voc_Str() const{
    return VocRules::VocToStr(voc);
}
//finds equipment given
WeaponClass* Humanoid::FindWeapon (WeaponClass * wpn){
    WeaponClass * returnWeapon = NULL;
    WeaponClass * tmpWeapon = NULL;
    
    if (Active() and (wpn != NULL)){
        tmpWeapon = CreatureClass::FindWeapon(wpn);
        if(tmpWeapon != NULL){
            pack.push_back(tmpWeapon);
        }
    }else if (!Active()){
        returnWeapon = wpn;
    }
    
    return returnWeapon;
}

// 
ArmorClass*  Humanoid::FindArmor (ArmorClass * armorGiven){
    ArmorClass * returnArmor = NULL;
    ArmorClass * tmpArmor = NULL;
    
    if (Active() and(armorGiven != NULL)){
        tmpArmor = CreatureClass::FindArmor(armorGiven);
        if (tmpArmor != NULL){
            pack.push_back(tmpArmor);
        }
    }else if (!Active()){
        returnArmor = armorGiven;
    }
    
    return returnArmor;
}


EquipClass*  Humanoid::FindEquipment (EquipClass * equipGiven){
    
    return CreatureClass::FindEquipment(equipGiven);
    
}

vector<string> Humanoid::Pack() const{
	vector<string> returnVec;
	
	for (int i=0; i < pack.size(); i++){
		returnVec.push_back(pack[i]->Name());
        
	}
	GameSpace::Sort(returnVec);
	return returnVec;
}

vector<string> Humanoid::EquipInventory() const{
	vector<string> returnVec;
    
    returnVec = Pack();
    
    if (HasWeapon()){
        returnVec.push_back(Weapon());
    }
    if (HasArmor()){
        returnVec.push_back(Armor());
    }
    
    return returnVec;
	
}

bool Humanoid::ChangeEquipment(string equipmentName){
    bool returnBool = false;
    string equipGiven = Ucase(equipmentName);
    EquipClass * tmp = NULL;
     
    if(Active()){
        for (int i = 0; i < pack.size(); i++){
            if (pack[i]->Name() == equipGiven){
                
                tmp = FindEquipment(pack[i]);
                pack.erase(pack.begin()+i);
                returnBool = true;
            }
        }
        
    }
    if (Armor() == equipGiven or Weapon() ==equipGiven){
            returnBool = true;
        }
    
    return returnBool;
}

EquipClass* Humanoid::BuyEquipment(EquipClass* equipGiven){
    EquipClass* returnEquip = NULL;
    
    if(equipGiven!=NULL){
        if (equipGiven->Cost() > GP() or !Active()){
            returnEquip = equipGiven;
        }else if(equipGiven->Cost() <= GP()){
            gp -= equipGiven->Cost();
            returnEquip = FindEquipment(equipGiven);
        }
    }
    return returnEquip;
}

EquipClass* Humanoid::SellEquipment(string equipGiven){
    EquipClass * returnEquip = NULL;
    bool ownsEquip = false;
    int i = 0;
    int foundLocation = 0;
    
    equipGiven = Ucase(equipGiven);
    
    if(equipGiven !=""){
        if(Active()and !ownsEquip){
            for (i = 0; i < pack.size() and !ownsEquip; i++){
                if(pack[i]->Name() == equipGiven){
                    ownsEquip = true;
                    foundLocation = i;
                }
            }
            if (!ownsEquip){
                if(Weapon() == equipGiven){
                    returnEquip =LoseWeapon();
                    if(returnEquip != NULL);
                    UpdateGP(returnEquip->Cost());
                }else if(Armor() == equipGiven){
                    returnEquip = LoseArmor();
                    if(returnEquip != NULL);
                    UpdateGP(returnEquip->Cost());
                }
            }
        }
        if(Active() and ownsEquip){
            gp += pack[foundLocation]->Cost();
            returnEquip = pack[foundLocation];
            pack.erase(pack.begin()+foundLocation);
        }
        
    }
    return returnEquip;
}
    
int Humanoid::AttackRoll() const{
    int returnInt = 0;
    
    returnInt = Dice::Roll(Name(), GameSpace::ATT, 1, 20) + AttackBonus();
    return returnInt;
    
}
int Humanoid::SavingThrow(SavingThrowType KindofThrow) const{
    int returnInt = 0;
    int baseSave = 0;
    int saveBonus = 0;
    
    if(KindofThrow > WILL or KindofThrow < FORT)
            throw INVALID_SAVINGTHROW;
    
    if(Active()){
        VocRules *vrPtr = VocRules::GetVocRules( );
        
       saveBonus = Dice::Roll(Name(),GameSpace::SVTH,1,20); 
        baseSave = vrPtr->BaseSaveBonus(voc,Level(),KindofThrow);
        switch(KindofThrow){
            case FORT:
                returnInt = saveBonus + baseSave+AbilityMod(CON);
                break;
            case REFLEX:
                returnInt = saveBonus + baseSave+AbilityMod(DEX);
                break;
            case WILL:
                returnInt = saveBonus + baseSave+AbilityMod(WIS);
                break;
        };
        
        vrPtr->VocRules::DeleteVocRules();
    }
    
    return returnInt;
}


///////////////////////////////////////////////



///////////////////////////////////////////////
//private methods//
Humanoid::Humanoid():CreatureClass(CreatureClass::NAME_DEFAULT){
}

void Humanoid::SetVoc(VocRules::VocType vocGiven, VocRules::VocType const DEF_VOC){
    
    if(vocGiven == VocRules::NNE){
        voc=DEF_VOC;
    }else if((vocGiven > VocRules::VOC_MAX) or (vocGiven <= VocRules::NNE)){
        throw GameSpace::INVALID_VOC;
    }else{
        voc=vocGiven;
    }
    
//     
    return;
}


void Humanoid::CopyIntoMe(const Humanoid & h){
    /*
    int level;
    long xp;
	long gp;
	VocRules::VocType voc;
	vector<EquipClass *> pack;*/
    
    int i =0;
    
    voc = h.voc;
    level=h.level;
    xp=h.xp;
    gp=h.gp;
    WeaponClass* wpnTmp = NULL;
    ArmorClass* armTmp = NULL;
    
    
    
    
    for(i=0; i< h.pack.size(); i++){
        if(h.pack[i]!=NULL){
            wpnTmp = dynamic_cast<WeaponClass*>(h.pack[i]);
            armTmp = dynamic_cast<ArmorClass*>(h.pack[i]);
            if(wpnTmp != NULL){
                pack.push_back(new WeaponClass(*wpnTmp));
            }else if(armTmp != NULL){ 
                pack.push_back(new ArmorClass(*armTmp));
            }
        }
    }
    
    
    
    return;
}

int Humanoid::AttackBonus() const{
    int returnInt = 0;
    
    VocRules *vrPtr = VocRules::GetVocRules( ); 	// Get ptr to singleton instance of VocRules
    returnInt = vrPtr->VocRules::BaseAttackBonus(voc,level);
    
    if (WeaponClass::IsMelee(Weapon())){
        returnInt +=  AbilityMod(STR);
        
    }else if(WeaponClass::IsRange(Weapon())){
        returnInt += AbilityMod(DEX);
    }else{
        returnInt += AbilityMod(STR);
    }
    
    vrPtr->VocRules::DeleteVocRules();
    
    return returnInt;
}
///////////////////////////////////////////////


///////////////////////////////////////////////
//protected constuctors//
Humanoid::Humanoid(string nameGiven, VocRules::VocType vocGiven, VocRules::VocType const DEF_VOC, int const abilAdj[]):CreatureClass(nameGiven){
    
    SetVoc(vocGiven, DEF_VOC);
    
    level=LEVEL_DEFAULT;
    xp=XP_DEFAULT;
    Humanoid::InitAbil(abilAdj);
    
    SetSkills();
    return;
}
Humanoid::Humanoid(const Humanoid& h):CreatureClass(h){
    CopyIntoMe(h);
    return;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//protected functions//
void Humanoid::SetSkills(){
    int hitDie=0;
    int newHP=0;
    vector <string> tmpSkill;
    
    //gp
    gp = Dice::Roll(Name(), GameSpace::GP, 1,4);
    
    //roll for hp
    VocRules *vrPtr = VocRules::GetVocRules( ); 	// Get ptr to singleton instance of VocRules
    hitDie = vrPtr->VocRules::HitDie(voc);
    //roll = Dice::Roll(forWho, forWhat, numDice, numDiceFaces);
    newHP= Dice::Roll(Name(),GameSpace::HP, 1, hitDie) + AbilityMod(CON);
    InitHP(newHP);
    if (HP() <= 0){
        InitHP(1);
    }
    vrPtr->VocRules::DeleteVocRules();
    
    for (int i = 0; i <SKILL_COUNT and HUM_SKILL_DEF[Voc()][i] !=  ""; i++)
        tmpSkill.push_back(HUM_SKILL_DEF[Voc()][i]);
    InitSkills(tmpSkill);
    
    return;
}
void Humanoid::InitAbil(int const ABIL_ADJ[]){
    int tmpAbil[6];
    for (int i = 0; i< 6; i++){
        tmpAbil[i] = Dice::Roll(Name(), GameSpace::RollType(i), HUM_DIE_COUNT,HUM_DIE_FACE)+ABIL_ADJ[i];
    }
    CreatureClass::InitAbil(tmpAbil);
    
    return;
}

Humanoid & Humanoid::operator= (const Humanoid& h){
    if (this!=&h){
        for (int i=0; i< pack.size(); i++){
            
            if(pack[i]!=NULL){
                delete pack[i];
            }
        }
        pack.clear();
        
        CopyIntoMe(h);
    }
    return *this;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
// //
///////////////////////////////////////////////
