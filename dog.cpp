#include "dog.h"
#include <iostream>
#include <sstream>
using namespace std;

Dog::Dog() : breed(""), name(""), age(0), photograph("") {
}

Dog::Dog(const string &breed, const string &name, int age, const string &photograph)
    : breed(breed), name(name), age(age), photograph(photograph) {
}

const string &Dog::getBreed() const { return breed; }
const string &Dog::getName() const { return name; }
int Dog::getAge() const { return age; }
const string &Dog::getPhotograph() const { return photograph; }

void Dog::setBreed(const string &newBreed) { breed = newBreed; }
void Dog::setName(const string &newName) { name = newName; }
void Dog::setAge(int newAge) { age = newAge; }
void Dog::setPhotograph(const string &newPhotograph) { photograph = newPhotograph; }

void Dog::display() const {
    cout << "Breed: " << breed << ", Name: " << name << ", Age: " << age << ", Photograph: " << photograph << endl;
}

std::ostream &operator<<(std::ostream &out, const Dog &d) {
    out << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph();
    return out;
}

std::istream &operator>>(std::istream &in, Dog &d) {
    std::string line;
    if (!std::getline(in, line)) return in;

    std::stringstream ss(line);
    std::string breed, name, age_str, photo;
    int age;

    std::getline(ss, breed, ',');
    std::getline(ss, name, ',');
    std::getline(ss, age_str, ',');
    std::getline(ss, photo);

    try {
        age = std::stoi(age_str);
    } catch (...) {
        return in;
    }

    d = Dog(breed, name, age, photo);
    return in;
}


void DogValidator::validate(const Dog &dog) {
    std::string errors;
    if (dog.getBreed().empty())
        errors += "Breed cannot be empty.\n";
    if (dog.getName().empty())
        errors += "Name cannot be empty.\n";
    if (dog.getAge() <= 0)
        errors += "Age must be greater than 0.\n";
    if (dog.getPhotograph().empty())
        errors += "Photo link cannot be empty.\n";

    if (!errors.empty())
        throw std::runtime_error(errors);
}
