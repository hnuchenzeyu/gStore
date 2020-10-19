#include "JumpingLikeJoin.h"

using namespace std;

TYPE_PREDICATE_ID JumpingLikeJoin::getPreID(String pre)
{
  return this->kvstore->getIDByPredicate(pre);
}

void JumpingLikeJoin::initSubObjListMap(TYPE_PREDICATE_ID preID)
{
  this->kvstore->getsubIDobjIDlistBypreID(preID, this->sub_obj_list, this->sub_obj_list_size);
  this->sub2pos[this->sub_obj_list[0]] = 0;

  unsigned prevID = this->sub_obj_list[0];
  for (int i = 2; i < this->sub_obj_list_size; i+=2)
  {
    if (this->sub_obj_list[i] == prevID)
      continue;
    
    this->sub2pos[this->sub_obj_list[i]] = i;
    prevID = this->sub_obj_list[i];
  }
}

void JumpingLikeJoin::buildSubTable(TempResultSet *temp)
{
  this->subTable.clear();
  for (int i = 0; i < temp->results[0].result.size(); i++)
  {
    if(this->subTable.find(temp->results[0].result[i].id[0]) == this->subTable.end())
      this->subTable[temp->results[0].result[i].id[0]] = vector<unsigned int*>();
    this->subTable[temp->results[0].result[i].id[0]].push_back(temp->results[0].result[i].id);
  }
}

TempResultSet* JumpingLikeJoin::intersect(TempResultSet *temp1, TempResultSet *temp2)
{
  int temp1_id_num = temp1->results[0].id_varset.getVarsetSize();
  int temp2_id_num = temp2->results[0].id_varset.getVarsetSize();
  
  TempResultSet *res = new TempResultSet();
  res->results.push_back(TempResult());

  // for (int i = 0; i < temp1_id_num + temp2_id_num; i++)
  // {
  //   stringstream ss;
  //   string var = "?x";
  //   ss<<var<<(i+1);
  //   ss>>var;
  //   res->results[0].id_varset.addVar(var);
  // }
  res->results[0].id_varset.addVar(temp1->results[0].id_varset.vars[0]);
  res->results[0].id_varset.addVar(temp2->results[0].id_varset.vars.back());

  // 得到左边结果的id下标
  int obj_index = temp1_id_num - 1;
  for(int i = 0; i < temp1->results[0].result.size(); i++)
  {
    unsigned int* left_ids = temp1->results[0].result[i].id;
    if(this->edgeTable.find(left_ids[obj_index]) != this->edgeTable.end())
    {
      // 得到以连接的id为主语的宾语集合
      const vector<unsigned int> &objects = this->edgeTable[left_ids[obj_index]];
      for (int j = 0; j < objects.size(); j++)
      {
        // 宾语对应连接右边集的主语
        if(this->subTable.find(objects[j]) != this->subTable.end())
        {
          vector<unsigned int*>& subid = this->subTable[objects[j]];
          for (int l = 0; l < subid.size(); l++)
          {
            res->results[0].result.push_back(TempResult::ResultPair());
            // unsigned int* res_id = new unsigned int[temp1_id_num + temp2_id_num];
            unsigned int* res_id = new unsigned int[2];
            // for(int k = 0; k < temp1_id_num; k++)
            //   res_id[k] = left_ids[k];
            res_id[0] = left_ids[0];
            
            res_id[1] = subid[l][temp2_id_num - 1];
            // for(int m = temp1_id_num + 1; m < temp1_id_num + temp2_id_num; m++)
            // {
            //   res_id[m] = subid[l][m - temp1_id_num];
            // }
            res->results[0].result.back().id = res_id;
          }
        }
      }
    }
  }
  return res;
}
