// widget.h

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

    void mousePressEvent(QMouseEvent *event); // mouse
    void mouseMoveEvent(QMouseEvent *event); // mouse

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

    QVector2D m_mousePosition; // mouse
    QQuaternion m_rotation; // mouse угол поворота

};
#endif // WIDGET_H

// wiget.cpp

#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>


Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_texture(0), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
    , ui(new Ui::Widget)
{
//    ui->setupUi(this); настройка форм
}

Widget::~Widget()
{
//    delete ui;
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0f);

//    loadObj(":/Monkey.obj");
//    append(m_objects[m_objects.size() - 1])

    m_arrayBuffer.bind();
    m_program.bind();
    m_indexBuffer.bind();
    m_texture->bind(0);

}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (h ? (float)h : 1);
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);

}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity( );
    viewMatrix.translate(0.0, 0.0, -4.0);

//    ModelViewMatrix.rotate(30, 1.0, 0.0, 0.0);
//    ModelViewMatrix.rotate(30, 0.0, 1.0, 0.0);

    viewMatrix.rotate(m_rotation); // mouse

    QMatrix4x4 modelMatrix;
    viewMatrix.setToIdentity();

    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue( "u_projectionMatrix" , m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", viewMatrix);
    m_program.setUniformValue("u_modelMatrix", modelMatrix);
    m_program.setUniformValue( "u_texture", 0);


    int VertLoc = m_program.attributeLocation("a_position");
    m_program.enableAttributeArray(VertLoc);
    m_program.setAttributeBuffer(VertLoc, GL_FLOAT, 0, 3, sizeof(VertexData));

    int texLoc = m_program.attributeLocation("a_texcoord");
    m_program.enableAttributeArray(texLoc);
    m_program.setAttributeBuffer(texLoc, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

    m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        m_mousePosition = QVector2D(event->localPos());
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) return;

    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    float angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);
    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

    update();
}

void Widget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
       exit(-230);

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
       exit(-229);

    if (!m_program.link())
       exit(-228);
}

void Widget::initCube(float width)
{
    float w_by2 = width / 2.0f;

    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;

    for (short i = 0; i < 24; i += 4) {

    indexes.append(i + 0);
    indexes.append(i + 1);
    indexes.append(i + 2);
    indexes.append(i + 2);
    indexes.append(i + 1);
    indexes.append(i + 3);
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes. constData(), vertexes.size() * sizeof(VertexData));
//     m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
//     m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

//void Widget::loadObj(QString path)
//    {
//        QFile objFile(path);
//        if (!objFile.exists())
//        {
//                qDebug() << "File not found";
//                return;
//        }
//        objFile.open(QIODevice::ReadOnly);
//        QTextStream input(&objFile);

//        QVector<QVector3D> coords;
//        QVector<QVector2D> texCoords;
//        QVector<QVector3D> normals;

//        QVector<VertexData> vertexes;
//        QVector<GLuint> indexes;

//        while (!input.atEnd())
//        {
//            QString str = input.readLine();
//            QStringList list = str.split(" ");
//            if (list[0] == "#") {
//                qDebug() << "this is comment:" << str;
//                continue;
//            } else if (list[0] == "mtllib") {
//                qDebug() << "File With material:" << str;
//                continue;
//            } else if (list[0] == "v") {
//                coords.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
//                continue;
//            } else if (list[0] == "f") {
//                for (int i = 1; i <= 3; ++i) {
//                    QStringList vert = list[i].split("/");
//                    vertexes.append(VertexData(coords[vert[0].toLong()-1], texCoords[vert[1].toLong()-1], normals[vert[2].toLong()-1]));
//                    indexes.append(indexes.size());

//                }
//                continue;
//            }

//        }
//        objFile.close();

//        // не введен текст из видео
//    }


// vshader.vsh

attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;
uniform highp mat4 u_ProjectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;

    gl_Position = u_ProjectionMatrix * mv_matrix * a_position;

    v_texcoord = a_texcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = mv_matrix * a_position;
}


// fshader.fsh

uniform sampler2D u_texture;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;


void main(void)
{
    gl_FragColor = texture2D(u_texture, v_texcoord);
}
