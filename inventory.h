#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

class Inventory
{
private:
	
	int pomodori;
	int insalata;
	int pane;
	int hamburger;
	int carne; 

	bool inventory;

public:

	Inventory(bool i)
	{
		pomodori = 0;
		insalata = 0;
		pane = 0; 
		carne = 0;

		hamburger = 0;
		inventory = i;
	}

	void SwapState() {
		if (inventory)
			inventory = false;
		else
			inventory = true;
	}

	bool GetState() {
		return inventory;
	}

	//ADD
	void AddPomodori() {
		pomodori += 1;
	}

	void AddInsalata() {
		insalata += 1;
	}

	void AddPane() {
		pane += 1;
	}

	void AddCarne() {
		carne += 1;
	}

	void AddHamburger() {
		hamburger += 1;
	}


	//SUB
	void SubPomodori() {
		if (pomodori == 0)
			return;
		pomodori -= 1;
	}

	void SubInsalata() {
		if(insalata == 0)
			return;
		insalata -= 1;
	}

	void SubPane() {
		if (pane == 0)
			return;
		pane -= 1;
	}

	void SubCarne() {
		if (carne == 0)
			return;
		carne -= 1;
	}

	void SubHamburger() {
		if (hamburger == 0)
			return;
		hamburger -= 1;
	}

	//GETTERS
	int GetPomodori() {
		return pomodori;
	}

	int GetInsalata() {
		return insalata;
	}

	int GetPane() {
		return pane;
	}

	int GetCarne() {
		return carne;
	}

	int GetHamburger() {
		return hamburger;
	}

	//SETTERS
	void SetPomodori(int value) {
		pomodori = value; 
		return;
	}

	void SetInsalata(int value) {
		insalata = value;
	    return;
	}

	void SetPane(int value) {
		pane = value; 
		return;
	}

	void SetCarne(int value) {
		carne = value;
		return;
	}

	void SetHamburger(int value) {
		hamburger = value; 
		return ;
	}

}; 

#endif
