#pragma once

#define SERIALIZABLE                 \
    friend class ISerializerVisitor; \
    friend class JsonSerializerVisitor;

class ISerializerVisitor;
class JsonSerializerVisitor;

class ISerializable
{
public:
    friend class ISerializerVisitor;
    friend class JsonSerializerVisitor;
};