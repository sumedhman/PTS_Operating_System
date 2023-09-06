# dealing with the file types, if the file exists then display the appropriate messages
fname=$1
echo "So the given file name is $fname..."
if [ -e $fname ] ; then  # sh ./shell8.sh mytest.txt
	echo "$fname is existing..."
    if [ -f $fname ] ; then     # ordinary file
		echo "$fname is an ORDINARY file..."
		perm=`ls -l $fname | cut -c2`
        if [ $perm = "r" ] ; then
			echo "$fname has READ PERMISSION ON..."
        fi
		perm=`ls -l $fname | cut -c3`
        if [ $perm = "w" ] ; then
			echo "$fname has WRITE PERMISSION ON..."
        fi
		perm=`ls -l $fname | cut -c4`
        if [ $perm = "x" ] ; then
			echo "$fname has EXECUTE PERMISSION ON..."
        fi

	elif [ -L $fname ] ; then   # link file
		echo "$fname is a LINK file..."  # sh ./shell8.sh /dev/fd
	elif [ -d $fname ] ; then
		echo "$fname is a DIRECTORY file..."  # sh ./shell8.sh /mydir
	elif [ -c $fname ] ; then
	    echo "$fname is a CHARACTER SPECIAL file..."  # sh ./shell8.sh /dev/fuse
	elif [ -b $fname ] ; then
	    echo "$fname is a BLOCK SPECIAL file..." # sh ./shell8.sh /dev/loop0
	fi
else
	echo "$fname is NOT existing..."  # sh ./shell8.sh mytest1.txt
fi

echo "\n\nEnd of the program..."
