#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    // Setup app
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Basic");

    // Engine
    QQmlApplicationEngine engine;
    QObject::connect(&engine,
            &QQmlApplicationEngine::objectCreationFailed,&app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    // Load app
    engine.loadFromModule("Hermes", "MainView");

    return app.exec();
}
