#include <QDebug>
#include <QDirIterator>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QPalette>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickStyle>
#include <qfont.h>
#include <qfontdatabase.h>
#include <qqml.h>

#include "Appearence/Theme.h"
#include "Engine/Engine.h"
#include "Log.h"
#include "Models/FileList.h"

void RegisterTypes() {
    qmlRegisterType<Hermes::FileListModel>("Hermes.Models", 1, 0,
                                           "FileListModel");
    qmlRegisterType<Hermes::QmlLogger>("Hermes.Log", 1, 0, "Logger");
    qmlRegisterType<Hermes::HermesEngine>("Hermes", 1, 0, "Engine");
}

void RegisterResources() {
    // Add fonts
    int id = QFontDatabase::addApplicationFont(
        ":/qt/qml/Hermes/resources/Inter.ttc");
    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);
        // fontFamilies will contain all font families in the TTC
        for (const QString &family : fontFamilies) {
            TRACE("Loaded font family: {}", family.toStdString());
        }
    } else
        ERROR("Failed to add Inter font!");
}

int main(int argc, char *argv[]) {
    // Start Engine
    Hermes::HermesEngine hermes;

    // Setup app
    QGuiApplication app(argc, argv);
    RegisterResources();
    RegisterTypes();

    // Font and themeing
    auto defaultFont = QFontDatabase::font("Inter", "Regular", 12);
    app.setFont(defaultFont);

    Hermes::Themes::CatppuccinMachiatto().Apply(app);

    // Engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() {
            CRITICAL("ObjectCreationFailed! Quitting!");
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    // Load QML View
    engine.rootContext()->setContextProperty("engine", &hermes);
    engine.loadFromModule("Hermes", "MainView");

    return app.exec();
}
