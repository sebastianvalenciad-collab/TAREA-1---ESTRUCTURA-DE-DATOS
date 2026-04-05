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
  Categoria* primera = list_first(categorias);

  if(primera == NULL)
  {
    printf("No hay categorias registradas.\n");
    return;
  }
  
  printf("Categorías:\n");
  printf("\n");
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
  if(primera == NULL)
  {
    printf("No hay tareas pendientes!\n");
    return;
  }
  while(primera != NULL)
  {
    printf("Categoria: %s\n",primera->categoria->nombre);
    printf("Descripcion: %s\n", primera->descripcion);
    printf("Hora: %d - %d\n",primera->hora.hora, primera->hora.minutos);
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
  printf("Hora: %d - %d\n",primera->hora.hora, primera->hora.minutos);
  printf("\n");
  list_popFront(tareas);
  free(primera->descripcion);
  free(primera);
}

void sumar_hora(Hora *actual)
{
  actual->minutos += 5;
  if(actual->minutos == 60)
  {
    actual->minutos = 0;
    actual->hora += 1;
    if(actual->hora == 25)
    {
      actual->hora = 0;
    }
  }
}

bool verificar_categoria(char *nombre, List *categorias)
{
  Categoria* primera = list_first(categorias);
  while(primera != NULL)
  {
    if(strcmp(primera->nombre, nombre) == 0)
    {
      return true;
    }
  }
  return false;
}

void filtrar_categorias(List *tareas, List *categorias)
{
  Categoria* primera = list_first(categorias);
  if(primera == NULL)
  {
    printf("No hay categorias registradas.\n");
    return;
  }
  printf("Categorias disponibles:\n");
  printf("\n");
  while(primera != NULL)
  {
    printf(" - %s\n", primera->nombre);
    primera = list_next(categorias);
  }
  printf("\n");
  
  char nombreCategoria[256];
  printf("Ingresar nombre de la categoria que deseas filtrar: ");
  scanf(" %[^\n]", nombreCategoria);

  if(verificar_categoria(nombreCategoria, categorias))
  {
    printf("\n");
    int contador = 0;
    Tarea* first = list_first(tareas);
    while(first != NULL)
    {
      if(strcmp(nombreCategoria, first->categoria->nombre) == 0)
      {
        printf(" - Descripcion: %s\n", first->descripcion);
        printf(" - Hora: %d - %d\n", first->hora.hora, first->hora.minutos);
        printf("\n");
        contador += 1;
      }
      first = list_next(tareas);
    }
    if(contador == 0)
    {
      printf("No hay pendientes registradas con esta categoria.\n");
    }
  }
  
}

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  List *tareas = list_create(); // Lista que usaremos como cola, osea agregaremos al final de esta
  Hora hora_actual; 
  hora_actual.hora = 8; // Durante la ejecucion del codigo, cada vez que termine una operacion se
  hora_actual.minutos = 0; // le sum 5 minutos hastas llegar a 60, ahi se reinicia y se suma 1 a hora
  
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_categorias(categorias);
      sumar_hora(&hora_actual);
      break;
    case '2':
      eliminar_categoria(categorias, tareas);
      sumar_hora(&hora_actual);
      break;
    case '3':
      mostrar_categorias(categorias);
      sumar_hora(&hora_actual);
      break;
    case '4':
      registrar_pendiente(tareas, categorias, hora_actual);
      sumar_hora(&hora_actual);
      break;
    case '5':
      atender_siguiente(tareas);
      sumar_hora(&hora_actual);
      break;
    case '6':
      mostrar_tablero(tareas);
      sumar_hora(&hora_actual);
      break;
    case '7':
      filtrar_categorias(tareas, categorias);
      sumar_hora(&hora_actual);
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
