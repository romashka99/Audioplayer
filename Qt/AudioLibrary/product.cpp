#include "product.h"

Product::Product(QString const& name)
{
    this->setName(name);
}

void Product::setName(QString const& name)
{
    this->name = name;
}

QString Product::getName()
{
    return this->name;
}
