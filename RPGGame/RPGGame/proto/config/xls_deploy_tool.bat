@echo off

set XLS_NAME=%1
set SHEET_NAME=%2

echo.
echo =========Compilation of %XLS_NAME%=========

::----------------------------------------
::服务器资源转化
::-----------------------------------------

@echo off
::---------------------------------------------------
::第一步，将xls经过xls_deploy_tool转成data和proto
::---------------------------------------------------
set STEP1_SERVER_XLS=..\xls
set STEP2_SERVER_PYTHON=..\python
set STEP2_SERVER_PROTO=..\proto
set STEP2_SERVER_DATA=..\data
set STEP2_SERVER_JSON=..\json
@echo on


call python xls_deploy_tool.py %SHEET_NAME% %STEP1_SERVER_XLS%\%XLS_NAME% s

@echo off
if  %errorlevel% LSS 0 ( echo  "Failed" & pause & exit ) else ( echo  "OK" )
@echo on

::---------------------------------------------------
::第二步：将data 传到STEP2_SERVER_DATA里
::---------------------------------------------------
::---------------------------------------------------
::        将proto传到STEP2_SERVER_PROTO里
::---------------------------------------------------
::---------------------------------------------------
::        将py   传到STEP2_SERVER_PYTHON里
::---------------------------------------------------
::---------------------------------------------------
::        将txt  传到STEP2_SERVER_JSON里
::---------------------------------------------------
@echo off

IF NOT EXIST "%STEP2_SERVER_DATA%" MD "%STEP2_SERVER_DATA%"
IF NOT EXIST "%STEP2_SERVER_PROTO%" MD "%STEP2_SERVER_PROTO%"
IF NOT EXIST "%STEP2_SERVER_PYTHON%" MD "%STEP2_SERVER_PYTHON%"
IF NOT EXIST "%STEP2_SERVER_JSON%" MD "%STEP2_SERVER_JSON%"

move *.data    %STEP2_SERVER_DATA%\
move *.proto   %STEP2_SERVER_PROTO%\
move *_pb2.py  %STEP2_SERVER_PYTHON%\
move *_pb2.pyc %STEP2_SERVER_PYTHON%\
move *.txt     %STEP2_SERVER_JSON%\
@echo on
