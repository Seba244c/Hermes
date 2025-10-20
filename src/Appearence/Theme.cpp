#include "Theme.h"

namespace Hermes::Themes {
Theme CatppuccinMachiatto() {
    const QColor Rosewater(244, 219, 214);
    const QColor Flamingo(240, 198, 198);
    const QColor Pink(245, 189, 230);
    const QColor Mauve(198, 160, 246);
    const QColor Red(237, 135, 150);
    const QColor Maroon(238, 153, 160);
    const QColor Peach(245, 169, 127);
    const QColor Yellow(238, 212, 159);
    const QColor Green(166, 218, 149);
    const QColor Teal(139, 213, 202);
    const QColor Sky(145, 215, 227);
    const QColor Sapphire(125, 196, 228);
    const QColor Blue(138, 173, 244);
    const QColor Lavender(183, 189, 248);
    const QColor Text(202, 211, 245);
    const QColor Subtext1(184, 192, 224);
    const QColor Subtext0(165, 173, 203);
    const QColor Overlay2(147, 154, 183);
    const QColor Overlay1(128, 135, 162);
    const QColor Overlay0(110, 115, 141);
    const QColor Surface2(91, 96, 120);
    const QColor Surface1(73, 77, 100);
    const QColor Surface0(54, 58, 79);
    const QColor Base(36, 39, 58);
    const QColor Mantle(30, 32, 48);
    const QColor Crust(24, 25, 38);

    const QColor Selection(147, 154, 183, 64); // Overlay 2 at 25% opacity

    return {.Window = Base,
            .WindowText = Text,
            .Base0 = Crust,
            .Base1 = Mantle,
            .Text = Text,
            .TextSelection = Selection,
            .Surface0 = Surface0,
            .Surface1 = Surface1,
            .Surface2 = Surface2};
}
} // namespace Hermes::Themes
