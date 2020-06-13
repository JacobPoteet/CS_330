/*
 * Jacob Poteet
 * CSCI 330 section 1
 * 171
 * program 5
 * Creates handle class for D&D game, Quest for Elgeon
 * Made 12/1/16
 * Updated 12/7/16
 * Database Class header file
 * Help from: chris, tyme, mike, jawaun, ben, gransburry, will
 * Helped: dakota, adam, ben
 */
#include "db5.h"
#include <iostream>
#include <string>

using namespace std;
using namespace GameSpace;

//declaed pointer as null
CreatureDB * CreatureDB::cPtr = NULL;

//constructor
CreatureDB::CreatureDB(){
    
}

//destructor
CreatureDB::~CreatureDB(){
//     if (cPtr != NULL){
//         delete cPtr;
//     }
}

//returns creature pointer
CreatureDB * CreatureDB::GetDB(){
    if(cPtr == NULL){
        cPtr = new CreatureDB();
    }
    return cPtr;
}

//deletes singleton
void CreatureDB::DeleteDB(){
    if (cPtr != NULL){
        delete cPtr;
    }
    cPtr = NULL;
}

//loads creatures into database
bool CreatureDB::LoadDB(istream & inStream){
    char type = ' ';
    char voc = ' ';
    char delTrash = ' ';
    string name="";
    int hp=0;
    int xp=0;
    VocRules::VocType vocGiven;
    bool returnBool = false;
    Creature insertCreature;
    
    //prime stream
    inStream >> type >> delTrash;
    while(inStream){
        
        
        
        if(IfHumanoidLoad(type)){
            inStream >> voc >>delTrash;
            vocGiven = CharToVoc(voc);
            
            getline(inStream,name,DEL);
            
            inStream >> hp >> delTrash;
            inStream >> xp >> delTrash;
            
            insertCreature =  HumanoidLoad(type,vocGiven, name, hp,xp);
            SetCreatureStats(insertCreature);
            cMap.insert(make_pair(name,insertCreature));
            
            returnBool = true;
            
        }else if (IfMonsterLoad(type)){
            getline(inStream,name,DEL);
            inStream >> hp >> delTrash;
            
            insertCreature = MonsterLoad(type, name, hp);
            SetCreatureStats(insertCreature);
            cMap.insert(make_pair(name,insertCreature));
            
            returnBool = true;
        }
        inStream >> type >> delTrash;
    }//end while loop
    
    
    return returnBool;
}

//sets creature stats
void CreatureDB::SetCreatureStats(Creature & creatureGiven){
    ArmorClass * armorTmp = NULL;
    WeaponClass * weaponTmp = NULL;
    vector<string> vectorTmp;
    
    vectorTmp = creatureGiven.EquipInitialList();
    
    
    for(int i = 0; i < vectorTmp.size(); i++){
        if(WeaponClass::IsEquipment(vectorTmp[i])){
            weaponTmp = new WeaponClass(vectorTmp[i]);
            creatureGiven.FindEquipment(weaponTmp);
        }else{
            armorTmp = new ArmorClass(vectorTmp[i]);
            creatureGiven.FindEquipment(armorTmp);
        }
        
    }
    
    return;
}

//if type given is humanoid
bool CreatureDB::IfHumanoidLoad(char typeGiven){
	bool returnBool = false;
	
	switch(typeGiven){
		case 'H':
		case 'E':
		case 'F':
		case 'O':
			returnBool = true;
			break;
	}
	
	return returnBool;
}

//if type given is monster
bool CreatureDB::IfMonsterLoad(char typeGiven){
	bool returnBool = false;
	
	switch(typeGiven){
		case 'T':
		case 'G':
			returnBool = true;
			break;
	}
	
	return returnBool;
}

