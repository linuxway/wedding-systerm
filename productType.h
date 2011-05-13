#ifndef PRODUCTTYPE_H
#define PRODUCTTYPE_H

#include<QString>
#include<QList>

class ProductDescription;
class ProductType
{
public:
    ProductType(QString);
    ~ProductType();

    QString Name();
    QList<ProductType*> &Children();
    QList<ProductDescription*> &DescriptionsFor();

private:
    QString _name;
    QList<ProductType*> _children;
    QList<ProductDescription*> _description;
};

#endif // PRODUCTTYPE_H
