/*****************************************************************************
 *                                                                            *
 *  OpenNI 1.x Alpha                                                          *
 *  Copyright (C) 2012 PrimeSense Ltd.                                        *
 *                                                                            *
 *  This file is part of OpenNI.                                              *
 *                                                                            *
 *  Licensed under the Apache License, Version 2.0 (the "License");           *
 *  you may not use this file except in compliance with the License.          *
 *  You may obtain a copy of the License at                                   *
 *                                                                            *
 *      http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                            *
 *  Unless required by applicable law or agreed to in writing, software       *
 *  distributed under the License is distributed on an "AS IS" BASIS,         *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *  See the License for the specific language governing permissions and       *
 *  limitations under the License.                                            *
 *                                                                            *
 *****************************************************************************/
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>
#include <XnPropNames.h>
#include <GL/glut.h>
#include "scene.h"
//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------

xn::Context g_Context;
xn::ScriptNode g_scriptNode;
xn::DepthGenerator g_DepthGenerator;
xn::UserGenerator g_UserGenerator;
xn::Player g_Player;

XnBool g_bNeedPose = FALSE;
XnChar g_strPose[20] = "";
XnBool g_bDrawBackground = TRUE;
XnBool g_bDrawPixels = TRUE;
XnBool g_bDrawSkeleton = TRUE;
XnBool g_bPrintID = TRUE;
XnBool g_bPrintState = TRUE;

XnBool g_bPrintFrameID = FALSE;
XnBool g_bMarkJoints = FALSE;

#define DEBUG 0
#define GL_WIN_SIZE_X 720
#define GL_WIN_SIZE_Y 480

XnBool g_bPause = false;
XnBool g_bRecord = false;

XnBool g_bQuit = false;

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------


// this function is called each frame
void glutDisplay (void)
{

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Setup the OpenGL viewpoint
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
#if DEBUG!=1
  xn::SceneMetaData sceneMD;
  xn::DepthMetaData depthMD;

  g_DepthGenerator.GetMetaData(depthMD);

  glOrtho(0, depthMD.XRes(), depthMD.YRes(), 0, -1.0, 1.0);

  if (!g_bPause){
      // Read next available data
      g_Context.WaitOneUpdateAll(g_UserGenerator);
    }

  // Process the data
  g_DepthGenerator.GetMetaData(depthMD);
  g_UserGenerator.GetUserPixels(0, sceneMD);
  DrawDepthMap(depthMD, sceneMD);

#else
  glOrtho(0, GL_WIN_SIZE_X , GL_WIN_SIZE_Y, 0, -1.0, 1.0);
#endif
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}


void glutIdle (void)
{
  if (g_bQuit) {
    CleanupExit();
  }

  // Display the frame
  glutPostRedisplay();
}

void glutKeyboard (unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
    {
    case 27:
      CleanupExit();
    case 'b':
      // Draw background?
      g_bDrawBackground = !g_bDrawBackground;
      break;
    case 'x':
      // Draw pixels at all?
      g_bDrawPixels = !g_bDrawPixels;
      break;
    case 's':
      // Draw Skeleton?
      g_bDrawSkeleton = !g_bDrawSkeleton;
      break;
    case 'i':
      // Print label?
      g_bPrintID = !g_bPrintID;
      break;
    case 'l':
      // Print ID & state as label, or only ID?
      g_bPrintState = !g_bPrintState;
      break;
    case 'f':
      // Print FrameID
      g_bPrintFrameID = !g_bPrintFrameID;
      break;
    case 'j':
      // Mark joints
      g_bMarkJoints = !g_bMarkJoints;
      break;
    case'p':
      g_bPause = !g_bPause;
      break;
    case 'S':
      SaveCalibration();
      break;
    case 'L':
      LoadCalibration();
      break;
    }
}
void glInit (int * pargc, char ** argv)
{
  glutInit(pargc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

  glutInitWindowPosition(100, 100);  

  glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
  glutCreateWindow ("User Tracker Viewer");
  //glutFullScreen();
  glutSetCursor(GLUT_CURSOR_NONE);

  glutKeyboardFunc(glutKeyboard);
  glutDisplayFunc(glutDisplay);
  glutIdleFunc(glutIdle);

  glClearColor (0.0f, 0.0f, 0.0f, 1.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);	
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix
  
  gluPerspective(45.0f,(GLfloat)GL_WIN_SIZE_X/(GLfloat)GL_WIN_SIZE_Y,0.1f,100.0f);
    
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glDisableClientState(GL_COLOR_ARRAY);
}




#define CHECK_RC(nRetVal, what)						\
  if (nRetVal != XN_STATUS_OK)						\
    {									\
      printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));	\
      return nRetVal;							\
    }



