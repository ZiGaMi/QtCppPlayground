#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;


    void InputFormatter(const QString& new_text);

    void AnnualExpenseUpdate(const QString& new_value);

    void Recalculate(const QString& new_value);
};
#endif // WIDGET_H
