#pragma once

#include <QString>

bool extractQrcFile(QString qrc_file, QString local_file);
void mkDir(QString local_file);
QString gbk2utf16(char* gbk);

namespace base {
namespace debug {

// Dummy classes to help generate a pure call violation.

class Derived;

class Base {
 public:
  Base(Derived* derived);
  virtual ~Base();
  virtual void DoSomething() = 0;

 private:
  Derived* derived_;
};

class Derived : public Base {
 public:
  Derived();
  virtual void DoSomething();
};


// Make the optimizer think that var is aliased. This is to prevent it from
// optimizing out variables that that would not otherwise be live at the point
// of a potential crash.
void Alias(const void* var);

}  // namespace debug
}  // namespace base
