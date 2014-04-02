//#include "stdafx.h"

#include "export.h"

//---------------------------------------------------------------------

//BVH constructor

//---------------------------------------------------------------------

BVH::BVH()

{

  m_rootName = "";

  m_fileName = "";

  m_hasRotChannel = false;

  m_hasPosChannel = false;

  m_offsetValues = NULL;

  m_filePtr = NULL;

  m_numFrames = 0;

}

//----------------------------------------

//OnBvhBnClickedOk:

//----------------------------------------

void BVH::ExportToBvh()

{

  //-- create bvh file

  float rootOffsetValues[3] = {1.0f, 1.0f, 1.0f};

  CreateBVHFile("Neck", true, true, rootOffsetValues);

  //-- Add Hierarchy

  AddHierarchy();

  {

    AddJoint("Head", true, false, rootOffsetValues);

    AddJointEndSite(rootOffsetValues);

    {

      for (int i = 0; i < SOME_NUMBER_HERE; ++i)

	{

	  AddChildJoint(SOME_NAME_HERE, false, true,

			rootOffsetValues);

	  AddChildJointEndSite(rootOffsetValues);

	  CloseChildJoint();

	}

    }

    CloseJoint();

  }

  CloseHierarchy();

  //-- Add Motion data or frame data

  SetNumFrames(theApp.m_lastTrackedFrame);

  AddMotionHeader(0.040000f);

  char motionData[2096] = {0};

  for(int f = 1; f <= theApp.m_lastTrackedFrame; ++f)

    {

      //      motionData = one complete frame's motoin data here.

      AddMotionFrameData(f,motionData);

    }

  //-- close bvh file

  CloseBVHFile();

}

//---------------------------------------------------------------------

//Create: creates the bvh file

//---------------------------------------------------------------------

int BVH::CreateBVHFile(char* rootName, bool hasRotChannel, bool

		       hasPosChannel, float* offsetValues)

{

  m_rootName.SetString(rootName);

  m_hasRotChannel = hasRotChannel;

  m_hasPosChannel = hasPosChannel;

  m_offsetValues = offsetValues;

  m_filePtr = fopen(m_fileName.GetString(), FILE_FLAGS);

  if (m_filePtr)

    return 1;

  return 0;

}

//---------------------------------------------------------------------

//Create: creates the bvh file

//---------------------------------------------------------------------

int BVH::CloseBVHFile()

{

  if (m_filePtr)

    fclose(m_filePtr);

  m_filePtr = NULL;

  return 1;

}

//---------------------------------------------------------------------

//BVH estructor

//---------------------------------------------------------------------

BVH::~BVH

{

  if (m_filePtr)

    fclose(m_filePtr);

  m_filePtr = NULL;

}

//---------------------------------------------------------------------

//AddHierarchy: Adds the default hierarchy data into .bvh file

//---------------------------------------------------------------------

int BVH::AddHierarchy()

{

  if (!m_filePtr)

    return 0;

  //Header data

  fwrite("HIERARCHY", 1, strlen("HIERARCHY"), m_filePtr);

  NEXT_LINE;

  fwrite("ROOT", 1, strlen("ROOT"), m_filePtr);

  //body

  return AddBody(m_rootName.GetBuffer(), m_hasRotChannel,

		 m_hasPosChannel, m_offsetValues, root);

}

//---------------------------------------------------------------------

//CloseHierarchy: closes hierarchy

//---------------------------------------------------------------------

int BVH::CloseHierarchy()

{

  if (!m_filePtr)

    return 0;

  NEXT_LINE;

  CLOSE_BRACKET;

  NEXT_LINE;

  return 1;

}

//---------------------------------------------------------------------

//AddJoint: Adds the joint into the .bvh file

//---------------------------------------------------------------------

int BVH::AddJoint(const char* jointName, bool hasRotChannel, bool

		  hasPosChannel, float* offsetValues)

{

  if (!m_filePtr)

    return 0;

  //only one tab space

  TAB_SPACE;

  fwrite("JOINT", 1, strlen("JOINT"), m_filePtr);

  return AddBody(jointName, hasRotChannel, hasPosChannel,

		 offsetValues, joint);

}

//---------------------------------------------------------------------

//CloseJoint: closes the joint

//---------------------------------------------------------------------

int BVH::CloseJoint()

{

  if (!m_filePtr)

    return 0;

  TAB_SPACE;

  CLOSE_BRACKET;

  return 1;

}

//---------------------------------------------------------------------

//AddJoint: Adds the child joint into the .bvh file

//---------------------------------------------------------------------

int BVH::AddChildJoint(const char* childName, bool hasRotChannel, bool

		       hasPosChannel, float* offsetValues)

{

  if (!m_filePtr)

    return 0;

  //two tabs

  TAB_SPACE;

  TAB_SPACE;

  fwrite("JOINT", 1, strlen("JOINT"), m_filePtr);

  return AddBody(childName, hasRotChannel, hasPosChannel,

		 offsetValues, childJoint);

}

//----------------------------------------------------------------------

//CloseChildJoint: closes the child joint

//---------------------------------------------------------------------

int BVH::CloseChildJoint()

{

  if (!m_filePtr)

    return 0;

  TAB_SPACE;

  TAB_SPACE;

  CLOSE_BRACKET;

  NEXT_LINE;

  return 1;

}

//---------------------------------------------------------------------

//AddJointEndSite: Adds the "End Site" of the joint into .bvh file

//---------------------------------------------------------------------

int BVH::AddJointEndSite(float* offsetValues)

