#pragma once

#include <QObject>
#include "../Parser/ISerializable.hpp"

class Video : public QObject, ISerializable
{
    SERIALIZABLE
    Q_OBJECT
    Q_PROPERTY(QString title READ title)

public:
    explicit Video(QObject *parent = nullptr, const QString &title = "") : QObject(parent), _title(title) {
                                                                           };
public slots:
    QString title() { return this->_title; }

private:
    QString _title;
};
