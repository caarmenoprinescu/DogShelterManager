#pragma once

#include <QWidget>
#include <QPixmap>
#include "service.h"
#include "ui_gui.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Gui : public QWidget {
    Q_OBJECT

public:
    explicit Gui(Service &srv, QWidget *parent = nullptr);

private slots:
    void onSwitchToAdmin();

    void onSwitchToUser();

    void onAddDog();

    void onRemoveDog();

    void onUpdateDog();

    void onNextDog();

    void onAdoptDog();

    void onFilterDogs();

    void onViewAdoptionList();

    void onUndo();

    void onRedo();

private:
    Ui::Gui ui;
    Service &service;

    std::vector<Dog> userDogs;
    int currentDogIndex = 0;
    QNetworkAccessManager *networkManager;

    void populateTable();

    void clearAdminInputs();

    void showCurrentDog();

    void resetUserDogs();
};
