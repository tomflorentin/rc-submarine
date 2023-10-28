#include <iostream>
#include <unistd.h>
#include <thread>
#include "RemoteControl.hpp"
#include "KeyboardHandler.hpp"
#include "PacketHandler.hpp"
#include <SFML/Graphics.hpp>
#include <uxtheme.h>
#include <dwmapi.h>

std::string SelectComPort();

RemoteControl *serial;
sf::RenderWindow *window;
Status status;
KeyboardHandler *keyboardHandler;
sf::Event event;
PacketHandler packetHandler(&status);


void serialThread() {
    std::cout << "SERIAL THREAD STARTED" << std::endl;

    while (true) {
        auto command = serial->receivePacket();
        if (command == Command::NO_COMMAND) {
            Sleep(50);
            continue;
        }
        packetHandler.handlePacket(command, serial->recv_buffer);
    }
}

void forwardThread() {
    while (true) {
        Sleep(200);
        keyboardHandler->handleKey(sf::Keyboard::Z, false);
    }
}

//
//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
int main()
{
    std::string comPort = SelectComPort();
    serial = new RemoteControl(comPort.c_str());
    keyboardHandler = new KeyboardHandler(serial, &status);

    if (serial->isConnected()) {
        std::cout << "Connected to COM" << std::endl;
    } else {
        std::cout << "Failed to connect to COM" << std::endl;
        exit(1);
    }


    auto activeWindow = GetActiveWindow();
    HMONITOR monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX monitorInfoEx;
    monitorInfoEx.cbSize = sizeof(monitorInfoEx);
    GetMonitorInfo(monitor, &monitorInfoEx);
    auto cxLogical = monitorInfoEx.rcMonitor.right - monitorInfoEx.rcMonitor.left;
    auto cyLogical = monitorInfoEx.rcMonitor.bottom - monitorInfoEx.rcMonitor.top;
    DEVMODE devMode;
    devMode.dmSize = sizeof(devMode);
    devMode.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
    auto cxPhysical = devMode.dmPelsWidth;
    auto cyPhysical = devMode.dmPelsHeight;

    std::cout << cxPhysical << " " << cyPhysical << std::endl;
    std::cout << cxLogical << " " << cyLogical << std::endl;
    window = new sf::RenderWindow(sf::VideoMode(cxPhysical, cyPhysical), "overlay");//, sf::Style::None);
    window->setPosition(sf::Vector2i(0,0));
    window->setFramerateLimit(10);


    MARGINS margins;
    margins.cxLeftWidth = -1;

    SetWindowLong(window->getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    DwmExtendFrameIntoClientArea(window->getSystemHandle(), &margins);

    int extendedStyle = GetWindowLong(window->getSystemHandle(), GWL_EXSTYLE);
    SetWindowLong(window->getSystemHandle(), GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT | WS_EX_LAYERED);
    SetWindowPos(window->getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    bool enabled = false;

    sf::Text keyText;
    sf::Font font;
    font.loadFromFile("font.ttf");
    keyText.setFont(font);
    keyText.setPosition({(float)(cxPhysical - 200), (float)(cyPhysical - 200) });
    keyText.setFillColor(sf::Color::Color::Red);
    keyText.setScale(sf::Vector2f(1, 1));

    sf::Text statusText;
    statusText.setFont(font);
    statusText.setPosition({(float)(cxPhysical - 500), 20 });
    statusText.setFillColor(sf::Color::Color::Red);
    statusText.setScale(sf::Vector2f(1, 1));

    auto hwnd = window->getSystemHandle();
//    sf::Event event;
    std::thread(&serialThread).detach();
//    std::thread(&forwardThread).detach();

    while (window->isOpen()) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        Sleep(200);
        while (window->pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window->close();
                    break;

                    // key pressed
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window->close();
                    else
                        keyboardHandler->handleKey(event.key.code, event.key.shift);
                    break;
                default:
                    break;
            }
        }

        window->clear(sf::Color::Transparent);
        keyText.setString(keyboardHandler->getCommandText());
        statusText.setString(status.getStatusText());
        window->draw(keyText);
        window->draw(statusText);
        window->display();
    }
    return 0;
//
//    while (serial.isConnected()) {
//        usleep(1000);
//        Command cmd = serial.receivePacket();
//        if (cmd == Command::LOG) {
//            std::cout << "LOG: " << serial.recv_buffer << std::endl;
//        }
//        if (cmd == Command::INSIDE_TEMPERATURE) {
//            std::cout << "INSIDE_TEMPERATURE: " << *(float *) serial.recv_buffer << std::endl;
//        }
//        if (cmd == Command::INSIDE_HUMIDITY) {
//            std::cout << "INSIDE_HIMIDITY: " << *(float *) serial.recv_buffer << std::endl;
//        }
//    }

//    return 0;
}
