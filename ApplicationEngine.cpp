// ApplicationEngine.cpp: implementation of the ApplicationEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayTracingEngine.h"
#include "ApplicationEngine.h"
#include "gz.h"
//#include "GzDisplay.h"
//#include "GzRender.h"

#include <cstdio>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INFILE  "rects"
#define OUTFILE "output.ppm"

// Might be useful. But I think we'll have better way.
//extern int tex_fun(float u, float v, GzColor color); // image texture function
//extern int ptex_fun(float u, float v, GzColor color); // procedural texture function

ApplicationEngine::ApplicationEngine()
{

}

ApplicationEngine::~ApplicationEngine()
{
    Clean();
}

int ApplicationEngine::Initialize()
{
    // Tokens need to be redesigned.
    //GzToken  nameListShader[9];      // shader attribute names
    //GzPointer   valueListShader[9];  // shader attribute pointers
    //GzToken     nameListLights[10];  // light info
    //GzPointer   valueListLights[10];
    //int   shaderType, interpStyle;
    //float  specpower;
    int status(GZ_SUCCESS); 

    try
    {
        // m_nWidth and m_nHeight are variables inherited from Application class.
        m_nWidth = 256;  // frame buffer and display width
        m_nHeight = 256;    // frame buffer and display height

        // Initialize frame buffer and display
        status = status || GzNewFrameBuffer(m_pFrameBuffer, m_nWidth, m_nHeight);

        status = status || GzNewDisplay(m_pDisplay, m_nWidth, m_nHeight);

        GzCamera *p_camera = new GzCamera(GzVector3(0.0f, 10.0f, -10.0f), GzVector3(0.0f, 5.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f), 116.0f);
        GzLight **g_lights = new GzLight*[1];
        //g_lights[0] = new GzLight(GzVector3(-15.0f, 25.0f, 5.0f), GzVector3(0, 0, -10.0f), GzVector3(0, -10.0f, 0.0f));
        //g_lights[0] = new GzLight(DIR_LIGHT, GzVector3(0.0f, 20.0f, 0.0f), GzColor::WHITE);
        //g_lights[0] = new GzLight(DIR_LIGHT, GzVector3(0, 1.0f, 0), GzColor::WHITE);
        g_lights[0] = new GzLight(POINT_LIGHT, GzVector3(-15, 20.0f, 0), GzColor::WHITE);
        //g_lights[1] = new GzLight(POINT_LIGHT, GzVector3(-10.0f, 20.0f, 0), GzColor::RED);
        //g_lights[0] = new GzLight(POINT_LIGHT, GzVector3(-10.0f, 20.0f, 0), GzColor::WHITE);
        //GzMaterial mTemp1;
        //GzMaterial mTemp2(GzColor::RED, GzColor::BLACK, GzColor::WHITE, 15, 0);
        // We'll do AA in renderer directly.
        //
        //**********************
        // Same routine. Set up camera, lights for our renderer
        // in this initialize function, like
        //```
        m_pRender = new GzRender(m_pDisplay);
        status = status || m_pRender->putCamera(p_camera);

        status = status || m_pRender->putLights(g_lights, 1);
        //GzVector3 *kernel4 = new GzVector3[4];
        //kernel4[0] = GzVector3(-0.25f, 0.25f, 0.25f);
        //kernel4[1] = GzVector3(0.25f, 0.25f, 0.25f);
        //kernel4[2] = GzVector3(-0.25f, -0.25f, 0.25f);
        //kernel4[3] = GzVector3(0.25f, -0.25f, 0.25f);
        GzAASetting *p_9SAA = new GzAASetting(3);
        status = status || m_pRender->putAASetting(p_9SAA); //optional
        //status = status || renderer.putAttribute(refractionmode); //optional
        //status = status || renderer.putAttribute(diffusemode); //optional
        //status = status || renderer.putAttribute(arealightmode); //optional
        //```
        // Still need tokens. But might be quite different from original.
        // Pass pointers and boolean values to renderer. And do
        // rendering inside Render() function.
        //************************
    }
    catch (GzException)
    {
        status = GZ_FAILURE;
    }
    if (status)
    {
        AfxMessageBox(_T("Initiating went wrong!\n"));
    }
    return(status);
}

