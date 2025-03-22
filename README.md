# Wakatime for KDevelop

## Dependencies:

The following are required to be installed:

* [CMake](https://cmake.org/)
* [Extra CMake Modules](https://invent.kde.org/frameworks/extra-cmake-modules)
* [KF6:I18n](https://github.com/KDE/ki18n)
* [KF6:KTextEditor](https://github.com/KDE/ktexteditor)
* [Qt6](https://doc.qt.io/qt-6/)

For information see: 
 * [Building KDE software with kde-builder](https://develop.kde.org/docs/getting-started/building/kde-builder-compile/)
 * [KDevelop - Arch Wiki](https://wiki.archlinux.org/title/KDevelop)

## Installation instructions:

First clone the repo:

```
cd ~/projects
git clone https://github.com/snej55/kdevelop-wakatime-plugin.git
cd kdevelop-wakatime-plugin
```

Build it:
```
cmake . -B build -DQT_MAJOR_VERSION=6 -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build/
```

Install:
```
sudo cmake --install build
```

Restart kdevelop, and the plugin should be installed!

### Default kdevelop installation instructions:

If the instructions above didn't work, you can try having a look at these (the default plugin installation instructions).

Make sure the project is configured to install to the directory of your choice:

In KDevelop, select the menu entry "Project" > "Open Configuration...",
then in the dialog choose the tab "CMake",
there select in the "Cache Values" list the entry with the name `CMAKE_INSTALL_PREFIX`
and ensure the correct path is set.

If you install to a custom directory, you need to extend the `QT_PLUGIN_PATH`
environment variable that KDevelop sees when it is started. The path to be added
is the "plugins" subdir, whose exact path depends on the operating system and
if that is a 64 bit or 32 bit one.
On Debian, Ubuntu & similar with a 64 bit system add:
    $my_install_prefix/lib/x86_64-linux-gnu/plugins
On openSUSE & similar with a 64 bit system add:
    $my_install_prefix/lib64/plugins
(where `$my_install_prefix` is the directory `CMAKE_INSTALL_PREFIX` is set to)

If you are unsure, check in the installation log the path to which the plugin is installed.


Example:
When CMAKE_INSTALL_PREFIX is set to "/home/userX/projects/mykdevplugin/" and
this is a Debian 64-bit system, open a console and enter:

    export QT_PLUGIN_PATH=$QT_PLUGIN_PATH:/home/userX/projects/mykdevplugin/lib/x86_64-linux-gnu/plugins 

Then start KDevelop from that console:

    kdevelop

If everything went well, you should see "Hello world, my plugin is loaded!" printed in the console and find the plugin also listed in the dialog opened by the menu entry "Help" > "Loaded Plugins".
