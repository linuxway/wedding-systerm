#include "productType.h"

ProductType::ProductType(QString name)
    :_name(name),_secondLevelTypes(QList<ProductType*>())
{

}

ProductType::~ProductType()
{

}

QString ProductType::Name()
{
    return _name;
}

QList<ProductType*> &ProductType::SecondLevelTypes()
{
    return _secondLevelTypes;
}
