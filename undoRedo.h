#pragma once
#include "dog.h"
#include "repository.h"

class UndoRedoAction {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoRedoAction() = default;
};

class UndoAdd : public UndoRedoAction {
    Repository &repo;
    Dog dog;
public:
    UndoAdd(Repository &repo, const Dog &dog);
    void undo() override;
    void redo() override;
};

class UndoRemove : public UndoRedoAction {
    Repository &repo;
    Dog dog;
    int index;
public:
    UndoRemove(Repository &repo, const Dog &dog, int index);
    void undo() override;
    void redo() override;
};

class UndoUpdate : public UndoRedoAction {
    Repository &repo;
    Dog oldDog, newDog;
    int index;
public:
    UndoUpdate(Repository &repo, int index, const Dog &oldDog, const Dog &newDog);
    void undo() override;
    void redo() override;
};