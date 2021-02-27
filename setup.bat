REM Run cmake
call cmake -B"./app" -S"." || echo cmake failed, Exit Code is %errorlevel% 

cmd /k