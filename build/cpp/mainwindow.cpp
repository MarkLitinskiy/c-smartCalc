#include "mainwindow.h"

#include <QDebug>

#include "c/s21_SmartCalc_v1.0.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  // цветовая схема проекта: https://colorscheme.ru/#2-421w0w0w0w0
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна

  /*Цифры*/
  connect(ui->pushButton_Zero, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_One, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Two, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Three, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Four, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Five, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Six, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Seven, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Eight, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Nine, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  /*Операторы*/
  connect(ui->pushButton_Plus, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Min, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Div, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Mult, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Dot, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_BracketOpen, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_BracketClose, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Step, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Mod, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Sin, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Cos, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Tan, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Asin, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Acos, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Atan, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Ln, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Log, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_Sqrt, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  /*Константы*/
  connect(ui->pushButton_Pi, SIGNAL(clicked()), this, SLOT(constants()));
  connect(ui->pushButton_Exp, SIGNAL(clicked()), this, SLOT(constants()));
  /*Очистка*/
  connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbersOperators() {  // обработка кнопок цифр и
                                              // операторов
  if (error != 0) {  // если последняя операция ошибка - стираем строку
    ui->lineEdit_Expression->setText("");
    error = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  expression = ui->lineEdit_Expression->text() + button->text();
  if ((button->text()).length() > 1) {  // Для сложных операторов
    expression = expression + "(";
  }
  ui->lineEdit_Expression->setText(expression);
}

void MainWindow::constants() {  // обработка кнопок-констант
  if (error != 0) {  // если последняя операция ошибка - стираем строку
    ui->lineEdit_Expression->setText("");
    error = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  if (button->text() == "exp")
    expression = ui->lineEdit_Expression->text() + "e";
  else if (button->text() == "Pi")
    expression = ui->lineEdit_Expression->text() + "P";

  ui->lineEdit_Expression->setText(expression);
}

void MainWindow::clear() {  // очистка дисплея
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  expression = ui->lineEdit_Expression->text();
  if (button->text() == "C")
    expression.resize(expression.size() - 1);
  else if (button->text() == "AC")
    expression.clear();
  ui->lineEdit_Expression->setText(expression);
}

void MainWindow::errorFunction(int error) {  // Вывод ошибки по коду
  switch (error) {
    case (-1):
      ui->lineEdit_Expression->setText("Некорректный символ!");
      break;
    case (1):
      ui->lineEdit_Expression->setText("Ошибка ввода sin/sqrt");
      break;
    case (2):
      ui->lineEdit_Expression->setText("Ошибка ввода cos");
      break;
    case (3):
      ui->lineEdit_Expression->setText("Ошибка ввода tan");
      break;
    case (4):
      ui->lineEdit_Expression->setText("Ошибка ввода asin/acos/atan");
      break;
    case (5):
      ui->lineEdit_Expression->setText("Ошибка ввода log/ln");
      break;
    case (6):
      ui->lineEdit_Expression->setText("Ошибка ввода mod");
      break;
    case (7):
      ui->lineEdit_Expression->setText("X не задан!");
      break;
    case (8):
      ui->lineEdit_Expression->setText("В дробном числе слишком много точек!");
      break;
    case (9):
      ui->lineEdit_Expression->setText("Два оператора не могут стоять рядом!");
      break;
    case (10):
      ui->lineEdit_Expression->setText("Пустые скобки не могут быть!");
      break;
    case (11):
      ui->lineEdit_Expression->setText(
          "После открывающей скобки не может быть оператора, кроме минуса!");
      break;
    case (12):
      ui->lineEdit_Expression->setText("Число не может начинаться с точки!");
      break;
    case (13):
      ui->lineEdit_Expression->setText(
          "Перед открывающей скобкой должен быть оператор!");
      break;
    case (14):
      ui->lineEdit_Expression->setText(
          "Колличество открывающих и закрывающих скобок не тождественно!");
      break;
    case (15):
      ui->lineEdit_Expression->setText(
          "Целое число не может начинаться с нуля!");
      break;
    case (16):
      ui->lineEdit_Expression->setText(
          "Нет оператора между числом и функцией!");
      break;
    case (17):
      ui->lineEdit_Expression->setText("Ошибка в выражении!");
      break;
    case (18):
      ui->lineEdit_Expression->setText("Некорректно задан X!");
      break;
  }
}

void MainWindow::calc() {  // функция вычисления
  error = 0;
  QString expression = QString::number(
      calculation(ui->lineEdit_Expression->text().toUtf8().data(),
                  ui->lineEdit_X->text().toUtf8().data(), &error));
  if (error == 0)
    ui->lineEdit_Expression->setText(expression);
  else
    errorFunction(error);
  if (expression == "nan" || expression == "inf")
    error = -2;  // добавляем код ошибки для nan/inf
}

void MainWindow::on_pushButton_Graph_clicked() {
  graphWindow window = graphWindow(nullptr, ui->lineEdit_Expression->text());
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_Equal_clicked() {  // если нажали кнопку
                                                  // вычисления
  calc();
}

void MainWindow::on_pushButton_CreditCalc_clicked() {
  creditWindow window;
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_DeposCalc_clicked() {
  depositWindow window;
  window.setModal(true);
  window.exec();
}
