# RelayBoard

A cross-platform 8-channel relay controller with a **Linux CLI** written in C and a **Windows GUI** built with C++ Builder. Communicates with relay hardware over serial (RS-232 / USB) at 57600 baud using a 5-byte binary protocol with CRC8 checksums.

![C](https://img.shields.io/badge/C-C99-A8B9CC?logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-Builder%206-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-064F8C?logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey)
![Serial](https://img.shields.io/badge/Serial-57600%20baud-yellow)

## Features

- **8-channel relay control** with individual on/off, all-on, all-off, status query, and state restore commands
- **Linux CLI** (`power_strip`) for headless operation and scripting, built with CMake
- **Native termios serial configuration** on Linux — no shell-out to `stty`, no command injection surface
- **State persistence** — every change is saved to `power_strip.state`; the `restore` command reapplies it on boot or after a power loss
- **Reply validation** — every received frame is checked for sync byte, device address, command byte and CRC8 before trusting its contents
- **Windows GUI** with per-relay toggle buttons, system tray integration, and COM port auto-detection
- **CRC8 checksums** on every command frame ensuring reliable communication with the relay board
- **Configurable relay names** via a plain-text configuration file on Linux
- **Scheduled actions** in the Windows GUI with per-relay day-of-week and time-based scheduling
- **TCP server** in the Windows GUI for remote network control of relays
- **Obfuscated passwords** for network authentication using a custom hash function
- **System tray** support with popup menu for quick relay toggling without opening the main window
- **Windows autostart** option via registry integration

## Serial Protocol

All communication uses a fixed 5-byte frame at **57600 baud, 8N1**:

| Byte | Value | Description |
|------|-------|-------------|
| 0 | `0x55` | Sync byte (start of frame) |
| 1 | `0x01` | Device address (always `0x01` for USB/RS-232) |
| 2 | Command | `'S'` = Set, `'O'` = On, `'F'` = Off, `'G'` = Get status |
| 3 | Data | Relay bitmask (Set/Get) or relay index 0-7 (On/Off) |
| 4 | CRC8 | Checksum over bytes 1-3 using a 256-byte lookup table |

The board responds to a **Get** command with a frame where byte 2 is `'R'` and byte 3 contains the relay states as a bitmask (bit 0 = relay 1, bit 7 = relay 8).

## Dependencies

### Linux CLI

| Dependency | Version | Purpose |
|------------|---------|---------|
| CMake | >= 3.10 | Build system |
| GCC / Clang | C99 | C compiler |
| POSIX `termios` | — | Serial port configuration (any modern Linux) |

### Windows GUI

| Dependency | Version | Purpose |
|------------|---------|---------|
| C++ Builder | 6.0 | IDE and VCL framework |

## Building

### Linux CLI

```bash
cd linux
mkdir build && cd build
cmake ..
make
```

The resulting binary `power_strip` will be in the `build/` directory.

### Windows GUI

1. Open **C++ Builder 6.0**
2. Select `File` -> `Open...` and open the `.bpr` project file from the `caly program/` directory
3. Click `Project` -> `Build All`
4. The executable will appear in the project output directory

## Usage (Linux CLI)

Before running, ensure the configuration file `power_strip.conf` is in the working directory:

```
/dev/ttyUSB0
Relay 1 Name
Relay 2 Name
Relay 3 Name
Relay 4 Name
Relay 5 Name
Relay 6 Name
Relay 7 Name
Relay 8 Name
```

Line 1 is the serial device path. Lines 2-9 are human-readable names for each relay.

### Commands

```bash
# Query the status of all relays (also refreshes power_strip.state)
./power_strip status

# Switch all relays on
./power_strip allon

# Switch all relays off
./power_strip alloff

# Switch a specific relay on (1-8)
./power_strip 3 on

# Switch a specific relay off (1-8)
./power_strip 3 off

# Reapply the last saved state from power_strip.state
./power_strip restore
```

Exit code is `0` on success and `1` on any error (bad arguments, config file missing, serial I/O failure, malformed reply, CRC mismatch, ...). Error details are written to `stderr`.

## State Persistence

Every command that changes the board writes the resulting 8-bit bitmask to `power_strip.state` next to the config file, as a single hex byte (for example `0x2a`). For single-relay operations (`N on` / `N off`) the program first queries the board with a `G` request to take the board's own state as the source of truth, flips the requested bit, sends an `S` frame with the new mask and finally updates the state file. This keeps the saved state consistent with the hardware even if the file was lost or edited manually.

`./power_strip restore` reads the saved bitmask and sends a single `S` frame to reapply it. It never talks to the file beyond reading it, so the board always ends up exactly in the last saved configuration.

### systemd integration

To automatically restore the last known relay state after a reboot or power loss, drop a unit file into `/etc/systemd/system/power-strip-restore.service`:

```ini
[Unit]
Description=Restore RelayBoard relay state on boot
After=local-fs.target

[Service]
Type=oneshot
WorkingDirectory=/opt/power_strip
ExecStart=/opt/power_strip/power_strip restore

[Install]
WantedBy=multi-user.target
```

Then enable it with `sudo systemctl enable power-strip-restore.service`. Place `power_strip`, `power_strip.conf` and the produced `power_strip.state` in `/opt/power_strip/` (or any other directory — just match `WorkingDirectory`).

## Project Structure

```
RelayBoard/
├── README.md                               # This file
├── linux/                                  # Linux CLI application
│   ├── CMakeLists.txt                      # CMake build configuration (C99, -Wall -Wextra -pedantic)
│   ├── main.c                              # CLI entry point, termios setup, command dispatch, state I/O
│   ├── main.h                              # Protocol constants, frame layout, file paths
│   ├── crc.c                               # CRC8 lookup-table implementation
│   ├── crc.h                               # CRC function declaration
│   └── build/
│       ├── power_strip.conf                # Sample configuration file
│       └── power_strip.state               # Generated at runtime: last known relay bitmask
├── caly program/                           # Windows GUI application (C++ Builder 6)
│   ├── SterowanieListwa.cpp                # Application entry point
│   ├── SterowanieListwa.bpr                # C++ Builder project file
│   ├── main.cpp                            # Main form: relay buttons, serial I/O, tray, server
│   ├── main.h                              # Main form class declaration
│   ├── main.dfm                            # Main form visual layout
│   ├── Unit2.cpp                           # Settings form: COM port, scheduling, relay names
│   ├── Unit2.h                             # Settings form declaration
│   ├── Unit2.dfm                           # Settings form layout
│   ├── Unit3.cpp                           # Schedule action dialog (day/time configuration)
│   ├── Unit3.h                             # Schedule action declaration
│   ├── Unit3.dfm                           # Schedule action layout
│   ├── about.cpp                           # About dialog
│   ├── about.h                             # About dialog declaration
│   ├── about.dfm                           # About dialog layout
│   ├── soc.cpp                             # Socket parameter parsing utilities
│   ├── soc.h                               # Socket utilities header
│   ├── hash.cpp                            # Password obfuscation functions
│   └── hash.h                              # Hash function declarations
├── klient sterowanie/                      # Standalone Windows network client
│   ├── Klient_SterowanieListwa.cpp         # Client application entry point
│   ├── Klient_SterowanieListwa.bpr         # Client project file
│   ├── main.cpp                            # Client main form with socket communication
│   ├── main.h                              # Client form declaration
│   ├── main.dfm                            # Client form layout
│   ├── soc.cpp                             # Socket utilities (shared)
│   └── soc.h                               # Socket utilities header
└── Specyfikacja protokolu.txt              # Protocol specification (Polish)
```

## License

This project is provided as-is for educational purposes.
