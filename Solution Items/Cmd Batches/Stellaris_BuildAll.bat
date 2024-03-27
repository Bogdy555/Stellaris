@echo off

echo on

if "%SolutionDir%" == "" call ".\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

MSBuild /m /property:Configuration=Release /property:Platform=x64
MSBuild /m /property:Configuration=Release /property:Platform=x86
MSBuild /m /property:Configuration=Debug /property:Platform=x64
MSBuild /m /property:Configuration=Debug /property:Platform=x86

@echo off

popd

echo on
