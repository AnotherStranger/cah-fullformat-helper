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
