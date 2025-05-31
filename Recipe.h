// recipe.h
#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>

#include "game_control.h"



class Recipe {

private:
    std::string name; 
    std::vector<std::string> requiredIngredients;
    std::vector<std::string> currentIngredients;
    bool isCompleted;

public:
    Recipe(const std::string& name, const std::vector<std::string>& ingredients);
    Recipe(const std::vector<std::string>& ingredients);
    void addIngredient(const std::string& ingredient);
    bool checkCompletion() const;
    void resetRecipe();
    std::vector<std::string> getRequiredIngredients() const;
    std::vector<std::string> getCurrentIngredients() const;
    std::string getName() const;
};


Recipe currentRecipe({});
extern Recipe getRandomRecipe(GameLevel level);

#endif // RECIPE_H