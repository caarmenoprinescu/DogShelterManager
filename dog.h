#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;

public:
    Dog();

    Dog(const std::string& breed, const std::string& name, int age, const std::string& photograph);

    const std::string& getBreed() const;
    const std::string& getName() const;
    int getAge() const;
    const std::string& getPhotograph() const;

    void setBreed(const std::string& newBreed);
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setPhotograph(const std::string& newPhotograph);

    void display() const;
};

std::ostream& operator<<(std::ostream& out, const Dog& dog);
std::istream& operator>>(std::istream& in, Dog& dog);

class DogValidator {
public:
    static void validate(const Dog& dog);
};