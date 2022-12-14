#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gifanimcplusplus/gifanim.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_model_info();

private slots:
    void on_scaleSlider_valueChanged(int value);

    void on_moveXslider_valueChanged(int value);
    void on_moveYslider_valueChanged(int value);
    void on_moveZslider_valueChanged(int value);

    void on_rotateXslider_valueChanged(int value);
    void on_rotateYslider_valueChanged(int value);
    void on_rotateZslider_valueChanged(int value);

    void on_radioOrho_clicked();
    void on_radioFrustum_clicked();

    void on_sceneColorButton_clicked();

    void on_lineColorButton_clicked();
    void on_lineWidthSlider_valueChanged(int value);
    void on_patternSlider_valueChanged(int value);

    void on_pointColorButton_clicked();
    void on_pointSizeSlider_valueChanged(int value);

    void on_actionOpen_model_triggered();
    void on_loadModelButton_clicked();

    void on_radioNone_clicked();
    void on_radioRounded_clicked();
    void on_radioQuad_clicked();

    void on_actionSave_profile_triggered();
    void on_actionLoad_profile_triggered();

    void on_screenshotButton_clicked();
    void on_recordButton_clicked();
    void recordTimerAlarm();

private:
    void load_model_dialog();

    Ui::MainWindow *ui;
    MainScene *m_mainScene;

    QTimer *recordTimer;
    int m_framesToEnd;
    QString m_gifFileName;
    QVector<QImage> *m_img_buf;
    GifAnim *m_ganim;
    GifWriter *m_gwriter;

    bool record = false;
};
#endif // MAINWINDOW_H
