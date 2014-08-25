#include <QLabel>
#include <QTreeView>
#include <QListView>
#include <QFileDialog>
#include <memory>
#include "iconsetbrowser.h"
#include "model/iconset.h"
#include "model/access/classificationtreemodel.h"
#include "model/access/iconlistmodel.h"
#include "scannerstrategies/freedesktopscannerstrategy.h"

IconSetBrowser::IconSetBrowser(QWidget *parent) :
    QWidget(parent)
{
    // TODO: A lot :-) This is basically to be considered testing code
    BorderLayout *layout = new BorderLayout(this);

    //Filechooser
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Icon Set", "/usr/share/icons",
            "Freedesktop index.theme Files (index.theme)");

    FreedesktopScannerStrategy scanner =
            FreedesktopScannerStrategy(fileName);

    IconSet* iconSet = scanner.loadIconSet().release();

    // List View
    QListView *listView = new QListView(this);

    // Set up List View to display Icons
    listView->setViewMode(QListView::IconMode);
    listView->setGridSize(QSize(100, 100));
    listView->setResizeMode(QListView::Adjust);
    listView->setWordWrap(true);

    IconListModel *listModel = new IconListModel(this, iconSet);
    listView->setModel(listModel);

    // Tree View
    QTreeView *treeView = new QTreeView(this);
    ClassificationTreeModel *treeModel =
            new ClassificationTreeModel(this, iconSet);
    treeView->setModel(treeModel);

    // Resize columns after the model has been set
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
    treeView->resizeColumnToContents(2);


    layout->addWidget(listView, BorderLayout::Center);
    layout->addWidget(treeView, BorderLayout::West);
}
