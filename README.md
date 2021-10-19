# GMSDLL

This is a "template" project for creating C++ DLLs for GameMaker!

Intended to be copied via [copyre](https://github.com/YAL-Haxe/copyre), like so:
```
copyre GMSDLL MyExtension GMSDLL
```
(which copies GMSDLL/ to MyExtension/ while changing each occurrence of GMSDLL in files/names to MyExtension)

---
As part of first-time setup, you'll also want to add
[GmlCppExtFuncs](https://github.com/YAL-GameMaker-Tools/GmlCppExtFuncs)
and [GmxGen](https://github.com/YAL-GameMaker-Tools/GmxGen)
either to your PATH or to the project directory.

These are used as pre-build and post-build steps respectively and are used to streamline the update process - so that you can do
```
int64_t my_id = 0;
dllg int64_t get_id() {
  return my_id;
}
```
without dealing with GM limitations or manually adding functions to the extension file via UI (see GmlCppExtFuncs documentation for details)
