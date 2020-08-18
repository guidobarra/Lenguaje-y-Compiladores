#include "../archivos_punto_h/assembler.h"
#include "../archivos_punto_h/constantes.h"

int numEtiqNoEsMayor = -1;

void generarAssembler(t_array_terceto t) {
	if (generarHeader() == 1) {
		printf("Error al generar el assembler");
		return;
	}
    
	if (generarInstrucciones(t) == 1) {
		printf("Error al generar el assembler");
		return;	
	}

	if (generarData() == 1) {
		printf("Error al generar el assembler");
		return;
	}

    if (generarFooter() == 1) {
		printf("Error al generar el assembler");
		return;
	}

    if (generarArchivoAssemblerFinal() == 1) {
		printf("Error al generar el assembler");
		return;
    }
}

int generarArchivoAssemblerFinal() {
    FILE * fpFinal = fopen("./assembler/Final.asm", "w");

    char buffer[100];
	
    if (fpFinal == NULL) {
		printf("Error al abrir el archivo final.asm");
		return 1;
	}

    setFile(fpFinal, "./assembler/header.txt", buffer);
    setFile(fpFinal, "./assembler/data.txt", buffer);
    setFile(fpFinal, "./assembler/instrucciones.txt", buffer);
    setFile(fpFinal, "./assembler/footer.txt", buffer);

    fclose(fpFinal);
    return 0;
}

int setFile(FILE* fpFinal, char * nameFile, char* buffer){
    FILE * file = fopen( nameFile, "r");

	if (file == NULL) {
		printf("Error al abrir el archivo %s", nameFile);
		return 1;
	}

    while(fgets(buffer, sizeof(buffer), file)) {
        fprintf(fpFinal, "%s", buffer);
    }

    fclose(file);
}

int generarHeader() {
	FILE * fp = fopen("./assembler/header.txt", "w");
	if (fp == NULL) {
		printf("Error al abrir el archivo header");
		return 1;
	}

	fprintf(fp, "INCLUDE macros2.asm\n");
    fprintf(fp, "INCLUDE number.asm\n");
    fprintf(fp, ".MODEL LARGE\n");
    fprintf(fp, ".386\n");
    fprintf(fp, ".STACK 200h\n"); 
    fclose(fp);
    return 0;
}

int generarData() {
	FILE * fp = fopen("./assembler/data.txt", "wt+");
	if (fp == NULL) {
		printf("Error al abrir el archivo data");
		return 1;
	}

	fprintf(fp, "\t.DATA\n");    
    fprintf(fp, "\tTRUE equ 1\n");
    fprintf(fp, "\tFALSE equ 0\n");
    fprintf(fp, "\tMAXTEXTSIZE equ %d\n", 200);

    //Aca va la tabla de simbolo con todos los auxiliares
    int i;
    int a = getPosicionTS();
    for (i = 0; i < a; i++) {
        if (tablaSimbolos[i].tipo == CTE_STRING)
            fprintf(fp, "%-32s\tdb\t%s,'$', %s dup (?)\n", getNombre(i), tablaSimbolos[i].valor,
                    tablaSimbolos[i].longitud);
        else
            fprintf(fp, "%-32s\tdd\t%s\n", getNombre(i), verSiVaInterrogacion(tablaSimbolos[i].valor));
    }

    fprintf(fp, "\n.CODE\n");
    fclose(fp);
    return 0;
}

int generarFooter() {
	FILE * fp = fopen("./assembler/footer.txt", "w");
	if (fp == NULL) {
		printf("Error al abrir el archivo fotter");
		return 1;
	}

    
    fprintf(fp, "\nliberar:\n");
    fprintf(fp, "\tffree\n");
	fprintf(fp, "\tmov ax, 4c00h\n");
    fprintf(fp, "\tint 21h\n");
    fprintf(fp, "\tjmp fin\n");

    fprintf(fp, "fin:\n");
    fprintf(fp, "\tEnd START\n"); 

    fclose(fp);
    return 0;
}

