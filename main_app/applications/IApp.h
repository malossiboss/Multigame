#pragma once

#include <string>

class IApp
{
private:

    std::string m_strAppName = "IApp";

public:

    virtual ~IApp() {}

    virtual bool Init() = 0;
    virtual bool Deinit();
    virtual bool HandleEvent();
    virtual const std::string& GetAppName();
    virtual void OnEnter();
    virtual void OnExit();
    virtual void OnDraw();
};
