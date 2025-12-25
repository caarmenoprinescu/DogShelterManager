# Dog Shelter Manager

This Qt-based GUI application implements a simple dog shelter management system with separate Admin and User modes.

## Features

- **Admin Mode**
  - Add, remove, and update dogs
  - Data is persisted to file
  - Undo and redo support for add, remove, and update operations

- **User Mode**
  - Browse available dogs
  - Adopt dogs during the current session
  - Filter dogs by breed and maximum age
  - Export the adoption list (CSV or HTML)

## Data Persistence

- Changes made in **Admin Mode** are saved to the repository file.
- In **User Mode**, adoption affects only the current session and does not modify the repository.

This approach keeps the dataset consistent across application runs and simplifies testing.

## Design & architecture

The code is written using standard **object-oriented principles**, including encapsulation, inheritance, and polymorphism.
Undo and redo functionality is implemented using polymorphic actions.
A layered architecture is used to separate the user interface, application logic, and data persistence.

## Technologies

- C++
- Qt 6 (Widgets, Core, Network)
- CMake
