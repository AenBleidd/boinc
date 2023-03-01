// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2023 University of California
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

#if defined(_WIN32)
#include "boinc_win.h"
#else
#include "config.h"
#endif

#ifdef _WIN32
#include <wincrypt.h>
#endif

#ifdef ANDROID
#include <stdlib.h>
#endif

#include "boinc_stdio.h"
#include "error_numbers.h"
#include <openssl/evp.h>

#include "md5_file.h"

class MD5 {
public:
    static MD5& init() {
        static MD5 instance;
        if (instance.m_initialized) {
            throw std::logic_error("MD5::init() already called");
        }
        EVP_DigestInit_ex(instance.m_context, instance.m_md, NULL);
        instance.m_initialized = true;
        return instance;
    }
    void update(const void* buf, const size_t len) {
        if (!m_initialized) {
            throw std::logic_error("MD5::init() must be called first");
        }
        EVP_DigestUpdate(m_context, buf, len);
    }
    void finalize(char* output, const size_t len) {
        if (!m_initialized) {
            throw std::logic_error("MD5::init() must be called first");
        }
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        EVP_DigestFinal_ex(m_context, md_value, &md_len);
        m_initialized = false;

        if (md_len * 2 + 1 > len) {
            throw std::logic_error("MD5::finalize() output buffer too small");
        }

        for (size_t i = 0; i < md_len; i++) {
            snprintf(output + 2 * i, len, "%02x", md_value[i]);
        }
        output[md_len*2] = 0;
    }

private:
    EVP_MD_CTX* m_context;
    const EVP_MD* m_md;    
    bool m_initialized;
    MD5() {
        m_context = EVP_MD_CTX_new();
        m_md = EVP_MD_fetch(NULL, "MD5", NULL);
        m_initialized = false;
    }
    ~MD5() {
        EVP_MD_CTX_free(m_context);
    }
    MD5(const MD5&);
    MD5& operator=(const MD5&);

};

int md5_file(const char* path, char* output, double& nbytes, bool is_gzip) {
    unsigned char buf[4096];
    int n;

    nbytes = 0;
    FILE *f = boinc::fopen(path, "rb");
    if (!f) {
        boinc::fprintf(stderr, "md5_file: can't open %s\n", path);
        boinc::perror("md5_file");

        return ERR_FOPEN;
    }

    // check and skip gzip header if needed
    //
    if (is_gzip) {
        n = static_cast<int>(boinc::fread(buf, 1, 10, f));
        if (n != 10) {
            boinc::fclose(f);
            return ERR_BAD_FORMAT;
        }
        if (buf[0] != 0x1f || buf[1] != 0x8b || buf[2] != 0x08) {
            boinc::fclose(f);
            return ERR_BAD_FORMAT;
        }
        nbytes = 10;
    }

    MD5& md5 = MD5::init();
    while (true) {
        n = static_cast<int>(boinc::fread(buf, 1, 4096, f));
        if (n<=0) break;
        nbytes += n;
        md5.update(buf, n);
    }
    md5.finalize(output, MD5_LEN);

    boinc::fclose(f);
    return 0;
}

int md5_block(const unsigned char* data, int nbytes, char* output,
    const unsigned char* data2, int nbytes2     // optional 2nd block
) {
    MD5& md5 = MD5::init();
    md5.update(data, nbytes);
    if (data2) {
        md5.update(data2, nbytes2);
    }
    md5.finalize(output, MD5_LEN);
    return 0;
}

std::string md5_string(const unsigned char* data, int nbytes) {
    char output[MD5_LEN];
    md5_block(data, nbytes, output);
    return output;
}

// make a secure (i.e. hard to guess)
// 32-char string using OS-supplied random bits
//
int make_secure_random_string_os(char* out) {
    char buf[256];
#ifdef _WIN32
    HCRYPTPROV hCryptProv;

    if(! CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        if (GetLastError() == NTE_BAD_KEYSET) {
            if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
                return -1;
            }
        } else {
            return -2;
        }
    }

    if(! CryptGenRandom(hCryptProv, static_cast<DWORD>(32), reinterpret_cast<BYTE*>(buf))) {
        CryptReleaseContext(hCryptProv, 0);
        return -3;
    }

    CryptReleaseContext(hCryptProv, 0);
#elif defined ANDROID
    return -1;
#else
    FILE* f = boinc::fopen("/dev/random", "r");
    if (!f) {
        return -1;
    }
    size_t n = boinc::fread(buf, 32, 1, f);
    boinc::fclose(f);
    if (n != 1) return -2;
#endif
    md5_block(reinterpret_cast<const unsigned char*>(buf), 32, out);
    return 0;
}

