#include "house_market.h"
#include "./ui_house_market.h"

#include <QDebug>
#include <QDoubleValidator>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Setup floating point entry for linedit
    ui->cena->setValidator( new QDoubleValidator( 0.0, 10.0, 1, ui->cena ));
    ui->velikost->setValidator( new QDoubleValidator( 0.0, 1000.0, 2, ui->velikost ));
    ui->renta->setValidator( new QDoubleValidator( 0.0, 1000.0, 2, ui->renta ));
    ui->nenajemnost->setValidator( new QDoubleValidator( 0.0, 12, 0, ui->nenajemnost ));

    ui->storitve_upravnik->setValidator(    new QDoubleValidator( 0.0, 1000.0, 2, ui->storitve_upravnik ));
    ui->obratovalni_stroski->setValidator(  new QDoubleValidator( 0.0, 1000.0, 2, ui->obratovalni_stroski ));
    ui->zavarovanje->setValidator(          new QDoubleValidator( 0.0, 1000.0, 2, ui->zavarovanje ));

    ui->davek_per->setValidator( new QIntValidator( 0, 100, ui->davek_per ));
    ui->normiran_doh_per->setValidator( new QIntValidator( 0, 100, ui->normiran_doh_per ));
    ui->obnova_per->setValidator( new QIntValidator( 0, 100, ui->obnova_per ));
    ui->stavbno->setValidator( new QDoubleValidator( 0.0, 1000.0, 2, ui->stavbno ));

    // Connection to formatter
    connect( ui->cena,      &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->velikost,  &QLineEdit::textChanged, this, &Widget::InputFormatter );
    connect( ui->renta,     &QLineEdit::textChanged, this, &Widget::InputFormatter );

    // Connect to income calculation
    connect( ui->cena,              &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->cena,              &QLineEdit::textChanged, this, &Widget::CalculatePricePerSize );
    connect( ui->velikost,          &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->velikost,          &QLineEdit::textChanged, this, &Widget::CalculatePricePerSize );
    connect( ui->renta,             &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->nenajemnost,       &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->davek_per,         &QLineEdit::textChanged, this, &Widget::CalculateIncome );
    connect( ui->normiran_doh_per,  &QLineEdit::textChanged, this, &Widget::CalculateIncome );

    // Connection to annual expenses update
    connect( ui->storitve_upravnik,     &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->zavarovanje,           &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );
    connect( ui->obratovalni_stroski,   &QLineEdit::textChanged, this, &Widget::AnnualExpenseUpdate );

    // Trigger annual expenses calculations
    emit ui->storitve_upravnik->textChanged( ui->storitve_upravnik->text() );
    emit ui->zavarovanje->textChanged( ui->zavarovanje->text() );
    emit ui->obratovalni_stroski->textChanged( ui->obratovalni_stroski->text() );

    // Connect to expense calculations
    connect( ui->storitve_upravnik,     &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->zavarovanje,           &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->obratovalni_stroski,   &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->obnova_per,            &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->renta,                 &QLineEdit::textChanged, this, &Widget::CalculateExpense );
    connect( ui->nenajemnost,           &QLineEdit::textChanged, this, &Widget::CalculateExpense );

    // Calculate income, expenses
    CalculateIncome( nullptr );
    CalculateExpense( nullptr );
    CalculatePricePerSize( nullptr );
    CalculateDonos( nullptr );


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
            value->setText( QString::number( new_value.toFloat() * 12 ) + " €/leto" );
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
    ui->bruto_dohodek->setText( QString::number( gross_earnings ));
    ui->davcna_osnova->setText( QString::number( tax_basis ));
    ui->davek_doh->setText( QString::number( tax ));
    ui->neto_dohodek->setText( QString::number( net_earnigns ));

    // Calculate donos
    CalculateDonos( nullptr );
}



void Widget::CalculateExpense(const QString &new_value)
{
    // Get new earnings
    const float net_earnings = ui->neto_dohodek->text().toFloat();

    // Get renovation percentage
    const float renovation_per = ui->obnova_per->text().toFloat();

    // Calculate renovation expenses
    const float renovation_expense = ( net_earnings * ( renovation_per / 100.0f ));

    // Get expenses
    const float upravnik_annual     = ( ui->storitve_upravnik->text().toFloat() * 12 );
    const float obratovanje_annual  = ( ui->obratovalni_stroski->text().toFloat() * 12 );
    const float zavarovanje_annual  = ( ui->zavarovanje->text().toFloat() * 12 );

    // Calculate total expenses
    const float total_expense = renovation_expense + upravnik_annual + obratovanje_annual + zavarovanje_annual;

    // Update GUI
    ui->obnova->setText( QString::number( renovation_expense ));
    ui->skupni_stroski->setText( QString::number( total_expense ));

    // Calculate donos
    CalculateDonos( nullptr );
}

void Widget::CalculatePricePerSize(const QString &new_value)
{
    // Get price and size
    const float price = ( ui->cena->text().toFloat() );
    const float size = ( ui->velikost->text().toFloat());

    // Calculate price per size
    const float price_per_size = ( price / size );

    // Update GUI
    ui->cena_na_velikost->setText( QString::number( price_per_size ));
}

void Widget::CalculateDonos(const QString &new_value)
{
    // Get new earnings and total expenses
    const float net_earnings = ui->neto_dohodek->text().toFloat();
    const float total_expense = ui->skupni_stroski->text().toFloat();

    // Calculate cash flow
    const float cash_flow = ( net_earnings - total_expense );

    // Calculate donos in percentage
    const float donosnost = ( cash_flow / ui->cena->text().toFloat() * 100.0f );

    // Update GUI
    ui->denarni_tok->setText( QString::number( cash_flow ));
    ui->denarni_tok_mes->setText( QString::number( cash_flow / 12 ));
    ui->donosnost->setText( QString::number( donosnost ));
    ui->letno_izplailo->setText( QString::number( 1/donosnost * 100.0f ));
}






















