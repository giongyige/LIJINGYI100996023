/*
 * Secure Storage Engine
 * Copyright (C) 2025 LIJINGYI
 * Licensed under Apache-2.0 WITH OpenSSL-exception
 * 
 * Encryption: XOR + AES-256 (OpenSSL)
 * Storage Format: Version 2.1
 */

#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <string>
#include <vector>
#include <map>

class StorageManager {
public:
    StorageManager();
    
    // 密码管理接口
    void setMasterPassword(const std::string& password);
    bool verifyMasterPassword(const std::string& password) const;
    void addPassword(const std::string& name, const std::string& password);
    std::vector<std::string> getPasswordNames() const;  // 统一使用这个名称
    std::string getPassword(const std::string& name) const;
    
    // 文件操作
    void saveToFile();
    void loadFromFile();

private:
    std::string masterPasswordHash;
    std::map<std::string, std::string> passwords;  // 统一使用这个成员变量名
    
    std::string encrypt(const std::string& plaintext) const;
    std::string decrypt(const std::string& ciphertext) const;
    std::string hashPassword(const std::string& password) const;
    
    const std::string filename = "passwords.dat";
};

#endif