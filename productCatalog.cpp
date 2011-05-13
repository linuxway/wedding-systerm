#include "productCatalog.h"

#include <QStringList>

ProductCatalog::ProductCatalog()
    :_firstLevelTypes(QList<ProductType*>()),
     _nullProductType(QList<ProductType*>()),
     _nullProductDescription(QList<ProductDescription*>())
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
    _AddTypes(typeList, _firstLevelTypes);
}

const QList<ProductType*> &ProductCatalog::SecondLevelTypes(QString firstType)
{
    int i;
    for(i = 0; i < _firstLevelTypes.size(); ++i){
        if(_firstLevelTypes[i]->Name() == firstType)
            return _firstLevelTypes[i]->Children();
    }

    return _nullProductType;
}

void ProductCatalog::EnterSecondLevelTypes(const QString &firstType,const QStringList &typeList)
{
    for(int i = 0; i < _firstLevelTypes.size(); ++i){
        if(_firstLevelTypes[i]->Name() == firstType){
            _AddTypes(typeList, _firstLevelTypes[i]->Children());
        }
    }
}

void ProductCatalog::_AddTypes(const QStringList &types, QList<ProductType *> &list)
{
    foreach(QString typeName, types) {
        ProductType *oneType = new ProductType(typeName);
        list.append(oneType);
    }
}

ProductType* ProductCatalog::_FindType(const QString& childType)
{
    /*Find in 1st catalog*/
    for(int i = 0; i < _firstLevelTypes.size(); ++i){
        if(childType == _firstLevelTypes[i]->Name())
            return _firstLevelTypes[i];
    }

    /*Find in child catalog*/
    for(int i = 0; i < _firstLevelTypes.size(); ++i){
        QList<ProductType*> children = _firstLevelTypes[i]->Children();
        for(int j = 0; j < children.size(); ++j){
            if(childType == children[j]->Name())
                return children[j];
        }
    }
    return NULL;
}

void ProductCatalog::EnterProductDescriptionForType(const QString& childType,ProductDescription *pd)
{
    ProductType* pt = _FindType(childType);
    if(pt)
        pt->DescriptionsFor().append(pd);
}

QList<ProductDescription*> &ProductCatalog::DescriptionsFor(QString childType)
{
    ProductType* pt = _FindType(childType);
    if(pt)
        return pt->DescriptionsFor();
    return _nullProductDescription;
}



