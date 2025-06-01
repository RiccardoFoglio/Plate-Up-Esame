// recipe.h
#ifndef RECIPE_H
#define RECIPE_H

#include <string>
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

};

#endif // RECIPE_H