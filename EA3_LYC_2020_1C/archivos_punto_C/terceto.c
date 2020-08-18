#include "../archivos_punto_H/terceto.h"

int crearTerceto(const char* dato1, const char* dato2, const char* dato3, t_array_terceto t) {
    int idx = t->cantElemTecetos;
    t_terceto nuevoTerceto;
    strcpy(t->tercetos[idx].d1, dato1);
    strcpy(t->tercetos[idx].d2, dato2);
    strcpy(t->tercetos[idx].d3, dato3);
    return t->cantElemTecetos++;
}

void inicializarTerceto(t_array_terceto t) {
    t->cantElemTecetos = 0;
}

void imprimirTercetos(t_array_terceto t) {
    int i;
    printf("***/        IMPRIMIR TERCETOS          /***\n");
    for ( i = 0; i < t->cantElemTecetos; i++) {
        printf("[%d]-->(%s, %s, %s)\n",
                                    i ,
                                    t->tercetos[i].d1, 
                                    t->tercetos[i].d2, 
                                    t->tercetos[i].d3);
    }
    
}

void guardarTercetos(t_array_terceto t) {
    int i;
    FILE * fp = fopen("./Intermedia.txt", "w");
	if (fp == NULL) {
		printf("Error al abrir el archivo Intermedia");
		return ;
	}
    for ( i = 0; i < t->cantElemTecetos; i++) {
        fprintf(fp,"[%d]-->(%s, %s, %s)\n",
                                    i ,
                                    t->tercetos[i].d1, 
                                    tsObtenerTipo(t->tercetos[i].d2) == CTE_STRING? aConstante(t->tercetos[i].d2): t->tercetos[i].d2, 
                                    t->tercetos[i].d3);
    }
    fclose(fp);
}

char* getIndex(int index) {
    char buffer[10];
    sprintf(buffer, "[%d]", index);
    return strdup(buffer);
}

int getIndexNumero(char* s) {
    if (strncmp(s,"[",1) != 0) {
        return -1;
    }
    int i = 1;
    char num [20];
    for(;i<strlen(s)-1;i++){
        num[i-1] = s[i];
    }
    num[i-1] = '\0';    
    return atoi(num);
}
