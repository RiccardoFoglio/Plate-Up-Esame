// recipe.c
#include "recipe.h"
#include <cstdlib> // for rand()
#include <algorithm> // for std::find
#include <iostream>
#include "game_control.h"
#include <vector>

#include "game_control.h"




Recipe::Recipe(const std::string& name, const std::vector<std::string>& ingredients)
    : name(name), requiredIngredients(ingredients), isCompleted(false) {}


void Recipe::addIngredient(const std::string& ingredient) {
    currentIngredients.push_back(ingredient);
    isCompleted = checkCompletion();
}

bool Recipe::checkCompletion() const {
    if (currentIngredients.size() != requiredIngredients.size())
        return false;

    for (const auto& req : requiredIngredients) {
        if (std::find(currentIngredients.begin(), currentIngredients.end(), req) == currentIngredients.end()) {
            return false;
        }
    }
    return true;
}

void Recipe::resetRecipe() {
    currentIngredients.clear();
    isCompleted = false;
}

std::vector<std::string> Recipe::getRequiredIngredients() const {
    return requiredIngredients;
}

std::vector<std::string> Recipe::getCurrentIngredients() const {
    return currentIngredients;
}

Recipe getRandomRecipe(GameLevel level) {
   
    std::vector<Recipe> pool;

    switch (level) {
    case LEVEL_0:
        pool.push_back({ "Panino 0", { "Pane", "Carne" } });
        break;
    case LEVEL_1:
        pool.push_back({ "Panino 0", { "Pane", "Carne" } });
        pool.push_back({ "Panino 1", { "Pane", "Carne", "Formaggio" } });
        break;
    case LEVEL_2:
        pool.push_back({ "Panino 2", { "Pane", "Carne", "Formaggio", "Insalata", "Pomodoro" } });
        pool.push_back({ "Panino 3", { "Pane", "Carne", "Insalata", "Formaggio", "Uova", "Pomodoro" } });
        break;
    default:
        pool.push_back({ "Panino base", { "Pane" } });
        break;
    }

    if (pool.empty()) {
        throw std::runtime_error("Pool di ricette vuoto!");
    }

    int index = rand() % pool.size();
    return pool[index];
}

std::string Recipe::getName() const {
    return name;
}
