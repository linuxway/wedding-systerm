#ifndef PRODUCTTYPE_H
#define PRODUCTTYPE_H

#include<QString>

class ProductType
{
public:
    ProductType(QString);
    ~ProductType();

    QString Name();

private:
    QString _name;
};

#endif // PRODUCTTYPE_H
