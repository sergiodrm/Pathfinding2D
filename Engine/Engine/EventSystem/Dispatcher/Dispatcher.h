#pragma once


#include <functional>
#include <utility>
#include <vector>
#include "Engine/MacroObject.h"

#pragma warning(push)
#pragma warning(disable: 4251)


template <typename ...Args>
class ENGINE_API Dispatcher
{
public:

  Dispatcher() {}

  template <typename T, void(T::*Method)(Args...)>
  void Bind(void* _pInstance)
  {
    Callback callback = std::make_pair(_pInstance, &Invoke<T, Method>);
    m_bindedCallbacks.push_back(callback);
  }

  void Broadcast(Args... _args)
  {
    for (Callback& iterator : m_bindedCallbacks)
    {
      (iterator.second)(iterator.first, _args...);
    }
  }

#define BindMethod(_Class, _Instance, _Method) Bind<_Class, _Method>(_Instance)

private:

  template <typename T, void(T::*Method)(Args...)>
  static void Invoke(void* _pInstance, Args... _args)
  {
    (static_cast<T*>(_pInstance)->*Method)(_args...);
  }

  typedef void(*FunctionType)(void*, Args...);
  typedef std::pair<void*, FunctionType> Callback;
  std::vector<Callback> m_bindedCallbacks;

};

#pragma warning(pop)