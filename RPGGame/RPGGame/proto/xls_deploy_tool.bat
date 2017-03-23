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
set STEP1_SERVER_XLS=xls
set STEP2_SERVER_PYTHON=python
set STEP2_SERVER_PROTO=proto
set STEP2_SERVER_DATA=data
set STEP2_SERVER_JSON=json
set STEP2_SERVER_SRC=src
@echo on

@echo off
echo TRY TO DELETE TEMP FILES:
del %STEP2_SERVER_PYTHON%\*_pb2.py
del %STEP2_SERVER_PYTHON%\*_pb2.pyc
del %STEP2_SERVER_PROTO%\*.proto
del %STEP2_SERVER_DATA%\*.data
del %STEP2_SERVER_JSON%\*.data
del %STEP2_SERVER_SRC%\proto\*.pb.cc
del %STEP2_SERVER_SRC%\proto\*.pb.h
::del *.log
::del *.txt
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

move *.data    %STEP2_SERVER_DATA%\
move *.proto   %STEP2_SERVER_PROTO%\
move *_pb2.py  %STEP2_SERVER_PYTHON%\
move *_pb2.pyc %STEP2_SERVER_PYTHON%\
move *.txt     %STEP2_SERVER_JSON%\
@echo on

::---------------------------------------------------
::第三步：将生成c++源代码
::---------------------------------------------------

echo =========Compilation of Proto=========
call protoc.exe --cpp_out=.  %STEP2_SERVER_PROTO%\*.proto
@echo off
if  %errorlevel% LSS 0 ( echo  "Failed" & pause & exit ) else ( echo  "OK" )
@echo on
@echo off
move %STEP2_SERVER_PROTO%\*.pb.cc %STEP2_SERVER_SRC%\proto\
move %STEP2_SERVER_PROTO%\*.pb.h %STEP2_SERVER_SRC%\proto\
@echo on