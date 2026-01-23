#pragma once

#include <QObject>
#include "../Parser/ISerializable.hpp"

class Video : public QObject, ISerializable
{
    SERIALIZABLE
    Q_OBJECT
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString url READ url)
    Q_PROPERTY(QString time READ time)

public:
    explicit Video(QObject *parent = nullptr, const QString &title = "", const QString &url = "", const QString &time = "")
        : QObject(parent), _title(title), _url(url), _time(time) {

          };
    bool operator==(const std::string &url)
    {
        return this->_url == url;
    }

    bool operator==(const Video &video)
    {
        return this->_url == video._url;
    }
public slots:
    QString title() { return this->_title; }
    QString url() { return this->_url; }
    QString time() { return this->_time; }

private:
    QString _title;
    QString _url;
    QString _time;
};
