#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Character {
public:
	void flip() { cout << "I know how to flip and I will flipping do it" << endl; }
	virtual void walk() { cout << "just in case they are too young to walk yet" << endl; }
	virtual void fly() = 0; //pure virtual function

	//Attacks
	bool powerAttack = false;
	bool fastAttack = false;
	bool rollAttack = false;

	//Health
	int health;
	void setHealth(int t_health) { health = t_health;}
	void decreaseHealth(int t_deductor) { health = health - t_deductor; }
	int getHealth() { return health; }

	//Using Attacks
	void usePowerAttack() { powerAttack = true; }
	void useFastAttack() { fastAttack = true; }
	void useRollAttack() { rollAttack = true; }

	//Getting Attacks
	bool getPowerAttack() { return powerAttack; }
	bool getFastAttack() { return fastAttack; }
	bool getRollAttack() { return rollAttack; }

	
	void resetAttacks() 
	{ 
		powerAttack = false; 
		fastAttack = false; 
		rollAttack = false; 
	}
};

class Orc : public Character {
public:
	void barrelRoll() { std::cout << "rooooooolllllllllllinggggggg" << endl; }
	void walk() { std::cout << "Doopers have a really cool walk!" << endl; }
	void fly() { std::cout << "Dooper is flapping and flying" << endl; }

};

class Troll : public Character {
public:
	void fly() { std::cout << "Average Dooper is flapping and flying" << endl; }
};


void combatResolver(Orc& t_player, Troll& t_enemy);
void resetAttacks(Orc& t_player, Troll& t_enemy);
void attackSelector(Orc& t_player);
void enemyAttack(Troll& t_enemy);
void introText();
void orcAscii();

int main(void)
{
	bool combatActive = true;

	//Objects
	Orc orc;
	Troll troll;

	//Pointers to address
	Character* player = &orc;
	Character* enemy1 = &troll;

	//Set Player and Enemy starting Health
	player->setHealth(10);
	enemy1->setHealth(5);

	//OrcASCII
	orcAscii();
	
	//Intro
	introText();

	while (combatActive == true)
	{
		//Player Attack Choice
		attackSelector(orc);

		//Random Generated Enemy Attack
		enemyAttack(troll);

		//Resolve Combat
		combatResolver(orc, troll);

		//Reset the attacks
		resetAttacks(orc, troll);

		//Check player alive
		if (player->getHealth() <= 0)
		{
			std::cout << "GAME OVER:: YOU HAVE BEEN SLAIN BY THE MIGHTY TROLL LORD!";
			combatActive = false;
		}
		//Check enemy is alive
		else if (enemy1->getHealth() <= 0)
		{
			std::cout << "The troll stumbles to the ground with blood pouring from his mouth, he begs for mercy as you deal one final blow to his skull" << std::endl;
			std::cout << "YOU HAVE WON THE GAME!!!" << std::endl;
			combatActive = false;
		}

		std::cout << "Your remaining Health is " << to_string(player->getHealth()) << std::endl;
		std::cout << "The enemys Health is " << enemy1->getHealth() << std::endl;
	}

	system("pause");
}

void attackSelector(Orc& t_player)
{
	bool selected = false;
	std::string selector;
	std::cout << "You have three attacks availible to select please type 'power', 'fast' or 'roll'" << std::endl;
	std::cout << "What attack will you use?" << std::endl;
	while (selected == false)
	{
		std::cin >> selector;
		std::cout << "" << std::endl;

		if (selector == "power")
		{
			t_player.usePowerAttack();
			std::cout << "You use your most powerfull atack, brutal in force, slow in timing!!!" << std::endl;
			selected = true;
		}
		else if (selector == "fast")
		{
			t_player.useFastAttack();
			std::cout << "You strick quickly!!!" << std::endl;
			selected = true;
		}
		else if (selector == "roll")
		{
			t_player.useRollAttack();
			std::cout << "You roll trying to dodge enemy attacks while striking!!!" << std::endl;
			selected = true;
		}
		else
		{
			std::cout << "Incorrect Entry Please Enter 'power', 'fast' or 'roll' to choose your attack" << std::endl;
		}
	}
}

void enemyAttack(Troll& t_enemy)
{

	int randAttackSelector;
	srand(time(NULL));


	//Generates the rand number
	randAttackSelector = rand() % 3;

	//Power
	if (randAttackSelector == 0)
	{
		t_enemy.usePowerAttack();
		std::cout << "The enemey troll uses all his might in a power attack!!!" << std::endl;
	}
	//Fast
	else if (randAttackSelector == 1)
	{
		t_enemy.useFastAttack();
		std::cout << "The enemy troll trys to be quick off the mark with a quick strike!!!" << std::endl;
	}
	//Roll
	else if (randAttackSelector == 2)
	{
		t_enemy.useRollAttack();
		std::cout << "The enemy troll rolls trying to dodge your attack while striking!!!" << std::endl;
	}
}


