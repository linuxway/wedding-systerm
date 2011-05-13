#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include<QList>

#include"productType.h"

class QStringList;
class ProductDescription;

class ProductCatalog
{
public:
    ProductCatalog();
    ~ProductCatalog();

    const QList<ProductType*> &FirstLevelTypes();
    const QList<ProductType*> &SecondLevelTypes(QString);
    QList<ProductDescription*> &DescriptionsFor(QString);

    void EnterFirstLevelTypes(const QStringList &typeList);
    void EnterSecondLevelTypes(const QString &firstType,const QStringList &typeList);
    void EnterProductDescriptionForType(const QString&,ProductDescription *);

private:
    void _AddTypes(const QStringList &, QList<ProductType *> &);
    ProductType* _FindType(const QString &);

    QList<ProductType*> _firstLevelTypes;
    QList<ProductType*> _nullProductType;
    QList<ProductDescription*> _nullProductDescription;
};

#endif // PRODUCTCATALOG_H
