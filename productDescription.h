#ifndef PRODUCTDESCRIPTION_H
#define PRODUCTDESCRIPTION_H

#include<QString>

class ProductDescription
{
public:
    enum FORMAT {
        FORMAT_BEGIN = 0,
        FORMAT_PICTURE = 0,
        FORMAT_MOVIE = 1,
        FORMAT_END = 1
      };

    ProductDescription();
    ~ProductDescription();

    void SetPath(const QString&);
    void SetText(const QString&);
    void SetPrice(double);
    void SetFormat(FORMAT);

    const QString &Path();
    const QString &Text();
    double Price();
    int Format();

private:
    QString _path;
    QString _description;
    double _price;
    FORMAT _format;
};

#endif // PRODUCTDESCRIPTION_H