void combatResolver(Orc& t_player, Troll& t_enemy)
{
	//Player Power Attacks
	if (t_player.getPowerAttack() && t_enemy.getPowerAttack())
	{
		t_player.decreaseHealth(2);
		t_enemy.decreaseHealth(2);
		std::cout << "The might of the two heavy attacks bludgends each of you! \nYou have taken -2HP damage \n The troll has taken -2HP damage" << std::endl;
	}
	else if (t_player.getPowerAttack() && t_enemy.getFastAttack())
	{
		t_enemy.decreaseHealth(1);
		std::cout << "The brute force of your attack smashes the enemy troll! \nThe troll has taken -1HP damage" << std::endl;
	}
	else if (t_player.getPowerAttack() && t_enemy.getRollAttack())
	{
		t_player.decreaseHealth(1);
		std::cout << "You power attack is to late as the enemy rolls around you stabbing you as he goes! \nYou have taken -1HP damage" << std::endl;
	}

	//Player Fast Attacks
	else if(t_player.getFastAttack() && t_enemy.getPowerAttack())
	{
		t_player.decreaseHealth(1);
	std::cout << "Your fast attack lacked the brute force of the trolls attack, you get smashed! \n You have taken -1HP damage" << std::endl;
	}
	else if (t_player.getFastAttack() && t_enemy.getFastAttack())
	{
		t_player.decreaseHealth(1);
		t_enemy.decreaseHealth(1);
		std::cout << "Simultaneously you stike both not having enough time to defend yourself, however you both land the strike! \nYou have taken -1HP damage \nThe troll has taken -1HP damage" << endl;
	}
	else if (t_player.getFastAttack() && t_enemy.getRollAttack())
	{
		t_enemy.decreaseHealth(1);
		std::cout << "You strike the enemy swiftly, rendering his roll useless! \nThe troll has taken -1HP damage" << std::endl;

	}

	//Player Roll Attack
	else if (t_player.getRollAttack() && t_enemy.getPowerAttack())
	{
		t_enemy.decreaseHealth(1);
		std::cout << "You quickly roll away from the enemys power attack and strike! \nThe troll has taken -1HP damage" << std::endl;
	}
	else if (t_player.getRollAttack() && t_enemy.getFastAttack())
	{
		t_player.decreaseHealth(1);
		std::cout << "You roll but are not quick enough to dodge the enemys fast attack! \n You have taken -1HP damage" << std::endl;
	}
	else if (t_player.getRollAttack() && t_enemy.getRollAttack())
	{
		t_player.decreaseHealth(1);
		t_enemy.decreaseHealth(1);
		std::cout << "You both roll by one another attacking! \nYou have taken -1HP damage \nThe troll has taken -1HP damage" << std::endl;
	}
}

void resetAttacks(Orc& t_player, Troll& t_enemy)
{
	t_player.resetAttacks();
	t_enemy.resetAttacks();
}

void introText()
{


	std::cout << "You are the war cheif of your clan of mighty orcs," << std::endl;
	std::cout << "the threat from the trolls has been persistant throughout these last years." << std::endl;
	std::cout << "However these last few weeks the attacks have begun to grow more frequent," << std::endl;
	std::cout << "with the full might of the orcs you have decided to make an attack on their main city." << std::endl;
	std::cout << "*************************************************************************" << std::endl;
	std::cout << "You have arrived close to the Troll camp," << std::endl;
	std::cout << "however the troll king will be protected, you must destroy his bodyguards first!" << std::endl;
	std::cout << "with a pincer movement set up you count to three and ATTACK!!! \n" << std::endl;
}

void orcAscii()
{
	std::cout << "                           __.--|~|--.__                    ORCS VS ,,;/;" << std::endl;
	std::cout << "                         /~     | |    ;~\                TROLLS! ,;;;/;;'" << std::endl;
	std::cout << "                        /|      | |    ;~\\                     ,;;;;/;;;'" << std::endl;
	std::cout << "                       |/|      \\_/   ;;;|\                    ,;;;;/;;;;'" << std::endl;
	std::cout << "                       |/ \\          ;;;/  )                 ,;;;;/;;;;;'" << std::endl;
	std::cout << "                   ___ | ______     ;_____ |___....__      ,;;;;/;;;;;'" << std::endl;
	std::cout << "             ___.-~ \\\\(| \\  \\.\\ \\__/ /./ /:|)~   ~   \   ,;;;;/;;;;;'" << std::endl;
	std::cout << "         /~~~    ~\\    |  ~-.     |   .-~: |//  _.-~~--,;;;;/;;;;;'" << std::endl;
	std::cout << "        (.-~___     \\.'|    | /-.__.-\\|::::| //~     ,;;;;/;;;;;'" << std::endl;
	std::cout << "        /      ~~--._ \\|   /          `\\:: |/      ,;;;;/;;;;;'" << std::endl;
	std::cout << "     .-|             ~~|   |  /V"">>>>V\ |:  |     ,;;;;/;;;;;' \\" << std::endl;
	std::cout << "    /                   \\  |  ~`^~~^'~ |  /    ,;;;;/;;;;;'    ;" << std::endl;
	std::cout << "   (        \\             \\|`\._____./'|/    ,;;;;/;;;;;'      '\\" << std::endl;
	std::cout << "  / \        \\                             ,;;;;/;;;;;'     /    |" << std::endl;
	std::cout << " |            |                          ,;;;;/;;;;;'      |     |" << std::endl;
	std::cout << "|`-._          |                       ,;;;;/;;;;;'              \\" << std::endl;
	std::cout << "|             /                      ,;;;;/;;;;;'  \\ \\__________" << std::endl;
	std::cout << "(             )                 |  ,;;;;/;;;;;'      |        _.--~" << std::endl;
	std::cout << " \          \\/ \\              ,  ;;;;;/;;;;;'       /( .-~_..--~~~~~~~~~~" << std::endl;
	std::cout << " \__         '  `       ,     ,;;;;;/;;;;;'    .   /  \\   / /~" << std::endl;
	std::cout << " /          \\'  |`._______ ,;;;;;;/;;;;;;'    /   :    \\/'/'       /|_/| ``|" << std::endl;
	std::cout << "| _.-~~~~-._ |   \\ __   .,;;;;;;/;;;;;;' ~~~~'   .'    | |       /~ (/\\/  || \n\n" << std::endl;

}