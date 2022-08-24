gcc lab1.c -o lab1.exe 
lab1.exe < ./input/test1.txt > ./output/result1.txt
lab1.exe < ./input/test2.txt > ./output/result2.txt
lab1.exe < ./input/test3.txt > ./output/result3.txt
lab1.exe < ./input/test4.txt > ./output/result4.txt

diff ./output/out1.txt ./output/result1.txt
diff ./output/out2.txt ./output/result2.txt
diff ./output/out3.txt ./output/result3.txt
diff ./output/out4.txt ./output/result4.txt
