#include "productDescription.h"

ProductDescription::ProductDescription()
{
}

ProductDescription::~ProductDescription()
{

}

void ProductDescription::SetPath(const QString &path)
{
    _path = path;
}

void ProductDescription::SetText(const QString &description)
{
    _description = description;
}

void ProductDescription::SetPrice(const QString &price)
{
    _price = price;
}

void ProductDescription::SetFormat(const QString &format)
{
    _format = format;
}

const QString &ProductDescription::Path()
{
    return _path;
}

const QString &ProductDescription::Text()
{
    return _description;
}

const QString &ProductDescription::Price()
{
    return _price;
}

const QString &ProductDescription::Format()
{
    return _format;
}
