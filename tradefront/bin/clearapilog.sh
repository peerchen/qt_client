#��������  ����  ����+ʱ��

if [ -f log/$1apilog.tar.gz ] ;then
echo "$1apilog.tar.gz�ļ��Ѵ��ڣ����ñ���" 
else
tar czvf log/$1apilog.tar.gz log/*.log log/*.wf
rm log/*.log
rm log/*.wf
clear
echo "������"
fi


