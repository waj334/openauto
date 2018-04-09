#include <f1x/openauto/autoapp/Projection/OMXVideoWidget.hpp>
#include <QtPlatformHeaders/QEGLNativeContext>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace projection
{

void OMXVideoWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
}

void OMXVideoWidget::paintGL()
{

}

void OMXVideoWidget::resizeGL(int, int)
{

}

EGLDisplay OMXVideoWidget::getDisplay() const
{
    auto glContext = this->context();
    auto eglHandle = qvariant_cast<QEGLNativeContext>(glContext->nativeHandle());

    return eglHandle.display();
}

EGLContext OMXVideoWidget::getContext() const
{
    auto glContext = this->context();
    auto eglHandle = qvariant_cast<QEGLNativeContext>(glContext->nativeHandle());

    return eglHandle.context();
}

}
}
}
}
