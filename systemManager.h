#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <QStringList>

class ProductCatalog;
class ProductDescription;
class DBFacade;

class SystemManager
{
public:
    SystemManager(DBFacade *);
    ~SystemManager();

    void MakeNewCatalog();
    ProductCatalog* Catalog();

    void EnterFirstLevelTypes(const QStringList&);
    void EnterSecondLevelTypes(const QString&,const QStringList&);
    void EnterProductDescriptionForType(const QString&,ProductDescription *pd);

private:
    ProductCatalog* _cataLog;
    DBFacade *_db;
};
#endif // SYSTEMMGR_H
