#include <QMessageBox>

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "phonenumbervalidator.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "productsmodel.h"
#include "providersmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_products(new ProductsModel)
    , m_providers(new ProvidersModel)
{
    m_ui->setupUi(this);

    {
        m_ui->tableViewProducts->setModel(m_products);
        m_ui->tableViewProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

    {
        m_ui->tableViewProviders->setModel(m_providers);
        connect(m_ui->tableViewProviders, &QTableView::doubleClicked,
                this, &MainWindow::providersDoubleClicked);
    }

    // validators

    {
        const auto regExpForTextFields = QRegularExpression("[A-Za-zА-Яа-я0-9]{10}");
        m_ui->lineEditProviderName->setValidator(
            new QRegularExpressionValidator(regExpForTextFields));
        m_ui->lineEditProviderDesc->setValidator(
            new QRegularExpressionValidator(regExpForTextFields));
        m_ui->lineEditProviderPhoneNumber->setValidator(
            new PhoneNumberValidator(this));
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

// TODO: move to model?

void MainWindow::providersDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    QMessageBox::information(this, "Provider Phone Number",
                             m_providers->getPhoneNumber(index.row()));
}

void MainWindow::on_pushButtonAddProvider_clicked()
{

}

