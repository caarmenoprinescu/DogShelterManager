#include "service.h"
#include "dog.h"
#include "undoRedo.h"

Service::Service(Repository &repo, AdoptionList *adoptionList)
    : repo(repo), adoptionList(adoptionList) {
}

Service::~Service() {
    clearUndoStack();
    clearRedoStack();
}


void Service::clearRedoStack() {
    while (!redoStack.empty()) {
        delete redoStack.top();
        redoStack.pop();
    }
}

void Service::clearUndoStack() {
    while (!undoStack.empty()) {
        delete undoStack.top();
        undoStack.pop();
    }
}


void Service::undo() {
    if (undoStack.empty()) throw std::logic_error("No more undos!");
    UndoRedoAction *action = undoStack.top();
    action->undo();
    undoStack.pop();
    redoStack.push(action);
}

void Service::redo() {
    if (redoStack.empty()) throw std::logic_error("No more redos!");
    UndoRedoAction *action = redoStack.top();
    action->redo();
    redoStack.pop();
    undoStack.push(action);
}

void Service::addDog(const Dog &dog) {
    DogValidator::validate(dog);

    const auto &dogs = repo.getAll();
    for (const Dog &d: dogs) {
        if (
            d.getName() == dog.getName() &&
            d.getBreed() == dog.getBreed() && d.getAge() == dog.getAge() && d.getPhotograph() == dog.getPhotograph()) {
            throw std::runtime_error("This dog has already been added!");

        }
        if (d.getPhotograph() == dog.getPhotograph())
            throw std::runtime_error("The dog must have unique photo!");
    }
    repo.addDog(dog);
    undoStack.push(new UndoAdd(repo, dog));
    clearRedoStack();
}

void Service::removeDog(int index) {
    if (index < 0 || index >= repo.getSize()) throw std::out_of_range("Invalid index");
    const Dog dog = repo.getDogAt(index);
    repo.removeDog(index);
    undoStack.push(new UndoRemove(repo, dog, index));
    clearRedoStack();
}

void Service::updateDog(int index, const Dog &dog) {
    DogValidator::validate(dog);

    if (index < 0 || index >= repo.getSize()) throw std::out_of_range("Invalid index");
    const Dog oldDog = repo.getDogAt(index);
    repo.updateDog(index, dog);
    undoStack.push(new UndoUpdate(repo, index, oldDog, dog));
    clearRedoStack();
}


const std::vector<Dog> &Service::getAll() const {
    return repo.getAll();
}

int Service::getSize() const {
    return repo.getSize();
}

AdoptionList *Service::getAdoptionList() const {
    return adoptionList;
}
