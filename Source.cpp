#include <iostream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#include <Windows.h>

using std::string;

std::vector<string> boyNames = { "James", "Wilson", "Christopher", "Jack", "Jacob", "Chandler", "Hewes", "Nicholas", "Paul", "Saul", "Walter", "Francis", "Robert", "John", "Yveltis", "Edward", "Ralph"};
std::vector<string> girlNames = { "Molly", "Kenzie", "Madeline", "Christina", "Frances", "Sophia", "Olivia", "Charlotte", "Amelia", "Ava", "Isabella", "Mia", "Elizabeth", "Eleanor", "Scarlett"};
std::vector<string> lastNames = { "Smith", "Johnson", "Ruste", "Polte", "Kalo", "Retyu", "Williams", "Brown", "Jones", "Glosta", "Cyntax", "Flix", "Star", "Smasher", "Miller", "Davis", "Berry"};
std::vector<string> townNames = { "Putlochry","Laencaster","Drumnacanvy","Waeldestone","Furness","Berxley","Calmarnock","Roselake","Norwich","Broughton" };
std::vector<string> disasterNames = { "hurricane","epidemic","tornado","war" };

class Human {
public:
	int gender; //1==Male,2==Female

	string name;

	int familyTreeStem = 0;

	unsigned int age;
	bool isMarried = false;
	bool isKing = false;
	//Special Traits
	bool immortal = false;
};

namespace ClassHelpers
{
	string classHelp_TownName;
	/*Human returnBoy(std::vector<Human> humans)
	{
		std::vector<Human> boys;
		for (Human human : humans)
		{
			if (human.gender == 1)
			{
				boys.push_back(human);
			}
		}
		int idx = rand() % boys.size() - 1;
		return boys[idx];
	}
	Human returnGirl(std::vector<Human> humans)
	{
		std::vector<Human> girls;
		for (Human human : humans)
		{
			if (human.gender == 2)
			{
				girls.push_back(human);
			}
		}
		int idx = rand() % girls.size() - 1;
		return girls[idx];
	}*/

	////////

	std::vector<Human> yearlyAdultBoys;
	std::vector<Human> yearlyAdultGirls;

	std::vector<int> yearlyAdultMaleIndex;
	std::vector<int> yearlyAdultFemaleIndex;

	int returnAdultMaleIndex(std::vector<Human> humans);
	void setAdultGenders(std::vector<Human>& humans)
	{
		std::vector<Human> boys;
		std::vector<Human> girls;

		std::vector<int> boysindex;
		std::vector<int> girlsindex;

		for (int i = 0; i < humans.size(); i++)
		{
			Human human = humans[i];
			if (human.gender == 1 && human.age > 17)
			{
				boys.push_back(human);
				boysindex.push_back(i);
			}
			else if (human.gender == 2 && human.age > 17)
			{
				girls.push_back(human);
				girlsindex.push_back(i);
			}

			
			/* AGING (STOP 2X LOOP) */


		}
		yearlyAdultBoys.clear();
		yearlyAdultBoys = boys;

		yearlyAdultGirls.clear();
		yearlyAdultGirls = girls;

		yearlyAdultMaleIndex.clear();
		yearlyAdultMaleIndex = boysindex;

		yearlyAdultFemaleIndex.clear();
		yearlyAdultFemaleIndex = girlsindex;

	}
	Human returnAdultBoy(std::vector<Human> humans)
	{
		int idx = rand() % yearlyAdultBoys.size();
		return yearlyAdultBoys[idx];
	}
	Human returnAdultGirl(std::vector<Human> humans)
	{
		int idx = rand() % yearlyAdultGirls.size();
		return yearlyAdultGirls[idx];
	}

	string genderToName(int gender)
	{
		std::vector<string> genders = { "NO_SUCH_GENDER","Male","Female" };
		return genders[gender];
	}
	int returnAdultMaleIndex(std::vector<Human> humans)
	{
		int idx = rand() % yearlyAdultMaleIndex.size();
		return yearlyAdultMaleIndex[idx];
	}
	int returnAdultFemaleIndex(std::vector<Human> humans)
	{
		int idx = rand() % yearlyAdultFemaleIndex.size();
		return yearlyAdultFemaleIndex[idx];
	}
}

namespace Breeding
{
	int canBreed(std::vector<Human> humans)
	{
		int boys = ClassHelpers::yearlyAdultBoys.size();
		int girls = ClassHelpers::yearlyAdultGirls.size();
		
		std::cout << boys << " | " << girls;

		if (boys > 0 && girls > 0)
		{
			if (boys > girls)
			{
				return girls;
			}
			return boys;
		}
		return false;
	}
	
