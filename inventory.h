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
	int formaggio; 
	int uovo; 

public:
	Inventory()
	{
		pomodori = 0;
		insalata = 0;
		pane = 0; 
		carne = 0;
		formaggio = 0;
		uovo = 0;
		hamburger = 0;
	}

	void ClearInventory() {
		pomodori = 0;
		insalata = 0;
		pane = 0;
		carne = 0;
		hamburger = 0;
		formaggio = 0;
		uovo = 0;
	}

	void ClearInventoryAfterRecipeCompleted() {
		pomodori = 0;
		insalata = 0;
		pane = 0;
		carne = 0;
		uovo = 0;
		formaggio = 0;
	}

	//GETTERS
	const int GetPomodori() {
		return pomodori;
	}

	int GetInsalata() {
		return insalata;
	}

	const int GetPane() {
		return pane;
	}

	const int GetCarne() {
		return carne;
	}

	const int GetHamburger() {
		return hamburger;
	}

	const int GetFormaggio() {
		return formaggio; 
	}

	const int GetUovo() {
		return uovo;
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

	void SetFormaggio(int value) {
		formaggio = value;
		return;
	}

	void SetUovo(int value) {
		uovo = value;
		return;
	}

}; 

#endif
