#ifndef _JUMPING_LIKE_JOIN
#define _JUMPING_LIKE_JOIN

#include "../Util/Util.h"
#include "TempResult.h"

class JumpingLikeJoin
{
private:
  std::map<unsigned int, std::vector<unsigned int>> edgeTable;
  std::map<unsigned int, std::vector<unsigned int*>> subTable;
public:
  void initEdgeTable(TempResultSet *temp);
  void buildSubTable(TempResultSet *temp);
  TempResultSet* intersect(TempResultSet *temp1, TempResultSet *temp2);
};

#endif //_JUMPING_LIKE_JOIN