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
