#ifndef SKELETON_H
#define SKELETON_H
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
#include <cmath>
#include <map>
#include <vector>
#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Quaternion.h"

class Skeleton;

class Joint{
  friend Skeleton;
 public:
  Joint(){}
  Joint(XnSkeletonJoint ,XnSkeletonJoint, const math::Mat4f& );
  ~Joint(){}
 private: 
  XnSkeletonJoint id;
  XnSkeletonJoint fatherId;
  math::Mat4f local2world;
  bool isVisible;
};


class Skeleton{
 public:
  //! Créer un squelette ayant la même structure que définit dans le BVH
  Skeleton(XnUserID );


  float distance(const Skeleton& ) const;

 private:
  void addJoint(const XnSkeletonJoint&,const XnSkeletonJoint&);
  void initMatrix();
  std::vector<Joint> joints;
  XnUserID id;
};



#endif
