#pragma once
#include <MinHook.h>
#include <vector>

namespace nfsu2::hook {
class IHook {
  public:
    virtual ~IHook() = default;
    virtual bool Install() = 0;
    virtual bool Remove() = 0;
    virtual const char *Name() const = 0;
};

class HookManager {
  public:
    static HookManager &Instance() {
        static HookManager instance;
        return instance;
    }

    void Register(IHook *hook) { m_hooks.push_back(hook); }

    bool InstallAll() {
        if (MH_Initialize() != MH_OK)
            return false;
        bool ok = true;
        for (auto *h : m_hooks) {
            if (!h->Install()) {
                ok = false;
            }
        }
        return ok;
    }

    void RemoveAll() {
        for (auto *h : m_hooks)
            h->Remove();
        MH_Uninitialize();
    }

  private:
    HookManager() = default;
    std::vector<IHook *> m_hooks;
};

template <typename Signature> class FunctionHook;

template <typename Ret, typename... Args>
class FunctionHook<Ret(__cdecl *)(Args...)> : public IHook {
  public:
    using Fn = Ret(__cdecl *)(Args...);

    FunctionHook(const char *name, uintptr_t address, Fn detour)
        : m_name(name), m_address(address), m_detour(detour) {
        HookManager::Instance().Register(this);
    }

    bool Install() override {
        void *target = reinterpret_cast<void *>(m_address);
        if (MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original)) != MH_OK)
            return false;
        return MH_EnableHook(target) == MH_OK;
    }

    bool Remove() override {
        void *target = reinterpret_cast<void *>(m_address);
        MH_DisableHook(target);
        return MH_RemoveHook(target) == MH_OK;
    }

    const char *Name() const override { return m_name; }
    Ret CallOriginal(Args... args) const { return m_original(args...); }

  private:
    const char *m_name;
    uintptr_t m_address;
    Fn m_detour;
    Fn m_original = nullptr;
};

template <typename Ret, typename... Args>
class FunctionHook<Ret(__stdcall *)(Args...)> : public IHook {
  public:
    using Fn = Ret(__stdcall *)(Args...);
    FunctionHook(const char *name, uintptr_t address, Fn detour)
        : m_name(name), m_address(address), m_detour(detour) {
        HookManager::Instance().Register(this);
    }
    bool Install() override {
        void *target = reinterpret_cast<void *>(m_address);
        if (MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original)) != MH_OK)
            return false;
        return MH_EnableHook(target) == MH_OK;
    }
    bool Remove() override {
        void *target = reinterpret_cast<void *>(m_address);
        MH_DisableHook(target);
        return MH_RemoveHook(target) == MH_OK;
    }
    const char *Name() const override { return m_name; }
    Ret CallOriginal(Args... args) const { return m_original(args...); }

  private:
    const char *m_name;
    uintptr_t m_address;
    Fn m_detour;
    Fn m_original = nullptr;
};

template <typename Ret, typename... Args>
class FunctionHook<Ret(__thiscall *)(Args...)> : public IHook {
  public:
    using Fn = Ret(__thiscall *)(Args...);
    FunctionHook(const char *name, uintptr_t address, Fn detour)
        : m_name(name), m_address(address), m_detour(detour) {
        HookManager::Instance().Register(this);
    }
    bool Install() override {
        void *target = reinterpret_cast<void *>(m_address);
        if (MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original)) != MH_OK)
            return false;
        return MH_EnableHook(target) == MH_OK;
    }
    bool Remove() override {
        void *target = reinterpret_cast<void *>(m_address);
        MH_DisableHook(target);
        return MH_RemoveHook(target) == MH_OK;
    }
    const char *Name() const override { return m_name; }
    Ret CallOriginal(Args... args) const { return m_original(args...); }

  private:
    const char *m_name;
    uintptr_t m_address;
    Fn m_detour;
    Fn m_original = nullptr;
};
} // namespace nfsu2::hook
