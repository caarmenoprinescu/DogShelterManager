cmake_minimum_required(VERSION 3.22)
project(DogShelterManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
        main.cpp
        dog.cpp
        dog.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        gui.cpp
        gui.h
        gui.ui
        HTML.cpp
        HTML.h
        CSV.cpp
        CSV.h
        undoRedo.cpp
        undoRedo.h
        AdoptionList.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
)