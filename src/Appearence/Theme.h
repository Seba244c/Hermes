#pragma once

#include <QColor>
#include <qguiapplication.h>
#include <qpalette.h>

#include "Log.h"

namespace Hermes {
struct Theme {
    const QColor Window;
    const QColor WindowText;
    const QColor Base0;
    const QColor Base1;
    const QColor Text;
    const QColor TextSelection;
    const QColor Surface0, Surface1, Surface2;

    void Apply(QGuiApplication &app) const {
        QPalette p;
        p.setColor(QPalette::Window, Window);
        p.setColor(QPalette::Dark, Window);
        p.setColor(QPalette::WindowText, WindowText);
        p.setColor(QPalette::Base, Base0);
        p.setColor(QPalette::AlternateBase, Base1);
        p.setColor(QPalette::Text, Text);
        p.setColor(QPalette::ColorRole::HighlightedText, TextSelection);
        p.setColor(QPalette::Light, Surface2);
        p.setColor(QPalette::Midlight, Surface1);
        p.setColor(QPalette::Mid, Surface0);
        app.setPalette(p);
    }
};

namespace Themes {
Theme CatppuccinMachiatto();
}
} // namespace Hermes
