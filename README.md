## Descripcion
Este programa permite a los usuarios gestionar sus pendientes, ayudándolos a optimizar su tiempo. En él, se puede elegir la categoría a la cual pertenece cada tarea, así como registrar nuevos pendientes. Además, permite visualizar todas las tareas y categorías ingresadas, y también eliminar tanto tareas como categorías.

## Como ejecutar el codigo
Este programa fue realizado en replit asi que les explicare como hacerlo funcionar en esta plataforma.
Para ejecutar la tarea1 primero debemos seguir los siguientes pasos:

1. Accede al repositorio de este codigo, y crea un nuevo repositorio usando el template
2. Coloca en la opción Import code or design. Luego importa desde Github.
3. Pega la dirección de tu repositorio y luego impórtalo (Import from Github).
4. Agrega una pestaña “Shell”
5. y ejecuta los siguientes codigos:
````
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
````

Y luego ejecutar:
````
./tarea1
````

## Funcionalidades

En mi código utilicé una lista para manejar las categorías y otra lista, utilizada como cola, para operar sobre las tareas.
Tambien desarrolle las siguientes funcionalidades, las cuales todas estan operativas:

- Registrar categorias
- Eliminar categorias
- Mostrar categorias
- Registrar pendiente / tarea
- Atender pendiente
- Visualizacion de datos
- Filtrado por categoria

## Ejemplo de uso

Paso 1: Registrar una nueva Categoria
Una vez ejecutado el programa escribimos 1. Luego nos pediran el nombre de la categoria e ingresamos nuestra respuesta. En este caso inscribimos la categoria Casa.

<img width="344" height="314" alt="image" src="https://github.com/user-attachments/assets/778e18c1-bbdc-4b76-987a-eafd280a5292" />

Paso 2: Eliminar categoria
Luego de ingresar una categoria es posible eliminarla, para esto primero escribimos 2. Una vez dentro de la funcionalidad, escribimos el nombre de la categoria que deseamos eliminar y hacemos enter. En este caso eliminamos la categoria antes incrita "Casa".

<img width="375" height="260" alt="image" src="https://github.com/user-attachments/assets/ef8b7ccc-4755-44ec-b537-4cc38f633b64" />

Paso 3: Mostrar categorias
Tambien podemos ver cuales son las categorias que hemos ingresado, para esto seleccionamos la opcion 3. Aqui nos muestra todas las categorias incritas, en este caso son Oficina y Universidad.

<img width="343" height="290" alt="image" src="https://github.com/user-attachments/assets/26c90d4b-3c73-4afa-b395-3851f6bf9ac0" />

Paso 4: Registrar pendiente
Para registrar un pendiente, debemos seleccionar la opcion 4. Luego nos pedira la descripcion de la tarea que queremos hacer y la categoria a la cual pertenece la tarea, despues solo hacemos enter y se guardara. Nuestra tarea en este caso es estudiar en el IBc y esta se guardara con la categoria universidad.

<img width="437" height="276" alt="image" src="https://github.com/user-attachments/assets/3f394f0e-9d2b-4e47-b087-fa63b6ba8383" />

Paso 5: Atender tarea
Para vaciar la lista de tareas, seleccionamos la opcion 5. Luego el programa eliminara la tarea que lleva mas tiempo sin hacer, ya que esta ya fue atendida. En este caso es "estudiar en el ibc" ya que fue la ultima que ingresamos.

<img width="315" height="246" alt="image" src="https://github.com/user-attachments/assets/c97b715e-a757-435b-9c2b-5ee690562a94" />

Paso 6: Visualizar tablero
Para ver todas las tareas que quedan por hacer, seleccionamos la opcion 6.

<img width="376" height="360" alt="image" src="https://github.com/user-attachments/assets/61d24f4b-4e27-4a91-8383-32aa6608b87c" />

Paso 7: Filtrar por categoria
Para poder ver todas las tareas pendientes de una categoria especifica, seleccionamos la opcion 7. Primero el programa nos mostrara todas las categorias disponibles y nos pedira que ingresemos el nombre de la categoria que deseamos filtrar.

<img width="490" height="392" alt="image" src="https://github.com/user-attachments/assets/2ae997cb-5daa-4c2a-8864-ad54b6969518" />

Paso 8: Salir
Para poder terminar de ejecutar el programa solo seleccionamos la opcion 8.




