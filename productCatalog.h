#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include<QList>

#include"productType.h"

class QStringList;
class ProductCatalog
{
public:
    ProductCatalog();
    ~ProductCatalog();

    const QList<ProductType*> &FirstLevelTypes();
    const QList<ProductType*> &SecondLevelTypes(QString);

    void EnterFirstLevelTypes(const QStringList &typeList);
    void EnterSecondLevelTypes(const QString &firstType,const QStringList &typeList);

private:
    QList<ProductType*> _firstLevelTypes;
};

#endif // PRODUCTCATALOG_H
