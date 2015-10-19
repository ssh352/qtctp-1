#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>

namespace Ui {
class DbForm;
}

class DbForm : public QWidget {
    Q_OBJECT

public:
    explicit DbForm(QWidget* parent = 0);
    ~DbForm();
    void Init(QString id);

private slots:
    void on_first128_clicked();

    void on_next128_clicked();

    void on_pre128_clicked();

    void on_last128_clicked();

private:
    void onGotMdItem(void* item);

private:
    Ui::DbForm* ui;
    QStringList ids_col_;
    QString id_;
};

#endif // DBFORM_H
