#pragma once

#include <QSplashScreen>
#include <QTimer>

class SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = nullptr);
    void showSplash();

private slots:
    void hideSplash();

private:
    QTimer *timer;
};