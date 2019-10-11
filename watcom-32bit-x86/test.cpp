#include <windows.h>
#include <wchar.h>
#include <stdlib.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#ifdef UNICODE
#define CreateWindow  CreateWindowW
#else
#define CreateWindow  CreateWindowA
#endif

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "User32.lib")


GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  
/* Red diffuse light. */

GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  
/* Infinite light location. */
/* Normals for the 6 faces of a cube. */
GLfloat n[6][3] = {  
  
{-1.0, 0.0, 0.0}, 
{0.0, 1.0, 0.0}, 
{1.0, 0.0, 0.0},
  
{0.0, -1.0, 0.0}, 
{0.0, 0.0, 1.0}, 
{0.0, 0.0, -1.0} 
};
/* Vertex indices for the 6 faces of a cube. */
GLint faces[6][4] = {  
  
{0, 1, 2, 3}, 
{3, 2, 6, 7}, 
{7, 6, 5, 4},
  
{4, 5, 1, 0}, 
{5, 6, 2, 1}, 
{7, 4, 0, 3} 
};


GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void
init(){
  /* Setup cube vertex data. */
  
        v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  
        v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  
        v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;

        v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
        
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;

        v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;


  /* Enable a single OpenGL light. */
  
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  
        glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  
/* Use depth buffering for hidden surface elimination. */
  
        glEnable(GL_DEPTH_TEST);

  
/* Setup the view of the cube. */
  
        glMatrixMode(GL_PROJECTION);
  /* field of view in degree */  /* aspect ratio */ /* Z near */  /* Z far */
        gluPerspective( 120.0, 1.0, 1.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
  /* eye is at (0,0,5) *//* center is at (0,0,0) */
        gluLookAt(0.0, 0.0, 5.0,  
    			0.0, 0.0, 0.0,      
    			0.0, 1.0, 0.0);      
/* up is in positive Y direction */

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
        MSG msg          = {0};
        WNDCLASSA wc      = {0}; 
        wc.lpfnWndProc   = WndProc;
        wc.hInstance     = hInstance;
        wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wc.lpszClassName = "oglversionchecksample";
	wc.lpszMenuName = "myopengl";
        wc.style = CS_OWNDC;
        if( !RegisterClass(&wc) )
                return 1;
        CreateWindow(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,500,500,0,0,hInstance,0);
	
        while( GetMessage( &msg, NULL, 0, 0 ) > 0 ){
		DispatchMessage( &msg );
	}

        return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		int i;

		PIXELFORMATDESCRIPTOR pfd =
                {
                        sizeof(PIXELFORMATDESCRIPTOR),
                        1,
                        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
                        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                        32,                   // Colordepth of the framebuffer.
                        0, 0, 0, 0, 0, 0,
                        0,
                        0,
                        0,
                        0, 0, 0, 0,
                        24,                   // Number of bits for the depthbuffer
                        8,                    // Number of bits for the stencilbuffer
                        0,                    // Number of Aux buffers in the framebuffer.
                        PFD_MAIN_PLANE,
                        0,
                        0, 0, 0
                };

                HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

                int  letWindowsChooseThisPixelFormat;
                letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
                SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

                HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
        switch(message)
        {
        case WM_CREATE:
                wglMakeCurrent (ourWindowHandleToDeviceContext,ourOpenGLRenderingContext);
                MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
		init();
                break;
	case WM_QUIT:
		wglMakeCurrent(ourWindowHandleToDeviceContext,NULL);
		wglDeleteContext(ourOpenGLRenderingContext);
		PostQuitMessage(0);
        	break;

	default:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
       		glRotatef(0.07, 1.0, 0.0, 0.0);
       		glRotatef(0.1, 0.0, 1.0, 0.0);  
       		for (i = 0; i < 6; i++) {
    
    	           	glBegin(GL_QUADS);
                
		    	glNormal3fv(&n[i][0]);

	               	glVertex3fv(&v[faces[i][0]][0]);
                
		    	glVertex3fv(&v[faces[i][1]][0]);

	               	glVertex3fv(&v[faces[i][2]][0]);

	               	glVertex3fv(&v[faces[i][3]][0]);
			
        	       	glEnd();
       		}
		glFlush();
		glDrawBuffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		wglSwapLayerBuffers(ourWindowHandleToDeviceContext, message);
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
}

