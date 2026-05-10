#pragma once
#include <cstdint>
#include <Windows.h>
#include <vector>
#include "../globals.hpp"

/*
 * Memory interface for safe and efficient Roblox memory access
 * Provides read/write operations with validation
 */

class MemoryInterface
{
private:
    HANDLE process_handle;
    uintptr_t base_address;
    const char* process_name;

public:
    MemoryInterface(const char* name) : process_name(name)
    {
        UpdateHandle();
    }

    ~MemoryInterface()
    {
        if (process_handle)
            CloseHandle(process_handle);
    }

    void UpdateHandle()
    {
        DWORD pid = GetProcessIdByName(process_name);
        if (pid == 0) return;

        process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        base_address = GetModuleBase(pid, process_name);
    }

    DWORD GetProcessIdByName(const char* name)
    {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) return 0;

        PROCESSENTRY32 entry = { sizeof(PROCESSENTRY32) };
        if (Process32First(snapshot, &entry))
        {
            do
            {
                if (strcmp(entry.szExeFile, name) == 0)
                {
                    CloseHandle(snapshot);
                    return entry.th32ProcessID;
                }
            } while (Process32Next(snapshot, &entry));
        }
        CloseHandle(snapshot);
        return 0;
    }

    uintptr_t GetModuleBase(DWORD pid, const char* name)
    {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        if (snapshot == INVALID_HANDLE_VALUE) return 0;

        MODULEENTRY32 entry = { sizeof(MODULEENTRY32) };
        if (Module32First(snapshot, &entry))
        {
            do
            {
                if (strcmp(entry.szModule, name) == 0)
                {
                    CloseHandle(snapshot);
                    return reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                }
            } while (Module32Next(snapshot, &entry));
        }
        CloseHandle(snapshot);
        return 0;
    }

    uintptr_t GetBase(const char* name = nullptr)
    {
        if (!name)
            return base_address;
        return GetModuleBase(GetProcessIdByName(process_name), name);
    }

    // ====== SAFE READ/WRITE OPERATIONS ======

    template<typename T>
    T Read(uintptr_t address)
    {
        T value = T{};
        if (!process_handle || address == 0)
            return value;

        SIZE_T bytes_read = 0;
        ReadProcessMemory(process_handle, reinterpret_cast<LPVOID>(address),
            &value, sizeof(T), &bytes_read);
        return value;
    }

    template<typename T>
    void Write(uintptr_t address, const T& value)
    {
        if (!process_handle || address == 0)
            return;

        SIZE_T bytes_written = 0;
        WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address),
            const_cast<T*>(&value), sizeof(T), &bytes_written);
    }

    template<typename T>
    T ReadChain(uintptr_t base, const std::vector<uintptr_t>& offsets)
    {
        uintptr_t address = base;
        for (size_t i = 0; i < offsets.size() - 1; ++i)
        {
            address = Read<uintptr_t>(address + offsets[i]);
            if (address == 0) return T{};
        }
        return Read<T>(address + offsets.back());
    }

    template<typename T>
    void WriteChain(uintptr_t base, const std::vector<uintptr_t>& offsets, const T& value)
    {
        uintptr_t address = base;
        for (size_t i = 0; i < offsets.size() - 1; ++i)
        {
            address = Read<uintptr_t>(address + offsets[i]);
            if (address == 0) return;
        }
        Write<T>(address + offsets.back(), value);
    }

    // ====== UTILITY FUNCTIONS ======

    bool IsValid(uintptr_t address)
    {
        return address > 0x10000 && address < 0x7FFFFFFF0000;
    }

    bool IsProcessRunning()
    {
        return GetProcessIdByName(process_name) != 0;
    }
};

extern MemoryInterface mem;
