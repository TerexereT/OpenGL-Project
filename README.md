CG3-P1
cuando clickeas el script genproject te saldrá el proyecto de visual studio 2019.

No añadas librerías usando la interfaz gráfica de visual studio porque esas dependencias se perderan.

Todas esas librerías deben incluirse editando el archivo premake5.lua

El proyecto
EasyDIPAPI
Contiene todo el código relacionado a la API del proyecto y es donde haremos el procesamiento de modelos

EasyDIPClient
Interfaz gráfica de la app que permite hacer un preview de todas las funciones de la API.

Acá solo se utiliza la API de EasyDIPAPI para trabajar en la app

Para cargar los modelos buscar en la carpeta "Models" dentro del proyecto. No mover el int que muestra los modelos fuera de la cantidad de modelos cargados, empezando en 0.
Ej: aumentar el int a 3 si solo se han cargado 3 modelos (0,1,2). Al intentar poner el 3 arroja error de memoria por no haber instancia en esa posicion