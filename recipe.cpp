#include "recipe.h"
#include <cstdlib>

bool Recipe::isSatisfiedBy(const Inventory& inv) const {
    return (!pane || inv.GetPane() >= 1) &&
        (!carne || inv.GetCarne() >= 1) &&
        (!formaggio || inv.GetFormaggio() >= 1) &&
        (!insalata || inv.GetInsalata() >= 1) &&
        (!pomodori || inv.GetPomodori() >= 1) &&
        (!uovo || inv.GetUovo() >= 1);
}

std::string Recipe::getName() const {
    if (pane && carne && !formaggio && !pomodori && !insalata && !uovo) return "Panino 0";
    if (pane && carne && formaggio && !pomodori && !insalata && !uovo) return "Panino 1";
    if (pane && carne && formaggio && insalata && pomodori && !uovo) return "Panino 2";
    if (pane && carne && formaggio && insalata && pomodori && uovo) return "Panino 3";
    return "Ricetta sconosciuta";
}

Recipe getRandomRecipe(GameLevel level) {
    Recipe r;
    int maxRecipeIndex = 0;

    switch (level) {
    case LEVEL_0: maxRecipeIndex = 0; break;
    case LEVEL_1: maxRecipeIndex = 1; break;
    case LEVEL_2: maxRecipeIndex = 2; break;
    case LEVEL_3: maxRecipeIndex = 3; break;
    default: maxRecipeIndex = 0;
    }

    int chosen = rand() % (maxRecipeIndex + 1);

    // Definizione panini
    if (chosen == 0) {
        r.pane = true;
        r.carne = true;
    }
    else if (chosen == 1) {
        r.pane = true;
        r.carne = true;
        r.formaggio = true;
    }
    else if (chosen == 2) {
        r.pane = true;
        r.carne = true;
        r.formaggio = true;
        r.insalata = true;
        r.pomodori = true;
    }
    else if (chosen == 3) {
        r.pane = true;
        r.carne = true;
        r.formaggio = true;
        r.insalata = true;
        r.pomodori = true;
        r.uovo = true;
    }

    return r;
}