#pragma once

#include <QVariant>
#include <QJsonObject>

QString variantToJson(QVariant variant);
QJsonObject variantToJsonObject(QVariant variant);
QVariant jsonToVariant(QString json);
QVariant jsonObjectToVariant(QJsonObject object);
