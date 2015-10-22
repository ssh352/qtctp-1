#include "sdk_utils.h"

#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QTextCodec>
#include <windows.h>

static void mkDir(QString local_file)
{
    QFileInfo info(local_file);
    QString dirPath = info.absoluteDir().path();
    QDir dir;
    dir.mkpath(dirPath);
}

bool extractQrcFile(QString qrc_file, QString local_file)
{
    QFile inFile(qrc_file);
    QFile outFile(local_file);

    mkDir(local_file);

    if (!inFile.open(QIODevice::ReadOnly))
        return false;
    if (!outFile.open(QIODevice::WriteOnly)) {
        inFile.close();
        return false;
    }

    outFile.write(inFile.readAll());

    inFile.close();
    outFile.close();

    return true;
}

