#include "house_market.h"
#include "./ui_house_market.h"

#include <QDebug>

typedef struct
{
    QLineEdit * p_month;
    QLineEdit * p_annual;
} map_table;



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Connection to formatter
    connect( ui->cena,      &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->velikost,  &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->renta,     &QLineEdit::textChanged, this, &Widget::InputFormatter );


    connect( ui->sklad,     &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );


}

Widget::~Widget()
{
    delete ui;
}

void Widget::InputFormatter(const QString &new_text)
{
    // Get pointer to line edit object that triggers that function
    QLineEdit * p_LineEdit = static_cast<QLineEdit*> ( this->sender() );

    // Debug line
    qInfo() << "New text: " << new_text << "Sends: " << p_LineEdit->objectName() << "size()=" << QString::number( new_text.size() );

    // TODO: Make a formater...
}





void Widget::AnnualExpenseUpdate(const QString &new_value)
{
    // Get pointer to line edit object that triggers that function
    //QLineEdit * p_LineEdit = static_cast<QLineEdit*> ( this->sender() );


    ui->sklad_leto->setText( QString::number( new_value.toInt() * 12 ) + " €/leto" );
}


