#ifndef INSTRUMENTSFORM_H
#define INSTRUMENTSFORM_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class InstrumentsForm;
}
namespace leveldb{
class DB;
}

class InstrumentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstrumentsForm(QWidget *parent = 0);
    ~InstrumentsForm();

public:
    void init(leveldb::DB* db,bool display_bar);

private slots:
    void on_refreshButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    void refresh();
    void onGotInstrument(void* p);

private:
    Ui::InstrumentsForm *ui;
    QStringList instruments_col_;
    leveldb::DB* db_ = nullptr;
    bool display_bar_ = false;
};

#endif // INSTRUMENTSFORM_H