char *getNombre(const int i) {
    if (tablaSimbolos[i].tipo == T_INTEGER || 
        tablaSimbolos[i].tipo == T_FLOAT ||
        tablaSimbolos[i].tipo == T_STRING
    ) {
        return tablaSimbolos[i].nombre;
    }
    return aConstante(tablaSimbolos[i].nombre);
}

char * verSiVaInterrogacion(char *valor) {
    if (strcmp(valor, "") == 0) {
        return "?";
    }
    return valor;
}

int generarInstrucciones(t_array_terceto t) {
	FILE * fp = fopen("./assembler/instrucciones.txt", "wt+");
	if (fp == NULL) {
		printf("Error al abrir el archivo instrucciones");
		return 1;
	}

    
    fprintf(fp, "\nSTART:\nMOV AX,@DATA\nMOV DS,AX\nMOV es,ax\nFINIT\nFFREE\n\n");
	recorreArbolAsm(fp, t);
	fclose(fp);
	return 0;

}

void recorreArbolAsm(FILE * fp, t_array_terceto t) {
    int idx = 0;
    int idxNumeroTerceto = 0;
    char varInterna [50];
    for (;idx<t->cantElemTecetos; idx++) { 
        idxNumeroTerceto = getIndexNumero(t->tercetos[idx].d2);
        if (numEtiqNoEsMayor == idx ) {
            fprintf(fp, "no_es_mayor%d:\n",numEtiqNoEsMayor);
            numEtiqNoEsMayor = -1;
        }
        if(strcmp(t->tercetos[idx].d1, "=") == 0) {
            idxNumeroTerceto = getIndexNumero(t->tercetos[idx].d2);
            if (idxNumeroTerceto == -1) {
                fprintf(fp, "fild %s\n", t->tercetos[idx].d2);
            } else {
                fprintf(fp, "fild @aux%d\n", idxNumeroTerceto);
            }
            fprintf(fp, "fistp %s\n", t->tercetos[idx].d3);
        } else if (strcmp(t->tercetos[idx].d1, "/") == 0) {
            
            sprintf(varInterna, "@aux%d", idx);
            fprintf(fp, "fild %s\n", t->tercetos[idx].d2);
            fprintf(fp, "fild %s\n", t->tercetos[idx].d3);
            fprintf(fp, "fdiv\n");
            fprintf(fp, "fistp %s\n", varInterna);
            
            tsInsertarToken(typeDecorator(T_INTEGER), varInterna, "", 0);
        } else if (strcmp(t->tercetos[idx].d1, "write") == 0) {

            if (tsObtenerTipo(t->tercetos[idx].d2) == CTE_STRING) {
                fprintf(fp, "displayString %s\n", aConstante(t->tercetos[idx].d2));
            } else {
                fprintf(fp, "DisplayInteger %s\n", t->tercetos[idx].d2);
                fprintf(fp, "newLine 1\n");
            }
            
        } else if (strcmp(t->tercetos[idx].d1, "read") == 0) {
            fprintf(fp, "GetInteger %s\n", t->tercetos[idx].d2);
        } else if (strcmp(t->tercetos[idx].d1, "CMP") == 0) {
            fprintf(fp, "fild %s\n", t->tercetos[idx].d2);
            fprintf(fp, "fild %s\n", t->tercetos[idx].d3);
            fprintf(fp, "fcom\n");
            fprintf(fp, "fstsw ax\n");
            fprintf(fp, "sahf\n");
        } else if (strcmp(t->tercetos[idx].d1, "JNB") == 0) {
            numEtiqNoEsMayor = getIndexNumero(t->tercetos[idx].d2);
            fprintf(fp, "JNB no_es_mayor%d\n", numEtiqNoEsMayor);
        } else {
            fprintf(fp, "fild %s\n", t->tercetos[idx].d1);
        }
    }
    
}