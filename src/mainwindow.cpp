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

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    m_mainScene = new MainScene();
    m_mainScene->setFormat(format);

    // create window container widget
    QWidget *container = QWidget::createWindowContainer(m_mainScene);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(container);
    ui->centralwidget->setLayout(layout);

//    QVBoxLayout * vlay = new QVBoxLayout();
//    vlay->setContentsMargins(0, 0, 0, 0);
//    vlay->addWidget(container);

//    QHBoxLayout * hlay = new QHBoxLayout;
//    hlay->setContentsMargins(0, 0, 0, 0);

//    QPushButton * changeColorBtn = new QPushButton(tr("Change colors"), this);
//    connect(changeColorBtn, SIGNAL(clicked()), this, SLOT(onChangeColors()));

//    QPushButton * changeColorAnimationBtn = new QPushButton(tr("Animate colors"), this);
//    connect(changeColorAnimationBtn, SIGNAL(clicked()), this, SLOT(onAnimateColors()));

//    QPushButton * closeBtn = new QPushButton(tr("Close"), this);
//    connect(closeBtn, SIGNAL(clicked()), this, SLOT(accept()));

//    hlay->addWidget(changeColorBtn);
//    hlay->addWidget(changeColorAnimationBtn);
//    hlay->addStretch();
//    hlay->addWidget(closeBtn);

//    vlay->addLayout(hlay);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onChangeColors()
{
    for (unsigned int i = 0; i < 4; ++i) {
        m_mainScene->m_vertexColors[i].setRgbF(
                    rand() * 1.0 / RAND_MAX,
                    rand()*1.0 / RAND_MAX,
                    rand()*1.0 / RAND_MAX
                    );
    }
    m_mainScene->updateScene();
}


void MainWindow::onAnimateColors()
{
    std::vector<QColor> newCols(4);
    for (unsigned int i = 0; i < 4; ++i) {
        newCols[i].setRgbF(
                    rand() * 1.0 / RAND_MAX,
                    rand() * 1.0 / RAND_MAX,
                    rand() * 1.0 / RAND_MAX
                    );
    }

    m_mainScene->animateColorsTo(newCols);
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
