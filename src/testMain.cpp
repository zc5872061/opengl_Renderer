/*
 
	Copyright 2010 Etay Meiri
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 Tutorial 03 - First triangle
 */

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>

GLuint VBO;

static void RenderSceneCB()
{
    glClearColor(0.0f, 0.25f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}


static void update_timer(void)
{
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    glm::vec3 Vertices[3];
    Vertices[0] =     glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] =     glm::vec3(1.0f, -1.0f, 0.0f);
    Vertices[2] =     glm::vec3(0.0f, 1.0f, 0.0f);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World");
    glutIdleFunc(&RenderSceneCB);
    
    glutDisplayFunc(&RenderSceneCB);
    
    glewInit();

    glutMainLoop();
    return 0;

}



