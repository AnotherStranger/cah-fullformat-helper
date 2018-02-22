/*
 * cahhelper a simple-to-use application for managing your own Cards Against
 * Humanity game
 * Copyright (C) 2018  André Büsgen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QCoreApplication>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QTimer>
#include "mainclass.h"
#include "mainwindow.h"

/*!
 * \brief createApplication Creates the Qapplication object
 *
 * This method ensures that no GUI components get initialized when the app is
 * started in batchmode.
 *
 * \param argc reference to the argument count
 * \param argv commandline arguments passed to the application
 * \return an instance of QApplication when the application is started in
 * GUI-mode, a QCoreApplication object otherwise.
 */
QCoreApplication* createApplication(int& argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    if (!qstrcmp(argv[i], "--gui") || !qstrcmp(argv[i], "-g")) {
      // Use QApplication for GUIs
      return new QApplication(argc, argv);
    }
  }

  // A core application is sufficient for batchmode
  return new QCoreApplication(argc, argv);
}

int main(int argc, char* argv[]) {
  QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

  QApplication::setApplicationName("cahhelper");
  QApplication::setApplicationVersion("0.1");

  // create the main class
  QSharedPointer<MainWindow> w;  // We need shared pointers here because the
                                 // object gets initialized later on.
  QSharedPointer<MainClass> myMain;

  if (qobject_cast<QApplication*>(app.data())) {  // GUI mode
    w = QSharedPointer<MainWindow>(new MainWindow());
    w->show();
  } else {  // Terminal mode
    myMain = QSharedPointer<MainClass>(new MainClass());

    // connect up the signals
    QObject::connect(myMain.data(), SIGNAL(finished()), app.data(),
                     SLOT(quit()));
    QObject::connect(app.data(), SIGNAL(aboutToQuit()), myMain.data(),
                     SLOT(aboutToQuitApp()));

    // This code will start the messaging engine in QT and in
    // 10ms it will start the execution in the MainClass.run routine;
    QTimer::singleShot(10, myMain.data(), SLOT(run()));
  }

  return app->exec();
}
