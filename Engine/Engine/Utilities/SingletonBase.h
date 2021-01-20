#pragma once

#include <assert.h>

#define DECLARE_SINGLETON_CLASS(_CLASS) \
private:\
friend ISingletonBase<_CLASS>; \
_CLASS() {} \
_CLASS(const _CLASS&) = delete; \
void operator=(const _CLASS&) = delete; 

template <typename T>
class ISingletonBase
{
private:

  static T* m_pInstance;

protected:

  static void CreateSingleton()
  {
    assert(m_pInstance == nullptr)
    m_pInstance = new T();
  }

  static T& GetSingleton()
  {
    assert(m_pInstance != nullptr);
    return m_pInstance;
  }

  static void DestroySingleton()
  {
    assert(m_pInstance != nullptr);
    delete m_pInstance;
    m_pInstance = nullptr;
  }

};

template <typename T>
T* ISingletonBase<T>::m_pInstance = nullptr;
