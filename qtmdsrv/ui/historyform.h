#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>
#include <QVector>

namespace Ui {
class HistoryForm;
}

#define USE_QCUSTOMPLOT

#ifndef USE_QCUSTOMPLOT
class QwtPlotCurve;
#endif
namespace leveldb{
class DB;
}

class HistoryForm : public QWidget {
    Q_OBJECT

public:
    explicit HistoryForm(QWidget* parent = 0);
    ~HistoryForm();
    void init(QString id,leveldb::DB* db,bool display_bar);

private slots:
    void on_first128_clicked();
    void on_next128_clicked();
    void on_pre128_clicked();
    void on_last128_clicked();
    void on_seekButton_clicked();
    void on_delButton_clicked();

private:
    void onGotTick(QString key,void* tick);
    void onGotBarM1(QString key,void* tick);
    void initGraph();
    void drawGraph();

    void on_first128Tick_clicked();
    void on_next128Tick_clicked();
    void on_pre128Tick_clicked();
    void on_last128Tick_clicked();
    void on_seekButtonTick_clicked();

    void on_first128Bar_clicked();
    void on_next128Bar_clicked();
    void on_pre128Bar_clicked();
    void on_last128Bar_clicked();
    void on_seekButtonBar_clicked();

private:
    Ui::HistoryForm* ui;
    QStringList instruments_col_;
    QString id_;
    QVector<double> x_;
    QVector<double> y_;

#ifndef USE_QCUSTOMPLOT
    QwtPlotCurve *curve_;
#endif

    leveldb::DB *db_ = nullptr;
    bool display_bar_ = false;
};

#endif // HISTORYFORM_H
