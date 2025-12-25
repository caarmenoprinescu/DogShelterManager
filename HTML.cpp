#include "HTML.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

HTML::HTML(const std::string &fname) : filename("../files/" + fname) {
}

void HTML::saveToFile() const {
    std::ofstream out(filename);
    out << "<!DOCTYPE html><html><body><table border=\"1\">\n";
    out << "<tr><th>Breed</th><th>Name</th><th>Age</th><th>Photograph</th></tr>\n";
    for (const auto &d: dogs)
        out << "<tr><td>" << d.getBreed() << "</td><td>" << d.getName()
            << "</td><td>" << d.getAge() << "</td><td><a href=\"" << d.getPhotograph()
            << "\">Link</a></td></tr>\n";
    out << "</table></body></html>\n";
    out.close();
}

void HTML::openInApp() const {
    std::string command;

#ifdef _WIN32
    command = "start " + filename;
#elif __APPLE__
    command = "open " + filename;
#elif __linux__
    command = "xdg-open " + filename;
#else
    std::cerr << "Unsupported platform.\n";
    return;
#endif

    if (std::system(command.c_str()) != 0)
        std::cerr << "Failed to open file: " << filename << std::endl;
}