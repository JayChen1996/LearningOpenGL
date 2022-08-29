#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>


#include <glad/glad.h>
#include <GLFW/glfw3.h>




//#include<pangolin/pangolin.h>
//#include<pangolin/display/display.h>
//#include<pangolin/display/view.h>

const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 "   color = vec3(aColor.x, aColor.y, aColor.z);\n"
                                 //"   gl_Position = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 color;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(color.x, color.y, color.z, 1.0f);\n"
                                   //"   FragColor = vec4(0.2f, 0.5f, 0.7f, 1.0f);\n"
                                   "}\n\0";

//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow *window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


int main(int argc, char** argv)
{

    glfwInit();    // 初始化窗口
    // glfwWindowHint用于设置OpenGL的一些选项，第一个参数是选项名，第二个参数是选项值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window= glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",NULL,NULL);
    if(window==NULL){
        std::cout<<"Failed to create FLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    // 窗口创建完毕，让当前窗口的环境在当前线程上成为当前环境
    glfwMakeContextCurrent(window);
    // 设置窗口大小改变时的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // 加载glfwGetProcAddress这个函数，用于查找函数地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    // 创建一个着色器对象并返回ID
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 为这个着色器绑定着色器源代码
    glCompileShader(vertexShader);                      // 编译源代码得到着色器程序对象
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    // 创建着色器程序对象，注意着色器对象和着色器程序对象是有区别的，着色器对象是着色器源代码编译结果，着色器程序对象是着色器对象编译链接后的结果。
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//    float vertices[] = {
//            0.5f,  0.5f, 0.0f,  // top right
//            0.5f, -0.5f, 0.0f,  // bottom right
//            -0.5f, -0.5f, 0.0f,  // bottom left
//            -0.5f,  0.5f, 0.0f   // top left
//    };
//    float colors[] = {
//            0.2f,0.3f,0.4f,  // top right
//            0.2f,0.5f,0.6f,  // bottom right
//            0.5f,0.6f,0.8f,  // bottom left
//            0.7f,0.4f,0.1f   // top left
//    };
    float vertices[] = {
//            0.2f,0.3f,0.4f,0.5f,  0.5f, 0.0f,  // top right
//            0.2f,0.5f,0.6f,0.5f, -0.5f, 0.0f,  // bottom right
//            0.5f,0.6f,0.8f,-0.5f, -0.5f, 0.0f,  // bottom left
//            0.7f,0.4f,0.1f,-0.5f,  0.5f, 0.0f   // top left
            0.2f,0.3f,0.4f,-1.0f,  0.0f, 0.0f,
            0.2f,0.5f,0.6f,-0.5f, -0.8f, 0.0f,
            0.5f,0.6f,0.8f,0.0f, -0.0f, 0.0f,
            0.7f,0.4f,0.1f,0.5f,  0.5f, 0.0f,
            0.4f,0.3f,0.1f,1.0f,0.0f,0.0f//
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,  // first Triangle
            2, 3, 4   // second Triangle
    };
    unsigned int VBO, VAO, EBO,COLOR;     // VBO顶点缓冲对象，VAO顶点数组对象，EBO元素缓冲对象(也叫索引缓冲对象IBO)
    glGenVertexArrays(1, &VAO);     // 生成顶点数组对象,第一个参数是数量，第二个参数是地址。如果生成多个对象，可以使用数组地址，函数会依次填入
    glGenBuffers(1, &VBO);          // 生成缓冲对象
    glGenBuffers(1, &EBO);          // 生成缓冲对象
    // glGenBuffers(1, &COLOR);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);         // 绑定顶点数组对象ID

    // OpenGL允许同时绑定多个缓冲，只要是不同的缓冲类型，也就是说绑定了GL_ARRAY_BUFFER这个缓冲类型
    // 后面不能再绑定GL_ARRAY_BUFFER这个缓冲类型。
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::cout<<"VBO: "<<VBO<<std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 复制顶点数据到显存，vertices是矩形顶点数据
    //glBindBuffer(GL_ARRAY_BUFFER, COLOR);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);  // 复制顶点数据到显存，vertices是矩形顶点数据

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);    // 拷贝索引缓冲对象,indices是索引数据

    // 第一个参数，指定要配置的顶点属性，在顶点着色器中使用layout(location=0)定义了position顶点属性的位置值(Location)
    // 意思应该是顶点属性组中的索引
    // 第二个参数指定顶点属性分量的个数。顶点属性是一个vec3，由3个值组成，所以大小是3,顶点属性的分量个数。
    // 第三个参数指定数据类型，这里是GL_FLOAT，GLSL中的vec*都是浮点数值
    // 第四个参数定义是否希望数据被标准化
    // 第五个参数意思是步长，给出连续的顶点属性组之间的间隔，如果有更多的顶点属性，就必须小心地定义每个顶点属性之间的间隔。
    // 最后一个参数类型是void* 表示位置数据在缓冲中起始位置的偏移量。
    // 顶点属性指针
    // 顶点数据在显存中只是一大块二进制内存块，这里告诉OpenGL这块内存的格式是什么
    // 顶点数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));       // 这个函数告诉OpenGL如何解析顶点数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);       // 默认情况下顶点属性变量是关闭的，需要使用glEnableVertexAttribArray启用
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // 注意这是允许的，对glVertexAttribPointer的调用将VBO注册为顶点属性的边界顶点缓冲对象，因此后续可以安全地解绑。
    // 注意这里是解绑的操作，绑定对象ID都是大于0的，等于0表示与所有已绑定的对象解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // 记住：当VAO还是活跃的，边界元素缓冲对象存储在VAO时不要解绑EBO
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        // 处理窗口的输入
        processInput(window);

        // render渲染
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle绘制第一个三角形
        glUseProgram(shaderProgram);
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // glfw:清除缓存并查询IO事件(键盘按下/释放，鼠标移动等)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;





//    //  顶点数据
//    float vertices[] = {
//            -0.5f,-0.5f,0.0f,
//            0.5f,-0.5f,0.0f,
//            0.0f,0.5f,0.0f
//    };
//    // 顶点数据被定义后，会被发送到图形渲染管线的第一个处理阶段：顶点着色器。
//    // 顶点着色器在GPU上创建内存(后面称为显存)用于存储顶点数据，还要配置OpenGL如何解释这些内存，并且指定其如何发送给显卡
//    // 顶点着色器会处理我们在内存中指定数量的顶点
//
//    // 顶点缓冲对象用于管理顶点着色器的显存，他会在显存中存储大量顶点
//    // 也就是说顶点着色器会将顶点数据从内存中发送到显存中的顶点缓冲对象里面。
//
//    // 顶点缓冲对象VBO和OpenGL其他对象一样，有一个独一无二的ID
//    // 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);  // 1是缓冲对象名编号ID,VBO是缓冲对象指针,这个函数创建顶点缓冲对象
//
//    // OpenGL有许多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER，OpenGL可以同时绑定多个不同的缓冲类型
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // 创建缓冲对象后要绑定缓冲对象类型
//    // 在Bind绑定之后，使用的任何在GL_ARRAY_BUFFER目标上的缓冲调用都会用来配置当前绑定的缓冲(VBO)。
//    // 然后可以调用glBufferData函数，将内存中的顶点数据复制到显存中。
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //将顶点数据复制到显存。VBO和数据通过GL_ARRAY_BUFFER联系
//    // 现在已经将顶点数据存储在显存中，使用VBO这个顶点缓冲对象管理这块数据。
//    // 下面创建一个顶点着色器和片段着色器真正处理这些数据
//
//    /*
//    // 版本声明，使用opengl3.3或更高版本编译这个着色器，使用核心模式
//    #version 330 core
//    layout (location = 0) in vec3 aPos;     // in 是关键字 aPos是变量名 vec3是数据类型 layou (location = 0) 设置了输入变量的位置值
//
//    void main()
//    {
//        // 为了设置顶点着色器的输出，必须把位置数据赋值给预定义的gl_Position变量，这个变量是vec4类型的，在main函数的最后，
//        // gl_POsition设置的值会成为该顶点着色器的输出。
//        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//    }
//    */
//    // 将着色器源代码硬编码进字符串
//    const char *vertexShaderSource = "#version 330 core\n"
//                                     "layout (location = 0) in vec3 aPos;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                     "}\0";
//    // 在运行时动态编译这个字符串源代码
//    // 创建一个着色器对象，OpenGL中的对象都是通过ID来引用
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource,, NULL);
//    glCompileShader(vertexShader);
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
//    }
//
//    // 片段着色器 Fragment Shader，用于计算像素最后的颜色输出
//    /*
//    #verssion 330 core
//    out vec4 FragColor
//    void main()
//    {
//            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    }
//    */
//    unsigned int fragmentShader;
//    const char *fragmentShaderSource = "#version 330 core\n"
//            "out vec4 FragColor;\n"
//            "\n"
//            "void main()\n"
//            "{\n"
//            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//            "}\0";
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    // 多个着色器合并之后并最终链接称为着色器程序对象。
//    // 在渲染对象时激活这个着色器程序
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    glUseProgram(shaderProgram);
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);




    // 2022-8-10
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if(window==NULL){
//        std::cout<<"Failed to create GLFW window"<<std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
//        std::cout<<"Failed to initialize GLAD"<<std::endl;
//        return -1;
//    }
//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    while(!glfwWindowShouldClose(window)){
//
//        processInput(window);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();


    // 2022-8-3
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("OpenGL Version");
//    const GLubyte* name=glGetString(GL_VENDOR);
//
//    const GLubyte* biaoshifu=glGetString(GL_RENDER);
//    const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
//    const GLubyte* gluVersion = glGetString(GLU_VERSION);
//    printf("OpenGL实现厂商名字: %s \n", name);
//    printf("渲染器标志符: %s \n", biaoshifu);
//    printf("OpenGL实现版本号: %s \n", OpenGLVersion);
//    printf("OGLU工具库版本: %s \n", gluVersion);




	return 0;
}






















