#include "productCatalog.h"

#include <QStringList>

ProductCatalog::ProductCatalog()
    :_firstLevelTypes(QList<ProductType*>())
{
}

ProductCatalog::~ProductCatalog()
{
    foreach(ProductType *type, _firstLevelTypes) {
        if (type) {
            delete type;
            type = NULL;
        }
    }
}

const QList<ProductType*> &ProductCatalog::FirstLevelTypes()
{
    return _firstLevelTypes;
}

void ProductCatalog::EnterFirstLevelTypes(const QStringList &typeList)
{
    foreach(QString typeName, typeList) {
        ProductType *type = new ProductType(typeName);
        _firstLevelTypes.append(type);
    }
}
