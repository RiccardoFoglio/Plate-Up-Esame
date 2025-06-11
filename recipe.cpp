#include "recipe.h"
#include "inventory.h"
#include <random>
#include <vector>
#include <ctime>
#include <cstdlib>

bool checkMissingIngredient(int n, Inventory inv) {
    if (n == 0) {
        if (inv.GetPane() == 0)
            return true;
    }
    else if (n == 1) {
        if (inv.GetCarneCotta() == 0)
            return true;
    }
    else if (n == 2) {
        if (inv.GetFormaggio() == 0)
            return true;
    }
    else if (n == 3) {
        if (inv.GetPomodori() == 0)
            return true;
    }
    else if (n == 4) {
        if (inv.GetInsalata() == 0)
            return true;
    }
    else if (n == 5) {
        if (inv.GetUovoCotto() == 0)
            return true;
    }
    return false;
}

void Recipe::addIngredient(Inventory& inv, Recipe r) {
    int p = inv.GetPane();
    int cc = inv.GetCarneCotta();
    int uc = inv.GetUovoCotto();
    int pom = inv.GetPomodori();
    int f = inv.GetFormaggio();
    int i = inv.GetInsalata();

    std::string name = r.getName();
    int n;

    if (name == "Deluxe") {
        if (r.isSatisfiedBy(inv))
            return;
        srand(time(NULL));
        n = rand() % 6;
        while (!checkMissingIngredient(n, inv)) {
            n = rand() & 6;
        }
    }
    else if (name == "BigMac") {
        if (r.isSatisfiedBy(inv))
            return;
        srand(time(NULL));
        n = rand() % 5;
        while (!checkMissingIngredient(n, inv)) {
            n = rand() & 5;
        }
    }
    
    else if (name == "Cheeseburger") {
        if (r.isSatisfiedBy(inv))
            return;
        srand(time(NULL));
        n = rand() % 3;
        while (!checkMissingIngredient(n, inv)) {
            n = rand() & 3;
        }
    }
    else {
        if (r.isSatisfiedBy(inv))
            return; 
        srand(time(NULL));
        n = rand() % 2;
        while (!checkMissingIngredient(n, inv)) {
            n = rand() & 2;
        }
    }

    if (n == 0) {
        inv.SetPane(1);
    }
    else if (n == 1) {
        inv.SetCarneCotta(1);
    }
    else if (n == 2) {
        inv.SetFormaggio(1);
    }
    else if (n == 3) {
        inv.SetPomodori(1);
    }
    else if (n == 4) {
        inv.SetInsalata(1);
    }
    else if (n == 5) {
        inv.SetUovoCotto(1);
    }

}

bool Recipe::isSatisfiedBy(Inventory& inv) const {
    return (!pane || inv.GetPane() > 0) &&
		(!carneCotta || inv.GetCarneCotta() > 0) &&
        (!formaggio || inv.GetFormaggio() > 0) &&
        (!insalata || inv.GetInsalata() > 0) &&
        (!pomodori || inv.GetPomodori() > 0) &&
	    (!uovoCotto || inv.GetUovoCotto() > 0);
}

Recipe Recipe::getRandomRecipe(int level) {
    std::vector<Recipe> available;

    if (level >= 0) available.emplace_back("Panino", true, false, true); // solo carneCotta
    if (level >= 1) available.emplace_back("Cheeseburger", true, false, true, true);
    if (level >= 2) available.emplace_back("BigMac", true, false, true, true, true, true);
    if (level >= 3) available.emplace_back("Deluxe", true, false, true, true, true, true, false, true); // aggiungi uovoCotto


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(available.size()) - 1);

    return available[dist(gen)];
}


