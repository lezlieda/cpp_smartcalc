#include "inputx.h"

#include "ui_inputx.h"

inputX::inputX(QWidget *parent) : QDialog(parent), ui(new Ui::inputX) {
  ui->setupUi(this);

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
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot_button()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(delete_button()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear_button()));
  connect(ui->pushButton_sign, SIGNAL(clicked()), this, SLOT(sign_button()));
  connect(ui->pushButton_enter, SIGNAL(clicked()), this, SLOT(enter_button()));
}

inputX::~inputX() { delete ui; }

void inputX::input_number() {
  QPushButton *button = (QPushButton *)sender();
  ui->x_value->insert(button->text());
}

void inputX::dot_button() {
  QString inp = ui->x_value->text();
  if (!inp.contains(".")) {
    if (inp.isEmpty()) ui->x_value->insert("0");
    ui->x_value->insert(".");
  }
}

void inputX::sign_button() {
  QString inp = ui->x_value->text();
  if (inp.contains("-")) {
    inp.remove(0, 1);
  } else {
    if (!inp.isEmpty()) inp.insert(0, "-");
  }
  ui->x_value->setText(inp);
}

void inputX::clear_button() { ui->x_value->clear(); }

void inputX::enter_button() {
  if (ui->x_value->text().isEmpty()) {
    QMessageBox::warning(this, "Attention!", "Variable x is not set!");
  } else {
    emit sendXvalue(ui->x_value->text());
    inputX::accept();
  }
}

void inputX::delete_button() {
  ui->x_value->backspace();
  QString inp = ui->x_value->text();
  if (!inp.compare("-") || !inp.compare("0") || !inp.compare("-0"))
    ui->x_value->clear();
}
