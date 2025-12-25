#pragma once
#include "AdoptionList.h"
#include <string>

class CSV : public AdoptionList {
private:
    std::string filename;

public:
    explicit CSV(const std::string &fname);

    void saveToFile() const override;
    void openInApp() const override;
};