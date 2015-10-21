#ifndef INSTRUMENTSFORM_H
#define INSTRUMENTSFORM_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class InstrumentsForm;
}

class InstrumentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstrumentsForm(QWidget *parent = 0);
    ~InstrumentsForm();

public:
    void init();

private slots:
    void on_refreshButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    void refresh();
    void onGotInstrument(void* p);

private:
    Ui::InstrumentsForm *ui;
    QStringList instruments_col_;
};

#endif // INSTRUMENTSFORM_H
