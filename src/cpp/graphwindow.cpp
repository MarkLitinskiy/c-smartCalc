#include "graphwindow.h"

#include <QDebug>
#include <iostream>

#include "ui_graphwindow.h"
#include "qcustomplot.h"
extern "C" {
double calculation(char *strIn, char *X, int *error);
}

graphWindow::graphWindow(QWidget *parent, QString str)
    : QDialog(parent), ui(new Ui::graphWindow) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  expression = str;
  reloadSize();
  qDebug() << str;
  QString toStr = QString::number(xBegin, 'g', 7);
  qDebug() << toStr;
  printGraph(toStr, str);
}

graphWindow::~graphWindow() { delete ui; }

void graphWindow::printGraph(QString strX, QString str) {
  for (X = xBegin; X <= xEnd; X += h) {
    if (X < 0.1 && X > -0.1)  // исключение для нуля(криво переводится)
      X = 0;
    strX = QString::number(X, 'g', 7);
    Y = calculation(str.toUtf8().data(), strX.toUtf8().data(), &errorGraph);
    if (errorGraph == 0) {
      x.push_back(X);
      y.push_back(Y);
    } else {
      ui->label_test->setText("В точке произошла ошибка вычисления");
    }
    errorGraph = 0;
  }
  x.remove(0);  // удиление самого первого элемента массива, который (0,0)
  y.remove(0);

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void graphWindow::on_pushButton_2_clicked() {
  reloadSize();
  QString toStr = QString::number(xBegin, 'g', 7);
  printGraph(toStr, expression);
}

void graphWindow::reloadSize() {
  h = ui->doubleSpinBox_step->value();
  xBegin = ui->doubleSpinBox_Xmin->value();
  xEnd = ui->doubleSpinBox_Xmax->value() + h;

  ui->widget->xAxis->setRange(ui->doubleSpinBox_Xmin->value() - 5,
                              ui->doubleSpinBox_Xmax->value() + 5);
  ui->widget->yAxis->setRange(ui->doubleSpinBox_Ymin->value() - 5,
                              ui->doubleSpinBox_Ymax->value() + 5);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  N = (xEnd - xBegin) / h + 2;
}

void graphWindow::on_pushButton_clicked() { close(); }
