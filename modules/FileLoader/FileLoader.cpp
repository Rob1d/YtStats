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

void FileLoader::openFileDialog(History *history)
{
    auto fileContentReady = [this, history](const QString &fileName, const QByteArray &fileContent)
    {
        if (fileName.isEmpty())
        {
            qDebug() << "No files";
        }
        else
        {
            try
            {
                this->setCurrentFile(fileName);
                JsonSerializerVisitor serializer(fileContent);
                history->init(serializer.visitHistory());
            }
            catch (const std::exception &e)
            {
                qDebug() << "Exception occured :" << e.what();
            }
        }
    };
    try
    {
        QFileDialog::getOpenFileContent("Documents (*.json *.html)", fileContentReady);
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception occured :" << e.what();
    }
}
