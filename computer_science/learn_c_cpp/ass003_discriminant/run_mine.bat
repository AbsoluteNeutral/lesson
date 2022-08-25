@REM gcc -Werror -Wall -Wextra -ansi -pedantic discriminant.c -o discriminant.exe
x86_64-w64-mingw32-gcc -Werror -Wall -Wextra -ansi -pedantic discriminant.c -o discriminant.exe
discriminant.exe < ./input/i1.txt > ./output/result1.txt
discriminant.exe < ./input/i2.txt > ./output/result2.txt
discriminant.exe < ./input/i3.txt > ./output/result3.txt
discriminant.exe < ./input/i4.txt > ./output/result4.txt
discriminant.exe < ./input/i5.txt > ./output/result5.txt
discriminant.exe < ./input/i6.txt > ./output/result6.txt

diff ./output/out1.txt ./output/result1.txt
diff ./output/out2.txt ./output/result2.txt
diff ./output/out3.txt ./output/result3.txt
diff ./output/out4.txt ./output/result4.txt
diff ./output/out5.txt ./output/result5.txt
diff ./output/out6.txt ./output/result6.txt

