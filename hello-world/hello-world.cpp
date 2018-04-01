#include <iostream>
#include <GL/glut.h>
#include "sdl2-wrapper.h"

class OpenGLError : public std::runtime_error
{
  public:
    OpenGLError(const std::string& what) : std::runtime_error(what) {}
    OpenGLError(const char* what) : std::runtime_error(what) {}
};

static void checkError() {
  //Check for error
  GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		throw OpenGLError{"Unable to initialize OpenGL"};
	}
}

static void initGL()
{
	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

int main(int argc, char** argv)
{
  try {

    // Initialize SDL
    SDL2::SDL sdl{SDL_INIT_EVERYTHING};

    // Use OpenGL 2.1, 3.3 or 4.5
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Create window
    SDL2::Window window{
      "Hello, World!",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    };

    SDL_GLContext context = SDL_GL_CreateContext(window.get());
    if (context == nullptr) {
      throw SDL2::SDLError{"OpenGL context could not be created"};
    }

    if (SDL_GL_SetSwapInterval(1) != 0) {
      SDL_Log("[WARN] Unable to set VSync. SDL Error: %s\n", SDL_GetError());
    }

    //Initialize OpenGL
    initGL();

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    double angle = 0.0;
    //While application is running
    while(!quit)
    {
      //Handle events on queue
      while(SDL_PollEvent(&e) != 0)
      {
        //User requests quit
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //Render quad 1
      glLoadIdentity();
      glRotated(angle, 0.0, 1.0, 0.0);
      angle = (static_cast<int>(angle) % 360) + 1.0;
      glTranslated(0.0, 0.3, 0.0);
      glBegin(GL_TRIANGLES);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(-0.5, -0.5, 0.0);

        glColor3d(1.0, 0.0, 0.0);
        glVertex3d( 0.5, -0.5, 0.0);

        glColor3d(0.0, 0.0, 1.0);
        glVertex3d( 0.0,  0.5, 0.0);
      glEnd();

      //Render quad 2
      glLoadIdentity();
      glRotated(/*180*/angle, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.3, 0.0);
      glBegin(GL_TRIANGLES);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(-0.5, -0.5, 0.0);

        glColor3d(0.0, 0.0, 1.0);
        glVertex3d( 0.5, -0.5, 0.0);

        glColor3d(0.0, 1.0, 0.0);
        glVertex3d( 0.0,  0.5, 0.0);
      glEnd();
      
      //Update screen
      SDL_GL_SwapWindow(window.get());
    }

    //SDL_DestroyContext();
  }
  catch(SDL2::SDLError& e) {
    e.print();
    return e.return_code();
  }
  catch (OpenGLError& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}

