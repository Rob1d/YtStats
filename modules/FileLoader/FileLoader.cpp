#include "FileLoader.hpp"
#include <QDebug>
#include <QFileDialog>

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

void FileLoader::openFileDialog()
{
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent)
    {
        if (fileName.isEmpty())
        {
            qDebug() << "No files";
        }
        else
        {
            this->setCurrentFile(fileName);
        }
    };
    QFileDialog::getOpenFileContent("Documents (*.json *.html)", fileContentReady);
}