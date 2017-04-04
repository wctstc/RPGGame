call xls_deploy_tool.bat frame.xlsx FRAME
call xls_deploy_tool.bat item.xlsx ITEM

::---------------------------------------------------
::protobuf编译，生成c++源代码
::---------------------------------------------------


set STEP2_SERVER_SRC=..\src

call protoc.exe --cpp_out=.  %STEP2_SERVER_PROTO%\*.proto --proto_path=%STEP2_SERVER_PROTO%
@echo off
if  %errorlevel% LSS 0 ( echo  "Failed" & pause & exit ) else ( echo  "OK" )
@echo on
@echo off
IF NOT EXIST "%STEP2_SERVER_SRC%\proto" MD "%STEP2_SERVER_SRC%\proto"
move *.pb.cc %STEP2_SERVER_SRC%\proto\
move *.pb.h %STEP2_SERVER_SRC%\proto\
@echo on