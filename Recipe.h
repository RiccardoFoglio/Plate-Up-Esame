// recipe.h
#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "inventory.h"

class Recipe {
private:
    std::string name;
    bool pane = false;
    bool carne = false;
    bool formaggio = false;
    bool insalata = false;
    bool pomodori = false;
    bool uovo = false;

public:
    Recipe() = default;

    Recipe(std::string recipeName, bool p, bool c, bool f = false, bool i = false, bool pom = false, bool u = false)
        : name(recipeName), pane(p), carne(c), formaggio(f), insalata(i), pomodori(pom), uovo(u) {
    }

    bool isSatisfiedBy(Inventory& inv) const;

    const std::string& getName() const { return name; }

    static Recipe getRandomRecipe(int level);

    const std::vector<std::string>& getCurrentIngredients() const {
        static std::vector<std::string> currentIngredients;
        currentIngredients.clear();
    if (pane) currentIngredients.push_back("Pane");
    if (carne) currentIngredients.push_back("Carne");
    if (formaggio) currentIngredients.push_back("Formaggio");
    if (insalata) currentIngredients.push_back("Insalata");
    if (pomodori) currentIngredients.push_back("Pomodori");
    if (uovo) currentIngredients.push_back("Uovo");
	if (currentIngredients.empty()) {
		currentIngredients.push_back("Nessun ingrediente");
	}


    return currentIngredients;
    }

};

#endif // RECIPE_H