// This file is part of BOINC.
// https://boinc.berkeley.edu
// Copyright (C) 2024 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <memory>

#include <Windows.h>
#include <fci.h>
#include <io.h>

#include "CabHelper.h"

static int chFilePlaced(PCCAB, LPSTR, long, BOOL, void*) noexcept {
    return 0;
}

static void* chAlloc(unsigned long cb) {
    return new char[cb];
}

static void chFree(void* memory) noexcept {
    delete[] memory;
}

static long long chFileOpen(LPSTR pszFile, int, int, int* err, void*) {
    auto handle = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        GetFileAttributes(pszFile) == INVALID_FILE_ATTRIBUTES ? CREATE_NEW : OPEN_EXISTING, 0, NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to CreateFile " << pszFile << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }

    return (INT_PTR)handle;
}

static unsigned int chFileRead(long long hf, void* memory, unsigned int cb, int* err, void*) {
    DWORD dwRead;

    if (!ReadFile((HANDLE)hf, memory, cb, &dwRead, NULL))
    {
        std::cerr << "Failed to ReadFile " << GetLastError() << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }

    return dwRead;
}

static unsigned int chFileWrite(long long hf, void* memory, unsigned int cb, int* err, void*) {
    DWORD dwWritten;

    if (!WriteFile((HANDLE)hf, memory, cb, &dwWritten, NULL)) {
        std::cerr << "Failed to WriteFile " << GetLastError() << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }
    return dwWritten;
}

static int chFileClose(long long hf, int* err, void*) {
    if (!CloseHandle((HANDLE)hf)) {
        std::cerr << "Failed to CloseHandle " << GetLastError() << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }
    return 0;
}

static long chFileSeek(long long hf, long dist, int seektype, int* err, void*) {
    DWORD ret;

    ret = SetFilePointer((HANDLE)hf, dist, NULL, seektype);
    if (ret == INVALID_SET_FILE_POINTER) {
        std::cerr << "Failed to SetFilePointer " << GetLastError() << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }
    return ret;
}

static int chFileDelete(LPSTR pszFile, int* err, void*) {
    if (!DeleteFileA(pszFile)) {
        std::cerr << "Failed to DeleteFile " << pszFile << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }
    return 0;
}

static int chGetNextCabinet(PCCAB, ULONG, void*) {
    return TRUE;
}

static long chProgress(UINT, ULONG, ULONG, void*) {
    return 0;
}

static long long chGetFileInfo(LPSTR pszName, USHORT* pdate, USHORT* ptime, USHORT* pattribs, int* err, void*) {
    BY_HANDLE_FILE_INFORMATION finfo;
    FILETIME filetime;
    HANDLE handle;
    DWORD attrs;
    BOOL res;

    handle = CreateFile(pszName, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to CreateFile " << pszName << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }

    res = GetFileInformationByHandle(handle, &finfo);
    if (!res) {
        std::cerr << "Expected GetFileInformationByHandle to succeed" << std::endl;
        if (err)
            *err = GetLastError();
        return -1;
    }

    FileTimeToLocalFileTime(&finfo.ftLastWriteTime, &filetime);
    FileTimeToDosDateTime(&filetime, pdate, ptime);

    attrs = GetFileAttributes(pszName);
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        std::cerr << "Failed to GetFileAttributes" << std::endl;
        if (err) {
            *err = GetLastError();
        }
        return -1;
    }

    return (INT_PTR)handle;
}

BOOL chGetTemp(char* pszTempName, int cbTempName, void*) {
    auto temp_path = std::make_unique<char[]>(cbTempName);
    if (!GetTempPath(MAX_PATH, temp_path.get())) {
        std::cerr << "Failed to get temporary path" << std::endl;
        return FALSE;
    }
    if (!GetTempFileName(temp_path.get(), "TMP", 0, pszTempName)) {
        std::cerr << "Failed to create temporary file name." << std::endl;
        return FALSE;
    }
    DeleteFile(pszTempName);
    return TRUE;
}

bool CabHelper::create(const std::filesystem::path& root_path, std::vector<File>& files) {
    const std::string configuration_template = "%%CONFIGURATION%%";
    const std::string configuration =
#ifdef _DEBUG
        "Debug";
#else
        "Release";
#endif
    const std::string platform_template = "%%PLATFORM%%";
    const std::string platform =
#ifdef _ARM64_
        "ARM64";
#else
        "x64";
#endif

    std::cout << "Creating CAB file..." << std::endl;

    CCAB ccab;
    memset(&ccab, 0, sizeof(ccab));
    strncpy(ccab.szCabPath, root_path.string().c_str(), CB_MAX_CAB_PATH);
    strncpy(ccab.szCab, "\\boinc.cab", CB_MAX_CABINET_NAME);

    ERF erf{};

    const auto cab = FCICreate(&erf, chFilePlaced, chAlloc, chFree, chFileOpen, chFileRead, chFileWrite, chFileClose, chFileSeek, chFileDelete, chGetTemp, &ccab, nullptr);
    if (!cab) {
        if (erf.fError)
            std::cerr << "Failed to create CAB file: " << erf.erfOper << ":" << erf.erfType << std::endl;
        else
            std::cerr << "Failed to create CAB file" << std::endl;
        return false;
    }

    for (auto& file : files) {
        auto p = file.getFilePath().string();
        auto index = p.find(configuration_template);
        if (index != std::string::npos) {
            p.replace(index, configuration_template.size(), configuration);
        }
        index = p.find(platform_template);
        if (index != std::string::npos) {
            p.replace(index, platform_template.size(), platform);
        }
        auto file_path = root_path / p;

        std::cout << "Adding file: " << file_path << " as " << file.getFileId() << std::endl;

        if (!FCIAddFile(cab, file_path.string().data(), file.getFileId().data(), FALSE, chGetNextCabinet, chProgress, chGetFileInfo, tcompTYPE_MSZIP)) {
            std::cerr << "Failed to add file. Error: " << erf.erfOper << std::endl;
            FCIDestroy(cab);
            return false;
        }
    }

    if (!FCIFlushCabinet(cab, FALSE, chGetNextCabinet, chProgress)) {
        std::cerr << "Failed to flush. Error: " << erf.erfOper << std::endl;
        FCIDestroy(cab);
        return 1;
    }

    return FCIDestroy(cab);
}
