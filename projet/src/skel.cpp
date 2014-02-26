#include "skel.h"


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


Joint::Joint(XnSkeletonJoint id, XnSkeletonJoint fatherId,  const math::Mat4f& m):id(id),fatherId(fatherId), local2world(m){}

Skeleton::Skeleton(XnUserID _id):id(_id) {
  joints.resize(24);//Nite donen un squelette de 24 jointures.
  addJoint(XN_SKEL_HEAD,XN_SKEL_HEAD);//root TODO : prendre une jointure vers le centre
  addJoint(XN_SKEL_NECK,XN_SKEL_HEAD);
  addJoint(XN_SKEL_TORSO,XN_SKEL_NECK);
  addJoint(XN_SKEL_WAIST,XN_SKEL_TORSO);

  addJoint(XN_SKEL_LEFT_COLLAR,XN_SKEL_NECK);
  addJoint(XN_SKEL_LEFT_SHOULDER,XN_SKEL_LEFT_COLLAR);
  addJoint(XN_SKEL_LEFT_ELBOW,XN_SKEL_LEFT_SHOULDER);
  addJoint(XN_SKEL_LEFT_WRIST,XN_SKEL_LEFT_ELBOW);
  addJoint(XN_SKEL_LEFT_HAND,XN_SKEL_LEFT_WRIST);
  addJoint(XN_SKEL_LEFT_FINGERTIP,XN_SKEL_LEFT_HAND);

  addJoint(XN_SKEL_RIGHT_COLLAR,XN_SKEL_NECK);
  addJoint(XN_SKEL_RIGHT_SHOULDER,XN_SKEL_RIGHT_COLLAR);
  addJoint(XN_SKEL_RIGHT_ELBOW,XN_SKEL_RIGHT_SHOULDER);
  addJoint(XN_SKEL_RIGHT_WRIST,XN_SKEL_RIGHT_ELBOW);
  addJoint(XN_SKEL_RIGHT_HAND,XN_SKEL_RIGHT_WRIST);
  addJoint(XN_SKEL_RIGHT_FINGERTIP,XN_SKEL_RIGHT_HAND);

  addJoint(XN_SKEL_LEFT_HIP,XN_SKEL_WAIST);
  addJoint(XN_SKEL_LEFT_KNEE,XN_SKEL_LEFT_HIP);
  addJoint(XN_SKEL_LEFT_ANKLE,XN_SKEL_LEFT_KNEE);
  addJoint(XN_SKEL_LEFT_FOOT,XN_SKEL_LEFT_ANKLE);

  addJoint(XN_SKEL_RIGHT_HIP,XN_SKEL_WAIST);
  addJoint(XN_SKEL_RIGHT_KNEE,XN_SKEL_RIGHT_HIP);
  addJoint(XN_SKEL_RIGHT_ANKLE,XN_SKEL_RIGHT_KNEE);
  addJoint(XN_SKEL_RIGHT_FOOT,XN_SKEL_RIGHT_ANKLE);

}

void Skeleton::addJoint( const XnSkeletonJoint& eJoint, const XnSkeletonJoint& eJoint_Parent){
  if (!g_UserGenerator.GetSkeletonCap().IsTracking(id))	{
    printf("not tracked!\n");
    return;
  }
  if (!g_UserGenerator.GetSkeletonCap().IsJointActive(eJoint))
    return;

  XnSkeletonJointPosition joint;
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(id, eJoint, joint);

  if (joint.fConfidence < 0.5) //sans doute le seuil pour affichage ou non ? à voir
    return;
  
  XnPoint3D pt;
  pt = joint.position;
  
  

  math::Vec3f p(pt.X,pt.Y,pt.Z);
  math::Mat4f m(p);
  
  Joint j(eJoint,eJoint_Parent,m);
  joints[eJoint-1] = j;
}

void Skeleton::initMatrix(){
  for(unsigned int i = 0; i<joints.size();i++){
    if(joints[i].id != joints[i].fatherId){//ne pas transformer root
      //multiplication avec la matrice du parent
      joints[i].local2world *= joints[joints[i].fatherId-1].local2world;
    }
  }
}

float Skeleton::distance(const Skeleton& s) const{
 float result = 0;
 if(joints.size()==s.joints.size()){
   //on suppose que le joint 0 est toujours root.
   for(unsigned int i = 1; i<joints.size();i++){
     math::Vec3f p1 = joints[i].local2world.getTranslation() ;
     math::Vec3f p2 = s.joints[i].local2world.getTranslation() ;
     result += sqrtf((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
   }
 }
 return result;
}

