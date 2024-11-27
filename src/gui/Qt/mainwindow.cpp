#include "mainwindow.h"

#include "../../headers/controler.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // ввод чисел
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(input_number()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(input_number()));
  // скобки
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(input_number()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(input_number()));
  // операции
  connect(ui->pushButton_dif, SIGNAL(clicked()), this, SLOT(input_operator()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(input_operator()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_operator()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(input_operator()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(input_operator()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(input_operator()));
  // функции
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_function()));
  // редактирование
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear_button()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(delete_button()));
  // рассчёт
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equal_button()));
  // построить график
  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(plot_button()));

  ui->lineEdit_sum->setValidator(new QIntValidator(1, INT_MAX));
  ui->lineEdit_duration->setValidator(new QIntValidator(1, 600));

  ui->doubleSpinBox_interes->setButtonSymbols(QAbstractSpinBox::NoButtons);
  ui->doubleSpinBox_interes->setLocale(QLocale::C);
  ui->doubleSpinBox_interes->clear();

  connect(ui->pushButton_Calc, SIGNAL(clicked()), this, SLOT(calc_button()));
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::invalid_input() {
  int res = 0;
  QString str = ui->main_display->text();
  res += !str.compare("Invalid input!");
  res += !str.compare("inf");
  res += !str.compare("-inf");
  res += !str.compare("nan");
  res += !str.compare("-nan");
  return res;
}

void MainWindow::input_number() {
  QPushButton *button = (QPushButton *)sender();
  if (invalid_input() || clickCounter == 1) {
    clickCounter--;
    ui->main_display->clear();
    ui->main_display->setStyleSheet("font: regular");
  }
  ui->main_display->insert(button->text());
}

void MainWindow::input_operator() {
  QPushButton *button = (QPushButton *)sender();
  if (invalid_input()) ui->main_display->clear();
  if (clickCounter == 1) {
    clickCounter--;
    ui->main_display->setStyleSheet("font: regular");
  }
  ui->main_display->insert(button->text());
}

void MainWindow::input_function() {
  QPushButton *button = (QPushButton *)sender();
  if (invalid_input() || clickCounter == 1) {
    clickCounter--;
    ui->main_display->clear();
    ui->main_display->setStyleSheet("font: regular");
  }
  ui->main_display->insert(button->text());
  ui->main_display->insert("(");
}

void MainWindow::clear_button() { ui->main_display->clear(); }

void MainWindow::delete_button() {
  if (invalid_input()) {
    ui->main_display->clear();
  } else if (clickCounter == 1) {
    clickCounter--;
    ui->main_display->setStyleSheet("font: regular");
  }
  ui->main_display->backspace();
}

void MainWindow::equal_button() {
  QString input_str = ui->main_display->text();
  input_str.replace("π", "pi");
  double x = 1;
  if (ui->main_display->text().contains("x")) {
    x_input = new inputX(this);
    x_input->setResult(0);
    connect(x_input, &inputX::sendXvalue, this, &MainWindow::getXvalue);
    x_input->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                            Qt::WindowTitleHint);
    x_input->exec();
    x = xxx.toDouble();
    if (xxx.isEmpty() == true) x = 0;
    delete x_input;
  }
  double dresult = 0;
  int ex = 0;
  try {
    dresult = controler.Calculus(input_str.toStdString(), x);
  } catch (...) {
    ++ex;
    ui->main_display->setStyleSheet("font: bold");
    ui->main_display->setText("Invalid input!");
  }

  if (!ex) {
    char output[256];
    sprintf(output, "%.*lf", ui->numbers_accuracy->value(), dresult);
    QString out = QString::fromUtf8(output);
    out.replace(",", ".");
    input_str.replace("pi", "π");
    if (!ui->checkBox->isChecked() && ui->numbers_accuracy->value()) {
      while (out.back() == '0') out.chop(1);
      if (out.back() == '.') out.chop(1);
    }
    input_str.append(" = ");
    input_str.append(out);
    if (input_str.contains("x")) {
      input_str.append("; x = ");
      input_str.append(xxx);
    }
    ui->second_display->append(input_str);
    ui->main_display->setText(out);
    ui->main_display->setStyleSheet("font: bold");

    clickCounter = 1;
  }
}

void MainWindow::plot_button() {
  QString input_str = ui->main_display->text();
  int ex = 0;
  try {
    controler.Calculus(input_str.toStdString(), 1);
  } catch (...) {
    ++ex;
    ui->main_display->setStyleSheet("font: bold");
    ui->main_display->setText("Invalid input!");
  }
  if (!ex) {
    draw_plot = new plot(this);
    connect(this, &MainWindow::sendFormula, draw_plot, &plot::getFunc);
    emit sendFormula(input_str);
    input_str.insert(0, "F(x) = ");
    draw_plot->setWindowTitle(input_str);
    draw_plot->exec();
    delete draw_plot;
    ui->second_display->append(input_str);
    ui->main_display->clear();
  }
}

void MainWindow::calc_button() {
  if (ui->lineEdit_duration->text().isEmpty()) {
    QMessageBox::warning(this, "Attention!", "No loan term!");
  } else if (ui->lineEdit_sum->text().isEmpty()) {
    QMessageBox::warning(this, "Attention!", "Loan amount not set!");
  } else if (!ui->doubleSpinBox_interes->value()) {
    QMessageBox::warning(this, "Attention!", "Interest rate cannot be zero!");
  } else if (ui->comboBox->currentIndex() == 0 &&
             ui->lineEdit_duration->text().toInt() > 50) {
    QMessageBox::warning(this, "Attention!", "Maximum loan term is 50 years!");
    ui->lineEdit_duration->clear();
  } else if (ui->comboBox->currentIndex() == 1 &&
             ui->lineEdit_duration->text().toInt() > 600) {
    QMessageBox::warning(this, "Attention!",
                         "Maximum loan term is 600 monnths!");
    ui->lineEdit_duration->clear();
  } else {
    int factor = 0;
    if (ui->comboBox->currentIndex() == 1) {
      factor = 1;
    } else if (ui->comboBox->currentIndex() == 0) {
      factor = 12;
    }
    ui->credit_output->append(QString::number(factor));
    double sum = ui->lineEdit_sum->text().toDouble();
    int month = factor * ui->lineEdit_duration->text().toInt();
    double percent = ui->doubleSpinBox_interes->value();
    ui->credit_output->setText(QString::fromStdString(controler.Credit(
        sum, month, percent, ui->radioButton_Ann->isChecked())));
  }
}
