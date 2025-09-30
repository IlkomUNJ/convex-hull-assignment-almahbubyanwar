#include "Window.h"
#include <QHBoxLayout>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QWidget{parent} {
    setWindowTitle("Computer Graphics 1");
    resize(640, 480);

    m_parentLayout = new QVBoxLayout(this);
    m_titleLayout = new QHBoxLayout();
    m_canvas = new CanvasContainer();
    
    m_font = QFont();
    m_font.setPointSize(32);
    m_titleLabel = new QLabel("Convex Hull", this);
    m_titleLabel->setFont(m_font);
    m_startSlowButton = new QPushButton("Draw hull (slow)");
    m_startButton = new QPushButton("Draw hull");
    m_clearButton = new QPushButton("Clear");

    m_titleLayout->addWidget(m_titleLabel);
    m_titleLayout->addStretch(1);
    m_titleLayout->addWidget(m_startSlowButton);
    m_titleLayout->addWidget(m_startButton);
    m_titleLayout->addWidget(m_clearButton);

    m_parentLayout->addLayout(m_titleLayout);
    m_parentLayout->addWidget(m_canvas, 1);

    QObject::connect(m_clearButton, &QPushButton::clicked, m_canvas, &CanvasContainer::clearPoints);
    QObject::connect(m_startButton, &QPushButton::clicked, m_canvas, &CanvasContainer::drawHull);
    QObject::connect(m_startSlowButton, &QPushButton::clicked, m_canvas, &CanvasContainer::drawHullSlow);

    m_parentLayout->setContentsMargins(8, 8, 8, 8);
    m_titleLayout->setContentsMargins(0, 0, 0, 0);
}

Window::~Window() {

}