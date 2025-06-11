#pragma once
#ifndef BONUS_MALUS_H
#define BONUS_MALUS_H

#include <glm/glm.hpp> 
#include <ctime>
#include <cstdlib>

class BonusMalus
{
private:

	float yPos = 0.3f;
	glm::vec3 bonusMalusPossiblePos[53] = { glm::vec3(0.0f, yPos, 3.0f), glm::vec3(0.0f, yPos, 4.0f), glm::vec3(0.0f, yPos, -3.0f), glm::vec3(0.0f, yPos, -4.0f),
		glm::vec3(-1.0f, yPos, 3.0f), glm::vec3(-1.0f, yPos, 4.0f), glm::vec3(-1.0f, yPos, -3.0f), glm::vec3(-1.0f, yPos, -4.0f),
		glm::vec3(1.0f, yPos, 0.0f), glm::vec3(1.0f, yPos, 1.0f), glm::vec3(1.0f, yPos, 2.0f), glm::vec3(1.0f, yPos, 3.0f), glm::vec3(1.0f, yPos, 4.0f),
		glm::vec3(1.0f, yPos, -1.0f), glm::vec3(1.0f, yPos, -2.0f), glm::vec3(1.0f, yPos, -3.0f), glm::vec3(1.0f, -0.25f, -4.0f), 
		glm::vec3(2.0f, yPos, 0.0f), glm::vec3(2.0f, yPos, 1.0f), glm::vec3(2.0f, yPos, 2.0f), glm::vec3(2.0f, yPos, 3.0f), glm::vec3(2.0f, yPos, 4.0f),
		glm::vec3(2.0f, yPos, -1.0f), glm::vec3(2.0f, yPos, -2.0f), glm::vec3(2.0f, yPos, -3.0f), glm::vec3(2.0f, yPos, -4.0f),
		glm::vec3(3.0f, yPos, 0.0f), glm::vec3(3.0f, yPos, 1.0f), glm::vec3(3.0f, yPos, 2.0f), glm::vec3(3.0f, yPos, 3.0f), glm::vec3(3.0f, yPos, 4.0f),
		glm::vec3(3.0f, yPos, -1.0f), glm::vec3(3.0f, yPos, -2.0f), glm::vec3(3.0f, yPos, -3.0f), glm::vec3(3.0f, yPos, -4.0f),
		glm::vec3(-2.0f, yPos, 0.0f), glm::vec3(-2.0f, yPos, 1.0f), glm::vec3(-2.0f, yPos, 2.0f), glm::vec3(-2.0f, yPos, 3.0f), glm::vec3(-2.0f, yPos, 4.0f),
		glm::vec3(-2.0f, yPos, -1.0f), glm::vec3(-2.0f, yPos, -2.0f), glm::vec3(-2.0f, yPos, -3.0f), glm::vec3(-2.0f, yPos, -4.0f),
		glm::vec3(-3.0f, yPos, 0.0f), glm::vec3(-3.0f, yPos, 1.0f), glm::vec3(-3.0f, yPos, 2.0f), glm::vec3(-3.0f, yPos, 3.0f), glm::vec3(-3.0f, yPos, 4.0f),
		glm::vec3(-3.0f, yPos, -1.0f), glm::vec3(-3.0f, yPos, -2.0f), glm::vec3(-3.0f, yPos, -3.0f), glm::vec3(-3.0f, yPos, -4.0f) };
	glm::vec3 bonusMalusPosition;
	bool isBonusMalusPlaced;
	bool isBonusMalusActive;
	int countBonusMalus;
	int numBonusMalusActive;

public:

	float timeStart;
	bool bonusMalusJustActivated = false;
	bool isStartOfLevel = true;
	bool enableRandom = false;

	BonusMalus() {
		bonusMalusPosition = glm::vec3(0.0f, -0.25f, -3.0f);
		isBonusMalusActive = false;
		isBonusMalusPlaced = false;
		countBonusMalus = 0;
		numBonusMalusActive = 0;
	}

	bool getIsBonusMalusActive() {
		return isBonusMalusActive;
	}

	void setIsBonusMalusActive(bool s) {
		isBonusMalusActive = s;
	}

	void setIsBonusMalusPlaced(bool s) {
		isBonusMalusPlaced = s;
	}


	bool getIsBonusMalusPlaced() {
		return isBonusMalusPlaced;
	}

	int getCountBonusMalus() {
		return countBonusMalus;
	}

	void setCountBonusMalus() {
		countBonusMalus = 1;
	}

	void resetCountBonusMalus() {
		countBonusMalus = 0;
	}

	void resetNumBonusMalusActive() {
		numBonusMalusActive = 0;
	}

	int getRandomBonusMalus(int n) {
		srand(time(NULL));
		numBonusMalusActive = rand() % n + 1;
		return numBonusMalusActive;
	}

	glm::vec3 getRandomBonusMalusPos() {
		srand(time(NULL));
		return bonusMalusPossiblePos[rand() % 53];
	}

	void decidePositionCube(glm::vec3 pos) {
		glm::vec3 possiblePos = getRandomBonusMalusPos();
		while (sqrt((pos.x - possiblePos.x) * (pos.x - possiblePos.x) + (pos.z - possiblePos.z) *
			(pos.z - possiblePos.z)) <= 2.0f) {
			possiblePos = getRandomBonusMalusPos();
		}
		bonusMalusPosition = possiblePos;
		isBonusMalusPlaced = true;
	}

	glm::vec3 getPositionBonusMalus() {
		return bonusMalusPosition;
	}

	bool playerIsOnBonusMalusCube(glm::vec3 pos1, glm::vec3 pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= 0.4f;
	}

	int getNumBonusMalusActive() {
		return numBonusMalusActive;
	}
};
#endif
