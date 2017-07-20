#include "calculator.h"
#include "ui_calculator.h"

struct Positions
{
  // Screen width and height
  static const ROWS_NUMBER    = 4;
  static const COLUMNS_NUMBER = 4;

  // Keyboard height and width
  // Implement keyboard as NXM matrix
  // with N rows and M columns
};

Calculator::Calculator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Calculator)
{
  m_plcd = new QLCDNumber(12);
  m_plcd->setSegmentStyle(QLCDNumber::Filled);
  m_plcd->setMinimumSize(150, 50);

  ui->setupUi(this);

  QChar aButtons[ROWS_NUMBER][COLUMNS_NUMBER] = {
    { '7', '8', '9', '/' },
    { '4', '5', '6', '*' },
    { '1', '2', '3', '-' },
    { '0', '.', '=', '+' }
  };

  // Layout setup
  QGridLayout *pTopLayout = new QGridLayout;
  pTopLayout->addWidget(m_plcd,             0, 0, 1, 4);
  pTopLayout->addWidget(createButton("CE"), 1, 3);

  for (int i = 0; i < ROWS_NUMBER; i++)
  {
    for (int j = 0; j < COLUMNS_NUMBER; j++)
    {
      pTopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
    }
  }
  setLayout(pTopLayout);
}

Calculator::~Calculator()
{
  delete ui;
  delete m_plcd;
}

QPushButton * Calculator::createButton(const QString& rStr)
{
  QPushButton *pCmd = new QPushButton(rStr);

  pCmd->setMinimumSize(40, 40);
  connect(pCmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
  return pCmd;
}

void Calculator::calculate()
{
  double  dOperand2    = m_stk.pop().toDouble();
  QString strOperation = m_stk.pop();
  double  dOperand1    = m_stk.pop().toDouble();
  double  dResult      = 0;

  if (strOperation == "+")
  {
    dResult = dOperand1 + dOperand2;
  }

  if (strOperation == "-")
  {
    dResult = dOperand1 - dOperand2;
  }

  if (strOperation == "*")
  {
    dResult = dOperand1 * dOperand2;
  }

  if (strOperation == "/")
  {
    if (dOperand2 != 0)
    {
      dResult = dOperand1 / dOperand2;
    }
  }

  m_plcd->display(dResult);
}

void Calculator::slotButtonClicked()
{
  QString str = ((QPushButton *)sender())->text();

  if (str == "CE") {
    m_stk.clear();
    m_strDisplay = "";
    m_plcd->display("0");
    return;
  }

  if (str.contains(QRegExp("[0-9]"))) {
    m_strDisplay += str;
    m_plcd->display(m_strDisplay.toDouble());
  }
  else if (str == ".") {
    m_strDisplay += str;
    m_plcd->display(m_strDisplay);
  }
  else {
    if (m_stk.count() >= 2) {
      m_stk.push(QString().setNum(m_plcd->value()));
      calculate();
      m_stk.clear();
      m_stk.push(QString().setNum(m_plcd->value()));

      if (str != "=") {
        m_stk.push(str);
      }
    }
    else {
      m_stk.push(QString().setNum(m_plcd->value()));
      m_strDisplay = "";
      m_plcd->display("0");
    }
  }
}
