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
#include "scene.h"


extern xn::Context g_Context;
extern xn::UserGenerator g_UserGenerator;
extern xn::DepthGenerator g_DepthGenerator;
extern xn::ScriptNode g_scriptNode;
extern xn::Player g_Player;

extern XnBool g_bNeedPose;
extern XnBool g_bDrawBackground;
extern XnBool g_bDrawPixels;
extern XnBool g_bDrawSkeleton;
extern XnBool g_bPrintID;
extern XnBool g_bPrintState;
extern XnChar g_strPose[20];

extern XnBool g_bPrintFrameID;
extern XnBool g_bMarkJoints;

std::map<XnUserID, Skeleton> m_skeleton;

std::map<XnUInt32, std::pair<XnCalibrationStatus, XnPoseDetectionStatus> > m_Errors;

/*
TODO : 
ajouter un conteneur permettant de stocker les poses précédentes des squelettes
 */


void CleanupExit(){
  g_scriptNode.Release();
  g_DepthGenerator.Release();
  g_UserGenerator.Release();
  g_Player.Release();
  g_Context.Release();

  exit (1);
}

// Callback: New user was detected
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/){
  XnUInt32 epochTime = 0;
  xnOSGetEpochTime(&epochTime);
  printf("%d New User %d\n", epochTime, nId);
  // New user found
  if (g_bNeedPose)    
    g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
  else
    g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
  
  // ICI ajout de l'utilisateur
  Skeleton s(nId);
  m_skeleton.insert(std::pair<XnUserID, Skeleton>(nId,s));
}
// Callback: An existing user was lost
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/){
  //TODO : soit suppression de l'utilisateur de la map, soit archivage. Les poses du squelette archivées ne doivent pas être supprimées car on peut les réutiliser.

  XnUInt32 epochTime = 0;
  xnOSGetEpochTime(&epochTime);
  printf("%d Lost user %d\n", epochTime, nId);	
}
// Callback: Detected a pose
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/){
  //TODO : archivage du squelette, puis mise à jours du squelette.
  // Si la distance est trop éloignée, reprendre le squelette précédent (peut être faire une transition entre les deux ?)
  // possibilité de détecter la pose courante et voir si elle n'a pas déjà été enregistrée (à un delta près), probablement il faut revoir la fonction distance du squelette
  // si on perd le personnage mais qu'on en trouve un nouveau dans une pose connue, on peu essayer de faire une transition.

  XnUInt32 epochTime = 0;
  xnOSGetEpochTime(&epochTime);
  printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
  g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
  g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);

  
}
// Callback: Started calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/){
  XnUInt32 epochTime = 0;
  xnOSGetEpochTime(&epochTime);
  printf("%d Calibration started for user %d\n", epochTime, nId);
}
// Callback: Finished calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/){
  XnUInt32 epochTime = 0;
  xnOSGetEpochTime(&epochTime);
  if (eStatus == XN_CALIBRATION_STATUS_OK){
      // Calibration succeeded
      printf("%d Calibration complete, start tracking user %d\n", epochTime, nId);		
      g_UserGenerator.GetSkeletonCap().StartTracking(nId);
    }else{
      // Calibration failed
      printf("%d Calibration failed for user %d\n", epochTime, nId);
      if(eStatus==XN_CALIBRATION_STATUS_MANUAL_ABORT){
	  printf("Manual abort occured, stop attempting to calibrate!");
	  return;
        }
      if (g_bNeedPose)
	  g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
      else
	  g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
    }
}



