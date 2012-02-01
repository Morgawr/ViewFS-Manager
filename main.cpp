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
 
#include <QtGui/QApplication>
#include "managerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ManagerWindow w;
    w.show();

    return a.exec();
}
