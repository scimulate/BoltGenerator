/*
    BoltGenerator is an automated CAD assistant which produces standard-size 3D
    bolts per ISO and ASME specifications.
    Copyright (C) 2021  Scimulate LLC <solvers@scimulate.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QQuickWindow>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
    //QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
