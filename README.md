<h1>OpenGL Project</h1>
<p>
cuando clickeas el script genproject te saldrá el proyecto de visual studio 2019.

No añadas librerías usando la interfaz gráfica de visual studio porque esas dependencias se perderan.

Todas esas librerías deben incluirse editando el archivo premake5.lua

El proyecto
<b>EasyDIPAPI</b>
Contiene todo el código relacionado a la API del proyecto y es donde haremos el procesamiento de modelos

<b>EasyDIPClient</b>
Interfaz gráfica de la app que permite hacer un preview de todas las funciones de la API.
![OpenGL-Project](https://raw.githubusercontent.com/TerexereT/OpenGL-Project/master/Screenshots/SS01.jpg)

Acá solo se utiliza la API de EasyDIPAPI para trabajar en la app

Para cargar los modelos buscar en la carpeta <b>"Models"</b> dentro del proyecto.

<b>"Model Number"</b>: es para seleccionar el modelo que ha sido previamente cargado, valores mas altos que la cantidad de modelos genera errores.

<b>"Navigate"</b>: Permite navegar en la escena, para salir de la navegacion se debe presionar 'ESC', Controles WASD
![OpenGL-Project1](https://raw.githubusercontent.com/TerexereT/OpenGL-Project/master/Screenshots/SS02.jpg)

</p>
