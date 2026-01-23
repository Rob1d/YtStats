#include "Channel.hpp"

QList<Video *> Channel::videos()
{
    QList<Video *> videosAsQ;
    for (const auto &it : this->_videos)
    {
        videosAsQ.push_back(it.get());
    }
    return videosAsQ;
}