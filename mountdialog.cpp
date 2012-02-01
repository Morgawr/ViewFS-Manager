#include "mountdialog.h"
#include "ui_mountdialog.h"
#include <stdio.h>
#include <QMessageBox>
#include <QFileDialog>


mountDialog::mountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mountDialog)
{
    ui->setupUi(this);
    ui->typeBox->addItem("move"); //0
    ui->typeBox->addItem("cow"); //1
    ui->typeBox->addItem("mincow"); //2
    ui->typeBox->addItem("merge"); //3
}

mountDialog::~mountDialog()
{
    delete ui;
}

void mountDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void mountDialog::SrcBrowseClicked()
{

    QString string = getDirectoryFromDialog();

    if(string == NULL)
        return;

    ui->srcText->setText(string);
}

void mountDialog::DstBrowseClicked()
{
    QString string = getDirectoryFromDialog();

    if(string == NULL)
        return;

    ui->dstText->setText(string);
}

void mountDialog::ExcpBrowseClicked()
{
    QString string = getDirectoryFromDialog();

    if(string == NULL)
        return;
    if(ui->excpText->text().length() > 0)
    {
        ui->excpText->setText(ui->excpText->text()+",");
    }

    ui->excpText->setText(ui->excpText->text()+"except="+string);
}

void mountDialog::Accepted()
{
    //Fill data before accept
    this->MountCommand = this->fillDataCommand();
    if(this->MountCommand == NULL) /* something went wrong! */
    {
        QMessageBox::about(this,"Cannot Mount Filesystem","Couldn't mount the ViewFS filesystem, please specify the right parameters.");
        this->reject();
        return;
    }

    printf("%s\n",this->MountCommand);
    this->accept();
}

char* mountDialog::fillDataCommand()
{
    char* cmd;

    if(ui->srcText->text().trimmed().length() <= 0) /* Obtain the source directory */
        return NULL;

    QByteArray bytearr = ui->srcText->text().trimmed().toLatin1(); /* Need to save it on the stack else Qt complains and screws up memory */
    const char* source = bytearr.data();

    if(ui->dstText->text().trimmed().length() <= 0) /* Obtain the destination directory */
        return NULL;

    QByteArray bytearr2 = ui->dstText->text().trimmed().toLatin1(); /* Same here, saving on the stack */
    const char* dest = bytearr2.data();

    char* mount_opt;

    switch((Ui::mountType)ui->typeBox->view()->currentIndex().row())
    {
    case Ui::move:
        asprintf(&mount_opt,"%s","move");
        break;
    case Ui::cow:
        asprintf(&mount_opt,"%s","cow");
        break;
    case Ui::mincow:
        asprintf(&mount_opt,"%s","mincow");
        break;
    case Ui::merge:
        asprintf(&mount_opt,"%s","merge");
        break;
    default:
        asprintf(&mount_opt,"%s","move");
    }

    QByteArray bytearr3 = ui->excpText->text().trimmed().toLatin1();

    if(bytearr3.length() > 0)
    {
        char* old = mount_opt; /* Swap values (and free memory) for 'dynamic strcat' */
        asprintf(&mount_opt,"%s,%s",mount_opt,bytearr3.data());
        free(old);
    }

    if(ui->vstatBox->isChecked())
    {
        char* old = mount_opt; /* Swap again */
        asprintf(&mount_opt,"%s,%s",mount_opt,"vstat");
        free(old);
    }


    if(ui->renewBox->isChecked())
    {
        char* old = mount_opt; /* Swap again */
        asprintf(&mount_opt,"%s,%s",mount_opt,"renew");
        free(old);
    }


    asprintf(&cmd,"mount -t viewfs -o %s %s %s",mount_opt,source,dest);

    free(mount_opt);
    return cmd;
}

QString mountDialog::getDirectoryFromDialog()
{
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptOpen);
    filedialog.setFileMode(QFileDialog::DirectoryOnly);

    if(filedialog.exec())
    {
         QString string = filedialog.selectedFiles().last().toLatin1();

         return string;

    }

    return NULL;
}
