#ifndef MERGEFORM_H
#define MERGEFORM_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class MergeForm;
}

class MergeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MergeForm(QWidget *parent = 0);
    ~MergeForm();
    void init();

signals:
    void mergeClicked();

private slots:
    void updateProgress(int progress);
    void beginMerge();
    void endMerge();
    void on_pushButton_clicked();

    void on_closeButton_clicked();

private:
    void closeEvent (QCloseEvent *event) override;

private:
    Ui::MergeForm *ui;
    bool merging_ = false;
};

#endif // MERGEFORM_H
