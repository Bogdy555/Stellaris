@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

set SignToolTemp=signtool sign /q /f ".\Solution Items\Digital Certificates\AuroraCore\AuroraCore_SPC_PFX.pfx" /fd SHA256 /p "AuroraCore" /tr "http://timestamp.digicert.com" /td SHA256 /ph /d "Stellaris"

echo on

if exist ".\Binaries\Stellaris\Release\x64\Stellaris.exe" %SignToolTemp% ".\Binaries\Stellaris\Release\x64\Stellaris.exe"
if exist ".\Binaries\Stellaris\Release\x86\Stellaris.exe" %SignToolTemp% ".\Binaries\Stellaris\Release\x86\Stellaris.exe"
if exist ".\Binaries\Stellaris\Debug\x64\Stellaris.exe" %SignToolTemp% ".\Binaries\Stellaris\Debug\x64\Stellaris.exe"
if exist ".\Binaries\Stellaris\Debug\x86\Stellaris.exe" %SignToolTemp% ".\Binaries\Stellaris\Debug\x86\Stellaris.exe"

@echo off

set SignToolTemp=

popd

echo on
