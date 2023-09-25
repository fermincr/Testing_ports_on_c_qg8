//Fermin Covarrubias Ramos - 20110309 - 8k
//Practica el cual probamos las cualidades del QG8 y mandamos un patron de luces LED con cambio y velocidad

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
//se definen nuestros botones para facilidad de manipulacion
#define boton1 PTAD_PTAD2 
#define boton2 PTAD_PTAD3

 /* el orden no importa*/
void MCUinit(void); //inicializar puertos
void velocidad (void); //manejo de la frecuencia a la que iran nuestros leds
void primermodo(void); //primer patron de leds
void segundomodo(void); //segundo patron de leds
void accion1(void); //acciones las cuales tomara nuestro codigo ante peticiones con botones en la clase de velocidad
void accion2(void); //acciones las cuales tomara nuestro codigo ante peticiones con botones en la clase de velocidad
void check(void); //verificacion de el funcionamiento correcto de las frecuencias.
void retardo(void); //delay al termino y en las pulsaciones de los botones para tener tiempo de hacer las acciones.

unsigned int momentum; //variable para seleccionar el modo de velocidad
unsigned int tiempo; //variable para manejar las frecuencias de nuestras velocidades de patrones
unsigned int botonrecordar; //recordatorio de cuantas pulsaciones se hicieron para el cambio de patron


void main(void) {
SOPT1=0x12; //Quitar WATCHDOG
MCUinit(); //inicializacion de puertos
momentum = 0x00; //iniciamos la variable de velocidad en 0


for(;;) {
	check(); //empezamos buscando el estado del patron
	retardo(); //delay para ver claro el proceso
	velocidad(); //entra la clase de velocidad para saber a cuanto se mostrara el patron
	retardo(); //delay para ver claro el proceso
  } /* loop forever */
  /* please make sure that you never leave main */
}



void MCUinit(void)
{
	PTBDD=0xFF; //hacer salidas PTBD
	PTBD = 0x00; //Activamos las entradas en 0
	PTBD_PTBD6=0; //Encender el LED
	PTBD_PTBD7=0; //Encender el LED
	PTAPE = 0x01; //PTA0 y PTA1 en modo resistencias pullup
	PTADD = 0x00; //inicializar puertos A en entradas
	PTAD = 0x00; //Activamos las entradas en 1
	
}



void velocidad (void)
{
	unsigned int m = momentum; //asignamos nuestra variable a un nombre mas corto para su facil manejo
	if(m>2){ //si esta vale mas de 2
		momentum = 0x00; //se reseteara
		PTBD_PTBD7=0; //Encendera el LED del qg8
		
	}else{//sino
	if (m==0){ //si vale 0...
		tiempo = 0xFFFF; //pondra el valor de la velocidad del patron en lo mas bajo posible
	}else if (m==1){ //si esta en 1...
		tiempo = 0x7FFF; //pondra el valor de la velocidad del patron en velocidad media
	}else if (m==2){ //si esta en 2...
		tiempo = 0x2FFF; //pondra el valor de la velocidad del patron en lo mas alto posible
	}
	while (tiempo!=0){ //mientras que chequea esos datos, a su vez si el valor del tiempo no es igual a 0..
		tiempo = tiempo-1; //restara 1 al valor progresivamente
		if (boton2==0){ //si el boton 2 del QG8 esta activo...
			  retardo(); ////delay para ver claro el proceso
			accion1(); //activa la accion1 del sistema
		}else if (boton1==0){ //si el boton 1 del QG8 esta activo..
			  retardo(); //delay para ver claro el proceso
			accion2(); //activa la accion2 del sistema
	}
}
}
}

void primermodo(void){ //clase del primer modo de nuestro patron
	unsigned char w; //elegimos la W para el uso de conteo de datos
	unsigned char seccion[5]={0x14 ,0x15 , 0x12 , 0x1C}; //este seria el orden de como encenderian los leds de forma hexadecimal
	
	for (w=0; w<=5; w++){ //para 4 objetos en nuestro array, desde izquierda a derecha y agregando valor a la w...
		PTBD = seccion[w]; //va a equivaler a una agregacion a los puertos B con la variable W.
		PTBD_PTBD6=1; //Apagar el LED
		PTBD_PTBD6=0; //Encender el LED
		velocidad(); //brinca hacia la clase de velocidad.

	}
}

void segundomodo(void){ //clase del primer modo de nuestro patron
	unsigned char w; //elegimos la W para el uso de conteo de datos
	unsigned char seccion[5]={0x1F ,0x03 , 0x0F , 0x0C}; //este seria el orden de como encenderian los leds de forma hexadecimal
	
	for (w=0; w<=5; w++){ //para 4 objetos en nuestro array, desde izquierda a derecha y agregando valor a la w...
		PTBD = seccion[w];  //va a equivaler a una agregacion a los puertos B con la variable W.
		PTBD_PTBD7=1; //Apagar el LED
		PTBD_PTBD7=0; //Encender el LED
		velocidad(); //brinca hacia la clase de velocidad.
	}
}

void accion1(void){ //clase de nuestra accion en el boton2 del QG8
	
		momentum = momentum+1; //Agrega valores a nuestra variable de conteo de velocidad
		  retardo(); //delay para ver claro el proceso
		velocidad(); //brinca hacia la clase de velocidad.
	}

void accion2(void){ //clase de nuestra accion en el boton1 del QG8
		botonrecordar = botonrecordar+1; //Agrega valores a nuestra variable de conteo de patrones de leds
		  retardo(); //delay para ver claro el proceso
		check(); //brinca hacia la clase de chequeo de variables de patrones.
	}


void check(void){ //clase de registro de conteo de que patron se elegira
	if (botonrecordar >= 2){ //si la variable de valor de nuestra clase de patrones vale 2...
		botonrecordar = 0; //se reiniciara la variable a 0
    }else if (botonrecordar == 1){ //si la variable de valor de nuestra clase de patrones vale 1...
		segundomodo(); //saltara al segundo patron de nuestro sistema
	}else{ //sino...
		botonrecordar = 0; //se reiniciara la variable a 0
		primermodo(); //y brincara hacia el primer patron de nuestro sistema.
	}
}


void retardo(void) //clase de delay
{
	unsigned int x=0xFFFF; //inicio de nuestra variable x en el valor mas alto.
	while(x!=0) //mientras sea indiferente de 0...
	{
		x=x-1; //va a ir restando a la variable.
		
	}
}
