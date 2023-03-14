// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>

#include "SceneGraphNode.hpp"

void processInput(GLFWwindow *window);
/*void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xpos, double ypos);*/

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.5f, 3.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float timeSpeed = 1.0;

//rotation
float angle = 0.;
float zoom = 1.;

bool display_cameraOrbitale = false;

bool PkeyIsPressed = false;
bool SemicolonkeyIsPressed = false;
bool CkeyIsPressed = false;
bool UpKeyIsPressed = false;
bool DownKeyIsPressed = false;

float timeCst = 0;


std::vector<glm::vec3> indexed_vertices;
std::vector<std::vector<unsigned short> > triangles;
std::vector<float> textureData;
int resolution = 8;
std::vector<unsigned short> indices;

SceneGraphNode* rootNode = new SceneGraphNode(indexed_vertices, textureData, indices, true);
SceneGraphNode* plan = new SceneGraphNode(indexed_vertices, textureData, indices, true);

bool isGrassTextureAlreadyImported = false;
    bool isRockTextureAlreadyImported = false;
    bool isSnowrocksTextureAlreadyImported = false;
    bool isHeightMapTextureAlreadyImported = false;

    bool isATexturedMesh = true;

/*******************************************************************************/

std::vector<glm::vec3> generatePlan(float length, int resolution) {

    std::vector<glm::vec3> vertices;

    float pas = length/(float)resolution;

    float positioni = 0, positionj;

    float nbSquare = pow(resolution, 2);

    float pasBasX = 0;
    float pasBasZ = 0;
    float pasHautX = pas;
    float pasHautZ = pas;

    int cpt = floor(nbSquare/resolution)-1;

    glm::vec3 basGauche, basDroit, hautGauche, hautDroit;

    for (int elt = 0; elt < nbSquare; elt++) {

        basGauche = glm::vec3(pasBasX, 0, pasBasZ);
        basDroit = glm::vec3(pasHautX, 0, pasBasZ);

        hautDroit = glm::vec3(pasHautX, 0, pasHautZ);
        hautGauche = glm::vec3(pasBasX, 0, pasHautZ);

        vertices.push_back(basGauche);
        vertices.push_back(basDroit);
        vertices.push_back(hautDroit);
        vertices.push_back(hautGauche);

        if (elt == cpt) {
            pasBasX -= pas*(resolution-1);
            pasHautX -= pas*(resolution-1);

            pasBasZ += pas;
            pasHautZ += pas;

            cpt += resolution;
        }
        else {
            pasBasX += pas;
            pasHautX += pas;
        }
    }

    return vertices;

}

std::vector<unsigned short> generateTriangle(int resolution) {

    std::vector<unsigned short> id;

    for (int i = 0; i < pow(resolution, 2)*4; i+=4) {

        id.push_back(i);
        id.push_back(i+1);
        id.push_back(i+2);

        id.push_back(i);
        id.push_back(i+2);
        id.push_back(i+3);

    }

    return id;

}

std::vector<float> generateTextureCoords(float length, int resolution) {

    std::vector<float> texture;

    texture.resize(resolution * resolution * 8);

    float pas = length/(float)resolution;

    float positioni = 0, positionj;

    float nbSquare = pow(resolution, 2);

    float pasBasX = 0;
    float pasBasZ = 0;
    float pasHautX = pas;
    float pasHautZ = pas;

    int cpt = floor(nbSquare/resolution)-1;

    int elt = 0;

    glm::vec3 basGauche, basDroit, hautGauche, hautDroit;

    for (int indexTexture = 0; indexTexture < resolution * resolution * 8; indexTexture+=8) {

        texture[indexTexture] = pasBasX;
        texture[indexTexture+1] = pasBasZ;
        texture[indexTexture+2] = pasHautX;
        texture[indexTexture+3] = pasBasZ;
        texture[indexTexture+4] = pasHautX;
        texture[indexTexture+5] = pasHautZ;
        texture[indexTexture+6] = pasBasX;
        texture[indexTexture+7] = pasHautZ;

        if (elt == cpt) {
            pasBasX -= pas*(resolution-1);
            pasHautX -= pas*(resolution-1);

            pasBasZ += pas;
            pasHautZ += pas;

            cpt += resolution;
        }
        else {
            pasBasX += pas;
            pasHautX += pas;
        }

        elt++;
    }

    return texture;

}


