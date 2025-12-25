#pragma once
#include "AdoptionList.h"

class HTML : public AdoptionList {
private:
    std::string filename;

public:
    explicit HTML(const std::string &fname);

    void saveToFile() const override;
    void openInApp() const override;
};