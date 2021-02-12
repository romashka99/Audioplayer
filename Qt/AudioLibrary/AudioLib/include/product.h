#pragma
#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <string>

#include "audiolib_global.h"

class AUDIOLIBSHARED_EXPORT Product
{
private:
    QString name;
public:
    Product(QString const& name);
    void setName(QString const& name);
    QString getName();
};

#endif // PRODUCT_H
