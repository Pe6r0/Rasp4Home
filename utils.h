#pragma once
#include <string>
#include <QString>
#include <QColor>

namespace globals {
static const QColor HINT_COLOR { 152, 151, 136 };
static const QColor TEXT_COLOR { 104,104, 104 };
static const QColor BACKGROUND_COLOR { 51, 51, 51 };

QString inline addColorTags(QString text, QColor color){
    text.prepend(QString("<html><span style=\"color:%1\">").arg(color.name()));
    text.append("</span></html>");
    return text;
}
}
