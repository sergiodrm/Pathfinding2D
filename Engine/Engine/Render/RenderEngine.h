#pragma once

#include "../Utilities/SingletonBase.h"


class CRenderEngine : public ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine)

public:

  static void Init();
  static CRenderEngine& Get();
  void Terminate();

};

