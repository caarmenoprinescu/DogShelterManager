#include <QApplication>
#include <QInputDialog>
#include "repository.h"
#include "CSV.h"
#include "HTML.h"
#include "service.h"
#include "gui.h"

#include <QStringList>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Repository repo("../files/dogs.txt");

    QStringList formats;
    formats << "HTML" << "CSV";
    bool ok;
    QString format = QInputDialog::getItem(nullptr, "Select Format", "Choose adoption list format:", formats, 0, false,
                                           &ok);

    if (!ok) return 0;

    AdoptionList *adoptionList;
    if (format == "CSV") {
        adoptionList = new CSV("adoption.csv");
    } else {
        adoptionList = new HTML("adoption.html");
    }

    Service service(repo, adoptionList);
    Gui gui(service);
    gui.show();

    int result = app.exec();
    delete adoptionList;
    return result;
}
