//sample
//put,114514
#define,PICTURE,95
#forwin		//windows限定追加機能を付けます
num,ieaaa=8.10//numは実数型の変数です
num,yey=5
num,printf
str,kyaragata,10
label,exsample
  //file.e
put,34hf6@n	//@nで改行します
info
			
put,神様！！！//ここはコメントだから見えないよ
if,12!=345{
	put,こんにち！@@114514//@@で@を表示させます
}
put,ABCD\EFGH//\は普通に表示できます
put,ソ連@n//0x5c問題なんてありません
put,入力→//
in,ieaaa
put,!ieaaa!秒待って！@n
wait,ieaaa//待たせることもできます
put,%d\n'win"lose?//%d\n'win"lose?って打ってもそのまま出ます
put,@/スラッシュの表示@/@/@///スラッシュは@/で表示できます
put,カンマの表示→@,できてる！@n//カンマは@,で表示できます
put,!yey!は!yey!です@n
put,変数ieaaaの値は!ieaaa!です@n//変数の値も表示できます
put,実数値の入力→
in,ieaaa
if,ieaaa=0,put,ieaaaは!ieaaa!でしたぁ！！！@n
if,0~5=ieaaa,put,ieaaaは0から5です@n
put,入力した値は!ieaaa!です、!ieaaa!ですよ!!そしてyeyの値は!yey!です！！！//!!で!を表示します
put,@n何かキーを押して終了します
pause
	exit,2
//fegtwe