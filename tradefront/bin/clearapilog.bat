rem ##$��������  ����  ����+ʱ��  Ŀ¼

@echo off 
cd %3/log


if exist %3/log/%1apilog/api.m.log goto unbak

mkdir %1apilog
move *.log %1apilog
move *.wf %1apilog
@echo "�������"

goto end


:unbak

@echo %3/log/%1apilog/api.m.log  �Ѵ��ڣ����ñ���

:end
cd ..