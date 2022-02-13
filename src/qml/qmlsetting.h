#ifndef QMLSETTING_H
#define QMLSETTING_H

#include <QObject>

class QmlSetting : public QObject
{
    Q_GADGET
    Q_PROPERTY(QString key READ getKey)
    Q_PROPERTY(QString type READ getType)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString description READ getDescription)
    Q_PROPERTY(QString value READ getValueString)
public:
    explicit QmlSetting();
    explicit QmlSetting(const QmlSetting& qmlSetting);
    explicit QmlSetting(
            QString key,
            QString type,
            QString name,
            QString value,
            QString description,
            QObject *parent = nullptr);

    QmlSetting& operator=(const QmlSetting& qmlSetting);

    QString getKey();
    QString getType();
    QString getName();
    QString getDescription();
    QString getValueString();
    double getValueDouble();
    int getValueInteger();

private:
    QString key;
    QString type;
    QString name;
    QString description;
    QString value;
};

Q_DECLARE_METATYPE(QmlSetting)

#endif // QMLSETTING_H
