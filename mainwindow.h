#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ProductsModel;
class ProvidersModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void providersDoubleClicked(const QModelIndex&);

private:
    Ui::MainWindow *m_ui;
    ProductsModel *m_products;
    ProvidersModel *m_providers;
};
#endif // MAINWINDOW_H
