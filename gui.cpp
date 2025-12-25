#include "gui.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDesktopServices>
#include <QUrl>
#include <climits>
#include <QShortcut>
#include <QToolTip>

Gui::Gui(Service &srv, QWidget *parent)
    : QWidget(parent), service(srv) {
    ui.setupUi(this);

    ui.table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    networkManager = new QNetworkAccessManager(this);

    connect(ui.switchToAdminButton, &QPushButton::clicked, this, &Gui::onSwitchToAdmin);
    connect(ui.switchToUserButton, &QPushButton::clicked, this, &Gui::onSwitchToUser);

    connect(ui.addButton, &QPushButton::clicked, this, &Gui::onAddDog);
    connect(ui.removeButton, &QPushButton::clicked, this, &Gui::onRemoveDog);
    connect(ui.updateButton, &QPushButton::clicked, this, &Gui::onUpdateDog);

    connect(ui.nextButton, &QPushButton::clicked, this, &Gui::onNextDog);
    connect(ui.adoptButton, &QPushButton::clicked, this, &Gui::onAdoptDog);
    connect(ui.filterButton, &QPushButton::clicked, this, &Gui::onFilterDogs);
    connect(ui.viewAdoptionListButton, &QPushButton::clicked, this, &Gui::onViewAdoptionList);

    connect(ui.table, &QTableWidget::cellClicked, [this, &srv](int row, int) {
        if (row >= 0 && row < srv.getSize()) {
            const Dog &d = srv.getAll()[row];
            ui.breedInput->setText(QString::fromStdString(d.getBreed()));
            ui.nameInput->setText(QString::fromStdString(d.getName()));
            ui.ageInput->setText(QString::number(d.getAge()));
            ui.photoInput->setText(QString::fromStdString(d.getPhotograph()));
        }
    });

    connect(ui.undoButton, &QPushButton::clicked, this, &Gui::onUndo);
    connect(ui.redoButton, &QPushButton::clicked, this, &Gui::onRedo);

    QShortcut *undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    connect(undoShortcut, &QShortcut::activated, this, &Gui::onUndo);

    QShortcut *redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    connect(redoShortcut, &QShortcut::activated, this, &Gui::onRedo);

    populateTable();
    resetUserDogs();
    showCurrentDog();
}

void Gui::onSwitchToAdmin() {
    ui.modeStack->setCurrentWidget(ui.adminWidget);
    populateTable();
}

void Gui::onSwitchToUser() {
    ui.modeStack->setCurrentWidget(ui.userWidget);
    resetUserDogs();
    showCurrentDog();
}

