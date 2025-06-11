// recipe.h
#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "inventory.h"
#include "bonus_malus.h"

class Recipe {
private:
    std::string name;
    bool pane = false;
    bool carne = false;
	bool carneCotta = false; // Per ricette con carne cotta
    bool formaggio = false;
    bool insalata = false;
    bool pomodori = false;
    bool uovo = false;
    bool uovoCotto = false; // Per ricette con carne cotta

public:
    Recipe() = default;

    Recipe(std::string recipeName, bool p, bool c, bool cc = false, bool f = false, bool i = false, bool pom = false, bool u = false, bool uc = false)
        : name(recipeName), pane(p), carne(c), carneCotta(cc), formaggio(f), insalata(i), pomodori(pom), uovo(u), uovoCotto(uc) {
    }

    void addIngredient(Inventory& inv, Recipe r);

    bool isSatisfiedBy(Inventory& inv) const;

    const std::string& getName() const { return name; }

    // Getter per ogni ingrediente
    bool hasPane() const { return pane; }
    bool hasCarne() const { return carne; }
    bool hasCarneCotta() const { return carneCotta; }
    bool hasFormaggio() const { return formaggio; }
    bool hasInsalata() const { return insalata; }
    bool hasPomodori() const { return pomodori; }
    bool hasUovo() const { return uovo; }
    bool hasUovoCotto() const { return uovoCotto; }

    static Recipe getRandomRecipe(int level);

};

#endif // RECIPE_H