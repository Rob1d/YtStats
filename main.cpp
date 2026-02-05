#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "modules/History/History.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    History *historyInstance = new History(&app);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterSingletonInstance("App.History", 1, 0, "History", historyInstance);

    engine.loadFromModule("YtStats", "Main");
    return app.exec();
}
