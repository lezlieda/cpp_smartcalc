#include "plot.h"

#include "ui_plot.h"

plot::plot(QWidget *parent) : QDialog(parent), ui(new Ui::plot) {
  ui->setupUi(this);

  ui->lineEdit_xMin->setValidator(new QIntValidator(-1000000, 1000000));
  ui->lineEdit_xMax->setValidator(new QIntValidator(-1000000, 1000000));
  ui->lineEdit_yMin->setValidator(new QIntValidator(-1000000, 1000000));
  ui->lineEdit_yMax->setValidator(new QIntValidator(-1000000, 1000000));

  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(close_button()));

  connect(ui->pushButton_print, SIGNAL(clicked()), this, SLOT(print_button()));
}

plot::~plot() { delete ui; }

void plot::close_button() { plot::close(); };

void plot::print_button() {
  if (ui->lineEdit_xMin->text().isEmpty() ||
      ui->lineEdit_xMax->text().isEmpty()) {
    QMessageBox::warning(this, "Attention!", "Domain is not determined!!");
  } else if (ui->lineEdit_yMin->text().isEmpty() ||
             ui->lineEdit_yMax->text().isEmpty()) {
    QMessageBox::warning(this, "Attention!", "Codomain is not determined!!");
  } else if (ui->lineEdit_xMin->text().toInt() >=
             ui->lineEdit_xMax->text().toInt()) {
    QMessageBox::warning(this, "Attention!",
                         "Domain set incorrectly!!"
                         "\nX max =< X min");
  } else if (ui->lineEdit_yMin->text().toInt() >=
             ui->lineEdit_yMax->text().toInt()) {
    QMessageBox::warning(this, "Attention!",
                         "Codomain set incorrectly!!"
                         "\nY max <= Y min");
  } else {
    double xMin = ui->lineEdit_xMin->text().toDouble();
    double xMax = ui->lineEdit_xMax->text().toDouble();
    double yMin = ui->lineEdit_yMin->text().toDouble();
    double yMax = ui->lineEdit_yMax->text().toDouble();
    int steps = 99;
    int ss = (xMax - xMin) * steps + 1;
    QVector<double> x(ss), y(ss);
    QCPGraph *graph = ui->widget->addGraph();
    for (int i = 0; i < ss; i++) {
      x[i] = xMin + 1. / steps * i;
      y[i] = controler.Calculus(func.toStdString(), x[i]);
    }
    for (int i = 1; i < ss - 1; i++) {
      if (fabs(y[i]) > 2 * (yMax - yMin)) {
        y[i] = qQNaN();
      } else if ((y[i] - y[i - 1]) * (y[i + 1] - y[i]) < 0) {
        y[i++] = qQNaN();
      }
    }
    graph->setData(x, y);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(xMin, xMax);
    ui->widget->yAxis->setRange(yMin, yMax);
    ui->widget->replot();
    x.clear();
    y.clear();
  }
};
