#pragma once

#include <QString>

bool extractQrcFile(QString qrc_file, QString local_file);
void mkDir(QString local_file);
QString gbk2utf16(char* gbk);
