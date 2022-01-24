@echo OFF

:: Validate that all release step have been completed
echo.
echo Did all the Cortex M0/M3/MX library were compile at high optimization
pause
echo.
echo Did all the TDD test have been run and all tests are passing
pause
echo.
echo Did the doxygen documentation have been updated
pause
echo.
echo Did the version.txt have been updated
pause

:: Get Version Number
echo.
echo What is the version Number in the format VMajorMinor example V105
set /p VersionNumber="Version Number: "


:: Get library path
echo.
echo The main folder path contains: Documents, Includes, Sources folders
set /p LibraryMainFolderPath="LibraryMainFolderPath: "

:: extract folder
set LibraryFolder=%LibraryMainFolderPath%
set "LibraryFolder=%LibraryFolder:*Components=Components%"

:: Copy Includes to release folder
::Copy Include
xcopy "%LibraryMainFolderPath%\Includes\*.h" "M:\R&D Projects\Embedded Software Teams Management\%LibraryFolder%\%VersionNumber%\Includes" /I /F

::Copy Version.txt
xcopy "%LibraryMainFolderPath%\Documents\Version.txt" "M:\R&D Projects\Embedded Software Teams Management\%LibraryFolder%" /I /F

::Copy Doxygen HTML
xcopy "%LibraryMainFolderPath%\Documents\Doxygen\HTML" "M:\R&D Projects\Embedded Software Teams Management\%LibraryFolder%\%VersionNumber%\Documents\HTML" /I /F

::Copy Library files
:loop
:: Copy .a
echo.
echo Enter the path of the .a file
set /p LibraryPath="LibraryPath: "

:: get file name
for %%i in ("%LibraryPath%\*.a") do set LibraryFileName=%%~ni
set LibraryFileNameMod="%LibraryFileName%%VersionNumber%"
rename "%LibraryPath%\%LibraryFileName%.a" %LibraryFileName%_%VersionNumber%.a
xcopy "%LibraryPath%" "M:\R&D Projects\Embedded Software Teams Management\%LibraryFolder%\%VersionNumber%" /I /F
rename "%LibraryPath%\%LibraryFileName%_%VersionNumber%.a" %LibraryFileName%.a 

::check if user is done
echo Have all the cortex been copied
CHOICE /C YN /M "Enter your choice:"
if ERRORLEVEL 2 goto loop

pause
