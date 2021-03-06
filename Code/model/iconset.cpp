#include "model/iconset.h"

IconSet::IconSet(
        std::unique_ptr<QVector<Icon>> icons,
        std::unique_ptr<IconClassification> classifications
        ) :
    icons(std::move(icons)),
    classifications(std::move(classifications)),
    groups(new QVector<IconGroup>)
{

}

const Icon &IconSet::getIcon(int index) const
{
    return icons->at(index);
}

int IconSet::iconCount() const
{
    return icons->size();
}

void IconSet::deleteIcon(int index, int count)
{
    icons->remove(index, count);
    notifyObservers();
}

void IconSet::insertIcon(int index, Icon icon)
{
    icons->insert(index, icon);
    notifyObservers();
}

IconClassification *IconSet::getClassifications()
{
    // Return a pointer without releasing ownership
    return classifications.get();
}

void IconSet::addObserver(IconSetObserver *observer)
{
    this->observers.append(observer);
}

void IconSet::notifyObservers()
{
    for (auto observer : observers) {
        observer->update();
    }
}
