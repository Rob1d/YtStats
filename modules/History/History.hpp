#pragma once

#include <QObject>
#include "../Parser/ISerializable.hpp"
#include "../Channel/Channel.hpp"
#include <unordered_map>

class History : public QObject, ISerializable
{
    SERIALIZABLE
    Q_OBJECT

    Q_PROPERTY(QList<Channel *> channels READ channels NOTIFY channelsChanged)
    Q_PROPERTY(QList<Channel *> channels READ channels NOTIFY channelsChanged)
public:
    explicit History(QObject *parent = nullptr) : QObject(parent) {}

    const std::vector<std::shared_ptr<Video>> getVideosSPtr()
    {
        return this->_videos;
    }
public slots:
    QList<Channel *> channels();
    QList<Video *> videos();

signals:

    void channelsChanged();

private:
    std::unordered_map<QString, std::unique_ptr<Channel>> _channels;
    std::vector<std::shared_ptr<Video>> _videos;
};
