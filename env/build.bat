@echo off

pushd "..\bin"
call cl "..\src\*.cpp" "..\env\*.cpp" /I C:\dwl\lib /EHsc /FeTesting /w
copy ".\Testing.exe" "..\env\Testing.exe"
popd

echo -------------------- PROGRAM RUN --------------------
Testing.exe