//takes char to voc for load db
VocRules::VocType CreatureDB::CharToVoc(char vocGiven){
	VocRules::VocType returnVoc;
	
	switch(vocGiven){
		case 'B':
			returnVoc = VocRules::BBN;
			break;
		case 'C':
			returnVoc = VocRules::CLR;
			break;
		case 'F':
			returnVoc = VocRules::FTR;
			break;
		case 'R':
			returnVoc = VocRules::ROG;
			break;
		case 'W':
			returnVoc = VocRules::WIZ;
			break;
	}
	
	return returnVoc;
}

//loads humanoids
Creature CreatureDB::HumanoidLoad(char typeGiven, VocRules::VocType vocGiven, string nameGiven,int hpGiven, int xpGiven){
    
    Creature returnCreature;
    
    switch(typeGiven){
        case 'H':
            returnCreature = Creature(nameGiven,Creature::HUMAN,vocGiven);
            break;
        case 'E':
            returnCreature = Creature(nameGiven,Creature::ELF,vocGiven);
            break;
        case 'F':
            returnCreature = Creature(nameGiven,Creature::HALFELF,vocGiven);
            break;
        case 'O':
            returnCreature = Creature(nameGiven,Creature::ORC,vocGiven);
            break;
        default:
            returnCreature = Creature("ERROR IN HUMANOID LOAD");
    }
    
    if(returnCreature.IsHumanoid())
        returnCreature.UpdateXP(xpGiven/*-returnCreature.XP()*/);
    
    returnCreature.UpdateHP(hpGiven-returnCreature.HP());
    
    
    return returnCreature;
}

//loads monster
Creature CreatureDB::MonsterLoad(char typeGiven, string nameGiven, int hpGiven){
	Creature returnCreature;	
    
    switch(typeGiven){
		case 'T':
			returnCreature =Creature(nameGiven,Creature::TROLL);
			break;
		case 'G':
			returnCreature =Creature(nameGiven,Creature::OGRE);
			break;
		default:
			returnCreature = Creature("ERROR IN monster LOAD");
	}
	
	
	returnCreature.UpdateHP(hpGiven-returnCreature.HP());
	
	
	return returnCreature;
		
}

//outputs the map to outstream parameter
bool CreatureDB::DumpDB (ostream & outStream) const{
    char type = ' ';
    string iterType;
    string vocString;
    char voc = ' ';
    char delTrash = ' ';
    string name="";
    int hp=0;
    int xp=0;
    VocRules::VocType vocGiven;
    bool returnBool = false;
    map<string,Creature>::const_iterator iter;
    
    if(cMap.size() == 0){
        returnBool = false;
    }else{
        
        for (iter = cMap.begin(); iter != cMap.end(); iter++){
			name = iter->first;
            iterType = iter->second.Race_Str();
            type = StrToType(iterType);
            
            outStream << type << DEL;
            
            if(IfHumanoidLoad(type)){
                vocString = iter->second.Voc_Str();
                
                outStream << vocString[0] << DEL << iter->first << DEL;
                outStream << iter->second.HP() << DEL << iter->second.XP()<<DEL;
            }else if(IfMonsterLoad(type)){
                outStream << iter->first << DEL <<iter->second.HP() << DEL;
            }
            outStream << endl;
        }//end iterator
        returnBool = true;
    }//end else
    
    return returnBool;
}

char CreatureDB::StrToType(string typeGiven){
    char returnChar = ' ';
    
    if(typeGiven == "HUMAN"){
        returnChar = 'H';
    }else if(typeGiven == "ELF"){
        returnChar = 'E';
    }else if(typeGiven == "HALFELF"){
        returnChar = 'F';
    }else if(typeGiven == "ORC"){
        returnChar = 'O';
    }else if(typeGiven == "TROLL"){
        returnChar = 'T';
    }else if(typeGiven == "OGRE"){
        returnChar = 'G';
    }
    
    return returnChar;
}

//add creature to db 
bool CreatureDB::Add(const Creature& creatureGiven){
    
    if(cMap.count(creatureGiven.Name()) == 0){
        cMap[creatureGiven.Name()] = creatureGiven;
        return true;
        
    }else{
        return false;
    }
}

