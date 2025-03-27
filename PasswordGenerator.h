// PasswordGenerator.h

/*
 * Password Generation Module
 * Copyright (C) 2025 LIJINGYI
 * SPDX-License-Identifier: GPL-3.0-or-later
 * 
 * Character substitution rules:
 * a→@, o→0, e→3, s→$, i→!
 */

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <string>

class PasswordGenerator {
public:
    std::string generatePassword(const std::string& input);

private:
    std::string shuffleCharacters(const std::string& input);
    std::string replaceCharacters(const std::string& input);
};

#endif