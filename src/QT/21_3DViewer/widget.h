//#ifndef WIDGET_H
//#define WIDGET_H

//#include <QWidget>

//#include <QOpenGLWidget>
//#include <QMatrix4x4>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLTexture>
//#include <QOpenGLBuffer>
//#include <QOpenGLFunctions>

//#include <QFile>


//struct VertexData
//{
//    VertexData()
//    {
//    }
//    VertexData(QVector3D p, QVector2D t, QVector3D n) :
//        position(p), texCoord(t), normal(n)
//    {
//    }
//    QVector3D position;
//    QVector2D texCoord;
//    QVector3D normal;
//};

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

//class Widget : public QOpenGLWidget, QOpenGLFunctions

//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();

//protected:
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();

//    void mousePressEvent(QMouseEvent *event); // mouse
//    void mouseMoveEvent(QMouseEvent *event); // mouse

//    void initShaders();
//    void initCube(float width);
//    void loadObj(QString path);


//private:
//    Ui::Widget *ui;

//    QMatrix4x4 m_projectionMatrix;
//    QOpenGLShaderProgram m_program;
//    QOpenGLTexture *m_texture;
//    QOpenGLBuffer m_arrayBuffer;
//    QOpenGLBuffer m_indexBuffer;

//    QVector2D m_mousePosition; // mouse
//    QQuaternion m_rotation; // mouse угол поворота

//};
//#endif // WIDGET_H



//____________________________-
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

#include <QFile>


struct VertexData
{
    VertexData()
    {
    }
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texCoord(t), normal(n)
    {
    }
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget, QOpenGLFunctions

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void initShaders();
    void initCube(float width);
    void loadObj(QString path);


private:
    Ui::Widget *ui;

    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QOpenGLTexture *m_texture;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    QVector2D m_mousePosition; // мышь
    QQuaternion m_rotation; // mouse угол поворота
};
#endif // WIDGET_H
