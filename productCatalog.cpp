#include "productCatalog.h"

#include <QStringList>

ProductCatalog::ProductCatalog()
    :_firstLevelTypes(QList<ProductType*>()),
     _nullProductType(QList<ProductType*>())
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

const QList<ProductType*> &ProductCatalog::SecondLevelTypes(QString firstType)
{
    int i;
    for(i = 0; i < _firstLevelTypes.size(); ++i){
        if(_firstLevelTypes[i]->Name()==firstType)
            return _firstLevelTypes[i]->Children();
    }
    return _nullProductType;

}

void ProductCatalog::EnterSecondLevelTypes(const QString &firstType,const QStringList &typeList)
{
    for(int i = 0; i < _firstLevelTypes.size(); ++i){
        if(_firstLevelTypes[i]->Name()==firstType){
            foreach(QString typeName, typeList) {
                ProductType *type = new ProductType(typeName);
                (_firstLevelTypes[i]->Children()).append(type);
            }
        }
    }
}
