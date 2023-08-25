#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVector>

#include "mainwindow.h"
#include "cpp/qcustomplot.h"

extern "C" {
#include "c/s21_SmartCalc_v1.0.h"
}

namespace Ui {
class graphWindow;
}

class graphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit graphWindow(QWidget *parent = nullptr, QString a = "");
  ~graphWindow();
  QString *graph;

 private slots:
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

 private:
  Ui::graphWindow *ui;
  double xBegin = 0, xEnd = 0, h = 0, X = 0,
         Y = 0;  // область отображения X, h - шаг между двумя точками, X -
                 // заполнение вектора
  int N = 0;     // кол-во точек
  void reloadSize();
  void printGraph(QString strX, QString str);
  QString expression = "";
  QVector<double> x = {0}, y = {0};
  int errorGraph = 0;
};

#endif  // GRAPHWINDOW_H
