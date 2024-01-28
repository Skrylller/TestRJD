#include "pch.h"
#include "FileCreator.h"

bool FileCreator::CreateServerFile(string path, string data)
{
    ofstream file(path);

    if (!file.is_open()) {
        return false;
    }

    file << data;
    file.close();
    return true;
}
