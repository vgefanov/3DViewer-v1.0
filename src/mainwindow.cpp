
#include <QGridLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

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
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_scaleXslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->scaleX = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_scaleYslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->scaleY = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_scaleZslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->scaleZ = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_moveXslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->moveX = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_moveYslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->moveY = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_moveZslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->moveZ = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_rotateXslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->rotateX = (float)value;
    m_mainScene->update();
}


void MainWindow::on_rotateYslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->rotateY = (float)value;
    m_mainScene->update();
}


void MainWindow::on_rotateZslider_valueChanged(int value)
{
    m_mainScene->sceneSettings->rotateZ = (float)value;
    m_mainScene->update();
}


void MainWindow::on_radioOrho_clicked()
{
    m_mainScene->sceneSettings->projection = Settings::Projection::Orho;
    m_mainScene->update();
}


void MainWindow::on_radioFrustum_clicked()
{
    m_mainScene->sceneSettings->projection = Settings::Projection::Frustum;
    m_mainScene->update();
}


void MainWindow::on_sceneColorButton_clicked()
{
    QColor selected = QColorDialog::getColor(Qt::darkCyan, this, "Scene Color");
    m_mainScene->sceneSettings->sceneColorR = selected.redF();
    m_mainScene->sceneSettings->sceneColorG = selected.greenF();
    m_mainScene->sceneSettings->sceneColorB = selected.blueF();
    m_mainScene->update();
}


void MainWindow::on_lineColorButton_clicked()
{
    QColor selected = QColorDialog::getColor(Qt::darkCyan, this, "Line Color");
    m_mainScene->sceneSettings->lineColorR = selected.redF();
    m_mainScene->sceneSettings->lineColorG = selected.greenF();
    m_mainScene->sceneSettings->lineColorB = selected.blueF();
    m_mainScene->update();
}


void MainWindow::on_lineWidthSlider_valueChanged(int value)
{
    m_mainScene->sceneSettings->lineWidth = value;
    m_mainScene->update();
}


void MainWindow::on_patternSlider_valueChanged(int value)
{
    switch (value) {
    case 1: m_mainScene->sceneSettings->linePattern = 0xffff; break;
    case 2: m_mainScene->sceneSettings->linePattern = 0xff00; break;
    case 3: m_mainScene->sceneSettings->linePattern = 0xf000; break;
    case 4: m_mainScene->sceneSettings->linePattern = 0x1000; break;
    }
    m_mainScene->update();
}


void MainWindow::on_pointColorButton_clicked()
{
    QColor selected = QColorDialog::getColor(Qt::darkCyan, this, "Point Color");
    m_mainScene->sceneSettings->vertexColorR = selected.redF();
    m_mainScene->sceneSettings->vertexColorG = selected.greenF();
    m_mainScene->sceneSettings->vertexColorB = selected.blueF();
    m_mainScene->update();
}


void MainWindow::on_pointSizeSlider_valueChanged(int value)
{
    m_mainScene->sceneSettings->pointSize = value;
    m_mainScene->update();
}


void MainWindow::on_actionOpen_model_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open model file"),
            ".",
            "Model file (*.obj)"
    );
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "info", file.errorString());
        return;
    }
    file.close();
    m_mainScene->model = load_model(filename.toLocal8Bit().data());
    m_mainScene->update();
}

