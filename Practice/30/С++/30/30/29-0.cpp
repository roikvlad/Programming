#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
vector<vector<string>> chnums = {
	{"Rune","0,06","10","FIRE"},
	{"Rune","0,07","10","EARTH"},
	{"Rune","0,13","10","WATER"},
	{"Rune","0,14","10","AIR"},
	{"Rune","0,6","5","FIRE"},
	{"Rune","0,7","5","EARTH"},
	{"Rune","1,3","5","WATER"},
	{"Rune","1,4","5","AIR"},
	{"Weapon","1,4","100","0","100"},
	{"Weapon","1,4","75","50","100"},
	{"Armor","2,8","50","100"},
	{"Rune","6","1","FIRE"},
	{"Rune","7","1","EARTH"},
	{"Rune","13","1","WATER"},
	{"Rune","14","1","AIR"},
	{"Coin","50","1000"} };

struct Item {
	enum class ItemType { 
		COIN,
		RUNE,
		WEAPON,
		ARMOR
	}TypeItem;
	union unionType { 

		struct RUNE { 
			unsigned int level;
			enum class Element {
				FIRE,
				WATER,
				EARTH,
				AIR
			}elements;
		} Runes;
		struct COIN { 
			unsigned int count;
		} Coins;
		struct WEAPON {
			unsigned int damage;
			unsigned int critical;
			unsigned int durability;

		} Weapons;
		struct ARMOR { 
			unsigned int guard;
			unsigned int durability;


		} Armors;
	} uniontypes;
};

typedef vector<Item> LootBox; 
Item operator++ (Item& a) {
	float f = rand() % 10000;
	f = f / 100;
	float sum = 0;
	for (int j = 0; j < chnums.size(); j++)
	{
		sum += stof(chnums[j][1]);
		if (f <= sum - 0.01)
		{
			
			if (chnums[j][0] == "Coin")
			{
				a.TypeItem = (Item::ItemType)0;
				a.uniontypes.Coins.count = stoi(chnums[j][2]);
				break;
			}

			if (chnums[j][0] == "Rune")
			{
				a.TypeItem = (Item::ItemType)1;
				a.uniontypes.Runes.level = stoi(chnums[j][2]);
				if (chnums[j][3] == "FIRE") { a.uniontypes.Runes.elements = static_cast<Item::unionType::RUNE::Element>(0); }
				if (chnums[j][3] == "WATER") { a.uniontypes.Runes.elements = static_cast<Item::unionType::RUNE::Element>(1); }
				if (chnums[j][3] == "EARTH") { a.uniontypes.Runes.elements = static_cast<Item::unionType::RUNE::Element>(2); }
				if (chnums[j][3] == "AIR") { a.uniontypes.Runes.elements = static_cast<Item::unionType::RUNE::Element>(3); } break;
			}

			if (chnums[j][0] == "Weapon")
			{
				a.TypeItem = (Item::ItemType)2;
				a.uniontypes.Weapons.damage = stoi(chnums[j][2]);
				a.uniontypes.Weapons.critical = stoi(chnums[j][3]);
				a.uniontypes.Weapons.durability = stoi(chnums[j][4]); break;
			}

			if (chnums[j][0] == "Armor")
			{
				a.TypeItem = (Item::ItemType)3;
				a.uniontypes.Armors.guard = stoi(chnums[j][2]);
				a.uniontypes.Armors.durability = stoi(chnums[j][3]); break;
			}
		}
	}

	return a;
}
LootBox generateLootBox() {
	LootBox LBox;
	LBox.push_back({});
	LBox.push_back({});
	LBox.push_back({});
	++LBox[0];
	++LBox[1];
	++LBox[2];
	return LBox;
}

LootBox operator<<(LootBox out, Item myitem)
{
	out.push_back(myitem);
	return out;
}
ostream& operator<<(ostream& out, Item myitem) 
{

	if (myitem.TypeItem == Item::ItemType::ARMOR)
	{
		out << "Armor of Victory" << endl;
	}

	if (myitem.TypeItem == Item::ItemType::COIN)
	{
		out << myitem.uniontypes.Coins.count << " gold" << endl;
	}

	if (myitem.TypeItem == Item::ItemType::RUNE)
	{
		if (myitem.uniontypes.Runes.elements == Item::unionType::RUNE::Element::AIR) 
		{ 
			out << "Rune of air " << myitem.uniontypes.Runes.level << " lvl" << endl; 
		}

		if (myitem.uniontypes.Runes.elements == Item::unionType::RUNE::Element::EARTH) 
		{ 
			out << "Rune of earth " << myitem.uniontypes.Runes.level << " lvl" << endl; 
		}
		if (myitem.uniontypes.Runes.elements == Item::unionType::RUNE::Element::FIRE) 
		{
			out << "Rune of fire " << myitem.uniontypes.Runes.level << " lvl" << endl; 
		}
		if (myitem.uniontypes.Runes.elements == Item::unionType::RUNE::Element::WATER) 
		{ 
			out << "Rune of water " << myitem.uniontypes.Runes.level << " lvl" << endl;
		}

	}

	if (myitem.TypeItem == Item::ItemType::WEAPON)
	{

		if (myitem.uniontypes.Weapons.damage == 100)
		{
			out << "Frostmourne" << endl;
		}

		else 
		{
			out << "Buster Sword" << endl;
		}

	}

	return out;
}

ostream& operator<<(ostream& out, LootBox myitems)
{

	for (int i = 0; i < myitems.size(); i++)
	{
		out << myitems[i];
	}

	return out;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		cout << "Открыть лутбокс? Yes/No" << endl;
		string s;
		cin >> s;
		string ls;
		for (int i = 0; i < s.size(); i++) { ls += tolower(s[i]); 
	}

		if (ls == "y" || ls == "yes")
		{
			cout << generateLootBox();
		}

		if (ls == "n" || ls == "no")
		{
			break;
		}

	}

}