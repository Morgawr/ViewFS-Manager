/*  
 *  Copyright 2012 Federico Pareschi (Morgawr)
 * 
 *  This file is part of the ViewFS-Manager software.
 *
 *  ViewFS-Manager is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 of 
 *  the License, or (at your option) any later version.
 *
 *  ViewFS-Manager is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ViewFS-Manager.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
