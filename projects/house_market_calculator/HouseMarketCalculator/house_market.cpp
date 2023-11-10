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


    connect( ui->sklad,         &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->zavarovanje,   &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->poloznice,     &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );


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



#include <QMap>

void Widget::AnnualExpenseUpdate(const QString &new_value)
{

    QHash<QLineEdit*,QLabel*> map;

    map.insert( ui->sklad,          ui->sklad_leto );
    map.insert( ui->zavarovanje,    ui->zavarovanje_leto );
    map.insert( ui->poloznice,      ui->poloznice_leto );


    // Get pointer to line edit object that triggers that function
    QLineEdit * p_LineEdit = static_cast<QLineEdit*> ( this->sender() );


    for ( auto [key, value] : map.asKeyValueRange())
    {
        if ( key == p_LineEdit )
        {
            value->setText( QString::number( new_value.toInt() * 12 ) + " €/leto" );
            break;
        }
    }

#if 0

        QHash<QString, int> hash;
    hash.insert("January", 1);
    hash.insert("February", 2);
    // ...
    hash.insert("December", 12);

    for (auto [key, value] : hash.asKeyValueRange()) {
        cout << qPrintable(key) << ": " << value << endl;
        --value; // convert to JS month indexing
    }


    qInfo() << "Line Edit: " << p_LineEdit->objectName();




    ui->sklad_leto->setText( QString::number( new_value.toInt() * 12 ) + " €/leto" );
#endif
}


