#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <QStringList>

class ProductCatalog;

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();

    void MakeNewCatalog();
    ProductCatalog* Catalog();

    void EnterFirstLevelTypes(const QStringList);
    void EnterSecondLevelTypes(QString,QStringList);

private:
    ProductCatalog* _cataLog;

};
#endif // SYSTEMMGR_H
