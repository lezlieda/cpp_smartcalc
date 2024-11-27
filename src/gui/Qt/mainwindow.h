#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <cstring>

#include "../../headers/controler.h"

#include "inputx.h"
#include "plot.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  bool invalid_input();
  char *inputPrepare(QString str);

 private:
  Ui::MainWindow *ui;
  inputX *x_input;
  plot *draw_plot;
  QString xxx;
  QString rr1;
  int clickCounter = 0;
  s21::Controler controler;

 private slots:
  void input_number();
  void input_operator();
  void input_function();
  void clear_button();
  void delete_button();
  void equal_button();
  void plot_button();
  void calc_button();

 public slots:
  void getXvalue(QString a) { xxx = a; };
  void getRange(QString a) { rr1 = a; };

 signals:
  void sendFormula(QString);
};
#endif  // MAINWINDOW_H
