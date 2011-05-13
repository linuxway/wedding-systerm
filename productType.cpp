#include "productType.h"

ProductType::ProductType(QString name)
    :_name(name),
    _children(QList<ProductType*>()),
    _description(QList<ProductDescription*>())
{

}

ProductType::~ProductType()
{

}

QString ProductType::Name()
{
    return _name;
}

QList<ProductType*> &ProductType::Children()
{
    return _children;
}

QList<ProductDescription*> &ProductType::DescriptionsFor()
{
    return _description;
}