	Human doBreed(std::vector<Human> humans, std::map<int, string> familyTrees)
	{
		Human ourBoy = ClassHelpers::returnAdultBoy(humans);
		Human ourGirl = ClassHelpers::returnAdultGirl(humans);
		Human ourBaby;
		//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
		int gender = rand() % 10 + 1;
		if (gender > 4)
		{
			ourBaby.name = boyNames[rand() % boyNames.size()];
			gender = 1;
		}
		else
		{
			ourBaby.name = girlNames[rand() % girlNames.size()];
			gender = 2;
		}
		ourBaby.gender = gender;
		ourBaby.name = ourBaby.name + ' ' + familyTrees[ourBoy.familyTreeStem]; //take father name
		ourBaby.age = 0;
		ourBaby.familyTreeStem = ourBoy.familyTreeStem;
		return ourBaby;
	}
}

namespace Marriage
{
	int canMarry(std::vector<Human> humans)
	{
		int boys = 0;
		int girls = 0;
		for (Human human : humans)
		{
			if (human.age > 17 && human.isMarried == false)
			{
				switch (human.gender)
				{
				case 1:
					boys++;
					break;
				case 2:
					girls++;
					break;
				}
			}
		}
		if (boys > 0 && girls > 0)
		{
			if (boys > girls)
			{
				return girls;
			}
			return boys;
		}
		return false;
	}

	void marryTwo(std::vector<Human>& humans, std::map<int, string>& familyTrees)
	{
		//Human ourBoy = ClassHelpers::returnAdultBoy(humans);
		//Human ourGirl = ClassHelpers::returnAdultGirl(humans);
		int ourBoyIndex = ClassHelpers::returnAdultMaleIndex(humans);
		int ourGirlIndex = ClassHelpers::returnAdultFemaleIndex(humans);


		std::vector<string> names;
		std::stringstream strs(humans[ourBoyIndex].name);
		string intermediate;
		while (std::getline(strs, intermediate, ' '))
		{
			names.push_back(intermediate);
		}
		std::stringstream strs2(humans[ourGirlIndex].name);
		while (std::getline(strs2, intermediate, ' '))
		{
			names.push_back(intermediate);
		}


		int lastNameType = rand() % 4; //1,2,3
		if (lastNameType == 1)
		{
			//males
			humans[ourGirlIndex].name = names[2] + ' ' + names[1];
		}
		else if (lastNameType == 2)
		{
			//hyphenated
			string lastName;
			bool disableNew = false;
			if (names[1].find(names[3]) != std::string::npos || names[3].find(names[1]) != std::string::npos)
			{
				lastName = names[1];
			}
			else
			{
				lastName = names[1] + '-' + names[3];
			}
			
			humans[ourGirlIndex].name = names[2] + ' ' + lastName;
			humans[ourBoyIndex].name = names[0] + ' ' + lastName;

			if (disableNew == false)
			{
				int treeKey = familyTrees.size() + 2;
				familyTrees[treeKey] = lastName;
				humans[ourGirlIndex].familyTreeStem = treeKey;
				humans[ourBoyIndex].familyTreeStem = treeKey;
			}
			else
			{
				humans[ourGirlIndex].familyTreeStem = humans[ourBoyIndex].familyTreeStem;
			}
		}
		else if (lastNameType == 3)
		{
			//new
			int nameKey = rand() % lastNames.size() - 1;
			nameKey = abs(nameKey);
			string lastName = lastNames[nameKey];
			humans[ourGirlIndex].name = names[2] + ' ' + lastName;
			humans[ourBoyIndex].name = names[0] + ' ' + lastName;

			int treeKey = familyTrees.size() + 2;
			familyTrees[treeKey] = lastName;
			humans[ourGirlIndex].familyTreeStem = treeKey;
			humans[ourBoyIndex].familyTreeStem = treeKey;
		}
		humans[ourGirlIndex].isMarried = true;
		humans[ourBoyIndex].isMarried = true;
	}

}


