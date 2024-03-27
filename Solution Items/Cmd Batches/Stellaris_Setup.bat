@echo off

echo on

if "%SolutionDir%" == "" call ".\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\Solution Items\Cmd Batches\Stellaris_CreateFolders.bat"

call ".\Solution Items\Cmd Batches\Stellaris_GenerateCertificates.bat"

@echo off

popd

echo on