int main(int argc, char **argv)
{
  #if DEBUG == 0
  XnStatus nRetVal = XN_STATUS_OK;

  xn::EnumerationErrors errors;
  nRetVal = g_Context.InitFromXmlFile(SAMPLE_XML_PATH, g_scriptNode, &errors);
  if (nRetVal == XN_STATUS_NO_NODE_PRESENT){
    XnChar strError[1024];
    errors.ToString(strError, 1024);
    printf("%s\n", strError);
    return (nRetVal);
  }else if (nRetVal != XN_STATUS_OK){
    printf("Open failed: %s\n", xnGetStatusString(nRetVal));
    return (nRetVal);
  }
    

  nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
  if (nRetVal != XN_STATUS_OK){

    printf("No depth generator found. Using a default one...");
    xn::MockDepthGenerator mockDepth;

    nRetVal = mockDepth.Create(g_Context);
        CHECK_RC(nRetVal, "Create mock depth");

	
    // set some defaults
    XnMapOutputMode defaultMode;
    defaultMode.nXRes = 320;
    defaultMode.nYRes = 240;
    defaultMode.nFPS = 30;
    nRetVal = mockDepth.SetMapOutputMode(defaultMode);
    CHECK_RC(nRetVal, "set default mode");

    // set FOV
    XnFieldOfView fov;
    fov.fHFOV = 1.0225999419141749;
    fov.fVFOV = 0.79661567681716894;
    nRetVal = mockDepth.SetGeneralProperty(XN_PROP_FIELD_OF_VIEW, sizeof(fov), &fov);
    CHECK_RC(nRetVal, "set FOV");

    XnUInt32 nDataSize = defaultMode.nXRes * defaultMode.nYRes * sizeof(XnDepthPixel);
    XnDepthPixel* pData = (XnDepthPixel*)xnOSCallocAligned(nDataSize, 1, XN_DEFAULT_MEM_ALIGN);

    nRetVal = mockDepth.SetData(1, 0, nDataSize, pData);
    CHECK_RC(nRetVal, "set empty depth map");

    g_DepthGenerator = mockDepth;
  }

  nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
  if (nRetVal != XN_STATUS_OK){
    nRetVal = g_UserGenerator.Create(g_Context);
    CHECK_RC(nRetVal, "Find user generator");
  }

  XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected, hCalibrationInProgress, hPoseInProgress;
  if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON)){
    printf("Supplied user generator doesn't support skeleton\n");
    return 1;
  }
  nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
  CHECK_RC(nRetVal, "Register to user callbacks");
  nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart, NULL, hCalibrationStart);
  CHECK_RC(nRetVal, "Register to calibration start");
  nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(UserCalibration_CalibrationComplete, NULL, hCalibrationComplete);
  CHECK_RC(nRetVal, "Register to calibration complete");

  if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration()){
    g_bNeedPose = TRUE;
    if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION)){
      printf("Pose required, but not supported\n");
      return 1;
    }
    nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseDetected(UserPose_PoseDetected, NULL, hPoseDetected);
    CHECK_RC(nRetVal, "Register to Pose Detected");
    g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);

    nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseInProgress(MyPoseInProgress, NULL, hPoseInProgress);
    CHECK_RC(nRetVal, "Register to pose in progress");
  }

  g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

  nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationInProgress(MyCalibrationInProgress, NULL, hCalibrationInProgress);
  CHECK_RC(nRetVal, "Register to calibration in progress");

  nRetVal = g_Context.StartGeneratingAll();
  CHECK_RC(nRetVal, "StartGenerating");

#endif
  glInit(&argc, argv);
  glutMainLoop();
}
