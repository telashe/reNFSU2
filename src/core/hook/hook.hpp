#pragma once
#include "core/utils/logger.hpp"
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
        LOG_INFO("Initializing hooks...");
        MH_STATUS status = MH_Initialize();
        if (status != MH_OK) {
            LOG_ERROR("[HookManager] Failed to initialize MinHook! Error: %s",
                      MH_StatusToString(status));
            return false;
        }

        LOG_INFO("Installing %zu hooks...", m_hooks.size());

        bool ok = true;
        int successCount = 0;

        for (auto *h : m_hooks) {
            if (!h->Install()) {
                LOG_ERROR("Hook installation aborted due to failure in: %s",
                          h->Name());
                ok = false;
            } else {
                successCount++;
            }
        }

        if (ok) {
            LOG_INFO("Succesfully installed all %d hooks.", successCount);
        } else {
            LOG_ERROR(
                "Hook installation finished with errors. (%d/%zu successful)",
                successCount, m_hooks.size());
        }

        return ok;
    }

    void RemoveAll() {
        LOG_INFO("Removing all hooks...");
        for (auto *h : m_hooks)
            h->Remove();

        MH_STATUS status = MH_Uninitialize();
        if (status == MH_OK) {
            LOG_INFO("MinHook uninitialized successfully.");
        } else {
            LOG_ERROR("Failed to uninitialize MinHook! Error: %s",
                      MH_StatusToString(status));
        }
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

        MH_STATUS createStatus =
            MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original));

        if (createStatus != MH_OK) {
            LOG_ERROR("[%s] MH_CreateHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(createStatus));
            return false;
        }

        MH_STATUS enableStatus = MH_EnableHook(target);
        if (enableStatus != MH_OK) {
            LOG_ERROR("[%s] MH_EnableHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(enableStatus));
            return false;
        }

        LOG_INFO("[%s] Installed successfully at 0x%zX", m_name, m_address);
        return true;
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

        MH_STATUS createStatus =
            MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original));

        if (createStatus != MH_OK) {
            LOG_ERROR("[%s] MH_CreateHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(createStatus));
            return false;
        }

        MH_STATUS enableStatus = MH_EnableHook(target);
        if (enableStatus != MH_OK) {
            LOG_ERROR("[%s] MH_EnableHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(enableStatus));
            return false;
        }

        LOG_INFO("[%s] Installed successfully at 0x%zX", m_name, m_address);
        return true;
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

        MH_STATUS createStatus =
            MH_CreateHook(target, reinterpret_cast<void *>(m_detour),
                          reinterpret_cast<void **>(&m_original));

        if (createStatus != MH_OK) {
            LOG_ERROR("[%s] MH_CreateHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(createStatus));
            return false;
        }

        MH_STATUS enableStatus = MH_EnableHook(target);
        if (enableStatus != MH_OK) {
            LOG_ERROR("[%s] MH_EnableHook failed at 0x%zX. Error: %s", m_name,
                      m_address, MH_StatusToString(enableStatus));
            return false;
        }

        LOG_INFO("[%s] Installed successfully at 0x%zX", m_name, m_address);
        return true;
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
