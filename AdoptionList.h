#pragma once
#include <vector>
#include "dog.h"

class AdoptionList {
protected:
    std::vector<Dog> dogs;
public:
    virtual void add(const Dog& d) { dogs.push_back(d); }
    virtual void saveToFile() const = 0;
    virtual void openInApp() const = 0;
    virtual ~AdoptionList() = default;
};
