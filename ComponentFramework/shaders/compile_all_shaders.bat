@echo off
set "directory=%~1"

@REM use current dir if no directory is passed in
if "%directory%"=="" set "directory=."

@REM loop over all files
for %%f in ("%directory%\*.frag" "%directory%\*.vert") do (
    set "filename=%%f"
    set "output=%%f.spv"
    echo ------------------{ Compiling: %%f }------------------

    @REM delete if exists
    if exist "%%f.spv" (del "%%f.spv")

    @REM edit this if glslc is not in ur PATH
    glslc.exe -c "%%f" -o "%%f.spv"
    echo Created spv file: %%f.spv
)
echo { Finished (re)compiling shaders }------------------------
exit 0

