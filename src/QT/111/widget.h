#ifndef WIDGET_H
#define WIDGET_H



#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QVector2D>

extern "C" {
#include "back.h"
}

struct VertexData {
  QVector3D position;
};

//struct VertexData {

//    VertexData() {}

//    VertexData(QVector3D p, QVector2D t, QVector3D n) : position (p),
//        texCoord(t), normal(n) {}

//    QVector3D position;
//    QVector2D texCoord;
//    QVector3D normal;
//};

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    using QOpenGLWidget::QOpenGLWidget;
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Widget *geometries = nullptr;
    QColor *color = new QColor(255, 249, 0, 255);
    QColor *color_back = new QColor(152, 255, 152, 255);
    QColor *color_ver = new QColor(17, 242, 0, 255);
    int check_projection = 0;
    int line_width = 1;
    int line_type = 0;
//    void setTimer();
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QString path_convert;



    Widget();
//    virtual ~Widget();
    void initCubeGeometry();
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void drawDots(QOpenGLShaderProgram *program);
    struct data file = {0, 0, {0, 0, 0}, 0};
    QVector<GLuint> indices;
    QVector<VertexData> vertices;
    int dot_type = 0;
    int size_vert = 5;


protected:

    void initializeGL() override;
    void initShaders();
    //  void initTextures();
//    void initColors();
    void initColorsVer();
//    void timerEvent(QTimerEvent *e) override;

//    void initializeGL(); //вызывается один раз, при создании приложения
//    void resizeGL(int w, int h); //вызывается при масштабировании окна
//    void paintGL(); //можно вызвать принудительно методом update()

//    void initShaders();

//    void initCube(float width);

private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

//    QMatrix4x4 ProjectionMatrix; //для вычисления перспективы, отрисовки
//    QOpenGLShaderProgram ShaderProgram;
    QOpenGLTexture *m_texture;
//    QOpenGLBuffer ArrayBuffer; //вершинный буфер. для передачи информации вершинному шейдеру.
//    QOpenGLBuffer IndexBuffer; //пиксельный буфер

    QOpenGLShaderProgram program;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QQuaternion rotation;
};
#endif // WIDGET_H
