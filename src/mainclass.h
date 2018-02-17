#ifndef MAINCLASS_H
#define MAINCLASS_H
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QObject>
#include "cardsdeck.h"
#include "commandlineparser.h"
#include "fileparser.h"

class MainClass : public QObject {
  Q_OBJECT
 private:
  QCoreApplication *app;
  CommandLineParser cmdParser;

  cah::FileParser fileParser;
  cah::CardsDeck deck;

 public:
  explicit MainClass(QObject *parent = 0);
  /////////////////////////////////////////////////////////////
  /// Call this to quit application
  /////////////////////////////////////////////////////////////
  void quit();

 signals:
  /////////////////////////////////////////////////////////////
  /// Signal to finish, this is connected to Application Quit
  /////////////////////////////////////////////////////////////
  void finished();

 public slots:
  /////////////////////////////////////////////////////////////
  /// This is the slot that gets called from main to start everything
  /// but, everthing is set up in the Constructor
  /////////////////////////////////////////////////////////////
  void run();

  /////////////////////////////////////////////////////////////
  /// slot that get signal when that application is about to quit
  /////////////////////////////////////////////////////////////
  void aboutToQuitApp();
};
#endif  // MAINCLASS_H