namespace Town
{
	string townName = "Your humans haven't made a town yet!";
	bool townExists = false;
	void electKing(std::vector<Human>& humans)
	{
		int kingIdx = ClassHelpers::returnAdultMaleIndex(humans);
		humans[kingIdx].isKing = true;
		std::cout << "\n\n\nA new king by the name of " << humans[kingIdx].name << " has been elected as the leader of " << townName << std::endl;
	}
	void doTown(std::vector<Human>& humans)
	{
		if (humans.size() > 120)
		{
			Sleep(1000);
			std::cout << "\n\nYour humans have decided to build a town." << std::endl;
			int townNameIndex = (rand() % townNames.size() - 1);
			townNameIndex = abs(townNameIndex);

			std::cout << "They named their town " << townNames[townNameIndex];
			townName = townNames[townNameIndex];
			ClassHelpers::classHelp_TownName = townName;

			electKing(humans);
			townExists = true;
			Sleep(4000);
		}
	}
}
namespace NaturalDisasters
{
	void disaster(std::vector<Human>& humans)
	{
		int doDisaster = rand() % 100;
		if (doDisaster < 90)
		{
			return;
		}

		int disasterType = rand() % disasterNames.size() - 1;
		disasterType = abs(disasterType);
		std::cout << "A " << disasterNames[disasterType] << " struck!";
		int deathToll = 0;
		for (int i = 0; i < humans.size(); i++)
		{
			int death = rand() % 100;
			if (death > 90)
			{
				if (humans[i].isKing)
				{
					Town::electKing(humans);
				}
				humans.erase(humans.begin() + i);
				deathToll += 1;
			}
		}

		std::cout << " The " << disasterNames[disasterType] << " resulted in " << deathToll << " deaths! :(" << std::endl;
		//std::cin.get();
	}
}

/*
Create a human being
name, gender, age, familyTreeStem
*/
Human createHuman(string name, int gender, unsigned int age, 
	int familyTreeStem)
{
	Human human;
	human.name = name;
	human.gender = gender;
	human.age = age;
	human.familyTreeStem = familyTreeStem;
	return human;
}
void incrementAges(std::vector<Human>& humans)
{
	for (int x = 0; x < humans.size(); x++)
	{
		humans[x].age += 1;
		if (humans[x].age > 62)
		{
			std::cout << "Oh no! " << humans[x].name << " has died!" << std::endl;
			if (humans[x].isKing)
			{
				Town::electKing(humans);
			}
			humans.erase(humans.begin() + x);
		}
	}

}
int main()
{
	/*IDEA TO UPGRADE SPEED
	///////////////////
	///////////////////
	
	Instead of scanning over the vector everytime to collect gender data,
	scan it over once for each gender every year and set that to a temporary
	variable used in every breed.

	Warning: may make it go ultra-fast :D :D

	*/
	srand(time(NULL)); // pseudo-random

	std::vector<Human> humans;
	std::map<int, string> familyTrees;

	humans.push_back(createHuman("Adam Dark", 1, 16, 0));
	familyTrees[0] = "Dark";
	humans.push_back(createHuman("Eve Light", 2, 16, 1));
	familyTrees[1] = "Light";

	int year = 0;
	while (1)
	{
		if (humans.size() < 2)
		{
			std::cout << "Your population died out.";
			break;
		}
		std::cout << "\n\n\n\n\nCurrent Year: " << year << "\nCurrent Population: " << humans.size()
			<< "\nBloodline(s): " << familyTrees.size() << "\nTown Name: " << Town::townName;
		std::cout << "\n\n";
		for (Human hu : humans)
		{
			std::cout << hu.name << " | " << ClassHelpers::genderToName(hu.gender) << " | Aged "
				<< hu.age << "\n";
				
		}
		std::cout << "\n\n\n\n\nAlmost Year: " << year + 1 << "\nCurrent Population: " << humans.size()
			<< "\nBloodline(s): " << familyTrees.size() << "\nTown Name: " << Town::townName;;
		std::cout << "\n\n";
		/* Breeding */
		ClassHelpers::setAdultGenders(humans);
		if (Breeding::canBreed(humans))
		{
			bool canMarry = Marriage::canMarry(humans);
			int canBreed = Breeding::canBreed(humans);
			for (int i = 0; i < canBreed; i++)
			{
				int casing = rand() % 4;
				switch (casing)
				{
				case 1:
					humans.push_back(Breeding::doBreed(humans, familyTrees));
					break;
				case 2:
					if (canMarry)
					{
						Marriage::marryTwo(humans, familyTrees);
					}
					break;
				}
			}

		}
		if (Town::townExists == false)
		{
			Town::doTown(humans);
		}
		


		if (year > 50)
		{
			NaturalDisasters::disaster(humans);
		}
		incrementAges(humans);
		year++;
		if (year % 100 == 0)
		{
			std::cin.get();
		}
		//std::cin.get();
	}

}
