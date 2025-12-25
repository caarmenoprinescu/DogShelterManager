#include "CSV.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

CSV::CSV(const std::string &fname)
    : filename("../files/" + fname) {
}

void CSV::saveToFile() const {
    std::ofstream out(filename);
    for (const auto &d : dogs) {
        out << d.getBreed() << ","
            << d.getName() << ","
            << d.getAge() << ","
            << d.getPhotograph() << "\n";
    }
    out.close();
}

void CSV::openInApp() const {
#ifdef _WIN32
    std::string command = "start \"\" \"" + filename + "\"";
#elif __APPLE__
    std::string command = "open \"" + filename + "\"";
#elif __linux__
    std::string command = "xdg-open \"" + filename + "\"";
#else
    std::cerr << "Unsupported OS.\n";
    return;
#endif

    if (std::system(command.c_str()) != 0) {
        std::cerr << "Failed to open the file: " << filename << "\n";
    }
}