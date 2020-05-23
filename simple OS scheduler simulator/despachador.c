#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define bandera printf("banderita\n");
//<tiempo de llegada>, <prioridad>, <tiempo de procesador>, <#impresoras>, <#scanners>, <#modems>, <#DVDs>, tiempo_CPU_restant, QUATUM, PID, Recursos_asignados
//3, 3, 6, 1, 0, 1, 2

// La lista necesariamente debe estar ordenada por tiempos de llegada, porque mi algoritmo verifica El primero que se encuentre con las caracteristicas deseadas ausumiendo que estan insertados correlativamente


int cubo[4][50][11], nro_TR=0, nro_user_uno=0, nro_user_dos=0, nro_user_tres=0;

int contadores[4]; //donde i es la cola, [i] = cantidad de procesos que tiene,

int reloj=0;

int PID_proceso_anterior=-1,proceso_anterior_sin_quatum=0;

int matriz_recursos[4][2]; //totales - disponibles -- <#impresoras>, <#scanners>, <#modems>, <#DVDs>

void read_data (char * path) {

	FILE * file = fopen (path, "r");
	int cont=0, i, quantum;

	int process_data[7];

	while (1) {

		char str[2];
		fscanf(file,"%s",str);
		if (feof(file)) break;

		str[1]='\0';
		int d=atoi(str);

		if (d==44) continue; //si es una coma
		process_data[cont++]=d;

		// printf("%d", d);

		if (cont==7) {
			// printf("\n");

			int queue = process_data[1];
			int id_p = contadores[queue];

			for (i = 0; i < 7; i++) {
				// printf("%d ", process_data[i]);
				cubo[queue] [ id_p ] [i] = process_data[i] ;
			}

			// printf("\n");
			cubo[queue][id_p][7] = process_data[2] ; //tiempo CPU restante inicialmente es igual al tiempo CPU total

			switch (process_data[1]) { //determinar quatum segun cola de prioridad

				case 1:
					quantum=3;
					break;
				case 2:
					quantum=2;
					break;
				case 3:
					quantum=1;
					break;
			}

			cubo[queue][id_p][8] = quantum ; // asignar quatum actual a proceso

			contadores[queue]++;

			cont=0;
		}
	}

}

void inicializar_estructuras () {

	int i,j,k;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 50; j++) {
			for (k = 0; k < 11; k++) {
				cubo[i][j][k]=-1;
			}
		}

		contadores[i]=0;
	}

	matriz_recursos[0][0]=2;
	matriz_recursos[1][0]=1;
	matriz_recursos[2][0]=1;
	matriz_recursos[3][0]=2;

	for (k = 0; k < 10; k++) {
		matriz_recursos[k][1]=matriz_recursos[k][0];
	}

}

void mostrar_data () {

	int i,j,k;
	for (i = 0; i < 4; i++) {
		printf("cola %d:\n",i );
		for (j = 0; j < 5; j++) {

			printf("p%d : ",j);
			for (k = 0; k < 10; k++) {
				printf("%d, ",cubo[i][j][k] );
			}
			printf("\n");
		}

		contadores[i]=0;
	}
	printf("\n\n\n");
}

void mostrar_data2 () {

	int i,j,k;
	for (i = 0; i < 4; i++) {
		printf("cola %d:\n",i );
		for (j = 0; j < contadores[i]; j++) {

			printf("p%d : ",j);
			for (k = 0; k < 10; k++) {
				printf("%d, ",cubo[i][j][k] );
			}
			printf("\n");
		}

		contadores[i]=0;
	}
	printf("\n\n\n");
}

void mostrar_contadores() {

	int i,j;

	for (i = 0; i < 4; i++) {
		printf("%d ",contadores[i]);
	}
}

struct process_info {
	int queue, id;
};

int es_ejecutable(int  queue, int id_p) { //Un Proceso es ejecutable si tiene todos los recursos disponibles, es su turno y su Tiempo de llegada <= tiempo reloj

	if (cubo[queue][id_p][10]==1) { // Si ya se le han asignado los recurso
		return 1;
	}

	if (cubo[queue][id_p][3]<=matriz_recursos[0][1]) { //la cantidad de impresoras que solicita esten disponibles

		if (cubo[queue][id_p][4]<=matriz_recursos[1][1]) {

			if (cubo[queue][id_p][5]<=matriz_recursos[2][1]) {

				if (cubo[queue][id_p][6]<=matriz_recursos[3][1]) { //dado que que tiene los recursos disponibles se le asignan y retorna 1 idicando que es ejecutable y todoslo recursos qu solicita han sido asignados

					matriz_recursos[0][1]-=cubo[queue][id_p][3];
					matriz_recursos[1][1]-=cubo[queue][id_p][4];
					matriz_recursos[2][1]-=cubo[queue][id_p][5];
					matriz_recursos[3][1]-=cubo[queue][id_p][6];

					return 1;
				}
			}
		}

	}

	return 0;

}

struct process_info * get_process (int reloj) {

