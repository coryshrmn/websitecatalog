@echo off

set SOURCE=..\source\WebsiteCatalog.c ..\source\BstManager.c ..\source\HashManager.c ..\source\InsertManager.c ..\source\queueADT.c ..\source\Utility.c ..\source\WebsiteManager.c

set VCBIN=%VS110COMNTOOLS%..\..\VC\bin

rem configure environment only once
echo Configuring environment...
if not defined VCV32CALLED (
  "%VCBIN%\vcvars32.bat"
  set VCV32CALLED=""
  echo     Configured environment.
) else (
  echo     Environment was already configured.
)
echo.


rem make bin directories
echo Making directory structure...
if not exist "bin" md "bin"
if not exist "bin\release" md "bin\release"
if not exist "obj" md "obj"
echo     Made directory structure.
echo.


echo Compiling and linking...
"%VCBIN%\cl.exe" /o bin\release\websitecatalog.exe -Ox -I ..\header /Foobj\ %SOURCE%

echo     Compiled and linked.
echo.

echo Cleaning obj files...
rd /s /q obj
echo     Cleaned.
echo.
echo Finished.