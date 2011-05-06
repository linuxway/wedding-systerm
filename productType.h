#ifndef PRODUCTTYPE_H
#define PRODUCTTYPE_H

#include<QString>
#include<QList>

class ProductType
{
public:
    ProductType(QString);
    ~ProductType();

    QString Name();
    QList<ProductType*> &SecondLevelTypes();

private:
    QString _name;
    QList<ProductType*> _secondLevelTypes;
};

#endif // PRODUCTTYPE_H
