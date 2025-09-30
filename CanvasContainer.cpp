#include "CanvasContainer.h"
#include <QLabel>
#include <QMouseEvent>
#include <string>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QPair>
#include <QHash>

CanvasContainer::CanvasContainer(QWidget *parent)
    : QWidget{parent} {
    m_testLabel = new QLabel(this);
    m_testLabel->setGeometry(0, 0, 240, 45);
    m_testLabel->show();
}

int CanvasContainer::calculateZCrossProduct(QPoint &p1, QPoint &p2, QPoint &p3) const {
    return ((p2.x() - p1.x()) * (p3.y() - p1.y())) - ((p2.y() - p1.y()) * (p3.x() - p1.x()));
}

void CanvasContainer::mousePressEvent(QMouseEvent *event) {
    m_isDrawHull = false;

    if (event->button() == Qt::LeftButton) {
        QPoint clickPos = event->pos();
        m_points.append(event->pos());
        QString posText = QString("Drawn a point at: (x=%1, y=%2)")
            .arg(clickPos.x())
            .arg(clickPos.y());
        m_testLabel->setText(posText);

        update();
    }
}

void CanvasContainer::clearPoints() {
    m_isDrawHull = false;
    m_points.clear();
    m_testLabel->setText("Cleared all points.");
    update();
}

void CanvasContainer::drawHull() {
    m_isDrawHull = true;
    m_drawHullMode = "fast";
    update();
}

void CanvasContainer::drawHullSlow() {
    m_isDrawHull = true;
    m_drawHullMode = "slow";
    update();
}

void CanvasContainer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FF0000"));

    for (const QPoint &point : m_points) {
        painter.drawEllipse(point, 2, 2);
    }

    if (m_isDrawHull && m_points.size() > 2) {
        int iterationCount = 0;
        if (m_drawHullMode != "slow") { // if drawing mode isn't set to slow -> uses the faster algo.
            // sorting by x, then y.
            QVector<QPoint> sortPoints(m_points);

            std::sort(sortPoints.begin(), sortPoints.end(), 
            [](const QPoint p1, const QPoint p2) {
                if (p1.x() != p2.x()) {
                    return p1.x() < p2.x();
                }
                return p1.y() < p2.y();
            });

            // building the upper hull
            QVector<QPoint> upperHullPoints;
            upperHullPoints.append(sortPoints[0]);
            upperHullPoints.append(sortPoints[1]);
            
            int pointsSize = sortPoints.size();
            for (int i = 2; i < pointsSize; ++i) {
                upperHullPoints.append(sortPoints[i]);
                ++iterationCount;
                int hullSize = upperHullPoints.size();
                while (hullSize > 2 &&
                calculateZCrossProduct(
                    upperHullPoints[hullSize - 1],
                    upperHullPoints[hullSize - 2],
                    upperHullPoints[hullSize - 3]
                ) /*>= 0 */ < 0) {
                    upperHullPoints.removeAt(hullSize - 2);
                    hullSize = upperHullPoints.size();
                    ++iterationCount;
                }
            }

            // building the lower hull
            QVector<QPoint> lowerHullPoints;
            lowerHullPoints.append(sortPoints[pointsSize - 1]);
            lowerHullPoints.append(sortPoints[pointsSize - 2]);
            for (int i = pointsSize - 3; i >= 0; --i) {
                lowerHullPoints.append(sortPoints[i]);
                ++iterationCount;
                int hullSize = lowerHullPoints.size();
                while (hullSize > 2 &&
                calculateZCrossProduct(
                    lowerHullPoints[hullSize - 1],
                    lowerHullPoints[hullSize - 2],
                    lowerHullPoints[hullSize - 3]
                ) /*>= 0 */ < 0) {
                    lowerHullPoints.removeAt(hullSize - 2);
                    hullSize = lowerHullPoints.size();
                    ++iterationCount;
                }
            }

            // remove first and last point from lower hull
            lowerHullPoints.removeFirst();
            lowerHullPoints.removeLast();

            QVector<QPoint> hullPoints;
            hullPoints.append(upperHullPoints);
            hullPoints.append(lowerHullPoints);

            // pen setup for drawing the outline
            QPen pen(Qt::blue, 1, Qt::SolidLine); // pen for drawing the convex hull outline.
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawPolygon(QPolygon(hullPoints));
            m_testLabel->setText(QString("Convex hull drawing (fast)\ncompleted in %1 iterations.").arg(iterationCount));
        }
        else { // if drawing mode is set to slow -> uses the slower bruteforcing algo.
            QVector<QPair<QPoint, QPoint>> hullEdges;

            for (int i = 0; i < m_points.size(); ++i) {
                ++iterationCount;
                for (int j = 0; j < m_points.size(); ++j) {
                    if (i == j) continue;
                    ++iterationCount;

                    QPoint& p = m_points[i];
                    QPoint& q = m_points[j];

                    bool isValidEdge = true;

                    for (int k = 0; k < m_points.size(); ++k) {
                        if (k == i || k == j) continue;
                        ++iterationCount;

                        QPoint& r = m_points[k];

                        if (calculateZCrossProduct(p, q, r) > 0) {
                            isValidEdge = false;
                            break;
                        }
                    }

                    if (isValidEdge) {
                        hullEdges.append({p, q});
                    }
                }
            }

            QHash<QPoint, QPoint> edgeMap;
            for (const auto& edge : hullEdges) {
                edgeMap[edge.first] = edge.second;
            }

            QVector<QPoint> convexHull;
            QPoint currentPoint = hullEdges[0].first;

            for (int i = 0; i < hullEdges.size(); ++i) {
                convexHull.append(currentPoint);
                currentPoint = edgeMap.value(currentPoint);
            }

            // pen setup for drawing the outline
            QPen pen(Qt::black, 1, Qt::SolidLine);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawPolygon(QPolygon(convexHull));
            m_testLabel->setText(QString("Convex hull drawing (slow)\ncompleted in %1 iterations.").arg(iterationCount));
        }
    }
}

CanvasContainer::~CanvasContainer() {

}
