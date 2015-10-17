#include "utils.h"

#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QTextCodec>

void mkDir(QString local_file)
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

QString gbk2utf16(char* gbk){
    QTextCodec* codec = QTextCodec::codecForName("gb18030");
    QString utf16 = codec->toUnicode(gbk);
    return utf16;
}

namespace base {
namespace debug {

#if defined(COMPILER_MSVC)
#pragma optimize("", off)
#endif

void Alias(const void* var) {
}

#if defined(COMPILER_MSVC)
#pragma optimize("", on)
#endif

Base::Base(Derived* derived)
    : derived_(derived) {
}

Base::~Base() {
  derived_->DoSomething();
}

#pragma warning(push)
#pragma warning(disable:4355)
// Disable warning C4355: 'this' : used in base member initializer list.
Derived::Derived()
    : Base(this) {  // C4355
}
#pragma warning(pop)

void Derived::DoSomething() {
}

}  // namespace debug
}  // namespace base
