#pragma once

#include <QObject>
#include "../Parser/ISerializable.hpp"
#include "../Video/Video.hpp"

class History : public QObject, ISerializable
{
    SERIALIZABLE
    Q_OBJECT

    Q_PROPERTY(QList<Video *> videos READ videos NOTIFY videosChanged)
public:
    explicit History(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    QList<Video *> videos();

signals:

    void videosChanged();

private:
    std::vector<std::unique_ptr<Video>> _videos;
};
