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

    connect( ui->cena,          &QLineEdit::textChanged, this, &Widget::Recalculate );
    connect( ui->velikost,      &QLineEdit::textChanged, this, &Widget::Recalculate );
    connect( ui->renta,         &QLineEdit::textChanged, this, &Widget::Recalculate );
    connect( ui->nenajemnost,   &QLineEdit::textChanged, this, &Widget::Recalculate );


    connect( ui->sklad,         &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->zavarovanje,   &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->poloznice,     &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );


    Recalculate( nullptr );
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
    const QHash<QLineEdit*,QLabel*> map =
    {
        { ui->sklad,        ui->sklad_leto },
        { ui->zavarovanje,  ui->zavarovanje_leto },
        { ui->poloznice,    ui->poloznice_leto },
    };


#if 0
    QHash<QLineEdit*,QLabel*> map;

    map.insert( ui->sklad,          ui->sklad_leto );
    map.insert( ui->zavarovanje,    ui->zavarovanje_leto );
    map.insert( ui->poloznice,      ui->poloznice_leto );
#endif

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

void Widget::Recalculate(const QString &new_value)
{



    // Calculate gross earnings
    const float gross_earnings = ( 12 - ui->nenajemnost->text().toFloat()) * ui->renta->text().toFloat();




    const float tax_per         = ui->davek_per->text().toFloat();
    const float nor_doh_per     = ui->normiran_doh_per->text().toFloat();
    const float tax_basis       = gross_earnings * (( 100.0f - nor_doh_per ) / 100.0f );
    const float tax             = ( tax_per / 100.0f ) * tax_basis;
    const float net_earnigns    = gross_earnings - tax;

    ui->bruto_dohodek->setText( QString::number( gross_earnings ) + " €" );
    ui->davcna_osnova->setText( QString::number( tax_basis ) + " €" );
    ui->davek_doh->setText( QString::number( tax ) + " €" );
    ui->neto_dohodek->setText( QString::number( net_earnigns ) + " €" );
}

























