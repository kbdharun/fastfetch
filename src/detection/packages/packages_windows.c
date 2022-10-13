#include "packages.h"

#include <handleapi.h>
#include <fileapi.h>

static uint32_t getNumElements(const char* searchPath /* including `\*` suffix */, DWORD type)
{
    uint32_t counter = 0;
    WIN32_FIND_DATAA wfd;
    HANDLE hFind = FindFirstFileA(searchPath, &wfd);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do // Managed to locate and create an handle to that folder.
        {
            if(wfd.dwFileAttributes & type)
                counter++;
        } while (FindNextFileA(hFind, &wfd));
        FindClose(hFind);
    }

    if(type == FILE_ATTRIBUTE_DIRECTORY && counter >= 2)
        counter -= 2; // accounting for . and ..

    return counter;
}

void ffDetectPackagesImpl(const FFinstance* instance, FFPackagesResult* result)
{
    FF_UNUSED(instance);

    FFstrbuf scoopPath;
    ffStrbufInitF(&scoopPath, "%s/scoop/apps/*", getenv("USERPROFILE"));
    counts->scoop = getNumElements(scoopPath.chars, FILE_ATTRIBUTE_DIRECTORY);
    if(counts->scoop > 0)
        counts->scoop-- // scoop
    ffStrbufDestroy(&scoopPath);
}
