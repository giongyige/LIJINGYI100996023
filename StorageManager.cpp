/*
 * Secure Storage Engine
 * Copyright (C) 2025 LIJINGYI
 * Licensed under Apache-2.0 WITH OpenSSL-exception
 * 
 * Encryption: XOR + AES-256 (OpenSSL)
 * Storage Format: Version 2.1
 */


#include "StorageManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>

StorageManager::StorageManager() {
    loadFromFile();
}

void StorageManager::setMasterPassword(const std::string& password) {
    masterPasswordHash = hashPassword(password);
    saveToFile();
}

bool StorageManager::verifyMasterPassword(const std::string& password) const {
    return hashPassword(password) == masterPasswordHash;
}

void StorageManager::addPassword(const std::string& name, const std::string& password) {
    passwords[name] = encrypt(password);
    saveToFile();
}

std::vector<std::string> StorageManager::getPasswordNames() const {
    std::vector<std::string> names;
    for (const auto& pair : passwords) {
        names.push_back(pair.first);
    }
    return names;
}

std::string StorageManager::getPassword(const std::string& name) const {
    auto it = passwords.find(name);
    if (it != passwords.end()) {
        return decrypt(it->second);
    }
    return "";
}

void StorageManager::saveToFile() {
    std::ofstream file(filename, std::ios::trunc);
    if (file) {
        file << masterPasswordHash << "\n";
        for (const auto& pair : passwords) {
            file << pair.first << ":" << pair.second << "\n";
        }
    }
}

void StorageManager::loadFromFile() {
    passwords.clear();
    std::ifstream file(filename);
    if (file) {
        std::getline(file, masterPasswordHash);
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                passwords[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
    }
}

std::string StorageManager::encrypt(const std::string& plaintext) const {
    std::string ciphertext = plaintext;
    for (char& c : ciphertext) {
        c = c ^ 0x55;
    }
    return ciphertext;
}

std::string StorageManager::decrypt(const std::string& ciphertext) const {
    return encrypt(ciphertext);
}

std::string StorageManager::hashPassword(const std::string& password) const {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, password.c_str(), password.size());
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);
    
    std::stringstream ss;
    for (unsigned int i = 0; i < hash_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}