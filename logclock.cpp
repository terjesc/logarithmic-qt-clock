/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <cmath>

#include "logclock.h"

#define SKEW -0.177

//! [0] //! [1]
LogarithmicClock::LogarithmicClock(QWidget *parent)
//! [0] //! [2]
	: QWidget(parent)
//! [2] //! [3]
{
//! [3] //! [4]
	QTimer *timer = new QTimer(this);
//! [4] //! [5]
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//! [5] //! [6]
	timer->start(50);
//! [6]

	setWindowTitle(tr("Logarithmic Clock"));
	resize(200, 200);
//! [7]
}
//! [1] //! [7]

//! [8] //! [9]
void LogarithmicClock::paintEvent(QPaintEvent *)
//! [8] //! [10]
{
	static const QPoint hourHand[3] = {
		QPoint(9, 5),
		QPoint(-9, 5),
		QPoint(0, -50)
	};
	static const QPoint minuteHand[3] = {
		QPoint(7, 7),
		QPoint(-7, 7),
		QPoint(0, -70)
	};
	static const QPoint secondHand[3] = {
		QPoint(5, 9),
		QPoint(-5, 9),
		QPoint(0, -90)
	};


	QColor hourColor(127, 0, 127);
	QColor minuteColor(0, 127, 127, 191);
	QColor secondColor(127, 127, 0, 191);

	int side = qMin(width(), height());
	QTime time = QTime::currentTime();
//! [10]

//! [11]
	QPainter painter(this);
//! [11] //! [12]
	painter.setRenderHint(QPainter::Antialiasing);
//! [12] //! [13]
	painter.translate(width() / 2, height() / 2);
//! [13] //! [14]
	painter.scale(side / 200.0, side / 200.0);
//! [9] //! [14]

//! [15]
	painter.setPen(Qt::NoPen);
//! [15] //! [16]
	painter.setBrush(hourColor);
//! [16]

//! [17] //! [18]
	painter.save();
//! [17] //! [19]
	painter.rotate(
		logSkew(
			(30.0 * ( (time.hour() % 12)
				+ (time.minute() / 60.0)
				+ (time.second() / 3600.0))),
			SKEW));
	painter.drawConvexPolygon(hourHand, 3);
	painter.restore();

//! [18] //! [19]
	painter.setPen(hourColor);
	for (int i = 0; i < 12; ++i) {
		painter.save();
		painter.rotate(logSkew(30.0 * i, SKEW));
		painter.drawLine(0, -84, 0, -96);
		painter.restore();
	}
//! [21]

//! [22]
	painter.setPen(Qt::NoPen);
//! [22] //! [23]
	painter.setBrush(minuteColor);

//! [24]
	painter.save();
	painter.rotate(
		logSkew(
			(6.0 * ( time.minute()
				+ (time.second() / 60.0)
				+ (time.msec() / 60000.0))),
			SKEW));
	painter.drawConvexPolygon(minuteHand, 3);
	painter.restore();
//! [23] //! [24]
	painter.setBrush(secondColor);
	painter.save();
	painter.rotate(
		logSkew(
			(6.0 * ( time.second() + (time.msec() / 1000.0))),
			SKEW));
	painter.drawConvexPolygon(secondHand, 3);
	painter.restore();

//! [25]
	painter.setPen(minuteColor);
//! [25] //! [26]

//! [27]
	for (int j = 0; j < 60; ++j) {
		if ((j % 5) != 0)
		{
			painter.save();
			painter.rotate(logSkew(6.0 * j, SKEW));
			painter.drawLine(0, -87, 0, -93);
			painter.restore();
		}
	}
//! [27]
}
//! [26]

double logSkew(double theta, double skew) {
	return -(57.2957795/skew) * log(1.0 + exp(skew*2*3.14159256) - exp(skew*theta/57.2957795));
}

