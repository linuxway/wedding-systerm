#include"systemManager.h"

//#include<stdio.h>

#include"productCatalog.h"

SystemManager::SystemManager(DBFacade *db)
    : _cataLog(NULL),
      _db(db)
{

}

SystemManager::~SystemManager()
{

}

void SystemManager::MakeNewCatalog()
{
    _cataLog = new ProductCatalog();
}

ProductCatalog* SystemManager::Catalog()
{
    return _cataLog;
}

void SystemManager::EnterFirstLevelTypes(const QStringList& typeList)
{
    Catalog()->EnterFirstLevelTypes(typeList);
}

void SystemManager::EnterSecondLevelTypes(const QString& firstType,const QStringList& typeList)
{
    Catalog()->EnterSecondLevelTypes(firstType,typeList);
}

void SystemManager::EnterProductDescriptionForType(const QString& childType,ProductDescription *pd)
{
    Catalog()->EnterProductDescriptionForType(childType,pd);
}
