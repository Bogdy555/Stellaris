@echo off

echo on

if "%SolutionDir%" == "" call ".\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

if not exist ".\AuroraCore\Cmd Batches\" mkdir ".\AuroraCore\Cmd Batches\"
if not exist ".\Stellaris\Files\" mkdir ".\Stellaris\Files\"

@echo off

popd

echo on
