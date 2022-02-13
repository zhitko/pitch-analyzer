#include "qmlsetting.h"

QmlSetting::QmlSetting()
    : QObject(nullptr)
{

}

QmlSetting::QmlSetting(const QmlSetting& qmlSetting)
    : QObject(qmlSetting.parent()), name(qmlSetting.name)
    , description(qmlSetting.description), value(qmlSetting.value)
    , key(qmlSetting.key), type(qmlSetting.type)
{

}

QmlSetting::QmlSetting(
        QString key,
        QString type,
        QString name,
        QString value,
        QString description,
        QObject *parent)
    : QObject(parent), key(key), type(type), name(name), description(description), value(value)
{

}

QmlSetting &QmlSetting::operator=(const QmlSetting &qmlSetting)
{
    this->key = qmlSetting.key;
    this->type = qmlSetting.type;
    this->name = qmlSetting.name;
    this->description = qmlSetting.description;
    this->value = qmlSetting.value;
    return *this;
}

QString QmlSetting::getKey()
{
    return this->key;
}

QString QmlSetting::getType()
{
    return this->type;
}

QString QmlSetting::getName()
{
    return this->name;
}

QString QmlSetting::getDescription()
{
    return this->description;
}

QString QmlSetting::getValueString()
{
    return this->value;
}

double QmlSetting::getValueDouble()
{
    return this->value.toDouble();
}

int QmlSetting::getValueInteger()
{
    return this->value.toInt();
}
