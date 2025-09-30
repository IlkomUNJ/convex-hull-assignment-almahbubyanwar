#pragma once

#ifndef CANVASCONTAINER_H
#define CANVASCONTAINER_H

#include <QWidget>

class QLabel;

class CanvasContainer: public QWidget {
    Q_OBJECT

public:
    explicit CanvasContainer(QWidget *parent = nullptr);
    ~CanvasContainer();
    QLabel *m_testLabel;
signals:
public slots:
    void clearPoints();
    void drawHull();
    void drawHullSlow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QVector<QPoint> m_points;
    bool m_isDrawHull = false;
    std::string m_drawHullMode = "fast";
    int calculateZCrossProduct(
        QPoint &p1,
        QPoint &p2,
        QPoint &p3
    ) const;
};

#endif