int ApplicationEngine::Render() 
{
    int status(GZ_SUCCESS); 

    try
    {
        // Initialize Display
        m_pDisplay->init(GzColor(0.4f, 0.8f, 1.0f));

        // I/O File open. Temporary
        //
        //FILE *infile;
        //if( (infile  = fopen( INFILE , "r" )) == NULL )
        //{
            //AfxMessageBox( "The input file was not opened\n" );
            //return GZ_FAILURE;
        //}
        //
        FILE *outfile;
        if( (outfile  = std::fopen( OUTFILE , "wb" )) == NULL )
        {
            AfxMessageBox(_T("The output file was not opened\n"));
            return GZ_FAILURE;
        }

        // Test display
        // Test Sphere
        //Sphere s0(GzVector3(0.0f, 0.0f, 10.0f), 2.0f);
        //GzCamera cam; // Test with default camera
        //for (int j = 0; j < m_nHeight; ++j)
        //{
            //for (int i = 0; i < m_nWidth; ++i)
            //{
                //int yj = j;
                //int xi = i;
                //float ndcx = xi * 2.0f / m_nWidth - 1;
                //float ndcy = -(yj * 2.0f / m_nHeight - 1);
                //GzRay rForPixel = cam.generateRay(ndcx, ndcy);
                //if (s0.intersect(rForPixel).p_geometry)
                //{
                    //m_pDisplay->putDisplay(xi, yj, (GzColor::BLUE + GzColor::RED) * 0.25);
                //}
            //}
        //}

        //*******************************
        //Sphere s0(GzVector3(0.0f, 0.0f, 10.0f), 2.0f);
        //GzMaterial mat(GzTexture(&GzTexture::checker_ptex_func), 15, 0.2f);
        //GzGeometry ** p_geos = new GzGeometry*[3];
        //p_geos[0] = new Sphere(GzVector3(5.2f, 5.0f, 0.0f), 5.0f, GzMaterial(GzColor(0.5f, 0.5f, 0.5f), 16.0f, 0.8f));
        //p_geos[1] = new Sphere(GzVector3(-5.2f, 5.0f, 0.0f), 5.0f, GzMaterial(GzColor(0.5f, 0.5f, 0.5f), 16.0f, 0.8f));
        //p_geos[2] = new Plane(GzVector3(0.0f, 1.0f, 0.0f), 0.0f, GzVector3(0.0f, 0.0f, 1.0f), mat);
        //GzMaterial mat(GzTexture(&GzTexture::checker_ptex_func), 0.4f);
		//GzMaterial mat2(GzTexture(&GzTexture::checker_ptex_func2), 0.4f);
        //GzGeometry ** p_geos = new GzGeometry*[3];
        //p_geos[0] = new Sphere(GzVector3(0.0f, 5.0f, 0.0f), 5.0f, GzMaterial(GzColor::RED, 16.0f, 1.1f, 0.05f, 0.95f));
        //p_geos[1] = new Plane(GzVector3(0.0f, 1.0f, 0.0f), 0.0f, GzVector3(0.0f, 0.0f, 1.0f), mat);
		//p_geos[2] = new Rec(GzVector3(-10.0f,1.0f,-10.0f), GzVector3(0,0,15), GzVector3(15, 0, 0), GzMaterial(GzColor::RED, 0));  // base, x dir , y dir
        const char* file = "tex_normal_golf.ppm";
        GzMaterial mat(GzTexture(&GzTexture::checker_ptex_func, 1), 0.2f);
        GzMaterial mat2(GzTexture(&GzTexture::checker_ptex_func, 5), 0.2f);
        GzMaterial mat_norm(GzColor::CYAN, GzTexture(file, &GzTexture::image_tex_func, 0), 16.0f, 1.12f, 0.5f, 0.0f);
        GzGeometry ** p_geos = new GzGeometry*[3];
        p_geos[0] = new Sphere(GzVector3(5.2f, 5.0f, 0.0f), 5.0f, mat_norm);
        p_geos[1] = new Sphere(GzVector3(-5.2f, 5.0f, 0.0f), 5.0f, GzMaterial(GzColor(0.5f, 0.5f, 0.5f), 16.0f, 1.12f, 0.5f, 0.5f));
        p_geos[2] = new Plane(GzVector3(0.0f, 1.0f, 0.0f), 0.0f, GzVector3(0.0f, 0.0f, 1.0f), mat);
        GzGeometry * p_unionGeometry = new Union(3, p_geos);
        //Sphere s0(GzVector3(0.0f, 0.0f, 10.0f), 5.0f);
        //p_s0->material = mat;
        //GzGeometry scene = constructScene(inFile);
        status = status || m_pRender->putScene(p_unionGeometry);
        status = status || m_pRender->renderToDisplay();
        //*******************************


        //GzFlushDisplay2File(outfile, m_pDisplay);  /* */
        //GzFlushDisplay2FrameBuffer(m_pFrameBuffer, m_pDisplay); // write out or update display to frame buffer
        m_pDisplay->flush2File(outfile); //write out or update display to file
        m_pDisplay->flush2FrameBuffer(m_pFrameBuffer); //write out or update display to frame buffer
        // 
        // Close file
        // 

        //if( fclose( infile ) )
            //AfxMessageBox( "The input file was not closed\n" );

        if( fclose( outfile ) )
        {
            AfxMessageBox(_T("The output file was not closed\n"));
        }
    }
    catch (GzException)
    {
        status = GZ_FAILURE;
    }
    if (status)
    {
        AfxMessageBox(_T("Rendering went wrong!\n"));
    }
    return(status); 
}

void ApplicationEngine::Clean()
{
    // Might need to clean renderer and texture and other objects
    delete m_pRender;
    m_pRender = nullptr;
    delete m_pDisplay;
    m_pDisplay = nullptr;
    //status |= GzFreeTexture();
}
