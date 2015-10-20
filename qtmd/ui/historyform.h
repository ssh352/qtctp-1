#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryForm(QWidget *parent = 0);
    ~HistoryForm();

public:
    void init();

private slots:
    void on_refreshButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    void refresh();
    void onGotItem(void* p);

private:
    Ui::HistoryForm *ui;
    QStringList ids_col_;
};

#endif // HISTORYFORM_H
