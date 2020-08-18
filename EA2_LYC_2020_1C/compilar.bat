flex Lexico.l
pause
bison -dyv --debug Sintactico.y

gcc.exe lex.yy.c y.tab.c arbol_sintactico.c -o Primera.exe 
pause
Primera.exe prueba.txt
pause
dot -Tpng gragh.dot -o gragh.png
dot -Tpng graghPolaca.dot -o graghPolaca.png
pause
delete.bat

pause