//removes entry in db
bool CreatureDB::Remove(const string& CreatureName){
    
    if(cMap.count(CreatureName)){
        cMap.erase(CreatureName);
        return true;
        
    }else{
        return false;
    }
}

//retrives creature and then changes Creature parameter
bool CreatureDB::Retrieve(const string & CreatureName, /*out*/ Creature& creatureGiven) const{
    map<string,Creature>::const_iterator iter;
    
    iter = cMap.find(CreatureName);
    
    if(iter != cMap.end()){
        creatureGiven = iter->second;
        return true;
    }else{
        return false;
    }
}

//deletes all entries in map;
void CreatureDB::MakeEmpty(){
    cMap.clear();
}

//returns true if map is empty
bool CreatureDB::IsEmpty() const{
    return (cMap.empty());
}

//returns humanoid count
int CreatureDB::HumanoidCount() const{
    map<string,Creature>::const_iterator iter;
    int count = 0;
    
    for (iter = cMap.begin(); iter != cMap.end(); iter++){
        if(iter->second.IsHumanoid()){
            count++;
        }   
    }
    
    return count;
}

//returns monster count
int CreatureDB::MonsterCount() const{
    return (cMap.size() - HumanoidCount());
}

//checks armor, weapon, and pack for total equipment
int CreatureDB::EquipCount() const{
    map<string,Creature>::const_iterator iter;
    int returnInt = 0;
    vector<string> tmpPack;
    
    for (iter = cMap.begin(); iter != cMap.end(); iter++){
//         if (iter->second.HasWeapon()){
//             returnInt++;
//         }
//         if(iter->second.HasArmor()){
//             returnInt++;
//         }

        tmpPack = iter->second.Pack();
        returnInt += tmpPack.size();
        tmpPack.clear();
        
        
    }//end loop
    return returnInt;
}

vector<string> CreatureDB::SortByName() const{
    vector<string> returnVec;
    map<string,Creature>::const_iterator iter;
    
    
    for (iter = cMap.begin(); iter != cMap.end(); iter++){
        returnVec.push_back(iter->first);
    }
    
    return returnVec;
}

vector<string> CreatureDB::SortByXP() const{
    vector<string> returnVec;
    vector<pair<int/*xp*/,string/*name*/> > intVec;
    map<string,Creature>::const_iterator iterFirst;
    
    for (iterFirst = cMap.begin(); iterFirst != cMap.end(); iterFirst++){
        intVec.push_back(make_pair(iterFirst->second.XP(),iterFirst->first));
    }
    
	sort(intVec.begin(), intVec.end());
    
    for (int i = 0; i <intVec.size(); i++){
        returnVec.push_back(intVec[i].second);
    }
    
    return returnVec;
}

vector<string> CreatureDB::SortByHP() const{
    vector<string> returnVec;
    vector<pair<int/*xp*/,string/*name*/> > intVec;
    map<string,Creature>::const_iterator iterFirst;
    
    for (iterFirst = cMap.begin(); iterFirst != cMap.end(); iterFirst++){
        intVec.push_back(make_pair(iterFirst->second.HP(),iterFirst->first));
    }
    
	sort(intVec.begin(), intVec.end());
    
    for (int i = 0; i <intVec.size(); i++){
        returnVec.push_back(intVec[i].second);
    }
    
    return returnVec;
}


const pair<const string, Creature>& CreatureDB::operator[] (int index) const{
    map<string,Creature>::const_iterator iter;
    int i = 0;
    
    if(index < 0){
        throw BELOW_VALID_INDEX;
    }else if (index >= cMap.size()){
        throw ABOVE_VALID_INDEX;
    }
    
    
    for (iter = cMap.begin(); i<index; iter++){
        i++;
    }
        return *iter;

}

ostream& operator<<(ostream& out, const CreatureDB* db){
    
    db->Write(out);
    return out;
}

void CreatureDB::Write(ostream & out)const{
    map<string,Creature>::const_iterator iter;
    
    for (iter = cMap.begin(); iter != cMap.end(); iter++){
        iter->second.Write(out);
    }
    
    return;
}
