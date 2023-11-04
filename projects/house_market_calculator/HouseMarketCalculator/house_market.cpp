#include "house_market.h"
#include "./ui_house_market.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    connect( ui->cena,      &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->velikost,  &QLineEdit::textChanged, this, &Widget::InputFormatter );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::InputFormatter(const QString &new_text)
{
    // Get pointer to line edit object that triggers that function
    QLineEdit * p_LineEdit = static_cast<QLineEdit*> ( this->sender() );

    qInfo() << "New text: " << new_text << "Sends: " << p_LineEdit->objectName();

    p_LineEdit->setText( "0000" );







    /*
    QObject * p_obj = this->sender();

    QLineEdit * p_line_edit = (QLineEdit*) (p_obj);

    qInfo() << "New text: " << new_text << "Sends: " << p_obj->objectName();

    QObject * p_parent = p_obj->parent();
    qInfo() << "Parent: " << p_parent->objectName();

    p_line_edit->setText( "0000" );
*/
}


