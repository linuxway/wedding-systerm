#ifndef PRODUCTDESCRIPTION_H
#define PRODUCTDESCRIPTION_H

#include<QString>

class ProductDescription
{
public:
    ProductDescription();
    ~ProductDescription();

    void SetPath(const QString&);
    void SetText(const QString&);
    void SetPrice(const QString&);
    void SetFormat(const QString&);

    const QString &Path();
    const QString &Text();
    const QString &Price();
    const QString &Format();

private:
    QString _path;
    QString _price;
    QString _description;
    QString _format;
};

#endif // PRODUCTDESCRIPTION_H
