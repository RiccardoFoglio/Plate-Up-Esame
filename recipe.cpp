#include "recipe.h"
#include "inventory.h"
#include <random>
#include <vector>

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


