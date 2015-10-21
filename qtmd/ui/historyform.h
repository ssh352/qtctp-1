#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget {
    Q_OBJECT

public:
    explicit HistoryForm(QWidget* parent = 0);
    ~HistoryForm();
    void Init(QString id);

private slots:
    void on_first128_clicked();

    void on_next128_clicked();

    void on_pre128_clicked();

    void on_last128_clicked();

private:
    void onGotTick(void* tick);

private:
    Ui::HistoryForm* ui;
    QStringList instruments_col_;
    QString id_;
};

#endif // HISTORYFORM_H