	int i,j;
	struct process_info * aux =(struct process_info *) calloc(1,sizeof(struct process_info));
	for (i = 0; i < 4; i++) {

		for (j = 0; j < contadores[i]; j++) {

			if (cubo[i][j][0]!=-1 && cubo[i][j][0]<=reloj) {

				// printf("Tiempo llegada : %d  -- Tiempo reloj : %d\n",cubo[i][j][0],reloj);

				if (es_ejecutable(i,j))
				{
					// printf("Proceso a ejecutar econtrado en COLA: %d ID_P:%d\n", i,j);
					aux->queue=i; aux->id=j;

					return aux;
				}
			}
		}
	}

	return NULL;
}

void liberar_recursos (int queue, int id_p) {

	matriz_recursos[0][1]+=cubo[queue][id_p][3];
	matriz_recursos[1][1]+=cubo[queue][id_p][4];
	matriz_recursos[2][1]+=cubo[queue][id_p][5];
	matriz_recursos[3][1]+=cubo[queue][id_p][6];

}

void process_scheduler() {

	int tiempo;

	while (1) {

		// printf("Tiempo %d\n",reloj );
		sleep(1);
		reloj++;

		struct process_info * p = get_process(reloj);

		if (p==NULL) {
			continue;
		}

		#define proceso_prioridad  cubo[p->queue][p->id][1]
		#define proceso_tiempo_CPU cubo[p->queue][p->id][2]
		#define proceso cubo[p->queue][p->id]

		tiempo = (proceso_prioridad==0) ? proceso_tiempo_CPU : 1; // tiempo = (cubo[p->queue][p->id][1]) ? cubo[p->queue][p->id][2] : 1;
		int tiempo2=tiempo;

		pid_t pid=fork();

		if (pid==0) //child
		{
			char number_str[12];
			sprintf(number_str,"%d",tiempo);

			char * args [] = {"./child",number_str,NULL};
			execvp("./child",args);
		}
		else	//parent
		{
			if (PID_proceso_anterior!= pid && PID_proceso_anterior!=proceso[9] && PID_proceso_anterior!=-1)
			{
				printf("Proceso con PID : %d ha sido suspendido\n\n",PID_proceso_anterior);
				proceso_anterior_sin_quatum=0;
			}


			if (proceso[7]==proceso[2]) {	// Si su tiempo de CPU restante = tiempo total CPU, entonces esta iniciando
				printf("Proceso con PID : %d ha empezado\n",pid);
				// printf("\tI'm the process %d , prioridad : %d , queamtum : %d \n",proceso[9],proceso[1],proceso[8] );
				proceso[9]=pid; //Asignar PID de procesos
				proceso[10]=1;
				PID_proceso_anterior=pid;
			}
			// || (proceso[7]>0 && PID_proceso_anterior==proceso[9] && proceso_anterior_sin_quatum==1 )
			if ((proceso[7]>0 && PID_proceso_anterior!=proceso[9])) {	// Si el proceso no ha terminado su, ejecucion y es distintos al proceso anterior en la CPU, entonces este continua
				printf("Proceso con PID : %d Continua\n",proceso[9] );

			}
			if (proceso[7]>0 && PID_proceso_anterior==proceso[9] && proceso_anterior_sin_quatum==1) {	// Si el proceso no ha terminado su, ejecucion y es distintos al proceso anterior en la CPU, entonces este continua
				printf("Proceso con PID : %d Continua\n",proceso[9] );
				proceso_anterior_sin_quatum=0;
			}
			PID_proceso_anterior=proceso[9];

			waitpid(pid,NULL); //wait child

			printf("\t PID : %d ejecutando\n", proceso[9]);


			if (proceso[7]>0) {	//Tiempo de ejecucion =  tiempo de ejecucion - 1
				proceso[7]-=1;
			}

			if (proceso[7]==0) { //tiempo cpu restante es igual a cero, es decir, si termino
				printf("Proceso con PID : %d Ha terminado su ejecucion\n\n",proceso[9]);
				proceso[0]=-1; //quito de cubo
				liberar_recursos(p->queue,p->id);
				PID_proceso_anterior=-1; // Indica que este proceso a terminado su ejecucion, me permite verificar quien ha sido suspendido
				continue;
			}


			if (proceso[8]>0) { //si el queatum del proceso es mayor a cer estonces le resto uno
				proceso[8]-=1;
				// printf("\tI'm the process %d , prioridad : %d , queamtum : %d \n",proceso[9],proceso[1],proceso[8] );
			}

			if (proceso[8]==0) { //si se le acabo el quatum, actualizar prioridad y quatum

				proceso_anterior_sin_quatum=1;
				printf("Proceso con PID : %d Suspendido debido a interrupcion de reloj\n\n",proceso[9]);
				// printf("\tI'm the process %d , prioridad : %d , queamtum : %d \n",proceso[9],proceso[1],proceso[8] );
				switch (proceso[1]) {	//actualizar quatum en base a su prioridad
					case 1:
						proceso[8]=2;
						break;
					case 2:
						proceso[8]=1;
						break;
					case 3:
						proceso[8]=1;
						break;
				}

				proceso[1] = (proceso[1]>0 && proceso[1]<3) ? proceso[1]+1 : proceso[1]; //bajar prioridad

			// printf("\t\tI'm the process %d , prioridad : %d , queamtum : %d \n",proceso[9],proceso[1],proceso[8] );
			}


		}

	}
}

int main(int argc, char *argv[])
{

	inicializar_estructuras();
	 read_data(argv[1]);
	process_scheduler();


	return 0;
}
