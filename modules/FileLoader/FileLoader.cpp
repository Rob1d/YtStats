#include "FileLoader.hpp"
#include <QDebug>

FileLoader::FileLoader(QObject *parent) : QObject(parent)
{
    this->_fileName = "";
}

void FileLoader::setCurrentFile(const QString &fileName)
{
    qDebug() << "new file !!" << fileName;
    this->_fileName = fileName;
    emit this->currentFileChanged();
}
