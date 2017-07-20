#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QString>
#include <QLCDNumber>
#include <QPushButton>
#include <QGridLayout>
#include <QRegExp>
#include <QMessageBox>

namespace Ui {
class Calculator;
}

class QLCDNumber;
class QPushButton;

class Calculator : public QWidget {
  Q_OBJECT

public:

  explicit Calculator(QWidget *parent = 0);
  ~Calculator();
  QPushButton* createButton(const QString&);
  void         calculate();

public slots:

  void slotButtonClicked();

private:

  Ui::Calculator *ui;
  QLCDNumber *m_plcd;
  QStack<QString>m_stk;
  QString m_strDisplay;
};

#endif // CALCULATOR_H
