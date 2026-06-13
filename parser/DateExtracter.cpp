#include "DateExtracter.h"
QDateTime DateExtracter::extract(const QString& raw) const
{
    if(raw.isEmpty()) {return {};}

    QDateTime extracted =QDateTime::fromString(raw,"dd.MM.yyyy HH:mm");
    if(extracted.isValid()) return extracted;
    auto splitRaw = raw.split(' ', Qt::SkipEmptyParts);
    if(splitRaw.size() == 2) {
        extracted =QDateTime::fromString(splitRaw[0],"dd.MM.yyyy");

        if(extracted.isValid()) {
            extracted =extracted.addSecs(splitRaw[1].toInt() * 60);
            return extracted;
        }
    }
    return {};
}
