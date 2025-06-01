#ifndef RECIPE_H
#define RECIPE_H

#include "inventory.h"
#include "game_control.h"
#include <string>

struct Recipe {
    bool pane = false;
    bool carne = false;
    bool pomodori = false;
    bool insalata = false;
    bool uovo = false;
    bool formaggio = false;

    bool isSatisfiedBy(const Inventory& inv) const;
    std::string getName() const;

};

Recipe getRandomRecipe(GameLevel level);

#endif // RECIPE_H