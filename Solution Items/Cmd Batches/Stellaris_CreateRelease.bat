@echo off

echo on

if "%SolutionDir%" == "" call ".\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\Solution Items\Cmd Batches\Stellaris_BuildAll.bat"

call ".\Stellaris\Cmd Batches\Stellaris_Sign.bat"

@echo off

popd

echo on
