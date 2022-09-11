#include "glwidget.h"
//#include "GLUT/glut.h"




GLWidget ::  GLWidget(QWidget *parent) : QOpenGLWidget (parent) {
    vertex = {0, nullptr};
    facet = {0, nullptr};
}


void GLWidget::initializeGL() {


    glEnable(GL_DEPTH_TEST);
// ///////////////////////////
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);



}

void GLWidget::resizeGL(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-100, 100, -100, 100, -100, 100);
//    glFrustum(0, 0, -0, 0, -0, 0);
    glOrtho(0, 0, 0, 0, 0, 0);


}

void GLWidget::paintGL() {


    glClearColor(0.8, 0.8, 0.8, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScaled(scale, scale, scale); // масштаб
    glTranslated(0, 0, 0);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    drawCubeLine();

    update();


}


void GLWidget::drawCubeLine() {

    glEnable(GL_POINT_SMOOTH);
    glPointSize(7);
    glColor3d(1,0,0);
            //Projection//

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_DOUBLE, 0 ,vertex.arg);

    glDrawElements(GL_POINTS, facet.count, GL_UNSIGNED_INT, facet.arg);

    glColor3d(0,0,1);
    glLineWidth(1);
    glDrawElements(GL_LINES, facet.count, GL_UNSIGNED_INT, facet.arg);

    glDisableClientState(GL_VERTEX_ARRAY);
}


void GLWidget::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {

    if (!(mo->pos().x() >= 625 && mo->pos().x() <= 901 && mo->pos().y() >= 630 && mo->pos().y() <= 851)) {
        xRot += 1 / M_PI*(mo->pos().y()-mPos.y());
        yRot += 1 / M_PI*(mo->pos().x()-mPos.x());
    }


    mPos = mo->pos();

    update();
}






















