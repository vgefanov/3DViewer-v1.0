#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

private slots:
    void on_scaleXslider_valueChanged(int value);
    void on_scaleYslider_valueChanged(int value);
    void on_scaleZslider_valueChanged(int value);

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

private:
    Ui::MainWindow *ui;
    MainScene *m_mainScene;

};
#endif // MAINWINDOW_H
