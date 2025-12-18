#include "History.hpp"

QList<Video *> History::videos()
{
    QList<Video *> videosAsQ;
    for (const auto &it : this->_videos)
    {
        videosAsQ.push_back(it.get());
    }
    return videosAsQ;
}
