#include "house_market.h"
#include "./ui_house_market.h"

#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Connection to formatter
    connect( ui->cena,      &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->velikost,  &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->renta,     &QLineEdit::textChanged, this, &Widget::InputFormatter );

    // Connect to income calculation
    connect( ui->cena,          &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->velikost,      &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->renta,         &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->nenajemnost,   &QLineEdit::textChanged, this, &Widget::CalculateIncome );

    // Connection to annual expenses update
    connect( ui->storitve_upravnik,     &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->zavarovanje,           &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->obratovalni_stroski,   &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );

    // Connect to expense calculations
    connect( ui->storitve_upravnik,     &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->zavarovanje,           &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->obratovalni_stroski,   &QLineEdit::textChanged, this, &Widget::CalculateExpense );

    // Calculate income, expenses
    CalculateIncome( nullptr );
    CalculateExpense( nullptr );
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
    //qInfo() << "New text: " << new_text << "Sends: " << p_LineEdit->objectName() << "size()=" << QString::number( new_text.size() );

    // TODO: Make a formater...
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Annual expense update
*
* @param[in]	new_value    - Reference to new value inside line edit widget
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
void Widget::AnnualExpenseUpdate(const QString &new_value)
{
    // Create a mapping table between monthly inputed value and calculated annual value
    const QHash<QLineEdit*,QLabel*> map =
    {
        { ui->storitve_upravnik,    ui->sklad_leto },
        { ui->zavarovanje,          ui->zavarovanje_leto },
        { ui->obratovalni_stroski,  ui->poloznice_leto },
    };

    // Get pointer to line edit object that triggers that function
    QLineEdit * p_LineEdit = static_cast<QLineEdit*> ( this->sender() );

    // Go thru mapping table
    for ( auto [key, value] : map.asKeyValueRange())
    {
        // Sender found in mapping table
        if ( key == p_LineEdit )
        {
            // Change annual value
            value->setText( QString::number( new_value.toInt() * 12 ) + " €/leto" );
            break;
        }
    }
}



////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Calculate income
*
* @param[in]	new_value    - Reference to new value inside line edit widget
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
void Widget::CalculateIncome(const QString &new_value)
{
    // Calculate gross earnings
    const float gross_earnings = ( 12 - ui->nenajemnost->text().toFloat()) * ui->renta->text().toFloat();

    // Get tax percentage
    const float tax_per = ui->davek_per->text().toFloat();

    // Get "normiran dohodek" percentage
    const float nor_doh_per = ui->normiran_doh_per->text().toFloat();

    // Calcualte tax base
    const float tax_basis = gross_earnings * (( 100.0f - nor_doh_per ) / 100.0f );

    // Calculate total tax
    const float tax = ( tax_per / 100.0f ) * tax_basis;

    // Calculate net earnings
    const float net_earnigns = ( gross_earnings - tax );

    // Update GUI
    ui->bruto_dohodek->setText( QString::number( gross_earnings ) + " €" );
    ui->davcna_osnova->setText( QString::number( tax_basis ) + " €" );
    ui->davek_doh->setText( QString::number( tax ) + " €" );
    ui->neto_dohodek->setText( QString::number( net_earnigns ) + " €" );
}



void Widget::CalculateExpense(const QString &new_value)
{

}






















