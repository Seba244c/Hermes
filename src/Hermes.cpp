#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <qqml.h>

#include "Engine/Engine.h"
#include "Log.h"
#include "Models/FileList.h"

int main(int argc, char *argv[]) {
    // Start Engine
    Hermes::HermesEngine hermes;

    // Setup app
    QGuiApplication app(argc, argv);

    // Engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() {
            CRITICAL("ObjectCreationFailed! Quitting!");
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    qmlRegisterType<Hermes::FileListModel>("Hermes.Models", 1, 0,
                                           "FileListModel");
    qmlRegisterType<Hermes::QmlLogger>("Hermes.Log", 1, 0, "Logger");

    // Load app
    engine.loadFromModule("Hermes", "MainView");

    return app.exec();
}
