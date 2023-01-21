echo "working directory:"
read dir_path

if [ ${dir_path} ]
then
	cd ${dir_path}
	if [ $? -ne 0 ]
	then
		echo "Check your permission rights and path to directory"
		exit 0
	fi
fi

for fd in *
do
	if [ -f $fd ]
	then
		mv $fd `echo $fd | tr '[A-Z][a-z]' '[a-z][A-Z]'`
	fi
done
