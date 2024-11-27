#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include <QMessageBox>
#include <QVector>


#include "../../headers/controler.h"


namespace Ui {
class plot;
}

class plot : public QDialog {
  Q_OBJECT

 public:
  explicit plot(QWidget *parent = nullptr);
  ~plot();

 private:
  Ui::plot *ui;
  char *fun;
  int counter = 0;
  QString func;
  s21::Controler controler;

  //  QVector<double> x, y;

 private slots:
  void close_button();
  void print_button();

 public slots:
  void getFunc(QString a) { func = a; };
};

#endif  // PLOT_H
