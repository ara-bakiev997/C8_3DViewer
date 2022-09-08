#include "widget.h"

#include <QVector2D>
#include <QVector3D>
#include <iostream>
using namespace std;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_texture(0), indexBuf(QOpenGLBuffer::IndexBuffer)
{
//  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
  initCubeGeometry();
}

Widget::~Widget() {
//  arrayBuf.destroy();
//  indexBuf.destroy();
}

void Widget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  initShaders();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  geometries = new GeometryEngine;
}

void Widget::initCubeGeometry() {
  for (int i = 0; i < file.count_of_vertexes; ++i) {
    VertexData tmp_vert = {QVector3D(file.matrix_3d.matrix[i][0],
                                     file.matrix_3d.matrix[i][1],
                                     file.matrix_3d.matrix[i][2])};
    vertices.push_back(tmp_vert);
  }

  for (int i = 0; i < file.count_of_facets; i++) {
    for (int j = 0; j < file.polygons[i].numbers_of_vertexes_in_facets - 1;
         j++) {
      indices.push_back(file.polygons[i].vertexes[j] - 1);
      indices.push_back(file.polygons[i].vertexes[j + 1] - 1);
    }
    indices.push_back(file.polygons[i].vertexes[0] - 1);
    indices.push_back(
        file.polygons[i]
            .vertexes[file.polygons[i].numbers_of_vertexes_in_facets - 1] -
        1);
  }
  arrayBuf.bind();
  arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));
  indexBuf.bind();
  indexBuf.allocate(indices.data(), indices.size() * sizeof(GLuint));
  m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMinificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);
  m_texture->bind(0);
}

void Widget::drawCubeGeometry(QOpenGLShaderProgram *program) {
  // Tell OpenGL which VBOs to use
  indexBuf.bind();
  if (arrayBuf.isCreated()) {
    arrayBuf.destroy();
    arrayBuf.create();
    arrayBuf.bind();
    QVector<VertexData> vertices;
    for (int i = 0; i < file.count_of_vertexes; ++i) {
      VertexData tmp_vert = {QVector3D(file.matrix_3d.matrix[i][0],
                                       file.matrix_3d.matrix[i][1],
                                       file.matrix_3d.matrix[i][2])};
      vertices.push_back(tmp_vert);
    }
    arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));
  }
  arrayBuf.bind();

      // Offset for position
  quintptr offset = 0;

      // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

      // Offset for texture coordinate
  offset += sizeof(QVector3D);

      // Tell OpenGL programmable pipeline how to locate vertex texture
  //    coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                              sizeof(VertexData));

  //    // Draw cube geometry using indices from VBO 1
  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

//void widget::paintGL()
void Widget::paintGL()
{
  glLineWidth(line_width);
//  initColors();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 matrix;
  matrix.translate(0.0, 0.0, -5.0);
//  matrix.rotate(rotation);

//  program.setUniformValue("mvp_matrix", projection * matrix);

  if (line_type) {
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 58360);
//    geometries->drawCubeGeometry(&program);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
  } else {
//    geometries->drawCubeGeometry(&program);
  }
//  initColorsVer();
//  geometries->drawDots(&program);
}





//Widget::Widget(QWidget *parent)
//    : QOpenGLWidget(parent), m_texture(0), IndexBuffer(QOpenGLBuffer::IndexBuffer)
//{
//   /*

//     QOpenGLBuffer по умолчанию является вершинным,
//     поэтому ArrayBuffer не трогаем

//    */
//}

//Widget::~Widget()
//{
//}

//void Widget::initializeGL()
//{
//    initializeOpenGLFunctions();

//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

//    glEnable(GL_DEPTH_TEST);
////    glEnable(GL_CULL_FACE); //не рисовать задние грани

//    initShaders();

//    initCube(1.0f);     ArrayBuffer.bind();

//ShaderProgram.bind();     IndexBuffer.bind();

//    m_texture->bind(0);
//}

//void Widget::resizeGL(int w, int h)
//{
//    float aspect = w / (float)h;

//    ProjectionMatrix.setToIdentity();
//    ProjectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
//}

//void Widget::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    QMatrix4x4 ModelViewMatrix;
//    ModelViewMatrix.setToIdentity();
//    ModelViewMatrix.translate(0.0, 0.0, -5.0);
//    ModelViewMatrix.rotate(30, 1.0, 0.0, 0.0);
//    ModelViewMatrix.rotate(30, 0.0, 1.0, 0.0);

//    m_texture->bind(0);

//    ShaderProgram.setUniformValue("qt_ModelViewProjectionMatrix", ProjectionMatrix * ModelViewMatrix);
//    ShaderProgram.setUniformValue("qt_Texture0", 0); //0 - номер текстуры, которая будет отрисована (по умолчанию 0)


//    int VertLoc = ShaderProgram.attributeLocation("qt_Vertex");
//    ShaderProgram.enableAttributeArray(VertLoc);
//    ShaderProgram.setAttributeBuffer(VertLoc, GL_FLOAT, 0, 3, sizeof(VertexData));

//    int texLoc = ShaderProgram.attributeLocation("qt_MultiTexCoord0");
//    ShaderProgram.enableAttributeArray(texLoc);
//    ShaderProgram.setAttributeBuffer(texLoc, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

//    glDrawElements(GL_TRIANGLES, IndexBuffer.size(), GL_UNSIGNED_INT, 0);
//}

//void Widget::initShaders()
//{
//   if (!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
//       exit(-230);

//   if (!ShaderProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
//       exit(-229);

//   if (!ShaderProgram.link())
//       exit(-228);
//}

//void Widget::initCube(float width)
//{
//    float w_by2 = width / 2.0f;

//    QVector<VertexData> vertexes;

//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

//    vertexes.append(VertexData(QVector3D(w_by2, w_by2, -w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, w_by2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(-w_by2, -w_by2, -w_by2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, w_by2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
//    vertexes.append(VertexData(QVector3D(w_by2, -w_by2, -w_by2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

//    QVector<GLuint> indexes;

//    for (short i = 0; i < 24; i += 4) {

//        indexes.append(i + 0);
//        indexes.append(i + 1);
//        indexes.append(i + 2);
//        indexes.append(i + 2);
//        indexes.append(i + 1);
//        indexes.append(i + 3);
//    }

//    ArrayBuffer.create();
//    ArrayBuffer.bind();
//    ArrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    
    
//    IndexBuffer.create();
//    IndexBuffer.bind();
//    IndexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    
//    m_texture = new QOpenGLTexture(QImage(":/large.png").mirrored());

//    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);

//    m_texture->setMinificationFilter(QOpenGLTexture::Linear);

//    m_texture->setWrapMode(QOpenGLTexture::Repeat);
//}
