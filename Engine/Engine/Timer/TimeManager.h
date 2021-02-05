#pragma once

#include "Engine/CoreUtilities/SingletonBase.h"
#include "Engine/MacroObject.h"

class ENGINE_API CTimeManager : public ISingletonBase<CTimeManager>
{
  DECLARE_SINGLETON_CLASS(CTimeManager);

public:

  static void Init();
  static CTimeManager& GetInstance();
  static void Shutdown();

  void StartTimer();
  double StopTimer();

private:

  double m_fixedTick;
  double m_previousTime;
  double m_elapsedTime;
  double m_timer;
};

