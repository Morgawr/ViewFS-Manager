#ifndef MOUNTDIALOG_H
#define MOUNTDIALOG_H

#include <QDialog>

namespace Ui {
    class mountDialog;
    enum mountType{
        move = 0,
        cow = 1,
        mincow = 2,
        merge = 3
    };
}

class mountDialog : public QDialog {
    Q_OBJECT

public:
    mountDialog(QWidget *parent = 0);
    ~mountDialog();
    char* MountCommand;

public slots:
    void SrcBrowseClicked();
    void DstBrowseClicked();
    void ExcpBrowseClicked();
    void Accepted();

protected:
    void changeEvent(QEvent *e);

private:
    QString getDirectoryFromDialog();
    char* fillDataCommand();
    Ui::mountDialog *ui;
};

#endif // MOUNTDIALOG_H
