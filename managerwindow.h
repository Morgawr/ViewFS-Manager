#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include <mntent.h>

namespace Ui {
    class ManagerWindow;
}

class ManagerWindow : public QMainWindow {
    Q_OBJECT
public:
    std::vector<struct mntent*> viewfs_mounts;
    ManagerWindow(QWidget *parent = 0);
    ~ManagerWindow();

public slots:
    void RefreshMounts();
    void AddMount();
    void RemoveMount();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ManagerWindow *ui;
    bool checkUmProc();
};

#endif // MANAGERWINDOW_H
