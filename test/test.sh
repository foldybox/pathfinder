# test.sh



printf "\n\033[32;1mTEST 00\033[0m\n"
rm user/test00
../pathfinder test00 > user/test00
printf "user output and test output\n"
diff user/test00 test/test00 | grep "^>" | wc -l
diff $@ user/test00 test/test00

printf "\n\033[32;1mTEST 01\033[0m\n"
rm user/test01
../pathfinder test01 > user/test01
printf "user output and test output\n"
diff user/test01 test/test01 | grep "^>" | wc -l
diff $@ user/test01 test/test01

printf "\n\033[32;1mTEST 02\033[0m\n"
rm user/test02
../pathfinder test02 > user/test02
printf "user output and test output\n"
diff user/test02 test/test02 | grep "^>" | wc -l
diff $@ user/test02 test/test02

printf "\n\033[32;1mTEST 03\033[0m\n"
rm user/test03
../pathfinder test03 > user/test03
printf "user output and test output\n"
diff user/test03 test/test03 | grep "^>" | wc -l
diff $@ user/test03 test/test03
