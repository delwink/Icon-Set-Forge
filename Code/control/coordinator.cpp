#include "coordinator.h"
#include <QFileDialog>
#include <QString>
#include "scannerstrategies/freedesktopscannerstrategy.h"

Coordinator::Coordinator(QObject *parent) :
    QObject(parent)
{
}

void Coordinator::openIconSet(std::unique_ptr<AbstractScannerStrategy> scannerStrategy)
{
    // Create new IconSetOperator which handles all other necessary operations
    std::shared_ptr<IconSetOperator> newOperator(
                new IconSetOperator(std::move(scannerStrategy)));
    openedIconSets.append(newOperator);
}

void Coordinator::openIconSet()
{
    //Filechooser
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                "Open Icon Set", "/usr/share/icons",
                "Freedesktop index.theme Files (index.theme)");

    //TODO: Remove hardcoded IconSet type. This is Testing code.
    std::unique_ptr<FreedesktopScannerStrategy> scanner(
                new FreedesktopScannerStrategy(fileName));

    openIconSet(std::move(scanner));w
}
