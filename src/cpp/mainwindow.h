#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "c/s21_SmartCalc_v1.0.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  void errorFunction(int error);

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int error = 0;

 public slots:
  void calc();

 private:
  Ui::MainWindow *ui;
 private slots:
  void digits_numbersOperators();
  void constants();
  void clear();
  void on_pushButton_Graph_clicked();
  void on_pushButton_Equal_clicked();
  void on_pushButton_CreditCalc_clicked();
  void on_pushButton_DeposCalc_clicked();
};
#endif  // MAINWINDOW_H
