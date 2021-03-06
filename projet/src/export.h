//-----------------------------
#define NEXT_LINE fwrite("\n", 1, strlen("\n"), m_filePtr)

#define TAB_SPACE fwrite("\t", 1, strlen("\t"), m_filePtr)

#define ONE_SPACE fwrite(" ", 1, strlen(" "), m_filePtr)

#define BEGIN_BRACKET fwrite("{", 1, strlen("{"), m_filePtr)

#define CLOSE_BRACKET fwrite("}", 1, strlen("}"), m_filePtr)

#define OFFSET fwrite("OFFSET", 1, strlen("OFFSET"), m_filePtr)

#define JOINT fwrite("JOINT", 1, strlen("JOINT"), m_filePtr)

#define CHANNELS fwrite("CHANNELS", 1, strlen("CHANNELS"),

m_filePtr)

#define END_SITE fwrite("End Site", 1, strlen("END Site"),

m_filePtr)

//-----------------------------

// Hierarchy

//-----------------------------

enum Hierarchy

{

  root = 0,

  joint,

  childJoint

};

//-----------------------------

// BVH class

//-----------------------------

class BVH

{

 public:

  BVH();

  ~BVH();

  int CreateBVHFile(char* rootName, bool hasRotChannel, bool

		    hasPosChannel, float* offsetValues);

  int CloseBVHFile();

  void SetFileName(CString& fileName);

  void ExportToBvh();

 protected:

  //-- HIERARCHY

  int AddHierarchy();

  int CloseHierarchy();

  int AddJoint(const char* jointName, bool hasRotChannel, bool

	       hasPosChannel, float* offsetValues);

  int AddChildJoint(const char* childName, bool hasRotChannel,

		    bool hasPosChannel, float* offsetValues);

  int AddJointEndSite(float* offsetValues);

  int AddChildJointEndSite(float* offsetValues);

  int CloseJoint();

  int CloseChildJoint();

  //-- MOTION

  int AddMotionHeader(float frameTime);

  int AddMotionFrameData(int currFrame, char* floatValStr);

  int GetNumFrames();

  void SetNumFrames(int numFrames);

 private:

  int AddBody(const char* name, bool hasRotChannel, bool

	      hasPosChannel, float* offsetValues, Hierarchy hierarchy);

  int AddEndSite(float* offsetValues, Hierarchy hierarchy);

  FILE* m_filePtr;

  CString m_rootName;

  CString m_fileName;

  bool m_hasRotChannel;

  bool m_hasPosChannel;

  float* m_offsetValues;

  int m_numFrames;

};

