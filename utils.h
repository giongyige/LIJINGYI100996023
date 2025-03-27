/*
 * Utility Functions
 * Copyright (C) 2025 LIJINGYI
 * Part of Password Manager project
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random> 

namespace Utils {
    std::string generateRandomString(size_t length);
    bool isValidInput(const std::string& input);
}

#endif