flex Lexico.l
pause
bison -dyv --debug Sintactico.y
pause
gcc.exe lex.yy.c y.tab.c archivos_punto_C/* -o Primera.exe 
pause
Primera.exe prueba.txt
pause
delete.bat
pause
