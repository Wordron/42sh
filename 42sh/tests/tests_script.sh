#!/bin/bash

########### BASIC TEST ################

echo  -en "\033[95mBASIC TEST :\033[00m"; echo

# Test command slash
echo "Test command slash :"
echo "/bin/ls" | ./42sh > "tests/output_42sh.txt"
/bin/ls > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo  -en  "\033[92msuccess !\033[00m"; echo
else
    echo  -en  "\033[91mfailure !\033[00m"; echo
fi

# Test PATH
echo "Test PATH :"
echo "ls" | ./42sh > "tests/output_42sh.txt"
ls > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi


########### TEST CD ################

echo; echo  -en "\033[95mTEST CD :\033[00m"; echo

# Test cd && cd -
echo "Test cd && cd -:"
echo "cd tests; pwd; cd -; pwd" | ./42sh > "tests/output_42sh.txt"
(cd tests; pwd; cd -) > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi

# Test cd home
echo "Test cd home :"
echo "cd; pwd" | ./42sh > "tests/output_42sh.txt"
(cd ; pwd) > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi


########### TEST REDIRECTIONS ################

echo; echo  -en "\033[95mTEST REDIRECTIONS :\033[00m"; echo

# Test pipe
echo "Test pipe :"
echo "ls | grep fork" | ./42sh > "tests/output_42sh.txt"
(ls | grep fork) > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi

# Test simple right redirection
echo "Test > :"
echo "ls > tests/output_42sh.txt" | ./42sh
ls > "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi

# Test double right redirection
echo "Test >> :"
echo "ls >> tests/output_42sh.txt" | ./42sh
ls >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi

# Test simple left redirection
echo "Test < :"
echo "grep run < Makefile" | ./42sh > tests/output_42sh.txt
grep "run" < "Makefile" > "tests/reference.txt"; echo >> "tests/reference.txt"
cmp "tests/output_42sh.txt" "tests/reference.txt"
if [ $? -eq 0 ]
then
    echo -en "\033[92msuccess !\033[00m"; echo
else
    echo -en "\033[91mfailure !\033[00m"; echo
fi