void Gui::onAddDog() {
    try {
        bool ok;
        int age = ui.ageInput->text().toInt(&ok);
        if (!ok) {
            QToolTip::showText(ui.ageInput->mapToGlobal(QPoint(0, ui.ageInput->height())), "Age must be a number!");
            return;
        }
        Dog d(
            ui.breedInput->text().toStdString(),
            ui.nameInput->text().toStdString(),
            age,
            ui.photoInput->text().toStdString()
        );
        service.addDog(d);
        populateTable();
        clearAdminInputs();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Gui::onRemoveDog() {
    QList<QTableWidgetItem *> selectedItems = ui.table->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Select a dog to remove.");
        return;
    }

    int row = selectedItems.first()->row();

    try {
        service.removeDog(row);
        populateTable();
        ui.table->clearSelection();
        clearAdminInputs();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Gui::onUpdateDog() {
    int row = ui.table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Select a dog to update.");
        return;
    }
    try {
        bool ok;
        int age = ui.ageInput->text().toInt(&ok);
        if (!ok) {
            QToolTip::showText(ui.ageInput->mapToGlobal(QPoint(0, ui.ageInput->height())), "Age must be a number!");
            return;
        }
        Dog d(
            ui.breedInput->text().toStdString(),
            ui.nameInput->text().toStdString(),
            age,
            ui.photoInput->text().toStdString()
        );
        service.updateDog(row, d);
        populateTable();
        clearAdminInputs();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Gui::onNextDog() {
    if (userDogs.empty()) return;
    currentDogIndex = (currentDogIndex + 1) % userDogs.size();
    showCurrentDog();
}

void Gui::onAdoptDog() {
    if (userDogs.empty()) return;
    const Dog &d = userDogs[currentDogIndex];
    service.getAdoptionList()->add(d);
    service.getAdoptionList()->saveToFile();
    userDogs.erase(userDogs.begin() + currentDogIndex);
    if (userDogs.empty()) {
        ui.dogDetails->setText("No more dogs available.");
        ui.dogImageLabel->clear();
        return;
    }
    if (currentDogIndex >= (int) userDogs.size())
        currentDogIndex = 0;
    showCurrentDog();
}

void Gui::onFilterDogs() {
    QString breed = ui.filterBreedInput->text();
    QString ageStr = ui.filterAgeInput->text();
    int maxAge = ageStr.isEmpty() ? INT_MAX : ageStr.toInt();
    userDogs.clear();
    for (const Dog &d: service.getAll()) {
        if ((breed.isEmpty() || QString::fromStdString(d.getBreed()).compare(breed, Qt::CaseInsensitive) == 0)
            && d.getAge() <= maxAge) {
            userDogs.push_back(d);
        }
    }
    currentDogIndex = 0;
    showCurrentDog();
}

void Gui::onViewAdoptionList() {
    service.getAdoptionList()->saveToFile();
    service.getAdoptionList()->openInApp();
}

void Gui::populateTable() {
    const auto &dogs = service.getAll();
    ui.table->setRowCount((int) dogs.size());
    ui.table->setColumnCount(4);
    for (int i = 0; i < (int) dogs.size(); ++i) {
        const Dog &d = dogs[i];
        ui.table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
        ui.table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
        ui.table->setItem(i, 2, new QTableWidgetItem(QString::number(d.getAge())));
        ui.table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(d.getPhotograph())));
    }
    ui.table->setHorizontalHeaderLabels({"Breed", "Name", "Age", "Photo"});
    ui.table->resizeColumnsToContents();
}

void Gui::clearAdminInputs() {
    ui.breedInput->clear();
    ui.nameInput->clear();
    ui.ageInput->clear();
    ui.photoInput->clear();
}

void Gui::showCurrentDog() {
    if (userDogs.empty()) {
        ui.dogDetails->setText("No dogs available.");
        ui.dogImageLabel->clear();
        return;
    }
    const Dog &d = userDogs[currentDogIndex];
    ui.dogDetails->setText(
        QString("Breed: %1\nName: %2\nAge: %3\n")
        .arg(QString::fromStdString(d.getBreed()))
        .arg(QString::fromStdString(d.getName()))
        .arg(d.getAge())
    );

    QUrl url(QString::fromStdString(d.getPhotograph()));
    if (url.isLocalFile()) {
        QPixmap pix;
        if (pix.load(url.toLocalFile())) {
            ui.dogImageLabel->setPixmap(pix.scaled(ui.dogImageLabel->size(), Qt::KeepAspectRatio));
        } else {
            ui.dogImageLabel->setText("Image not available.");
        }
    } else {
        QNetworkReply *reply = networkManager->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            QPixmap pix;
            if (pix.loadFromData(reply->readAll())) {
                ui.dogImageLabel->setPixmap(pix.scaled(ui.dogImageLabel->size(), Qt::KeepAspectRatio));
            } else {
                ui.dogImageLabel->setText("Image not available.");
            }
            reply->deleteLater();
        });
    }
}

void Gui::resetUserDogs() {
    userDogs = service.getAll();
    currentDogIndex = 0;
}

void Gui::onUndo() {
    try {
        service.undo();
        populateTable();
        resetUserDogs();
        showCurrentDog();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Undo Error", e.what());
    }
}

void Gui::onRedo() {
    try {
        service.redo();
        populateTable();
        resetUserDogs();
        showCurrentDog();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Redo Error", e.what());
    }
}