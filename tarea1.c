#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
  int hora;
  int minutos;
} Hora;

typedef struct
{
  char *nombre;
} Categoria;

typedef struct 
{
  char *descripcion;
  Categoria* categoria;
  Hora hora;
} Tarea;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Planificador de Tareas");
  puts("========================================");

  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Pendiente");
  puts("5) Atender Siguiente");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}

void registrar_categorias(List *categorias) 
{
  printf("Registrar nueva categoría\n");
  // Aquí implementarías la lógica para registrar una nueva categoría
  
  char nombre[256];
  printf("Ingresar nombre de la Categoria: ");
  scanf(" %[^\n]", nombre);

  Categoria* primero = list_first(categorias);
  while(primero != NULL)
  {
    if(strcmp(primero->nombre, nombre) == 0) // Existe una categoria con ese nombre
    {
      printf("Esta categoria ya existe.\n");
      return;
    }
    primero = list_next(categorias);
  }
  
  Categoria* nuevaCategoria = malloc(sizeof(Categoria));
  nuevaCategoria->nombre = malloc(strlen(nombre) + 1);
  strcpy(nuevaCategoria->nombre, nombre);

  list_pushBack(categorias, nuevaCategoria);
  printf("Categoria agregada correctamente.\n");
}

void mostrar_categorias(List *categorias) {
  // Mostrar categorías
  printf("Categorías:\n");
  Categoria* primera = list_first(categorias);
  while(primera != NULL)
  {
    printf("  - %s\n", primera->nombre);
    primera = list_next(categorias);
  }
}

void eliminar_tareas(List *tareas, char *nombre)
{
  Tarea* primera = list_first(tareas);
  while(primera != NULL)
  {
    if(strcmp(primera->categoria->nombre,nombre) == 0)
    {
      free(primera->descripcion);
      free(primera);
      list_popCurrent(tareas);
      primera = list_next(tareas);
    }
    primera = list_next(tareas);
  }
    
}

void eliminar_categoria(List *categorias, List *tareas)
{
  char nombre[256];
  printf("Ingresar Categoria que deseas eliminar: ");
  scanf(" %[^\n]", nombre);

  Categoria* primera = list_first(categorias);
  while(primera != NULL)
  {
    if(strcmp(primera->nombre, nombre) == 0) // comparamos si son iguales
    {
      eliminar_tareas(tareas, nombre);
      free(primera->nombre); // Liberamos memoria
      free(primera);
      list_popCurrent(categorias);
      printf("Categoria eliminada.\n");
      return;
    }
    primera = list_next(categorias); // pasamos a la siguiente
  }
  printf("Esa Categoria no existe.\n");
}

void registrar_pendiente(List *tareas, List *categorias, Hora hora_actual)
{
  char descripcion[256];
  printf("Ingresar Descripcion de la tarea: ");
  scanf(" %[^\n]", descripcion);

  char nombreCategoria[256];
  printf("Ingresar Categoria de la tarea: ");
  scanf(" %[^\n]", nombreCategoria);

  Categoria *primera = list_first(categorias);
  Categoria *elegida= NULL;

  while(primera != NULL)
  {
    if(strcmp(primera->nombre, nombreCategoria) == 0)
    {
      elegida = primera;
      break;
    }
    primera = list_next(categorias);
  }

  if(elegida == NULL)
  {
    printf("%s no es una categoria valida.\n", nombreCategoria);
    return;
  }
  
  // Agregamos la descripcion
  Tarea* pendiente = malloc(sizeof(Tarea));
  pendiente->descripcion = malloc(strlen(descripcion) + 1);
  strcpy(pendiente->descripcion, descripcion);

  pendiente->categoria = elegida;
  pendiente->hora = hora_actual;
  list_pushBack(tareas, pendiente);
  printf("Tarea agregada correctamente.\n");
}

void mostrar_tablero(List *tareas)
{
  Tarea* primera = list_first(tareas);
  while(primera != NULL)
  {
    printf("Categoria: %s\n",primera->categoria->nombre);
    printf("Descripcion: %s\n", primera->descripcion);
    printf("\n");
    primera = list_next(tareas);
  }
}

void atender_siguiente(List *tareas)
{
  Tarea* primera = list_first(tareas);
  if(primera == NULL)
  {
    printf("¡Libre de pendientes!\n");
    return;
  }
  printf("Categoria: %s\n",primera->categoria->nombre);
  printf("Descripcion: %s\n", primera->descripcion);
  printf("Hora: \n");
  printf("\n");
  list_popFront(tareas);
  free(primera->descripcion);
  free(primera);
}

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  List *tareas = list_create(); // Lista que usaremos como cola, osea agregaremos al final de esta
  Hora hora_actual; 
  hora_actual.hora = 0; // Durante la ejecucion del codigo, cada vez que termine una operacion se
  hora_actual.minutos = 0; // le sum 1 a minuto hastas llegar a 60, ahi se reinicia y se suma 1 a hora
  
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_categorias(categorias);
      break;
    case '2':
      eliminar_categoria(categorias, tareas);
      break;
    case '3':
      mostrar_categorias(categorias);
      break;
    case '4':
      registrar_pendiente(tareas, categorias, hora_actual);
      // crear funcion para actualizar la hora
      break;
    case '5':
      atender_siguiente(tareas);      
      break;
    case '6':
      mostrar_tablero(tareas);
      break;
    case '7':
      // Lógica para filtrar por categoría
      break;
    case '8':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  list_clean(categorias);

  return 0;
}
