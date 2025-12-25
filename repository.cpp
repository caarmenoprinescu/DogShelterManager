#include <vector>
#include <fstream>
#include "repository.h"

Repository::Repository(const std::string &file) : fileName(file) {
    loadFromFile(fileName);
}

void Repository::addDog(const Dog &dog) {
    dogs.push_back(dog);
    saveToFile(fileName);
}

void Repository::removeDog(int index) {
    if (index < 0 || index >= dogs.size())
        throw RepositoryException("Invalid index");

    dogs.erase(dogs.begin() + index);
    saveToFile(fileName);
}

void Repository::updateDog(int index, const Dog &dog) {
    if (index < 0 || index >= dogs.size())
        throw RepositoryException("Invalid index");
    dogs[index] = dog;
    saveToFile(fileName);
}

const std::vector<Dog> &Repository::getAll() const {
    return dogs;
}

const Dog &Repository::getDogAt(int index) const {
    if (index < 0 || index >= dogs.size())
        throw RepositoryException("Invalid index");

    return dogs[index];;
}

void Repository::insertDogAt(const Dog &dog, int index) {
    if (index < 0 || index > dogs.size())
        throw RepositoryException("Invalid index");

    dogs.insert(dogs.begin() + index, dog);
    saveToFile(fileName);
}

int Repository::getSize() const {
    return dogs.size();
}

void Repository::loadFromFile(const std::string &filename) {
    dogs.clear();
    std::ifstream fin(filename);
    if (!fin.is_open())
        throw RepositoryException("Could not open file: " + filename);

    Dog d;
    while (fin >> d) {
        dogs.push_back(d);
    }
}

void Repository::saveToFile(const std::string &filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw RepositoryException("Could not write to file");
    for (const auto &d: dogs) {
        fout << d << "\n";
    }
}
