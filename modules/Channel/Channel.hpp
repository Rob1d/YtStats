#pragma once

#include <QObject>
#include "../Parser/ISerializable.hpp"
#include "../Video/Video.hpp"

class Channel : public QObject, ISerializable
{
    SERIALIZABLE
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString url READ url)
    Q_PROPERTY(QList<Video *> videos READ videos NOTIFY videosChanged)

public:
    explicit Channel(QObject *parent = nullptr, const QString &name = "", const QString &url = "")
        : QObject(parent), _name(name), _url(url) {

          };

    bool operator==(const Channel &channel)
    {
        return this->_url == channel._url && this->_name == channel._name;
    }

    bool operator==(const QString &url)
    {
        return this->_url == url;
    }

public slots:
    QString name() { return this->_name; }
    QString url() { return this->_url; }
    QList<Video *> videos();

signals:

    void videosChanged();

private:
    QString _url;
    QString _name;
    std::vector<std::shared_ptr<Video>> _videos;
};