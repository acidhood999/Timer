# Qt Shutdown Timer

A lightweight and stylish Windows desktop application built with C++ and Qt 6. It allows users to set a countdown timer to automatically shut down their PC.

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

## Features

* **Smart Shutdown:** Schedules a system shutdown using native Windows commands (`shutdown /s /t`).
* **Easy Presets:** Quick-access buttons for 15m, 30m, 45m, 1h, and 2h.
* **System Tray Integration:** Runs in the background. Closing the window minimizes the app to the system tray.
* **Autorun Support:** Automatically registers itself in the Windows Registry to start on boot (minimized).
* **Smart Input:** Custom input handling that formats numbers into a `00d 00h 00m 00s` format as you type.
* **Persistence:** Saves the active timer state. If the app is restarted, it recalculates the remaining time and resumes the shutdown schedule.
* **Modern UI:** Clean white-and-black interface with custom CSS (Qt Style Sheets).

## How to Use

1.  **Manual Input:** Click on the time display and type the desired duration.
2.  **Presets:** Click any of the preset buttons (e.g., "1h") to start the timer immediately.
3.  **Activation:** Press the **ON** button to start the countdown. The button will turn into a red **OFF** border, indicating the timer is active.
4.  **Cancellation:** Press the **OFF** button to abort the scheduled shutdown.

## Technical

* **Framework:** Qt 6.10.1
* **Compiler:** MSVC 2022 (x64)
* **Language:** C++17 / C++20
* **Platform:** Windows only (uses `HKEY_CURRENT_USER` registry and `shutdown` CLI).

## Installation

1.  Go to the [Releases](https://github.com/acidhood999/Timer/releases) section.
2.  Download the `Timer_v1.zip` archive.
3.  Extract all files into a folder.
4.  Run `Timer.exe`.

## Building from Source

1.  Clone the repository:
    ```bash
    git clone [https://github.com/acidhood999/Timer.git](https://github.com/acidhood999/Timer.git)
    ```
2.  Open `Timer.sln` in **Visual Studio 2022**.
3.  Ensure you have the **Qt VS Tools** extension installed and the **Qt 6.10.1 MSVC** kit configured.
4.  Build the project in **Release** mode.
5.  Use `windeployqt` to gather necessary dependencies.

---
*Created by [acidhood999](https://github.com/acidhood999)*
