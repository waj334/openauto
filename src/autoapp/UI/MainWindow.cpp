/*
*  This file is part of openauto project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  openauto is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  openauto is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with openauto. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QTime>
#include <QTimer>
#include <f1x/openauto/autoapp/UI/MainWindow.hpp>
#include "ui_mainwindow.h"

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    updateTime();

    QTimer *clockTimer = new QTimer(this);
    clockTimer->start(1000);

    connect(clockTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(ui_->homeButton, &QPushButton::clicked, [this](){
        this->ui_->stackedWidget->setCurrentIndex(1);
    });
    connect(ui_->MusicButton, &QPushButton::clicked, [this](){
        this->ui_->stackedWidget->setCurrentIndex(0);
    });
    connect(ui_->SettingsButton, &QPushButton::clicked, [this](){
        this->ui_->stackedWidget->setCurrentIndex(2);
    });

    connect(ui_->pushButtonSettings, &QPushButton::clicked, this, &MainWindow::openSettings);
    connect(ui_->pushButtonExit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(ui_->pushButtonToggleCursor, &QPushButton::clicked, this, &MainWindow::toggleCursor);
    connect(ui_->pushButtonWirelessConnection, &QPushButton::clicked, this, &MainWindow::openConnectDialog);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::updateTime() {
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString timeText = time.toString("hh:mm");
    QString dateText = date.toString("dddd, MMMM d, yyyy");
    ui_->timeLabel->setText(timeText);
    ui_->dateLabel->setText(dateText);
}

}
}
}
}
