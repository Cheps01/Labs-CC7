# Calculadora para QEMU

Este proyecto consiste en el desarrollo de una **calculadora ejecutándose sobre QEMU**, como parte de un laboratorio de programación de bajo nivel. El objetivo principal fue reorganizar el código base proporcionado en la asignación para **separar responsabilidades**, mejorar la mantenibilidad y extender la funcionalidad del sistema.

---

## Organización del proyecto

El proyecto fue reorganizado siguiendo una división clara por capas:

- **`os/`**  
  Contiene el código relacionado con el sistema base necesario para arrancar el programa en QEMU. Incluye el código de inicialización, el script del linker y rutinas de bajo nivel como el manejo del UART y el punto de entrada del sistema.

- **`lib/`**  
  Implementa librerías reutilizables que reemplazan funcionalidades básicas de la biblioteca estándar, como manejo de strings y entrada/salida. Aquí se encuentran las implementaciones personalizadas de `printf` y `scanf`, diseñadas para comunicarse a través del UART.

- **`app/`**  
  Contiene la lógica de negocio de la aplicación: la calculadora. Esta capa se apoya únicamente en las funciones expuestas por las librerías, sin depender directamente de detalles del hardware o del sistema.

Además, el directorio **`bin/`** almacena los binarios generados tras la compilación.

---

## Funcionalidades implementadas

- **Calculadora interactiva** ejecutándose dentro de QEMU.
- **Soporte para números de punto flotante**, permitiendo realizar operaciones aritméticas con decimales.
- **Implementación propia de `printf` y `scanf`**, utilizando el UART como medio de entrada y salida.
- **Manejo básico de strings**, necesario para el parseo de entradas y formateo de salidas.
- **Pruebas básicas** incluidas en un archivo separado para validar el funcionamiento de la lógica.

---

## Automatización

Se añadieron dos scripts para simplificar el uso del proyecto:

- **`build.sh`**  
  Compila todo el código, enlaza usando el script del linker y genera el binario final.

- **`run.sh`**  
  Ejecuta el binario resultante en QEMU, redirigiendo la salida del UART a la consola.

Gracias a estos scripts, el proyecto puede compilarse y ejecutarse con pocos comandos.

---

## Conclusión

Este laboratorio permitió aplicar conceptos de programación de bajo nivel, diseño modular y sistemas embebidos. La separación entre sistema, librerías y aplicación mejora la claridad del código y facilita futuras extensiones, como agregar más funcionalidades, nuevos drivers o aplicaciones adicionales sobre la misma base.
