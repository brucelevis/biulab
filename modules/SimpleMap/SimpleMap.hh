#pragma once
#ifndef SIMPLE_MAP_H_
#define SIMPLE_MAP_H_

#include "BiuLabConfig.hh"
#include "BiuLabTypes.hh"
#include "MapBase.hh"
#include <string>
#include <vector>

using namespace std;

class SimpleMap : public MapBase {
  private:
    void Print(vec_2i pos);
    void CleanTarget();

  public:
    SimpleMap();
    SimpleMap(vec_2i map_size);
    ~SimpleMap();
    vec_2i size;
    int**  map;
    int**  target;
    int    rubbish_cnt;
    string map_name;
    string path_name;
    string version;

    void        Init();
    void        RandomMap();
    void        ClearMap();
    bool        InMap(vec_2i pos);
    void        UpdateSize(vec_2i new_size);
    void        LoadMap(const string& load_path);
    void        SaveMap(const string& save_path);
    int         GetHash(vec_2i pos);
    int         GetTarget(vec_2i pos);
    void        SetTarget(vec_2i pos, int key);
    int         GetElem(vec_2i pos);
    void        SetElem(vec_2i pos, int key);
    int         DoAction(vec_2i start, vec_2i offset);
    int         GetValue(vec_2i pos) { return target[pos.y][pos.x]; }
    inline int* operator[](int row);
};
#endif