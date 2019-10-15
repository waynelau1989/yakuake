#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFont>
#include <QFontMetrics>
#include <QVariant>
#include <QtGlobal>

#include "font_util.h"

int get_current_font_height()
{
    QString homePath = QDir::homePath() + QString::fromLatin1("/");
    QString kcrcPath = homePath + QString::fromLatin1(".config/konsolerc");
    QSettings kcrc(kcrcPath, QSettings::IniFormat);
    QString profileName = kcrc.value(QString::fromLatin1("Desktop Entry/DefaultProfile"),
                                     QString::fromLatin1("Shell.profile")).toString();
    //qDebug() << "profileName:" << profileName;
    QString profilePath = homePath + QString::fromLatin1(".local/share/konsole/") + profileName;
    //qDebug() << "profilePath:" << profilePath;
    QSettings profile(profilePath, QSettings::IniFormat);
    //qDebug() << "All keys:" << profile.allKeys();

    QVariant fontVal = profile.value(QString::fromLatin1("Appearance/Font"));

    QStringList fontInfos = fontVal.toStringList();
    if (fontInfos.isEmpty() || fontInfos.count() < 3) {
        return 0;
    }
    QFont font(fontInfos[0], fontInfos[1].toInt(),
                fontInfos.contains(QString::fromLatin1("Bold")) ? QFont::Bold : QFont::Normal);
    QFontMetrics metrics(font);

    return metrics.height();
}
