rem ##$三个参数  日期  日期+时间  目录

@echo off 
cd %3/log


if exist %3/log/%1apilog/api.m.log goto unbak

mkdir %1apilog
move *.log %1apilog
move *.wf %1apilog
@echo "备份完成"

goto end


:unbak

@echo %3/log/%1apilog/api.m.log  已存在，不用备份

:end
cd ..