// Save calibration to file
void SaveCalibration(){
  XnUserID aUserIDs[20] = {0};
  XnUInt16 nUsers = 20;
  g_UserGenerator.GetUsers(aUserIDs, nUsers);
  for (int i = 0; i < nUsers; ++i){
      // Find a user who is already calibrated
    if (g_UserGenerator.GetSkeletonCap().IsCalibrated(aUserIDs[i])){
	  // Save user's calibration to file
	  g_UserGenerator.GetSkeletonCap().SaveCalibrationDataToFile(aUserIDs[i], XN_CALIBRATION_FILE_NAME);
	  break;
	}
    }
}
// Load calibration from file
void LoadCalibration(){
  XnUserID aUserIDs[20] = {0};
  XnUInt16 nUsers = 20;
  g_UserGenerator.GetUsers(aUserIDs, nUsers);
  for (int i = 0; i < nUsers; ++i){
      // Find a user who isn't calibrated or currently in pose
      if (g_UserGenerator.GetSkeletonCap().IsCalibrated(aUserIDs[i])) continue;
      if (g_UserGenerator.GetSkeletonCap().IsCalibrating(aUserIDs[i])) continue;

      // Load user's calibration from file
      XnStatus rc = g_UserGenerator.GetSkeletonCap().LoadCalibrationDataFromFile(aUserIDs[i], XN_CALIBRATION_FILE_NAME);
      if (rc == XN_STATUS_OK){
	  // Make sure state is coherent
	  g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(aUserIDs[i]);
	  g_UserGenerator.GetSkeletonCap().StartTracking(aUserIDs[i]);
	}
      break;
    }
}

void XN_CALLBACK_TYPE MyCalibrationInProgress(xn::SkeletonCapability& /*capability*/, XnUserID id, XnCalibrationStatus calibrationError, void* /*pCookie*/){
  m_Errors[id].first = calibrationError;
}
void XN_CALLBACK_TYPE MyPoseInProgress(xn::PoseDetectionCapability& /*capability*/, const XnChar* /*strPose*/, XnUserID id, XnPoseDetectionStatus poseError, void* /*pCookie*/){
  m_Errors[id].second = poseError;
}

unsigned int getClosestPowerOfTwo(unsigned int n){
  unsigned int m = 2;
  while(m < n) m<<=1;

  return m;
}

void DrawJoint(XnUserID player, XnSkeletonJoint eJoint){
  if (!g_UserGenerator.GetSkeletonCap().IsTracking(player))	{
    printf("not tracked!\n");
    return;
  }

  if (!g_UserGenerator.GetSkeletonCap().IsJointActive(eJoint))
    return;

  XnSkeletonJointPosition joint;
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, eJoint, joint);

  if (joint.fConfidence < 0.5)
    return;

  XnPoint3D pt;
  pt = joint.position;

  glVertex3f(pt.X, pt.Y, pt.Z);
	
}

void DrawDepthMap(const xn::DepthMetaData& dmd, const xn::SceneMetaData& smd)
{
 	
  char strLabel[50] = "";
  XnUserID aUsers[15];
  XnUInt16 nUsers = 15;

  glBegin(GL_POINT);

  g_UserGenerator.GetUsers(aUsers, nUsers);
  for (int i = 0; i < nUsers; ++i)
    {
      if (g_bDrawSkeleton && g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])){
	
	DrawJoint(aUsers[i], XN_SKEL_HEAD);
	DrawJoint(aUsers[i], XN_SKEL_NECK);
	DrawJoint(aUsers[i], XN_SKEL_TORSO);
	DrawJoint(aUsers[i], XN_SKEL_WAIST);

	DrawJoint(aUsers[i], XN_SKEL_LEFT_COLLAR);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_SHOULDER);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_ELBOW);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_WRIST);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_HAND);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_FINGERTIP);

	DrawJoint(aUsers[i], XN_SKEL_RIGHT_COLLAR);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_SHOULDER);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_ELBOW);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_WRIST);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_HAND);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_FINGERTIP);

	DrawJoint(aUsers[i], XN_SKEL_LEFT_HIP);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_KNEE);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_ANKLE);
	DrawJoint(aUsers[i], XN_SKEL_LEFT_FOOT);

	DrawJoint(aUsers[i], XN_SKEL_RIGHT_HIP);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_KNEE);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_ANKLE);
	DrawJoint(aUsers[i], XN_SKEL_RIGHT_FOOT);



      }
    }

  glEnd();

}
