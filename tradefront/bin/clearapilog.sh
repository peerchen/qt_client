#两个参数  日期  日期+时间

if [ -f log/$1apilog.tar.gz ] ;then
echo "$1apilog.tar.gz文件已存在，不用备份" 
else
tar czvf log/$1apilog.tar.gz log/*.log log/*.wf
rm log/*.log
rm log/*.wf
clear
echo "配份完成"
fi


