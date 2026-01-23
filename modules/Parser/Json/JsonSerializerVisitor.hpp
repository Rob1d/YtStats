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
        JsonParsingError(const std::string &jsonPart, const std::string &value, const std::string &message) : std::runtime_error("Error at " + jsonPart + " invalid value : " + value + " message: " + message) {}
    };

    JsonSerializerVisitor(const QByteArray &data);
    JsonSerializerVisitor(const QJsonObject &object);

    std::shared_ptr<Video> visitVideo();
    std::unique_ptr<Channel> visitChannel();
    std::unique_ptr<History> visitHistory();

private:
    template <typename T>
    T getValueFromObjectOrThrows(const QString &key)
    {
        constexpr bool is_valid = std::is_same_v<T, QString> ||
                                  std::is_same_v<T, QJsonObject> ||
                                  std::is_same_v<T, double> ||
                                  std::is_same_v<T, int> ||
                                  std::is_same_v<T, QJsonArray> ||
                                  std::is_same_v<T, bool>;

        static_assert(is_valid, "Template type must be a valid json type !");

        if (!this->_object.has_value())
        {
            qDebug() << "No value";
            throw JsonParsingError("Invalid json type for " + key.toStdString() + ", expecting object");
        }
        auto value = this->_object->value(key);
        QJsonValue::Type valueType = templateToJsonValueType<T>();
        if (value.type() != valueType)
        {
            qDebug() << "Not valid value";
            throw JsonParsingError(QJsonDocument(this->_object.value()).toJson().toStdString(), key.toStdString(), "Invalid type");
        }
        return value.toVariant().value<T>();
    }

    template <typename T>
    QJsonValue::Type templateToJsonValueType()
    {
        if constexpr (std::is_same_v<T, QString>)
        {
            return QJsonValue::String;
        }
        else if constexpr (std::is_same_v<T, QJsonObject>)
        {
            return QJsonValue::Object;
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return QJsonValue::Double;
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return QJsonValue::Double;
        }
        else if constexpr (std::is_same_v<T, QJsonArray>)
        {
            return QJsonValue::Array;
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return QJsonValue::Bool;
        }
        throw std::runtime_error("Unsupported template type");
    }
    std::optional<QJsonObject>
        _object;
    std::optional<QJsonArray> _array;
};