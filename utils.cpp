/*
 * Utility Functions
 * Copyright (C) 2025 LIJINGYI
 * Part of Password Manager project
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "utils.h"
#include <random>     
#include <algorithm>  
#include <cctype>     

namespace Utils {
    std::string generateRandomString(size_t length) {
        const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
        std::string result;
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<size_t> dist(0, charset.size() - 1);
        for (size_t i = 0; i < length; ++i) {
            result += charset[dist(g)];
        }
        return result;
    }

    bool isValidInput(const std::string& input) {
        return !input.empty();
    }
}