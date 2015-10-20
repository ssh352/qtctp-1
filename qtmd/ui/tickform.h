#ifndef TICKFORM_H
#define TICKFORM_H

#include <QWidget>

namespace Ui {
class TickForm;
}

class TickForm : public QWidget
{
    Q_OBJECT

public:
    explicit TickForm(QWidget *parent = 0);
    ~TickForm();
    void Init(QString id);

private:
    void scanMd();
    void onGotMdItem(void* item);

private slots:
    void on_historyButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::TickForm *ui;
    QStringList ids_col_;
    QString id_;
};

#endif // TICKFORM_H
