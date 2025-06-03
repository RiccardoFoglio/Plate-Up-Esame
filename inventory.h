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

	//CLEAR
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

	void AddFormaggio() {
		formaggio += 1;
	}

	void AddUovo() {
		uovo += 1;
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

	void SubFormaggio() {
		if (formaggio == 0)
			return;
		formaggio -= 1;
	}

	void SubUovo() {
		if (uovo == 0)
			return;
		uovo -= 1;
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
