#include "productType.h"

ProductType::ProductType(QString name)
    :_name(name)
{

}

ProductType::~ProductType()
{

}

QString ProductType::Name()
{
    return _name;
}
