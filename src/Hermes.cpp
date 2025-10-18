#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <qqml.h>

#include "Log.h"
#include "Models/FileList.h"

int main(int argc, char *argv[]) {
    // Start Engine
    Hermes::Log::Init();

    // Setup app
    QGuiApplication app(argc, argv);

    // Engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    qmlRegisterType<Hermes::FileListModel>("Hermes.Models", 1, 0,
                                           "FileListModel");

    // Load app
    engine.loadFromModule("Hermes", "MainView");

    return app.exec();
}
