@REM gcc -Werror -Wall -Wextra -ansi -pedantic coin_counter.c -o coin_counter.exe
x86_64-w64-mingw32-gcc -Werror -Wall -Wextra -ansi -pedantic coin_counter.c -o coin_counter.exe
coin_counter.exe < ./input/test1.txt > ./output/result1.txt
coin_counter.exe < ./input/test2.txt > ./output/result2.txt
coin_counter.exe < ./input/test3.txt > ./output/result3.txt
coin_counter.exe < ./input/test4.txt > ./output/result4.txt
coin_counter.exe < ./input/test5.txt > ./output/result5.txt
coin_counter.exe < ./input/test6.txt > ./output/result6.txt
coin_counter.exe < ./input/test7.txt > ./output/result7.txt
coin_counter.exe < ./input/test8.txt > ./output/result8.txt

diff ./output/out1.txt ./output/result1.txt
diff ./output/out2.txt ./output/result2.txt
diff ./output/out3.txt ./output/result3.txt
diff ./output/out4.txt ./output/result4.txt
diff ./output/out5.txt ./output/result5.txt
diff ./output/out6.txt ./output/result6.txt
diff ./output/out7.txt ./output/result7.txt
diff ./output/out8.txt ./output/result8.txt
