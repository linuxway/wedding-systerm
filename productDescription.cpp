#include "productDescription.h"

ProductDescription::ProductDescription()
    : _path(""),
      _description(""),
      _price(0.0),
      _format(FORMAT_PICTURE)
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

void ProductDescription::SetPrice(double price)
{
    _price = price;
}

void ProductDescription::SetFormat(FORMAT format)
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

double ProductDescription::Price()
{
    return _price;
}

int ProductDescription::Format()
{
    return _format;
}
