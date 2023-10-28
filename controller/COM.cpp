//
// Created by tomfl on 3/26/2023.
//

#include <Windows.h>
#include <string>
#include <iostream>

std::string SelectComPort() //added function to find the present serial
{
    char lpTargetPath[5000]; // recv_buffer to store the path of the COMPORTS
    bool gotPort = false; // in case the port is not found

    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        std::string str = "COM" + std::to_string(i); // converting to COM0, COM1, COM2
        DWORD test = QueryDosDevice(str.c_str(), lpTargetPath, 5000);

        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
            std::cout << str << ": " << lpTargetPath << std::endl;
            return str;
        }

        if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
        }
    }
    throw std::invalid_argument("No COM port found");
}