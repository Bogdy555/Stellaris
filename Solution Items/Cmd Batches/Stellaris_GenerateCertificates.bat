@echo off

echo on

if "%SolutionDir%" == "" call ".\Stellaris_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

if not exist ".\Solution Items\Digital Certificates\AuroraCore\" mkdir ".\Solution Items\Digital Certificates\AuroraCore\"

@echo off

pushd ".\Solution Items\Digital Certificates\AuroraCore\"

echo on

if not exist ".\AuroraCore_CA_CER.cer" makecert /r /pe /n "CN=AuroraCore" /ss CA /a SHA256 /cy authority /sky signature /sv ".\AuroraCore_CA_PK.pvk" ".\AuroraCore_CA_CER.cer"
if not exist ".\AuroraCore_SPC_CER.cer" makecert /pe /n "CN=AuroraCore" /a SHA256 /cy end /sky signature /ic ".\AuroraCore_CA_CER.cer" /iv ".\AuroraCore_CA_PK.pvk" /sv ".\AuroraCore_SPC_PK.pvk" ".\AuroraCore_SPC_CER.cer"
if not exist ".\AuroraCore_SPC_PFX.pfx" pvk2pfx /pvk ".\AuroraCore_SPC_PK.pvk" /spc ".\AuroraCore_SPC_CER.cer" /pfx ".\AuroraCore_SPC_PFX.pfx" /pi "AuroraCore" /po "AuroraCore"

@echo off

popd

popd

echo on
