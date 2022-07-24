
#include <QGridLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"
#include "scenesettings.h"


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

    ui->modelName->setText(m_mainScene->sceneSettings->visibleModelName);
    ui->pointsNum->setText(QString::number(m_mainScene->model.v_num / 3));
    ui->linesNum->setText(QString::number(m_mainScene->model.f_num / 2));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_scaleSlider_valueChanged(int value)
{
      float temp = m_mainScene->sceneSettings->scaleX;
      m_mainScene->sceneSettings->scaleX = (float)value / 50;
      m_mainScene->sceneSettings->scaleY = (float)value / 50;
      m_mainScene->sceneSettings->scaleZ = (float)value / 50;
      scale(&m_mainScene->model, (float)value/ temp / 50);
      m_mainScene->update();
//    m_mainScene->sceneSettings->scaleX = (float)value / 50;
//    m_mainScene->sceneSettings->scaleY = (float)value / 50;
//    m_mainScene->sceneSettings->scaleZ = (float)value / 50;
//    m_mainScene->update();
}


void MainWindow::on_moveXslider_valueChanged(int value)
{
      float tempX = m_mainScene->sceneSettings->moveX;
      m_mainScene->sceneSettings->moveX = (float)value / 50;
      moveXYZ(&m_mainScene->model, (float)value / 50 - tempX, 0.0, 0.0);
      m_mainScene->update();
//    m_mainScene->sceneSettings->moveX = (float)value / 50;
//    m_mainScene->update();
}


void MainWindow::on_moveYslider_valueChanged(int value)
{
    float tempY = m_mainScene->sceneSettings->moveY;
    m_mainScene->sceneSettings->moveY = (float)value / 50;
    moveXYZ(&m_mainScene->model, 0.0, (float)value / 50 - tempY, 0.0);
    m_mainScene->update();
//    m_mainScene->sceneSettings->moveY = (float)value / 50;
//    m_mainScene->update();
}


void MainWindow::on_moveZslider_valueChanged(int value)
{
//    float temp = m_mainScene->sceneSettings->moveZ;
//    m_mainScene->sceneSettings->moveZ = (float)value / 50;
//    moveXYZ(&m_mainScene->model, 0.0, 0.0, (float)value / 50 - temp);
//    m_mainScene->update();
    m_mainScene->sceneSettings->moveZ = (float)value / 50;
    m_mainScene->update();
}


void MainWindow::on_rotateXslider_valueChanged(int value)
{
      float temp = m_mainScene->sceneSettings->rotateX;
      m_mainScene->sceneSettings->rotateX = (float)value;
      rotationX(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
      m_mainScene->update();
//    m_mainScene->sceneSettings->rotateX = (float)value;
//    m_mainScene->update();
}


void MainWindow::on_rotateYslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->rotateY;
    m_mainScene->sceneSettings->rotateY = (float)value;
    rotationY(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
    m_mainScene->update();
//    m_mainScene->sceneSettings->rotateY = (float)value;
//    m_mainScene->update();
}


void MainWindow::on_rotateZslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->rotateZ;
    m_mainScene->sceneSettings->rotateZ = (float)value;
    rotationZ(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
    m_mainScene->update();
//    m_mainScene->sceneSettings->rotateZ = (float)value;
//    m_mainScene->update();
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
    load_model_dialog();
}


void MainWindow::on_sceneColorButton_2_clicked()
{
    load_model_dialog();
}


void MainWindow::load_model_dialog() {
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
    // убить старую модель
    m_mainScene->model = load_model(filename.toLocal8Bit().data());
    m_mainScene->update();
}



void MainWindow::on_radioNone_clicked()
{
    m_mainScene->sceneSettings->pointStyle = Settings::PointStyle::None;
    m_mainScene->update();
}




void MainWindow::on_radioRounded_clicked()
{
    m_mainScene->sceneSettings->pointStyle = Settings::PointStyle::Rounded;
    m_mainScene->update();
}


void MainWindow::on_radioQuad_clicked()
{
    m_mainScene->sceneSettings->pointStyle = Settings::PointStyle::Quad;
    m_mainScene->update();
}


void MainWindow::on_actionSave_profile_triggered()
{
    m_mainScene->sceneSettings->save();
}


void MainWindow::on_actionLoad_profile_triggered()
{
    m_mainScene->sceneSettings->load();
    m_mainScene->update();
}


void MainWindow::on_screenshotButton_clicked()
{
    std::string ext = ".png";
    if (ui->screenshotExtCombo->currentIndex() == 1) ext = ".bmp";
    if (ui->screenshotExtCombo->currentIndex() == 2) ext = ".jpg";
    std::string filter = "Image file (*" + ext + ")";
    QString filename = QFileDialog::getSaveFileName(
            this,
            "Screenshot file",
            ".",
            QString::fromUtf8(filter.c_str())
    );
    m_mainScene->screenshot(filename);
}


void MainWindow::on_recordButton_clicked()
{
    record = !record;
    if (record) {
        ui->recordButton->setText("Stop");
    } else {
        ui->recordButton->setText("Record to GIF");
    }

}

