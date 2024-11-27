#ifndef INPUTX_H
#define INPUTX_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class inputX;
}

class inputX : public QDialog {
  Q_OBJECT

 public:
  explicit inputX(QWidget *parent = nullptr);
  ~inputX();

 private:
  Ui::inputX *ui;

 private slots:
  void input_number();
  void clear_button();
  void delete_button();
  void dot_button();
  void sign_button();
  void enter_button();

 signals:
  void sendXvalue(QString);
};

#endif  // INPUTX_H