{

  TAB_SPACE;

  TAB_SPACE;

  return AddEndSite(offsetValues, joint);

}

//---------------------------------------------------------------------

//AddChildJointEndSite: Adds the "End Site" of the child joint into

.bvh file

 //---------------------------------------------------------------------

int BVH::AddChildJointEndSite(float* offsetValues)

{

  TAB_SPACE;

  TAB_SPACE;

  TAB_SPACE;

  return AddEndSite(offsetValues, childJoint);

}

//---------------------------------------------------------------------

//AddEndSite: Adds the "End Site" of the joint or child joint

//---------------------------------------------------------------------

int BVH::AddEndSite(float* offsetValues, Hierarchy hierarchy)

{

  char floatVal[32] = {0};

  END_SITE;

  NEXT_LINE;

  if (hierarchy == joint)

    {

      TAB_SPACE;

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  BEGIN_BRACKET;

  NEXT_LINE;

  if (hierarchy == joint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  OFFSET;

  TAB_SPACE;

  sprintf(floatVal,"%f",offsetValues[0]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  ONE_SPACE;

  sprintf(floatVal,"%f",offsetValues[0]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  ONE_SPACE;

  sprintf(floatVal,"%f",offsetValues[0]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  NEXT_LINE;

  if (hierarchy == joint)

    {

      TAB_SPACE;

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  CLOSE_BRACKET;

  NEXT_LINE;

  return 1;

}

//---------------------------------------------------------------------

//AddBody: Adds the body of the Root, Joint and child joint

//---------------------------------------------------------------------

int BVH::AddBody(const char* name, bool hasRotChannel, bool

		 hasPosChannel, float* offsetValues, Hierarchy hierarchy)

{

  char floatVal[32] = {0};

  if (!m_filePtr)

    return 0;

  ONE_SPACE;

  fwrite(name, 1, strlen(name), m_filePtr);

  NEXT_LINE;

  if (hierarchy == joint)

    {

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

    }

  BEGIN_BRACKET;

  NEXT_LINE;

  if (hierarchy == root)

    {

      TAB_SPACE;

    }

  else if (hierarchy == joint)

    {

      TAB_SPACE;

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  OFFSET;

  TAB_SPACE;

  sprintf(floatVal,"%f",offsetValues[0]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  sprintf(floatVal," %f",offsetValues[1]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  sprintf(floatVal," %f",offsetValues[2]);

  fwrite(floatVal, 1, strlen(floatVal), m_filePtr);

  NEXT_LINE;

  if (hierarchy == root)

    {

      TAB_SPACE;

    }

  else if (hierarchy == joint)

    {

      TAB_SPACE;

      TAB_SPACE;

    }

  else if (hierarchy == childJoint)

    {

      TAB_SPACE;

      TAB_SPACE;

      TAB_SPACE;

    }

  //channel data

  CHANNELS;

  ONE_SPACE;

  if (hasRotChannel & hasPosChannel)

    {

      fwrite("6 Xposition Yposition Zposition Zrotation

Xrotation Yrotation",

	     1, strlen("6 Xposition Yposition Zposition

Zrotation Xrotation Yrotation"), m_filePtr);

    }

  else if(hasRotChannel)

    {

      fwrite("3 Zrotation Xrotation Yrotation",

	     1, strlen("3 Zrotation Xrotation Yrotation"),

	     m_filePtr);

    }

  else if(hasPosChannel)

    {

      fwrite("3 Xposition Yposition Zposition",

	     1, strlen("3 Xposition Yposition Zposition"),

	     m_filePtr);

    }

  NEXT_LINE;

  return 1;

}

//---------------------------------------------------------------------

//SetNumFrames: Sets the number frames into the .bvh file

//---------------------------------------------------------------------

void BVH::SetFileName(CString& fileName)

{

  m_fileName = fileName;

}

//---------------------------------------------------------------------

//SetNumFrames: Sets the number frames into the .bvh file

//---------------------------------------------------------------------

void BVH::SetNumFrames(int numFrames)

{

  m_numFrames = numFrames;

}

//---------------------------------------------------------------------

//GetNumFrames: returns the number of frames in a .bvh file

//---------------------------------------------------------------------

int BVH::GetNumFrames()

{

  return m_numFrames;

}

//---------------------------------------------------------------------

//AddMotionHeader: Adds the minimum default motion data into .bvh

file

//---------------------------------------------------------------------

int BVH::AddMotionHeader(float frameTime)

{

  char frameStr[32] = {0};

  fwrite("MOTION", 1, strlen("MOTION"), m_filePtr);

  NEXT_LINE;

  fwrite("Frames:", 1, strlen("Frames:"), m_filePtr);

  TAB_SPACE;

  sprintf(frameStr, "%d", m_numFrames);

  fwrite(frameStr, 1, strlen(frameStr), m_filePtr);

  NEXT_LINE;

  fwrite("Frame Time:", 1, strlen("Frame Time:"), m_filePtr);

  ONE_SPACE;

  sprintf(frameStr, "%f", frameTime);

  fwrite(frameStr, 1, strlen(frameStr), m_filePtr);

  NEXT_LINE;

  return 1;

}

//---------------------------------------------------------------------

//AddMotionFrameData: Adds the motion data or frame data into .bvh

file

//---------------------------------------------------------------------

int BVH::AddMotionFrameData(int currFrame, char* floatValStr)

{

  if (currFrame > m_numFrames)

    return 0;

  fwrite(floatValStr, 1, strlen(floatValStr), m_filePtr);

  NEXT_LINE;

  return 1;

}
