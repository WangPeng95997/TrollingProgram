#include "utils.h"

HCRYPTPROV hProv;
int Random()
{
    if (hProv == 0)
        if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            return 0x7FFFFFFF;

    int out = 0;
    CryptGenRandom(hProv, sizeof(out), (BYTE*)(&out));

    return out & 0x7FFFFFFF;
}