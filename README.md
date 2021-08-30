# Audio

[![Issues](https://img.shields.io/github/issues/Asiern/Audio)]()
[![License](https://img.shields.io/github/license/Asiern/Audio)](LICENSE)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/asiern/audio/ubuntu-CMake?label=linux)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/asiern/audio/windows-CMake?label=windows)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/asiern/audio)

## Workspace Setup

### Ubuntu

```
# Configuring audio
$ git clone https://github.com/Asiern/Audio.git
$ cd Audio
$ ./scripts/UbuntuSetup.sh
```

### Windows

```
# Configuring audio
$ git clone https://github.com/Asiern/Audio.git
$ cd Audio
$ ./scripts/WindowsSetup.bat
```

## Building

### Ubuntu

```
# Building audio
$ cd build
$ make all
```

## Libraries

| Name      | Description                                                           | More info                                        |
| --------- | --------------------------------------------------------------------- | ------------------------------------------------ |
| json      | JSON for Modern C++                                                   | [GitHub](https://github.com/nlohmann/json)       |
| wxWidgets | Cross-Platform GUI Library                                            | [GitHub](https://github.com/wxWidgets/wxWidgets) |
| BASS      | BASS is an audio library for use in software on several platforms.    | [Web](https://www.un4seen.com/)                  |
| curl      | A command line tool and library for transferring data with URL syntax | [GitHub](https://github.com/curl/curl)           |

## License

[MIT](LICENSE)
