// MAT- II- Text-based RPG Adventure Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string>

class BaseClass {
protected:
    string name;
    int level;
    int health;
    int baseHeal;
    int baseHealth;
    int baseDamage;
    int heal;
    int upgradeHealth;
    int upgradeDamage;
    int meleeDamage;
    bool alive;
    int minMeleeDamage;
    int maxMeleeDamage;
    int specialAbilityChance;
    int specialAbilityActivated;
    int increaseDamage;

public:
    BaseClass() {
        level = 0;
        baseHealth = 0;
        baseDamage = 0;
        specialAbilityActivated = 0;
        increaseDamage = 3;
    }

    string getName() { return name; }
    bool isAlive() { return alive; }
    int getLevel() { return level; }
    int getMinMeleeDamage() { return minMeleeDamage; }
    int getMaxMeleeDamage() { return maxMeleeDamage; }
    int getBaseHeal() { return baseHeal; }
    int getHealth() { return health; }
    int getBaseHealth() { return baseDamage; }
    int getBaseDamage() { return baseDamage; }

    virtual int getMeleeDamage() {
        meleeDamage = minMeleeDamage + rand() % (maxMeleeDamage - minMeleeDamage);
        return meleeDamage;
    }

    int restoreHealth(int heal) {
        if (health + heal > baseHealth)
            heal -= health + heal - baseHealth;
        health = health + heal;
        return heal;
    }

    virtual void takeDamage(int damage) = 0;
    virtual void useHeal(int heal) = 0;
    virtual void levelUp() = 0;
    virtual void activateSA() = 0;
    virtual void disableSA() = 0;
};

class Player : public BaseClass {
    bool criticalHitSA;
    bool blockerSA;
    bool lifeStealSA;
    bool rangedAttackSA;
    int lifeStealSAPower;
    int healingPotion;

public:
    Player(string name) {
        this->name = "Player";
        alive = true;
        upgradeHealth = 100;
        upgradeDamage = 10;
        baseHeal = 500;
        healingPotion = 1;
        specialAbilityActivated = 0;
        specialAbilityChance = 5;
        levelUp();
        disableSA();
    }

    int getMeleeDamage() {
        BaseClass::getMeleeDamage();
        if (lifeStealSA)
            lifeStealSAPower++;
        if (criticalHitSA)
            return meleeDamage * increaseDamage;
        return meleeDamage;
    }

    int getRanagedDamage() {
        if (lifeStealSA)
            lifeStealSAPower++;
        if (criticalHitSA)
            return baseDamage * increaseDamage;
        return baseDamage;
    }

    void takeDamage(int damage) {
        if (blockerSA) {
            cout << name << " blocked all damage.\n";
            return;
        }
        health = health - damage;
        cout << "- " << name << " took " << damage << " damage.\n";
        if (health <= 0) {
            alive = false;
            cout << "~ " << name << " died.\n";
            return;
        }
        if (lifeStealSA) {
            useHeal(lifeStealSAPower * upgradeHealth / 2);
        }
    }

    void useHeal(int heal) {
        if (health == baseHealth) {
            cout << name << "'s health is already full\n";
            return;
        }
        heal = restoreHealth(heal);
        cout << name << " health increased by " << heal << " HP\n";
    }

    int useHealingPotion() {
        if (healingPotion == 0)
            return false;
        healingPotion--;
        return true;
    }

    void activateSA() {
        if (specialAbilityActivated == 0)
            return;
        if (rangedAttackSA) {
            rangedAttackSA = false;
            blockerSA = true;
            return;
        }
        disableSA();
        if (rand() % specialAbilityChance != 0)
            return;
        int choiceSA = rand() % specialAbilityActivated;
        switch (choiceSA) {
        case 0:
            cout << "* " << name << " used Critical Hit Special Ability\n";
            criticalHitSA = true;
            break;
        case 1:
            cout << "* " << name << " used Blocker Special Ability\n";
            blockerSA = true;
            break;
        case 2:
            cout << "* " << name << " used Life Steal Special Ability\n";
            lifeStealSA = true;
            break;
        case 3:
            cout << "* " << name << " used Ranged Attack Special Ability\n";
            rangedAttackSA = true;
            break;
        }
    }

    void disableSA() {
        criticalHitSA = false;
        blockerSA = false;
        lifeStealSA = false;
        rangedAttackSA = false;
        lifeStealSAPower = 0;
    }

