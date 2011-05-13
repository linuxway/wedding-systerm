#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <QStringList>

class ProductCatalog;
class ProductDescription;

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();

    void MakeNewCatalog();
    ProductCatalog* Catalog();

    void EnterFirstLevelTypes(const QStringList&);
    void EnterSecondLevelTypes(const QString&,const QStringList&);
    void EnterProductDescriptionForType(const QString&,ProductDescription *pd);

private:
    ProductCatalog* _cataLog;

};
#endif // SYSTEMMGR_H
