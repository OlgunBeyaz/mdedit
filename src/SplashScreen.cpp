#include "SplashScreen.h"
#include <QApplication>
#include <QPainter>
#include <QFont>
#include <QPixmap>
#include <QTimer>

SplashScreen::SplashScreen(QWidget *parent) : QSplashScreen(), timer(new QTimer(this))
{
    // Create splash screen image
    QPixmap splashPixmap(400, 300);
    splashPixmap.fill(QColor(44, 62, 80)); // Dark blue background

    QPainter painter(&splashPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Title
    QFont titleFont("Arial", 32, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(QColor(231, 76, 60)); // Red
    painter.drawText(QRect(0, 80, 400, 50), Qt::AlignCenter, "mdedit");

    // Subtitle
    QFont subtitleFont("Arial", 14);
    painter.setFont(subtitleFont);
    painter.setPen(QColor(236, 240, 241)); // Light gray
    painter.drawText(QRect(0, 140, 400, 30), Qt::AlignCenter, "Markdown Editor mit Live-Preview");

    // Author info
    QFont authorFont("Arial", 12);
    painter.setFont(authorFont);
    painter.setPen(QColor(52, 152, 219)); // Blue
    painter.drawText(QRect(0, 180, 400, 25), Qt::AlignCenter, "von Kemal Akçocuk");

    // Freeware notice
    QFont freeFont("Arial", 10);
    painter.setFont(freeFont);
    painter.setPen(QColor(46, 204, 113)); // Green
    painter.drawText(QRect(0, 210, 400, 20), Qt::AlignCenter, "Freeware - Kostenlos für alle");

    // Version
    painter.setPen(QColor(149, 165, 166)); // Gray
    painter.drawText(QRect(0, 250, 400, 20), Qt::AlignCenter, "Version 1.0 - Qt6");

    // Border
    painter.setPen(QPen(QColor(52, 73, 94), 2));
    painter.drawRoundedRect(5, 5, 390, 290, 10, 10);

    setPixmap(splashPixmap);
    
    // Setup timer
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &SplashScreen::hideSplash);
}

void SplashScreen::showSplash()
{
    show();
    QApplication::processEvents();
    timer->start(2500); // Show for 2.5 seconds
}

void SplashScreen::hideSplash()
{
    close();
}