
#include <QGridLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

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

    show_model_info();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::show_model_info()
{
    ui->modelName->setText(m_mainScene->sceneSettings->visibleModelName);
    ui->pointsNum->setText(QString::number(m_mainScene->model.v_num / 3));
    ui->linesNum->setText(QString::number(m_mainScene->model.f_num / 2));
}


void MainWindow::on_scaleSlider_valueChanged(int value)
{
      float temp = m_mainScene->sceneSettings->scaleX;
      m_mainScene->sceneSettings->scaleX = (float)value / 50;
      m_mainScene->sceneSettings->scaleY = (float)value / 50;
      m_mainScene->sceneSettings->scaleZ = (float)value / 50;
      scale(&m_mainScene->model, (float)value / temp / 50);
      m_mainScene->update();
}


void MainWindow::on_moveXslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->moveX;
    float newX = (float)value / 50 * m_mainScene->diapason;
    m_mainScene->sceneSettings->moveX = newX;
    moveXYZ(&m_mainScene->model, newX - temp, 0.0, 0.0);
    m_mainScene->update();
}


void MainWindow::on_moveYslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->moveY;
    float newY = (float)value / 50 * m_mainScene->diapason;
    m_mainScene->sceneSettings->moveY = newY;
    moveXYZ(&m_mainScene->model, 0.0, newY - temp, 0.0);
    m_mainScene->update();
}


void MainWindow::on_moveZslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->moveZ;
    float newZ = (float)value / 10 * m_mainScene->diapason;
    m_mainScene->sceneSettings->moveZ = newZ;
    moveXYZ(&m_mainScene->model, 0.0, 0.0, newZ - temp);
    m_mainScene->update();
}


void MainWindow::on_rotateXslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->rotateX;
    m_mainScene->sceneSettings->rotateX = (float)value;
    rotationX(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
    m_mainScene->update();
}


void MainWindow::on_rotateYslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->rotateY;
    m_mainScene->sceneSettings->rotateY = (float)value;
    rotationY(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
    m_mainScene->update();
}


void MainWindow::on_rotateZslider_valueChanged(int value)
{
    float temp = m_mainScene->sceneSettings->rotateZ;
    m_mainScene->sceneSettings->rotateZ = (float)value;
    rotationZ(&m_mainScene->model, ((float)value - temp) * M_PI / 180);
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
    load_model_dialog();
}


void MainWindow::on_loadModelButton_clicked()
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

    release_model(m_mainScene->model);
    m_mainScene->model = load_model(filename.toLocal8Bit().data());

    delete m_mainScene->sceneSettings;
    m_mainScene->sceneSettings = new SceneSettings(filename);

    show_model_info();
    ui->scaleSlider->setValue(50);
    ui->moveXslider->setValue(0);
    ui->moveYslider->setValue(0);
    ui->moveZslider->setValue(0);
    ui->rotateXslider->setValue(0);
    ui->rotateYslider->setValue(0);
    ui->rotateZslider->setValue(0);
    ui->radioOrho->setChecked(1);
    ui->lineWidthSlider->setValue(1);
    ui->patternSlider->setValue(1);
    ui->pointSizeSlider->setValue(1);
    ui->radioNone->setChecked(1);

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
    release_model(m_mainScene->model);
    m_mainScene->model = load_model(m_mainScene->sceneSettings->modelPath.toLocal8Bit().data());

    show_model_info();
    ui->scaleSlider->setValue(m_mainScene->sceneSettings->scaleX * 50);
    ui->moveXslider->setValue(m_mainScene->sceneSettings->moveX * 50 / m_mainScene->diapason);
    ui->moveYslider->setValue(m_mainScene->sceneSettings->moveY * 50 / m_mainScene->diapason);
    ui->moveZslider->setValue(m_mainScene->sceneSettings->moveZ * 10 / m_mainScene->diapason);
    ui->rotateXslider->setValue(m_mainScene->sceneSettings->rotateX);
    ui->rotateYslider->setValue(m_mainScene->sceneSettings->rotateY);
    ui->rotateZslider->setValue(m_mainScene->sceneSettings->rotateZ);
    if (m_mainScene->sceneSettings->projection == Settings::Projection::Orho) {
        ui->radioOrho->setChecked(1);
    } else {
        ui->radioFrustum->setChecked(1);
    }
    ui->lineWidthSlider->setValue(m_mainScene->sceneSettings->lineWidth);
    switch (m_mainScene->sceneSettings->linePattern) {
        case 0xffff: ui->patternSlider->setValue(1); break;
        case 0xff00: ui->patternSlider->setValue(2); break;
        case 0xf000: ui->patternSlider->setValue(3); break;
        case 0x1000: ui->patternSlider->setValue(4); break;
    }
    ui->pointSizeSlider->setValue(m_mainScene->sceneSettings->pointSize);
    switch (m_mainScene->sceneSettings->pointStyle) {
        case Settings::PointStyle::None: ui->radioNone->setChecked(1); break;
        case Settings::PointStyle::Rounded: ui->radioRounded->setChecked(1); break;
        case Settings::PointStyle::Quad: ui->radioQuad->setChecked(1); break;
    }

    scale(&m_mainScene->model, m_mainScene->sceneSettings->scaleX);
    moveXYZ(&m_mainScene->model, m_mainScene->sceneSettings->moveX, m_mainScene->sceneSettings->moveY, m_mainScene->sceneSettings->moveZ);
    rotationX(&m_mainScene->model, m_mainScene->sceneSettings->rotateX * M_PI / 180);
    rotationY(&m_mainScene->model, m_mainScene->sceneSettings->rotateY * M_PI / 180);
    rotationZ(&m_mainScene->model, m_mainScene->sceneSettings->rotateZ * M_PI / 180);

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
        m_framesToEnd = 50;
        recordTimer = new QTimer();
        connect(recordTimer, SIGNAL(timeout()), this, SLOT(recordTimerAlarm()));
        recordTimer->start(100); // И запустим таймер
    } else {
        ui->recordButton->setText("Record to GIF");
        recordTimer->stop();
    }

}


void MainWindow::recordTimerAlarm()
{
    int width = 1720 / 3;
    int height = 1698 / 3;
    int delay = 10;
    int loopcount = 0; // 0 means infinite, otherwise as specified
    int bitdepth = 8;
    bool dither=false;

    if (m_framesToEnd == 50) {
        m_gifFileName = QFileDialog::getSaveFileName(this, "GIF file", ".", "Image file (*.gif)");
        m_img_buf = new QVector<QImage>();
        m_ganim = new GifAnim();
        m_gwriter = new GifWriter();
        m_ganim->GifBegin(m_gwriter, m_gifFileName.toLocal8Bit().data(), width, height, delay, loopcount, bitdepth, dither);
    }
    if (m_framesToEnd > 0) {
        QImage small = m_mainScene->grabFramebuffer().scaled(width, height, Qt::KeepAspectRatio)
                .convertToFormat(QImage::Format_Indexed8).convertToFormat(QImage::Format_RGBA8888);
        m_img_buf->append(small);
        m_ganim->GifWriteFrame(m_gwriter, small.constBits(), width, height, delay, bitdepth, dither);
        qDebug() << m_framesToEnd << small.depth();
    }
    else {
        m_ganim->GifEnd(m_gwriter);
        delete m_img_buf;
        delete m_ganim;
        delete m_gwriter;
        on_recordButton_clicked();
    }
    --m_framesToEnd;
}
