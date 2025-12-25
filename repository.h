#pragma once
#include <vector>
#include "dog.h"

class Repository {
private:
    std::vector<Dog> dogs;
    std::string fileName;

public:
    Repository() = default;

    explicit Repository(const std::string &file);

    void addDog(const Dog &dog);

    void removeDog(int index);

    void updateDog(int index, const Dog &dog);

    void insertDogAt(const Dog &dog, int index);

    const Dog &getDogAt(int index) const;

    const std::vector<Dog> &getAll() const;

    int getSize() const;

    void loadFromFile(const std::string &filename);

    void saveToFile(const std::string &filename) const;
};


#include <stdexcept>
#include <string>

class RepositoryException : public std::exception {
private:
    std::string message;

public:
    explicit RepositoryException(const std::string &msg) : message(msg) {
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};
