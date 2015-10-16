#ifndef TICKFORM_H
#define TICKFORM_H

#include <QWidget>

namespace Ui {
class TickForm;
}
class MdSm;

class TickForm : public QWidget
{
    Q_OBJECT

public:
    explicit TickForm(QWidget *parent = 0);
    ~TickForm();
    void Init(MdSm* mdsm,QString id);

private:
    void scanMd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TickForm *ui;
    QStringList ids_col_;
    void onGotMdItem(void* item);
    MdSm* mdsm_;
    QString id_;
};

#endif // TICKFORM_H
