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

#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <qmetatype.h>
#include <qtextstream.h>
#include <EGL/egl.h>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace projection
{

class OMXVideoWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    EGLDisplay getDisplay() const;
    EGLContext getContext() const;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

}
}
}
}
