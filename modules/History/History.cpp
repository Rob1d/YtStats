#include "History.hpp"

QList<Channel *> History::channels()
{
    QList<Channel *> channelsAsQ;
    for (const auto &it : this->_channels)
    {
        channelsAsQ.push_back(it.second.get());
    }
    return channelsAsQ;
}

QList<Video *> History::videos()
{
    QList<Video *> videosAsQ;
    for (const auto &it : this->_videos)
    {
        videosAsQ.push_back(it.get());
    }
    return videosAsQ;
}

void History::init(std::unique_ptr<History> history)
{
    this->_channels = std::move(history->_channels);
    this->_videos = std::move(history->_videos);
    emit this->channelsChanged();
    emit this->videosChanged();
    qDebug() << "History updated with " << this->_channels.size() << " channels and " << this->_videos.size() << " videos";
}