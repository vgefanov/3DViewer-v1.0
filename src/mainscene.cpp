#include "mainscene.h"


MainScene::MainScene() :
    m_vertexColors{ QColor("#f6a509"),
                    QColor("#cb2dde"),
                    QColor("#0eeed1"),
                    QColor("#068918") },
    m_program(nullptr),
    m_frameCount(5000)
{
    model = load_model("/Users/farfetch/C8_3DViewer_v1.0-0/src/models/small/cube.obj");
}


MainScene::~MainScene()
{
    makeCurrent();
    m_vao.destroy();
    m_vbo.destroy();
    m_ibo.destroy();
    delete m_program;
}


void MainScene::initializeGL()
{
    m_program = new QOpenGLShaderProgram();

    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/pass_through.vert"))
        qDebug() << "Vertex shader errors:\n" << m_program->log();

    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag"))
        qDebug() << "Fragment shader errors:\n" << m_program->log();

    if (!m_program->link())
        qDebug() << "Shader linker errors:\n" << m_program->log();

    float vertices[] = {
         0.8f,  0.8f, 0.0f,  // top right
         0.8f, -0.8f, 0.0f,  // bottom right
        -0.8f, -0.8f, 0.0f,  // bottom left
        -0.8f,  0.8f, 0.0f,  // top left
    };

    m_vertexBufferData.resize(2 * 4 * 3);
    float *buf = m_vertexBufferData.data();
    for (int v = 0; v < 4; ++v, buf += 6) {
        // coordinates
        buf[0] = vertices[3 * v];
        buf[1] = vertices[3 * v + 1];
        buf[2] = vertices[3 * v + 2];
        // colors
        buf[3] = m_vertexColors[v].redF();
        buf[4] = m_vertexColors[v].greenF();
        buf[5] = m_vertexColors[v].blueF();
    }

    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo.create();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.bind();
    m_vbo.allocate(m_vertexBufferData.data(), m_vertexBufferData.size() * sizeof(float));
    //m_vbo.allocate(model.vertexes, model.v_num * sizeof(float));

    m_vao.create();
    m_vao.bind();

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Mind: use 'IndexBuffer' here
    m_ibo.create();
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ibo.bind();
    m_ibo.allocate(indices, sizeof(indices) );
    // m_ibo.allocate(model.faces, model.f_num * sizeof(unsigned int));

    int stride = 6 * sizeof(float);

    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, stride);

    m_program->enableAttributeArray(1);
    int colorOffset = 3 * sizeof(float);
    m_program->setAttributeBuffer(1, GL_FLOAT, colorOffset, 3, stride);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void MainScene::paintGL()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    m_vao.release();

    animate();
}


void MainScene::updateScene()
{
    float * buf = m_vertexBufferData.data();
    for (int v=0; v<4; ++v, buf += 6) {
        buf[3] = m_vertexColors[v].redF();
        buf[4] = m_vertexColors[v].greenF();
        buf[5] = m_vertexColors[v].blueF();
    }

    makeCurrent();
    m_vbo.bind();
    m_vbo.allocate(m_vertexBufferData.data(), m_vertexBufferData.size() * sizeof(float));
    update();
}


void MainScene::animateColorsTo(const std::vector<QColor> & toColors)
{
    m_fromColors = m_vertexColors;
    m_toColors = toColors;
    m_frameCount = 0;
    animate();
}


void MainScene::animate()
{
    const unsigned int FRAMECOUNT = 120;
    if (++m_frameCount > FRAMECOUNT)
        return;

    double alpha = double(m_frameCount) / FRAMECOUNT;

    for (unsigned int i = 0; i < m_vertexColors.size(); ++i) {
        float fromH, fromS, fromV;
        m_fromColors[i].getHsvF(&fromH, &fromS, &fromV);
        float toH, toS, toV;
        m_toColors[i].getHsvF(&toH, &toS, &toV);

        m_vertexColors[i] = QColor::fromHsvF(toH * alpha + fromH * (1 - alpha),
                                             toS * alpha + fromS * (1 - alpha),
                                             toV * alpha + fromV * (1 - alpha));
    }

    updateScene();
}