    void showPlayerChoice() {
        cout << "Select your move." << endl;
        cout << "1. Melee Attack \n2. Ranged Attack \n3. Use Healing Potion";
        cout << "(" << healingPotion << ")\n";
        cout << "Player choice : ";
    }

    void levelUp() {
        switch (level) {
        case 0:
            cout << "\nPlayer saw an attack on Village\n";
            cout << "The village was attacked by a monster called murlocs. :( \n";
            cout << "Murlocs attacked and kidnapped our queen, now to save the queen and to take revenge for attacking village life, player must defeat murlocs.\n";
            cout << "In order to defeat murlocs, player needs to collect the 5 items listed below.\n";
            cout << "Map, Sword, Shield, Armour and Bow.\n";
            cout << "Each item will unlock as you clears every level.\n";
            cout << "The will be defeated only if you have all items unlocked.\n";
            break;
        case 1:
            cout << "\nRewards for Completing level " << level << endl;
            cout << "+ Map and 1 Healing Potion.\n";
            cout << "+ Player's health incresed by 100\n";
            healingPotion++;
            break;
        case 2:
            cout << "\nRewards for Completing level " << level << endl;
            cout << "+ Sword and 1 Healing Potion.\n";
            cout << "+ Player's health incresed by 100\n";
            cout << "+ Special Ability Awarded - Critical hits\n";
            healingPotion++;
            specialAbilityActivated++;
            break;
        case 3:
            cout << "\nRewards for Completing level " << level << endl;
            cout << "+ Shield  and 1 Healing Potion.\n";
            cout << "+ Player's health incresed by 100\n";
            cout << "+ Special Ability Awarded - Blocker\n";
            healingPotion++;
            specialAbilityActivated++;
            break;
        case 4:
            cout << "\nRewards for Completing level " << level << endl;
            cout << "+ Armour and 2 Healing Potion.\n";
            cout << "+ Player's health incresed by 100\n";
            cout << "+ Special Ability Awarded - Life steal \n";
            healingPotion += 2;
            specialAbilityActivated++;
            break;
        case 5:
            cout << "\nRewards for Completing level " << level << endl;
            cout << "+ Bow  and 2 Healing Potion.\n";
            cout << "+ Special Ability Awarded - Ranged Attack\n";
            cout << "+ All Special Ability chances boosted by 2 times.\n";
            healingPotion += 2;
            specialAbilityChance = 4;
            specialAbilityActivated++;
            baseHealth -= upgradeHealth;
            baseDamage -= upgradeDamage;
        }
        baseHealth += upgradeHealth;
        baseDamage += upgradeDamage;
        health = baseHealth;
        minMeleeDamage = baseDamage - (baseDamage / 2);
        maxMeleeDamage = baseDamage + (baseDamage / 2);
        level++;
    }
};

class Enemy : public BaseClass {
    int dodgeProbability;
    bool bossEnemy;
    int bossLevel;
    bool groundSlashSA;
    bool speedDashSA;
    bool HealthRegenSA;

public:
    Enemy(string name) {
        this->name = name;
        alive = false;
        level = 0;
        baseHealth = 0;
        baseDamage = 0;
        upgradeHealth = 25;
        upgradeDamage = 10;
        dodgeProbability = 4;
        bossEnemy = false;
        bossLevel = 6;
        specialAbilityChance = 5;
        specialAbilityActivated = 3;
        disableSA();
    }

    bool isBossEnemy() { return bossEnemy; }
    void respawn() { alive = true; }

    int getMeleeDamage() {
        BaseClass::getMeleeDamage();
        if (groundSlashSA) {
            cout << "! " << name << " used Ground Slash attack with " << meleeDamage * increaseDamage << " damage.\n";
            return meleeDamage * increaseDamage;
        }
        cout << name << " used melee attack with " << meleeDamage << " damage.\n";
        return meleeDamage;
    }

    void takeDamage(int damage) {
        if (speedDashSA) {
            cout << "! " << name << " used Speed Dash Ability and avoided all damage.\n";
            return;
        }
        if (rand() % dodgeProbability == 0) {
            damage = damage / 2;
            cout << "! " << name << " dodged and took " << damage << " damage.\n";
        }
        else
            cout << "+ " << name << " took " << damage << " damage.\n";
        health = health - damage;
        if (health <= 0) {
            alive = false;
            cout << "~ " << name << " died.\n";
            return;
        }
        if (HealthRegenSA) {
            useHeal(baseHeal);
        }
    }

