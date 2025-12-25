#pragma once
#include <stack>
#include "repository.h"
#include "AdoptionList.h"
#include "undoRedo.h"

class Service {
private:
    Repository &repo;
    AdoptionList *adoptionList;
    std::stack<UndoRedoAction *> undoStack;
    std::stack<UndoRedoAction *> redoStack;

public:
    Service(Repository &repo, AdoptionList *adoptionList);
    ~Service();

    void clearRedoStack();
    void clearUndoStack();

    void addDog(const Dog &dog);
    void removeDog(int index);
    void updateDog(int index, const Dog &dog);

    void undo();
    void redo();

    const std::vector<Dog> &getAll() const;
    int getSize() const;

    AdoptionList *getAdoptionList() const;
};