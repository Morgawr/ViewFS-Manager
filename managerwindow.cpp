#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "mountdialog.h"
#include <QMessageBox>
#include <stdio.h>

ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);

    if(!checkUmProc())
    {
        QMessageBox::about(this,"ViewOS Required!","Error: This program can be used only inside ViewOS with "\
                 "umproc module loaded. (If you are in a ViewOS machine and you see this, load umproc with \"um_add_service umproc\" and try again).");
        exit(1);
    }

    this->RefreshMounts();
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* Refreshes the mount list in the main window */
void ManagerWindow::RefreshMounts()
{
    FILE *fp = setmntent("/proc/mounts","r");
    struct mntent *fs;
    viewfs_mounts.clear();
    ui->mountList->clear();
    while((fs = getmntent(fp))  !=  NULL)
    {
        if(!strcmp(fs->mnt_type,"viewfs")) /* It's a mounted viewfs! */
        {
            viewfs_mounts.push_back(fs);
            QString str;
            str.append(fs->mnt_fsname);
            str.append(" -> ");
            str.append(fs->mnt_dir);
            ui->mountList->addItem(str);
        }
    }

    endmntent(fp);


}

/* Opens a popup window to mount a new partition */
void ManagerWindow::AddMount()
{
    mountDialog mnt(this);

    mnt.exec();

    if(mnt.result()==QDialog::Rejected)
        return;

    const char* result = mnt.MountCommand;

    system(result); /* TODO: Need to make this part better with error detection. Also I need to stop using system! :( */

    RefreshMounts();
}

/* Unmounts the currently selected partition */
void ManagerWindow::RemoveMount()
{
    int selected;
    QItemSelectionModel *qitm = ui->mountList->selectionModel();
    selected = (int)qitm->currentIndex().row();
    if(selected < 0)
        return;

    char* command;
    asprintf(&command,"umount %s",viewfs_mounts[selected]->mnt_dir);

    system(command);

    free(command);
    RefreshMounts();
}

bool ManagerWindow::checkUmProc()
{
    FILE *fp = setmntent("/proc/mounts","r");
    struct mntent *fs;
    bool umproc_loaded = false;
    while ((fs = getmntent(fp))  !=  NULL) /* detect if /proc/mounts is mounted by umproc */
    {
      if(!(strcmp(fs->mnt_fsname,"none") || strcmp(fs->mnt_dir,"/proc/mounts") || strcmp(fs->mnt_type,"proc")))
                      umproc_loaded = true;
    }
    endmntent(fp);
    return umproc_loaded;
}
