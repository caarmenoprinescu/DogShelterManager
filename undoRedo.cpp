#include "undoRedo.h"

// UndoAdd
UndoAdd::UndoAdd(Repository &repo, const Dog &dog) : repo(repo), dog(dog) {}

void UndoAdd::undo() {
    auto &dogs = repo.getAll();
    for (size_t i = 0; i < dogs.size(); ++i) {
        if (dogs[i].getName() == dog.getName() && dogs[i].getBreed() == dog.getBreed()) {
            repo.removeDog((int)i);
            break;
        }
    }
}

void UndoAdd::redo() {
    repo.addDog(dog);
}

// UndoRemove
UndoRemove::UndoRemove(Repository &repo, const Dog &dog, int index) 
    : repo(repo), dog(dog), index(index) {}

void UndoRemove::undo() {
    repo.insertDogAt(dog, index);

}

void UndoRemove::redo() {
    repo.removeDog(index);
}

// UndoUpdate
UndoUpdate::UndoUpdate(Repository &repo, int index, const Dog &oldDog, const Dog &newDog)
    : repo(repo), oldDog(oldDog), newDog(newDog), index(index) {}

void UndoUpdate::undo() {
    repo.updateDog(index, oldDog);
}

void UndoUpdate::redo() {
    repo.updateDog(index, newDog);
}