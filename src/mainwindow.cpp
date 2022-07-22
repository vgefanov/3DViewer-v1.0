//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
#include <QGridLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1200, 900);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);

    m_mainScene = new MainScene();
    m_mainScene->setFormat(format);
    QWidget *container = QWidget::createWindowContainer(m_mainScene);
    ui->verticalLayout->addWidget(container);

    // TODO: удалить
    ui->label->setText(QString::number(myMatrixXYZ()));

//    QGridLayout *layout = new QGridLayout();
//    layout->addWidget(container);
//    ui->centralwidget->setLayout(layout);
}


MainWindow::~MainWindow()
{
    delete ui;
}


// диалог для загрузки модели
//void MainWindow::on_pushButton_clicked()
//{
//    QString filename = QFileDialog::getOpenFileName(
//            this,
//            tr("Open model file"),
//            ".",
//            "Model file (*.obj)"
//            );
//    QFile file(filename);
//    if (!file.open(QIODevice::ReadWrite))
//    {
//        QMessageBox::information(0, "info", file.errorString());
//        return;
//    }
//    file.close();
//    //gl->model = load_model(filename.toLocal8Bit().data());
//}
