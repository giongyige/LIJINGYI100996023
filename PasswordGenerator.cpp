// PasswordGenerator.cpp

/*
 * Password Generation Module
 * Copyright (C) 2025 LIJINGYI
 * SPDX-License-Identifier: GPL-3.0-or-later
 * 
 * Character substitution rules:
 * a→@, o→0, e→3, s→$, i→!
 */


#include "PasswordGenerator.h"
#include <algorithm>
#include <random>
#include <map>

std::string PasswordGenerator::generatePassword(const std::string& input) {
    std::string shuffled = shuffleCharacters(input);
    std::string replaced = replaceCharacters(shuffled);
    return replaced;
}

std::string PasswordGenerator::shuffleCharacters(const std::string& input) {
    std::string result = input;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(result.begin(), result.end(), g);
    return result;
}

std::string PasswordGenerator::replaceCharacters(const std::string& input) {
    std::map<char, char> replacements = {
        {'a', '@'}, {'o', '0'}, {'e', '3'}, {'s', '$'}, {'i', '!'}
    };
    std::string result = input;
    for (char& c : result) {
        if (replacements.find(tolower(c)) != replacements.end()) {
            c = replacements[tolower(c)];
        }
    }
    return result;
}