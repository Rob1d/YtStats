#pragma once
#include "../Video/Video.hpp"
#include "../History/History.hpp"

#include <memory>

class ISerializerVisitor
{
public:
    virtual ~ISerializerVisitor() = default;

    virtual std::unique_ptr<Video> visitVideo() = 0;
    virtual std::unique_ptr<History> visitHistory() = 0;
};