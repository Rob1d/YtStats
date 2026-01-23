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

std::shared_ptr<Video> JsonSerializerVisitor::visitVideo()
{
    return std::make_shared<Video>(nullptr,
                                   this->getValueFromObjectOrThrows<QString>("title"),
                                   this->getValueFromObjectOrThrows<QString>("titleUrl"),
                                   this->getValueFromObjectOrThrows<QString>("time"));
}

std::unique_ptr<History> JsonSerializerVisitor::visitHistory()
{
    if (!this->_array.has_value() || this->_object.has_value())
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
        auto vidJsonValue = it->toObject();
        JsonSerializerVisitor tmpVisitor(vidJsonValue);
        auto video = tmpVisitor.visitVideo();
        history->_videos.push_back(video);
        // handle channels
        // handle of video made by multiple channels soon
        JsonSerializerVisitor channelVisitor(tmpVisitor.getValueFromObjectOrThrows<QJsonArray>("subtitles").at(0).toObject());
        auto channel = channelVisitor.visitChannel();
        auto findedChannel = history->_channels.find(channel->url());
        if (findedChannel == history->_channels.end())
        {
            channel->_videos.push_back(video);
            history->_channels.insert({channel->url(), std::move(channel)});
        }
        else
        {
            findedChannel->second->_videos.push_back(video);
        }
    }
    return std::move(history);
}

std::unique_ptr<Channel> JsonSerializerVisitor::visitChannel()
{
    QString channelName = this->getValueFromObjectOrThrows<QString>("name");
    QString url = this->getValueFromObjectOrThrows<QString>("url");
    return std::make_unique<Channel>(nullptr, channelName, url);
}
