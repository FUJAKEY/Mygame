# MyGame

This repository contains a barebones skeleton of a DDNet style 2D platformer. It
uses **SFML** for rendering and **Box2D** for physics. The layout is organised so
that the same code base can be compiled on Linux, Windows and Android.

The current demo implements a simple frozen block that can freeze the player and
a basic grappling hook using a Box2D distance joint. Levels are loaded from a
CSV text file located in `assets/level.csv`.

## Directory layout

```
include/        # C++ headers
src/            # C++ source files
assets/         # level data (csv/tmx), configs
platform/       # platform specific entry points
    windows/
    android/
third_party/    # external libraries (SFML/Box2D/...)
build/          # build output directories
```

Only a minimal set of source files is included. Extend them with your game
logic (player, hook mechanics, blocks, levels).

## Controls

- **H** – fire the grappling hook toward the mouse position
- **J** – release the hook
- **R** – respawn (also unfreezes the player if frozen)

## Building on Linux

```bash
sudo apt-get install build-essential cmake libsfml-dev libbox2d-dev
mkdir -p build/linux && cd build/linux
cmake ../..
make -j$(nproc)
./GameApp
```

## Cross‑compiling for Windows on Linux

1. Install the MinGW‑w64 toolchain
   ```bash
   sudo apt-get install mingw-w64
   ```
2. Configure CMake using the MinGW toolchain and build
   ```bash
   mkdir -p build/windows && cd build/windows
   cmake -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw-w64/toolchain-x86_64.cmake ../..
   # path may vary by distro; search for toolchain-*.cmake if not present
   make -j$(nproc)
   ```
3. Copy `GameApp.exe` together with the SFML DLLs from your system to a Windows
   machine. No Windows installation is required on the build machine.

## Building for Android (NDK) on Linux

1. Download the Android NDK and set `ANDROID_NDK_HOME` to its path.
   Add the NDK toolchain to `PATH` so CMake can find `clang`:
   `export PATH=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH`.
2. Configure and build with the Android toolchain
   ```bash
   mkdir -p build/android && cd build/android
   cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
         -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-23 ../..
   make -j$(nproc)
   ```
3. The resulting shared library can be packaged into an APK using Gradle or your
   favourite build system. All compilation happens on Linux without the Android
   SDK installed locally.

## Building in Google Colab

Colab provides a Linux environment where you can run the same commands as above.
Example setup:

```python
!apt-get update && apt-get install -y build-essential cmake \
    libsfml-dev libbox2d-dev
!mkdir -p build/colab && cd build/colab && cmake ../.. && make -j2
```

Because Colab does not allow direct window output, you can run the game under
`xvfb`:

```python
!apt-get install -y xvfb
!xvfb-run ./GameApp
```

This quick tutorial shows how to compile for Linux, cross‑compile for Windows
or Android, and even build inside Google Colab.

## Сборка на русском

Ниже приведены краткие шаги на русском языке.

### Сборка под Windows

```bash
sudo apt-get install mingw-w64
mkdir -p build/windows && cd build/windows
cmake -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw-w64/toolchain-x86_64.cmake ../..
# path may vary by distro; search for toolchain-*.cmake if not present
make -j$(nproc)
```

Скопируйте `GameApp.exe` и DLL‑файлы SFML на целевую машину с Windows.

### Сборка под Android

```bash
export ANDROID_NDK_HOME=/path/to/ndk
mkdir -p build/android && cd build/android
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-23 ../..
make -j$(nproc)
```

Полученную библиотеку можно упаковать в APK через Gradle.

### Google Colab

В Colab установите зависимости и соберите проект теми же командами, что и на Linux:

```python
!apt-get update && apt-get install -y build-essential cmake \
    libsfml-dev libbox2d-dev
!mkdir -p build/colab && cd build/colab && cmake ../.. && make -j2
```
# Extended script to build Windows and Android in Colab
```python
!apt-get update && apt-get install -y build-essential cmake ninja-build git wget unzip \
    mingw-w64 openjdk-11-jdk
!wget https://dl.google.com/android/repository/android-ndk-r25c-linux.zip -O ndk.zip
!unzip -q ndk.zip
!git clone --depth=1 https://github.com/erincatto/box2d.git Box2D
!git clone --depth=1 https://github.com/SFML/SFML.git SFML
```
```bash
%%bash
set -e
export ANDROID_NDK_HOME=$PWD/android-ndk-r25c

# Build Box2D for Android
mkdir -p Box2D/build-android && cd Box2D/build-android
cmake -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 \
    -DBOX2D_BUILD_UNIT_TESTS=OFF -DBOX2D_BUILD_TESTBED=OFF ..
ninja
cd ../..

# Build SFML for Android
mkdir -p SFML/build-android && cd SFML/build-android
cmake -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 \
    -DSFML_BUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=$PWD/../android-install ..
ninja install
cd ../..

# Build Windows executable
mkdir -p build/windows && cd build/windows
cmake -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw-w64/toolchain-x86_64.cmake ../..
make -j$(nproc)
cd ../..

# Build Android arm64 library and optionally an APK
mkdir -p build/android && cd build/android
cmake -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 \
    -DSFML_DIR=$PWD/../../SFML/android-install/lib/cmake/SFML \
    -DBox2D_DIR=$PWD/../../Box2D/build-android ..
ninja
cd ../..
if [ -f platform/android/gradlew ]; then
    cd platform/android && ./gradlew assembleDebug
    cd ../..
fi
```
