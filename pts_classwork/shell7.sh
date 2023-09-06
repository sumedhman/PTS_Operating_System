# command line arguments
echo $0 $1 $2 $3
echo $$
echo $#
echo $*

# $1, $2, $3, $4 ... are command line arugments in order
# $$ is the current process identification number
# $# number of command line arguments excuding the file name
# $* prints all the command line arguments in the form of a string

# Inputs and Outputs -
# sh ./shell7.sh Amitava Developer Pune 85000
# ./shell7.sh Amitava Developer Pune
# 2603
# 4
# Amitava Developer Pune 85000

