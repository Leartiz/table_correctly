#include <QMessageBox>

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
