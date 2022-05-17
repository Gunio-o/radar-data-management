@echo off
echo parametr: %1
rem ************** version 1.0 ***************************
@For /F "tokens=2,3,4 delims=/ " %%A in ('Date /t') do @( 
    Set Month=%%A
    Set Day=%%B
    Set Year=%%C
)
Set MY_TIME=%Year%%Month%%Day%
Set LOCAL_DIR="C:\Qt\projekty\Pomiary\pliki\"

IF "%1"=="K1" (
    Set CONF_NAME="K1#mirek@mirek-manjaro:/home/mirek/barti"
    Set RMT_USER="mirek"
    Set RMT_PASS="C:\Users\Basia\Documents\_ssh_test\pas.txt"
    Set RMT_SERVER="mirek-manjaro"
    Set RMT_DIR="/home/mirek/barti"
    goto LSCP
)
IF "%1"=="K2" (
    Set CONF_NAME="K2#mirek@mirek-manjaro:/home/mirek/bartek"
    Set RMT_USER="mirek"
    Set RMT_PASS=""
    Set RMT_SERVER="mirek-manjaro"
    Set RMT_DIR="/home/mirek/bartek"
    goto LSCP
)
IF "%1"=="K3" (
    Set CONF_NAME="K3#\\nas326\Dokumenty\mirek\btest"
    Set RMT_USER="admin"
    Set RMT_PASS=""
    Set RMT_SERVER=""
    Set RMT_DIR="\\nas326\Dokumenty\mirek\btest"
    goto LXCOPY
)
echo Brak konfiguracji
Set ERRORLEVEL=1001
rem pause
rem exit
goto LEND


:LSCP
    echo scp -r %RMT_USER%@%RMT_SERVER%:%RMT_DIR% %LOCAL_DIR% 
    "C:\Program Files\Git\usr\bin\scp" -r %RMT_USER%@%RMT_SERVER%:%RMT_DIR% %LOCAL_DIR% 
    goto LEND

REM ----------- nie dziala przekazanie hasla ani wczytanie pliku, ani wyswietlenie pliku ----------------------
REM type %RMT_PASS% | scp -r %RMT_USER%@%RMT_SERVER%:%RMT_DIR% %LOCAL_DIR% 
REM scp -r mirek@mirek-manjaro:/home/mirek/barti "%LOCAL_DIR%"< "C:\Users\Basia\Documents\_ssh_test\pas.txt" <%RMT_PASS%

:LXCOPY
    echo %RMT_DIR% -> %LOCAL_DIR%
    xcopy %RMT_DIR% %LOCAL_DIR% /E /Y
    goto LEND
REM    echo %RMT_DIR% "->" %LOCAL_DIR% >> c:\test\_backup_dom_log.txt
:LEND
    
