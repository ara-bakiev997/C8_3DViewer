#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QBitmap>

class ColorPalette : public QLabel
{
    Q_OBJECT
public:
    explicit ColorPalette(QWidget *parent = 0);
    double r = 0, g = 0, b = 0;

signals:
    void Color(QColor color);
    void clicked();

public slots:
    virtual void mousePressEvent(QMouseEvent *e);
};

#endif // COLORPALETTE_H
