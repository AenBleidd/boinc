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

#include <sstream>

#include "FileTable.h"
#include "CabHelper.h"
#include "StreamTable.h"
#include "MediaTable.h"
#include "MsiFileHashTable.h"
#include "ValidationTable.h"

int FileTable::GetFileLanguage(const std::string& filePath) {
    DWORD handle;
    const auto size = GetFileVersionInfoSize(filePath.c_str(), &handle);
    if (size == 0) {
        return 0;
    }

    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfo(filePath.c_str(), handle, size, buffer.data())) {
        return 0;
    }

    struct LANGANDCODEPAGE {
        WORD wLanguage;
        WORD wCodePage;
    } *lpTranslate;

    UINT cbTranslate;
    if (!VerQueryValue(buffer.data(), TEXT("\\VarFileInfo\\Translation"), reinterpret_cast<LPVOID*>(&lpTranslate), &cbTranslate)) {
        return 0;
    }

    if (cbTranslate < sizeof(LANGANDCODEPAGE)) {
        return 0;
    }

    return lpTranslate->wLanguage;
}

std::string FileTable::GetFileVersion(const std::string& filePath) {
    DWORD handle;
    const auto size = GetFileVersionInfoSize(filePath.c_str(), &handle);
    if (size == 0) {
        return {};
    }

    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfo(filePath.c_str(), handle, size, buffer.data())) {
        return {};
    }

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT fileInfoSize = 0;
    if (!VerQueryValue(buffer.data(), TEXT("\\"), reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoSize) || fileInfoSize == 0) {
        return {};
    }

    DWORD majorVersion = HIWORD(fileInfo->dwFileVersionMS);
    DWORD minorVersion = LOWORD(fileInfo->dwFileVersionMS);
    DWORD buildNumber = HIWORD(fileInfo->dwFileVersionLS);
    DWORD revisionNumber = LOWORD(fileInfo->dwFileVersionLS);

    std::stringstream ss;
    ss << majorVersion << "." << minorVersion << "." << buildNumber << "." << revisionNumber;
    return ss.str();
}

size_t FileTable::GetFileSize(const std::string& filePath) {
    const auto hFile = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return 0;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        CloseHandle(hFile);
        return 0;
    }

    CloseHandle(hFile);
    return fileSize.QuadPart;
}

std::filesystem::path FileTable::GetAbsolutePath(const std::filesystem::path& filePath) {
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

    auto p = filePath.string();
    auto index = p.find(configuration_template);
    if (index != std::string::npos) {
        p.replace(index, configuration_template.size(), configuration);
    }
    index = p.find(platform_template);
    if (index != std::string::npos) {
        p.replace(index, platform_template.size(), platform);
    }
    return root_path / p;
}

FileTable::FileTable(const std::vector<Directory>& directories, const std::filesystem::path& root_path) : root_path(root_path) {
    int sequence = 0;
    for (const auto& directory : directories) {
        for (const auto& component : directory.getComponents()) {
            for (auto file : component.getFiles()) {
                file.setFilepath(GetAbsolutePath(file.getFilepath()));
                file.setAttributes(16384);
                file.setSequence(++sequence);
                const auto language = GetFileLanguage(file.getFilepath().string());
                if (language > 0) {
                    file.setLanguage(std::to_string(language));
                }
                const auto version = GetFileVersion(file.getFilepath().string());
                if (!version.empty()) {
                    file.setVersion(version);
                }
                file.setFilesize(static_cast<int>(GetFileSize(file.getFilepath().string())));
                files.push_back(file);
            }
        }
    }
}

bool FileTable::generate(MSIHANDLE hDatabase) {
    const auto cabname = std::string("boinc.cab");
    if (!CabHelper::create(root_path, cabname, files)) {
        return false;
    }
    
    if (!StreamTable({ Stream("#" + cabname, root_path / cabname) }).generate(hDatabase)) {
        std::cerr << "Failed to generate StreamTable" << std::endl;
        return false;
    }

    std::filesystem::remove(root_path / cabname);

    if (!MediaTable({ Media(1, static_cast<int>(files.size()), "1", "#" + cabname, "DISK1", "")}).generate(hDatabase)) {
        std::cerr << "Failed to generate MediaTable" << std::endl;
        return false;
    }
    if (!MsiFileHashTable(files).generate(hDatabase)) {
        std::cerr << "Failed to generate MsiFileHashTable" << std::endl;
        return false;
    }

    std::cout << "Generating FileTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `File` (`File` CHAR(72) NOT NULL, `Component_` CHAR(72) NOT NULL, `FileName` CHAR(255) NOT NULL LOCALIZABLE, `FileSize` LONG NOT NULL, `Version` CHAR(72), `Language` CHAR(20), `Attributes` SHORT, `Sequence` SHORT NOT NULL PRIMARY KEY `File`)";
    const auto sql_insert = "INSERT INTO `File` (`File`, `Component_`, `FileName`, `FileSize`, `Version`, `Language`, `Attributes`, `Sequence`) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("File", "File", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Primary key, non-localized token, must match identifier in cabinet.  For uncompressed files, this field is ignored.");
    records.emplace_back("File", "Component_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Component", "1", "Identifier", "", "Foreign key referencing Component that controls the file.");
    records.emplace_back("File", "FileName", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Filename", "", "File name used for installation, may be localized.  This may contain a \"short name | long name\" pair.");
    records.emplace_back("File", "FileSize", "N", 0, 2147483647, "", "", "", "", "Size of file in bytes (long integer).");
    records.emplace_back("File", "Version", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "File", "1", "Version", "", "Version string for versioned files;  Blank for unversioned files.");
    records.emplace_back("File", "Language", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Language", "", "List of decimal language Ids, comma-separated if more than one.");
    records.emplace_back("File", "Attributes", "Y", 0, 32767, "", "", "", "", "Integer containing bit flags representing file attributes (with the decimal value of each bit position in parentheses)");
    records.emplace_back("File", "Sequence", "N", 0, 32767, "", "", "", "", "Sequence with respect to the media images; order must track cabinet order.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, files);
}