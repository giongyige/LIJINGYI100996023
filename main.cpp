#include <iostream>
#include <limits>
#include "PasswordGenerator.h"
#include "StorageManager.h"

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showAllPasswords(StorageManager& storage) {
    // 先验证主密码
    std::cout << "Enter master password: ";
    std::string input;
    std::getline(std::cin, input);
    
    if(!storage.verifyMasterPassword(input)) {
        std::cout << "Access denied!\n";
        return;
    }
    
    // 验证通过后才显示密码
    std::cout << "\n[DEBUG] Total passwords in memory: " 
              << storage.getPasswordNames().size() << std::endl;
              
    auto names = storage.getPasswordNames();
    if (names.empty()) {
        std::cout << "No passwords stored.\n";
        return;
    }
    
    std::cout << "\nSaved Passwords:\n";
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout << i + 1 << ". " << names[i] << "\n";
    }
    
    std::cout << "Select password to retrieve (0 to cancel): ";
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    if (choice > 0 && choice <= static_cast<int>(names.size())) {
        std::cout << "Password: " << storage.getPassword(names[choice-1]) << "\n";
    }
}

int main() {
    PasswordGenerator generator;
    StorageManager storage;
    
    // 检查是否已有主密码
    if (storage.getPasswordNames().empty()) {
        std::cout << "First use, set master password: ";
        std::string masterPassword;
        std::cin >> masterPassword;
        clearInputBuffer();
        storage.setMasterPassword(masterPassword);
        std::cout << "Master password set!\n";
    }
    
    while (true) {
        std::cout << "\n=== Password Manager ===\n";
        std::cout << "1. Generate new password\n";
        std::cout << "2. View saved passwords\n";
        std::cout << "3. Add new password\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        clearInputBuffer();
        
        if (choice == 1) {
            std::string input;
            std::cout << "Enter base word: ";
            std::getline(std::cin, input);
            
            std::string password = generator.generatePassword(input);
            std::cout << "Generated Password: " << password << std::endl;
            
            std::cout << "Enter service name (e.g. 'Email'): ";
            std::string service;
            std::getline(std::cin, service);
            
            storage.addPassword(service, password);
            std::cout << "Password saved for " << service << "\n";
        }
        else if (choice == 2) {
            showAllPasswords(storage);
        }
        else if (choice == 3) {
            std::cout << "Enter service name: ";
            std::string service;
            std::getline(std::cin, service);
            
            std::cout << "Enter password: ";
            std::string password;
            std::getline(std::cin, password);
            
            storage.addPassword(service, password);
            std::cout << "Password saved for " << service << "\n";
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
    
    return 0;
}