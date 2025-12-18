#pragma once

#include <QObject>
#include <QQmlEngine>

class FileLoader : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString fileName READ fileName WRITE setCurrentFile NOTIFY currentFileChanged)

public:
    explicit FileLoader(QObject *parent = nullptr);

public slots:
    QString fileName() { return this->_fileName; }

    void setCurrentFile(const QString &fileName);

    void openFileDialog();

signals:
    void currentFileChanged();

private:
    QString _fileName;
};
