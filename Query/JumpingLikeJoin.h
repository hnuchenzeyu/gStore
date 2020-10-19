#ifndef _JUMPING_LIKE_JOIN
#define _JUMPING_LIKE_JOIN

#include "../KVstore/KVstore.h"
#include "../Util/Util.h"
#include "TempResult.h"

class JumpingLikeJoin
{
private:
  KVstore* kvstore;

  map<unsigned, unsigned> sub2pos; // 记录subID第一次出现的位置
  unsigned* sub_obj_list;
  unsigned sub_obj_list_size;

  std::map<unsigned int, std::vector<unsigned int>> edgeTable;
  std::map<unsigned int, std::vector<unsigned int*>> subTable;
public:
  JumpingLikeJoin(){}
  JumpingLikeJoin(KVstore* _kvstore):kvstore(_kvstore){}

  TYPE_PREDICATE_ID getPreID(std::string pre);
  void initSubObjListMap(TYPE_PREDICATE_ID preID);
  void buildSubTable(TempResultSet *temp);
  TempResultSet* intersect();
  TempResultSet* intersect(TempResultSet *temp1, TempResultSet *temp2);
};

#endif //_JUMPING_LIKE_JOIN