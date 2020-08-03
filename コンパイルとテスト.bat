@echo off
echo mainapp.c⇒mainapp.exe	コンパイルを開始、テストを実行します
call gcc mainapp.c -g -o mainapp.exe
	echo コンパイル完了
	echo;
	echo プログラムを起動します
	pause
	mainapp
echo;
echo;
pause