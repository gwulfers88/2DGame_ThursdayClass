@echo off

IF NOT EXIST ..\build\Debug mkdir ..\build\Debug
pushd ..\build\Debug

REM this are the compiler flags we want to use for our program.
set compilerFlags= -MTd -nologo -Gm- -GR- -EHa- -EHsc- -Od -Oi -W4 -wd4201 -wd4100 -wd4189 -wd4505 -FC -Z7 -DEMACS
set linkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib /SUBSYSTEM:CONSOLE

del *.pdb > NUL 2> NUL

cl %compilerFlags% ..\..\2DGame_Wulfers\main.cpp ..\..\2DGame_Wulfers\Manager.cpp ..\..\2DGame_Wulfers\GameObject.cpp -Fmmain.map /link %linkerFlags% /PDB:main.pdb

popd