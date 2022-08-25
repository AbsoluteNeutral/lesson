@REM gcc -Werror -Wall -Wextra -ansi -pedantic advance_coin_counter.c -o advance_coin_counter.exe
x86_64-w64-mingw32-gcc -Werror -Wall -Wextra -ansi -pedantic advance_coin_counter.c -o advance_coin_counter.exe
advance_coin_counter.exe < ./input/i1.txt > ./output/result1.txt
advance_coin_counter.exe < ./input/i2.txt > ./output/result2.txt
advance_coin_counter.exe < ./input/i3.txt > ./output/result3.txt
advance_coin_counter.exe < ./input/i4.txt > ./output/result4.txt
advance_coin_counter.exe < ./input/i5.txt > ./output/result5.txt
advance_coin_counter.exe < ./input/i6.txt > ./output/result6.txt
advance_coin_counter.exe < ./input/i7.txt > ./output/result7.txt
advance_coin_counter.exe < ./input/i8.txt > ./output/result8.txt
advance_coin_counter.exe < ./input/i9.txt > ./output/result9.txt
advance_coin_counter.exe < ./input/i10.txt > ./output/result10.txt
advance_coin_counter.exe < ./input/i11.txt > ./output/result11.txt
advance_coin_counter.exe < ./input/i12.txt > ./output/result12.txt

diff ./output/out1.txt ./output/result1.txt
diff ./output/out2.txt ./output/result2.txt
diff ./output/out3.txt ./output/result3.txt
diff ./output/out4.txt ./output/result4.txt
diff ./output/out5.txt ./output/result5.txt
diff ./output/out6.txt ./output/result6.txt
diff ./output/out7.txt ./output/result7.txt
diff ./output/out8.txt ./output/result8.txt
diff ./output/out9.txt ./output/result9.txt
diff ./output/out10.txt ./output/result10.txt
diff ./output/out11.txt ./output/result11.txt
diff ./output/out12.txt ./output/result12.txt
