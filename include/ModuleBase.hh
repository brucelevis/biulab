#pragma once
#ifndef MODULES_BASE_H_
#define MODULES_BASE_H_

#include "BiuLabConfig.hh"
#include "DataManager.hh"
#include <iostream>

class ModuleBase {
  public:
    DataManager* data_manager;

    ModuleBase() {}

    ~ModuleBase() {}

    void SetEnvironment(DataManager* data_manager_) {
        data_manager = data_manager_;
    }

    void Init();

    virtual void UpdateModule() = 0;
};

#endif