#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "CanvasContainer.h"

class QPushButton;
class QLabel;
class QFont;
class QHBoxLayout;
class QVBoxLayout;

class Window: public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    
signals:
public slots:

private:
    QVBoxLayout *m_parentLayout;
    QHBoxLayout *m_titleLayout;
    QPushButton *m_startButton;
    QPushButton *m_startSlowButton;
    QPushButton *m_clearButton;
    QLabel *m_titleLabel;
    QFont m_font;
    CanvasContainer *m_canvas;
};
#endif
