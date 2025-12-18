#pragma once

#include "../ISerializerVisitor.hpp"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class JsonSerializerVisitor
{
public:
    class JsonParsingError : public std::runtime_error
    {
    public:
        JsonParsingError(const std::string &error) : std::runtime_error("Error when parsing json" + error) {}
    };

    JsonSerializerVisitor(const QByteArray &data);
    JsonSerializerVisitor(const QJsonObject &object);

    std::unique_ptr<Video> visitVideo();
    std::unique_ptr<History> visitHistory();

private:
    QString getValueFromObjectOrThrows(const QString &key);
    std::optional<QJsonObject>
        _object;
    std::optional<QJsonArray> _array;
};