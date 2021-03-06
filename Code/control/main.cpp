#include "view/mainwindow.h"
#include <QApplication>
#include "control/coordinator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("mank319");
    QCoreApplication::setOrganizationDomain("manuel-kehl.de");
    QCoreApplication::setApplicationName("Icon Set Forge");

    QApplication a(argc, argv);
    MainWindow w;
    Coordinator c;

    // Connect the corresponding signals and slots
    QObject::connect(&w, SIGNAL(actionOpenIconSet()),
                     &c, SLOT(openIconSet()));
    QObject::connect(&c, SIGNAL(newIconSetOpened(IconFilterProxyModel*,
                                                 ClassificationTreeModel*)),
                     &w, SLOT(displayNewIconSet(IconFilterProxyModel*,
                                                ClassificationTreeModel*)));
    QObject::connect(&w, SIGNAL(actionDeleteIcon(int, int)),
                     &c, SLOT(deleteIcon(int, int)));


    w.show();

    return a.exec();
}