int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "TP3 - GLFW", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    /*glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetCursorPosCallback(window, scroll_callback);*/

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);


    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);


    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "vertex_shader.glsl", "fragment_shader.glsl" );

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms

    /****************************************/
    //Chargement du fichier de maillage
    /*std::string filename("cube.off");
    loadOFF(filename, indexed_vertices, indices, triangles );*/


    //Solar system
    /*bool isATexturedMesh = false;
    std::string filename("sphere.off");

    SceneGraphNode* rootNode = new SceneGraphNode(filename, isATexturedMesh);
    
    float sunScale = 0.75;
    SceneGraphNode* sun = new SceneGraphNode(filename, isATexturedMesh);
    sun->transform.position.x = 1;
    sun->transform.scale = {sunScale, sunScale, sunScale};

    float earthScale = 0.5;
    SceneGraphNode* earth = new SceneGraphNode(filename, isATexturedMesh);
    earth->transform.position.x = 3.5;
    earth->transform.scale = {earthScale, earthScale, earthScale};

    float moonScale = 0.2;
    SceneGraphNode* moon = new SceneGraphNode(filename, isATexturedMesh);
    moon->transform.position.x = 5;
    moon->transform.scale = {moonScale, moonScale, moonScale};
    
    rootNode->addChild(sun);
    sun->addChild(earth);
    earth->addChild(moon);*/

    
    //Mountain plan
    indexed_vertices = generatePlan(1, resolution);
    indices = generateTriangle(resolution);
    textureData = generateTextureCoords(1, resolution);

    rootNode->updateMeshData(indexed_vertices, textureData, indices);
    plan->updateMeshData(indexed_vertices, textureData, indices);
    rootNode->addChild(plan);

    GLuint vertexbuffer;
    GLuint elementbuffer;
    GLuint textureBuffer;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");


    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    do{

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);


        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change

        // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms

        /****************************************/
        glm::mat4 modelMatrix, viewMatrix, projectionMatrix;

        viewMatrix = glm::lookAt(camera_position, camera_position + camera_target, camera_up);

        projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);
        
        //Solar system
        /*glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, false, &earth->children[0]->transform.changeModelMatrix()[0][0]);
        earth->drawScene(programID);

        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, false, &sun->children[0]->transform.changeModelMatrix()[0][0]);
        sun->drawScene(programID);

        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, false, &rootNode->children[0]->transform.changeModelMatrix()[0][0]);
        rootNode->drawScene(programID);


        float earthRotationSpeed = 50.0f;
        glm::vec3 earthPositionRelativeToSun = earth->transform.position - sun->transform.position;
        glm::mat4 earthRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(earthRotationSpeed*deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        earthPositionRelativeToSun = glm::vec3(earthRotationMatrix * glm::vec4(earthPositionRelativeToSun, 1.0f));

        earth->transform.position = sun->transform.position + earthPositionRelativeToSun;
        earth->transform.rotation.x += 23*deltaTime;


        float moonRotationSpeed = 200.0f;
        glm::vec3 moonPositionRelativeToEarth = moon->transform.position - earth->transform.position;
        glm::mat4 moonRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(moonRotationSpeed*deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        moonPositionRelativeToEarth = glm::vec3(moonRotationMatrix * glm::vec4(moonPositionRelativeToEarth, 1.0f));

        moon->transform.position = earth->transform.position + moonPositionRelativeToEarth;
        moon->transform.position.x += 0.07;
        moon->transform.rotation.x += 6*deltaTime;


        earth->update();
        sun->transform.rotation.y += 20*deltaTime;
        sun->update();
        rootNode->update();
        
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1 , GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1 , GL_FALSE, &projectionMatrix[0][0]);*/


        //Moutain plan
        if (!display_cameraOrbitale) {

            modelMatrix = glm::mat4(1.0f);
        }
        else if (display_cameraOrbitale) {

            timeCst += deltaTime*timeSpeed;

            modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            modelMatrix = glm::rotate(modelMatrix, timeCst, glm::vec3(0, 1, 0));
        }


        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1 , GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1 , GL_FALSE, &projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, false, &modelMatrix[0][0]);

        rootNode->drawScene(programID);

        /*glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, rootNode->indexed_vertices.size() * sizeof(glm::vec3), &rootNode->indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, rootNode->indices.size() * sizeof(unsigned short), &rootNode->indices[0] , GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        if (isATexturedMesh) {
            glGenBuffers(1, &textureBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
            glBufferData(GL_ARRAY_BUFFER, rootNode->textureData.size() * sizeof(float), &rootNode->textureData[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
        }


        if (isATexturedMesh) {
            if (!isGrassTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE0);
                loadBMP_custom("grass.bmp");
                glUniform1i(glGetUniformLocation(programID, "grassTexture"), 0);

                isGrassTextureAlreadyImported = true;
            }

            if (!isRockTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE1);
                loadBMP_custom("rock.bmp");
                glUniform1i(glGetUniformLocation(programID, "rockTexture"), 1);

                isRockTextureAlreadyImported = true;
            }

            if (!isSnowrocksTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE2);
                loadBMP_custom("snowrocks.bmp");
                glUniform1i(glGetUniformLocation(programID, "snowrocksTexture"), 2);

                isSnowrocksTextureAlreadyImported = true;
            }

            if (!isHeightMapTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE3);
                loadBMP_custom("Heightmap_Mountain.bmp");
                glUniform1i(glGetUniformLocation(programID, "textureCoords"), 3);

                isHeightMapTextureAlreadyImported = true;
            }
        }

        glDrawElements(
                    GL_TRIANGLES,      // mode
                    rootNode->indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );*/


        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteProgram(programID);
    rootNode->deleteBuffer();
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    //Camera zoom in and out
    float cameraSpeed = 2.5 * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) { //touche W en azerty
        camera_position += cameraSpeed * camera_target;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { 
        camera_position -= cameraSpeed * camera_target;
    }
    //TODO add translations

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { //touche A
        camera_position -= glm::normalize(glm::cross(camera_position, camera_up)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_position += glm::normalize(glm::cross(camera_position, camera_up)) * cameraSpeed;
    }

    /*if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        camera_position += cameraSpeed * glm::vec3(0.0f, 0.0f, -0.2f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { //touche Q
        camera_position += cameraSpeed * glm::vec3(0.0f, 0.0f, 0.2f);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) { //W
        camera_position += cameraSpeed * glm::vec3(0.0f, -0.2f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera_position += cameraSpeed * glm::vec3(0.0f, 0.2f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera_position += cameraSpeed * glm::vec3(-0.2f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera_position += cameraSpeed * glm::vec3(0.2f, 0.0f, 0.0f);
    }*/


    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !PkeyIsPressed) {
        resolution ++;

        indexed_vertices = generatePlan(1, resolution);
        indices = generateTriangle(resolution);
        textureData = generateTextureCoords(1, resolution);

        rootNode->updateScene(indexed_vertices, textureData, indices);
        plan->updateScene(indexed_vertices, textureData, indices);

        PkeyIsPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
    {
        PkeyIsPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS && !SemicolonkeyIsPressed) { //M
        resolution --;

        indexed_vertices = generatePlan(1, resolution);
        indices = generateTriangle(resolution);
        textureData = generateTextureCoords(1, resolution);

        rootNode->updateScene(indexed_vertices, textureData, indices);
        plan->updateScene(indexed_vertices, textureData, indices);

        SemicolonkeyIsPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_RELEASE)
    {
        SemicolonkeyIsPressed = false;
    }


    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !CkeyIsPressed) {
        display_cameraOrbitale = !display_cameraOrbitale;

        CkeyIsPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
    {
        CkeyIsPressed = false;
    }


    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !UpKeyIsPressed) {
        timeSpeed += 0.1;

        UpKeyIsPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
    {
        UpKeyIsPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !DownKeyIsPressed) {
        timeSpeed -= 0.1;

        DownKeyIsPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
    {
        DownKeyIsPressed = false;
    }


}

/*void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_target = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}