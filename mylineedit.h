#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
  Q_OBJECT

public:
  MyLineEdit(QWidget *parent = 0);
  ~MyLineEdit();

signals:
  void focussed(bool hasFocus);

protected:
  virtual void focusInEvent(QFocusEvent *e);
//  virtual void focusOutEvent(QFocusEvent *e);
};

#endif // MYLINEEDIT_H
