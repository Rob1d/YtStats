#include "JsonSerializerVisitor.hpp"

JsonSerializerVisitor::JsonSerializerVisitor(const QByteArray &data)
{
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        throw JsonParsingError(parseError.errorString().toStdString());
    }

    if (jsonDoc.isObject())
    {
        this->_object = jsonDoc.object();
        return;
    }
    if (jsonDoc.isArray())
    {
        this->_array = jsonDoc.array();
        return;
    }
    throw JsonParsingError("Invalid json type");
}

JsonSerializerVisitor::JsonSerializerVisitor(const QJsonObject &object)
{
    this->_object = object;
}

std::unique_ptr<Video> JsonSerializerVisitor::visitVideo()
{
    QString title = this->getValueFromObjectOrThrows("title");
    return std::make_unique<Video>(nullptr, title);
}

std::unique_ptr<History> JsonSerializerVisitor::visitHistory()
{
    if (!this->_array.has_value())
    {
        throw JsonParsingError("Invalid json type, expecting array");
    }
    auto history = std::make_unique<History>();
    for (auto it = this->_array->begin(); it != this->_array->end(); ++it)
    {
        if (!it->isObject())
        {
            throw JsonParsingError("Invalid or malformed json, expected array of objects");
        }
        JsonSerializerVisitor tmpVisitor(it->toObject());
        history->_videos.push_back(tmpVisitor.visitVideo());
    }
    return std::move(history);
}

QString JsonSerializerVisitor::getValueFromObjectOrThrows(const QString &key)
{
    if (!this->_object.has_value())
    {
        qDebug() << "No value";
        throw JsonParsingError("Invalid json type, expecting object");
    }
    auto value = this->_object->value(key);
    if (value.type() != QJsonValue::String)
    {
        qDebug() << "Not valid value";
        throw JsonParsingError("Invalid json key at :" + key.toStdString());
    }
    return value.toString();
}