    void useHeal(int heal) {
        if (health == baseHealth) {
            cout << "! " << name << " used Health Regen and healed 0 HP.\n";
            return;
        }
        heal = restoreHealth(heal);
        cout << "! " << name << " used Health Regen and healed " << heal << " HP.\n";
    }

    void activateSA() {
        disableSA();
        if (rand() % specialAbilityChance != 0)
            return;
        int choiceSA = rand() % specialAbilityActivated;
        switch (choiceSA) {
        case 0:
            groundSlashSA = true;
            break;
        case 1:
            speedDashSA = true;
            break;
        case 2:
            HealthRegenSA = true;
            break;
        }
    }

    void disableSA() {
        groundSlashSA = false;
        speedDashSA = false;
        HealthRegenSA = false;
    }

    void spawnBossEnemy() {
        bossEnemy = true;
        name = "Murlocs";
        baseHealth = 750;
        health = baseHealth;
        baseDamage = 50;
        baseHeal = 100;
    }

    void levelUp() {
        level++;
        baseHealth += upgradeHealth;
        baseDamage += upgradeDamage;
        health = baseHealth;
        minMeleeDamage = baseDamage - baseDamage / 2;
        maxMeleeDamage = baseDamage + baseDamage / 2;
        if (level == bossLevel)
            spawnBossEnemy();
    }
};

class GameLogic {
    unique_ptr<Player> player;
    unique_ptr<Enemy> enemy[4];
    bool invalidInput;
    bool exitGame;
    char playerChoice;
    int maxEnemySize = 4;
    int bossLevel = 6;
    int totalEnemy;
    int damage;
    bool levelCompleted;

    void startGame() {

        player = unique_ptr<Player>(new Player("Player"));
        for (int i = 0; i < maxEnemySize; i++)
            enemy[i] = unique_ptr<Enemy>(new Enemy("Enemy " + to_string(i + 1)));
        gameLoop();
        if (player->isAlive())
            cout << "\033[3;44;30m" << "You Won" << " \033[0m";
        else
            cout << "\n>> Player lost Try Again! <<\n";
        cout << "\nPress any key to go to Main Menu : ";
        cin >> playerChoice;
    }

    void gameLoop() {
        levelLoading();
        while (player->isAlive() > 0 && player->getLevel() <= bossLevel) {
            cout << "\nHealth status\n";
            showHealthStatus();
            do {
                invalidInput = playerTurn();
            } while (invalidInput);
            cout << "\nEnemy turn\n";
            enemyTurn();
            if (levelCompleted) {
                cout << "All Enemies Defeated. <\n";
                player->levelUp();
                levelLoading();
            }
        }
    }

    void showHealthStatus() {
        cout << "Player HP : " << player->getHealth() << endl;
        for (int i = 0; i < totalEnemy; i++)
            if (enemy[i]->isAlive())
                cout << enemy[i]->getName() << " HP : " << enemy[i]->getHealth() << endl;
    }

    bool playerTurn() {
        player->showPlayerChoice();
        cin >> playerChoice;
        if (enemy[0]->isBossEnemy())
            enemy[0]->activateSA();
        switch (playerChoice) {
        case '1':
            player->activateSA();
            cout << "Player used melee attack with " << player->getMinMeleeDamage() << "-" << player->getMaxMeleeDamage() << " damage.\n";
            for (int i = 0; i < totalEnemy; i++)
                if (enemy[i]->isAlive()) {
                    damage = player->getMeleeDamage();
                    enemy[i]->takeDamage(damage);
                }
            break;
        case '2':
            player->activateSA();
            cout << "Player used ranged attack with " << player->getBaseDamage() << " damage.\n";
            for (int i = 0; i < totalEnemy; i++)
                if (enemy[i]->isAlive()) {
                    damage = player->getRanagedDamage();
                    enemy[i]->takeDamage(damage);
                }
            break;
        case '3':
            player->disableSA();
            if (player->useHealingPotion())
                player->useHeal(player->getBaseHeal());
            else
                cout << "No Healing Potions Left.\n";
            break;
        default:
            return true;
        }
        return false;
    }

    void enemyTurn() {
        damage = 0;
        for (int i = 0; i < totalEnemy; i++)
            if (enemy[i]->isAlive())
                damage += enemy[i]->getMeleeDamage();
        if (damage > 0)
            player->takeDamage(damage);
        else
            levelCompleted = true;
    }

