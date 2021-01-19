# Paquete de ROS para drone DJI-UFRO

## Problemas encontrados y causas
Hubo problemas al compilar y se encontraron 3 causas:
- Ignorancia sobre CMAKE
- Ignorancia al configurar cmake y, por tanto, el archivo CMakeLists.txt
- El paquete Onboard-SDK-ROS está constantemente cambiando y está mal configurado, depende de paquetes obsoletos

### Soluciones
- Aprender las bases de cmake, especificamente: saber cual es su función, como vincular librerias y configurarlas como dependencias y como configurar un ejecutable.
- NO IMPORTAR DJI_OSDK_ROS, si no se puede obviar este caso, probar con importar y ver si compila, si no, será necesario hacer un fork y solucionar errores.
- Lo más importante, configurar bien el CMakeLists.txt y confirmar que los paquetes que estén dando problemas realmente están en el sistema.
- Los "types" que utiliza DJI_OSDK_ROS son estándares de ros basados en: "std_msgs", "sensor_msgs", "nmea_msgs"...Por lo tanto se pueden importar independientemente.

## Dependencias
- SQlite3, headers y sources en su respectiva carpeta "slite"
- ROS
- geometry_msgs
- sensor_msgs
- roscpp
- rospy
- std_msgs


## Referencias utilizadas o utiles
- Gentle Introduction to ros
- http://wiki.ros.org/ROS/Tutorials/CreatingPackage
- https://dabit-industries.github.io/turtlebot2-tutorials/08c-ROSCPP_Building.html
- https://varhowto.com/cpp-ros-catkin-package/
- https://www.wangzerui.com/2017/11/26/a-very-brief-ros-tutorial/
- https://riptutorial.com/ros/example/28374/hello-world-publisher

## VERSION PRUEBA
Última compilación sin error: 19 enero 2021

