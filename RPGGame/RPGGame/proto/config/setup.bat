call xls_deploy_tool.bat frame.xlsx FrameConfig
call xls_deploy_tool.bat item.xlsx ItemConfig
call xls_deploy_tool.bat map.xlsx MapConfig
call xls_deploy_tool.bat map.xlsx MapActionConfig
call xls_deploy_tool.bat map.xlsx MonsterConfig
call xls_deploy_tool.bat map.xlsx DropConfig

::---------------------------------------------------
::protobuf编译，生成c++源代码
::---------------------------------------------------


set STEP2_SERVER_SRC=..\src
set STEP2_SERVER_PROTO=..\proto
set STEP2_SERVER_DB=..\DB

call protoc.exe --cpp_out=.  %STEP2_SERVER_PROTO%\*.proto --proto_path=%STEP2_SERVER_PROTO%
call protoc.exe --cpp_out=.  %STEP2_SERVER_DB%\*.proto --proto_path=%STEP2_SERVER_DB%
@echo off
if  %errorlevel% LSS 0 ( echo  "Failed" & pause & exit ) else ( echo  "OK" )
@echo on
@echo off
IF NOT EXIST "%STEP2_SERVER_SRC%\proto" MD "%STEP2_SERVER_SRC%\proto"
move *.pb.cc %STEP2_SERVER_SRC%\proto\
move *.pb.h %STEP2_SERVER_SRC%\proto\
@echo on