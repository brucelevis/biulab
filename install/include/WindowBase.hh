#pragma once
#ifndef WINDOW_BASE_H_
#define WINDOW_BASE_H_

#include "WidgetBase.hh"

class WindowBase : public WidgetBase {
   public:
    WindowBase() {}

    ~WindowBase() {}

    virtual void show() = 0;
};

#endif