    void levelLoading() {
        cout << "\nPress any key to continue : ";
        cin >> playerChoice;
        levelCompleted = false;
        switch (player->getLevel()) {
        case 1:
            totalEnemy = 1;
            cout << "\nLevel 1\n";
            cout << totalEnemy << " Enemy is coming\n";
            break;
        case 2:
            totalEnemy = 2;
            cout << "\nLevel 2\n";
            cout << totalEnemy << " Enemies are coming\n";
            break;
        case 3:
            totalEnemy = 3;
            cout << "\nLevel 3\n";
            cout << totalEnemy << " Enemies are coming\n";
            break;
        case 4:
            totalEnemy = 3;
            cout << "\nLevel 4\n";
            cout << totalEnemy << " Enemies are coming\n";
            break;
        case 5:
            totalEnemy = 4;
            cout << "\nLevel 5\n";
            cout << totalEnemy << " Enemies are coming\n";
            break;
        case 6:
            totalEnemy = 1;
            cout << "\nLevel 6\n";
            cout << "!!! Murlocs is getting raged to fight !!!\n";
            break;
        case 7:
            totalEnemy = 0;
            cout << "\n Congratulations!!!! You Won.\n";
            cout << "You saved the queen and freed the village from terror organisations.\n";
            cout << "People of village started looking towards you as their saviour.\n";
            cout << "Now happiness and peace in the village is back again.\n";
            break;
        }
        for (int i = 0; i < maxEnemySize; i++)
            enemy[i]->levelUp();
        for (int i = 0; i < totalEnemy; i++)
            enemy[i]->respawn();
    }

    void NecessaryInfo() {
        cout << "\nWelcome to RPG Adventure.\n";
        cout << "\nRules:-\n";
        cout << "1. You play as the commoner man of the village and your goal is to save the queen who is captured by the monster called Murlocs. To save the queen's life who is the only kind ruler of the entire kingdom and take revenge of attacking and destroying the village life's, player decides to defeat Murlocs.\n";
        cout << "2. To defeat murlocs player has to collect 5 items like Map, Sword, Shield, Armour and Bow.\n";
        cout << "3. Player and enemy will play 1 turn at a time.\n";
        cout << "4. Player has 2 types of attacks 'Melee and Ranged' at the start and will unlock new abilities which each level passed.\n";
        cout << "5. Enemy stats will increase after each level with increase i in no. of enemies.\n";
        cout << "5. Enemies can also randomly dodge which reduces 50% damage.\n";
        cout << "6. There are 6 levels in this game and after completing each level you get the rewards listed below.\n";
        cout << " a). One Item and a special ability.\n";
        cout << " b). Increased Health and damage stats.\n";
        cout << " c). Health potions to fully recover the player's health.\n";
        cout << "\nSpecial Abilities of Player:-\n";
        cout << "1. Critical Hit - Increases damage by 300% for all attacks.\n";
        cout << "2. Blocker Hit - Blocks all incoming damage.\n";
        cout << "3. Life Steal Hit - The Player recovers a small amount of health after dealing damage.\n";
        cout << "4. Ranged Attack - Player won't take any damage in the next turn.\n";
        cout << "\nSpecial Abilities of Murlocs:-\n";
        cout << "1. Ground Slash - It increases damage by 300% for all attacks.\n";
        cout << "2. Speed Dash - Uses high-speed movement to avoid all damages \n";
        cout << "3. Health Regeneration - Increases  health by a certain fixed amount.\n";
    }

public:
    GameLogic()
    {
        srand(time(0));
    }

    void StartInfo() {
        do {
            exitGame = false;
            cout << "\033[3;42;30m" << "Welcome to" << " \033[0m";
            cout << "\033[3;43;30m" << "Text-Based" << " \033[0m";
            cout << "\033[3;44;30m" << "RPG" << " \033[0m";
            cout << "\033[3;45;30m" << "Adventure" << " \033[0m";
            cout << "\033[3;46;30m" << "Game" << " \033[0m\n";
            cout << "Press 1 to Start. \n";
            cout << "Press 2 for Rules and GameStory.\n";
            cout << "Press 3 to exit the game. \n";
            cout << "\nEnter Your Choice : ";
            cin >> playerChoice;
            switch (playerChoice) {
            case '1': startGame();
                break;
            case '2': NecessaryInfo();
                break;
            case '3': exitGame = true;
                break;
            default: cout << "You entered an invalid input, Choose again!\n";
            }
        } while (!exitGame);
    }
};

int main()
{
    GameLogic gm;
    gm.StartInfo();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
