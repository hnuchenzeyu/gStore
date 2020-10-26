#ifndef _JUMPING_LIKE_JOIN
#define _JUMPING_LIKE_JOIN

#include "../Util/Util.h"
#include "TempResult.h"

class JumpingLikeJoin
{
private:
  KVstore* kvstore;
  std::map<unsigned int, std::vector<unsigned int> > edgeTable;
  std::map<unsigned int, std::vector<unsigned int*> > subTable;
public:

  JumpingLikeJoin(KVstore* _kvstore):kvstore(_kvstore)
  {}

  TYPE_PREDICATE_ID getPreID(std::string pre);
  void initEdgeTable(TYPE_PREDICATE_ID preid);
  void buildSubTable(TempResultSet *temp);
  TempResultSet* intersect(TempResultSet *temp2); // TempResultSet *temp1 is removed
};

#endif //_JUMPING_LIKE_JOIN