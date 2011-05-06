#include"systemManager.h"

#include<stdio.h>

#include"productCatalog.h"

SystemManager::SystemManager()
    :_cataLog(NULL)
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

void SystemManager::EnterFirstLevelTypes(const QStringList typeList)
{
    Catalog()->EnterFirstLevelTypes(typeList);
}

void SystemManager::EnterSecondLevelTypes(const QString firstType,const QStringList typeList)
{
    Catalog()->EnterSecondLevelTypes(firstType,typeList);
}
