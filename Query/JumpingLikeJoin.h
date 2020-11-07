#ifndef _JUMPING_LIKE_JOIN
#define _JUMPING_LIKE_JOIN

#include "../Util/Util.h"
#include "TempResult.h"

class JumpingLikeJoin
{
private:
  KVstore* kvstore;

  //use array
  unsigned* sub_obj_list;
  unsigned sub_obj_list_size;
  map<unsigned, unsigned> sub2posOfEdgeOne;
  map<unsigned, unsigned> sub2posOfEgdeJoined;


  //based on map.
  std::map<unsigned int, std::vector<unsigned int> > edgeTable;
  std::map<unsigned int, std::vector<unsigned int*> > subTable;
public:

  JumpingLikeJoin(KVstore* _kvstore):kvstore(_kvstore)
  {}

  TYPE_PREDICATE_ID getPreID(std::string pre);

  //function based on array.
  void initSub2Pos(TYPE_PREDICATE_ID preid);
  void buildSubTableUsedArray(TempResultSet *temp);
  TempResultSet* intersectUsedArray(TempResultSet *temp);

  // functions based on map.
  void initEdgeTable(TYPE_PREDICATE_ID preid);
  void buildSubTable(TempResultSet *temp);
  TempResultSet* intersect(TempResultSet *temp2); // TempResultSet *temp1 is removed
  TempResultSet* intersect(TempResultSet* temp1, TempResultSet* temp2);
};

#endif //_JUMPING_LIKE_JOIN