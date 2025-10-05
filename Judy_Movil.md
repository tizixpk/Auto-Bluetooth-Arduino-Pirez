###### Este archivo es lo mismo que Judy Movil.docx. Las imagenes no estan aca
# Judy Móvil: Vehículo Robótico a Escala Controlado por Arduino

## Introducción

El proyecto **Judy Móvil** consiste en el diseño y programación de un
vehículo robótico a escala controlado electrónicamente. El objetivo es
construir un sistema mecatrónico sencillo que integre electrónica y
programación: una placa Arduino UNO actúa como unidad central, enviando
señales a un controlador de motores (puente en H) para mover las ruedas.
De este modo el vehículo puede avanzar, retroceder o girar según el
programa cargado o las órdenes recibidas desde un dispositivo externo.
Este proyecto ilustra conceptos de control de motores, uso de sensores y
comunicación inalámbrica. En particular, **Judy Móvil** se controla
desde un teléfono móvil vía Bluetooth HC-05 y está equipado con sensores
ultrasónicos para detectar y esquivar obstáculos. La integración de
estos elementos demuestra cómo la electrónica puede generar un
comportamiento autónomo o semiautónomo en un sistema móvil.

## Arquitectura del sistema

El diagrama de bloques de la Figura muestra los principales componentes
del vehículo. La placa **Arduino UNO** es el cerebro del sistema (bloque
azul); recibe comandos inalámbricos desde el teléfono móvil (bloque
verde, vía el módulo Bluetooth HC-05) y procesa las señales de los
sensores. Arduino envía entonces señales digitales (PWM y lógica) al
**driver de motores L298N** (bloque púrpura), el cual acciona cuatro
motores DC conectados a las ruedas (círculos amarillos). Una fuente de
energía (bloque rojo, batería) alimenta a los motores y a la placa
Arduino. En conjunto, esta arquitectura permite que las órdenes enviadas
desde la app móvil (adelante, atrás, girar, detener, etc.) se traduzcan
en movimiento del vehículo; adicionalmente, la entrada de los sensores
ultrasónicos permite que Arduino detenga o modifique la marcha al
detectar un obstáculo próximo.

## Unidad de control: Arduino UNO

La placa Arduino UNO R3 es una computadora de placa única muy popular
para proyectos embebidos. Está basada en el microcontrolador ATmega328P
(8 bits, 16 MHz), con 32 KB de memoria Flash para el programa, 2 KB de
SRAM y 1 KB de
EEPROM[\[5\]](https://www.arrow.com/es-mx/research-and-events/articles/arduino-uno-product-overview#:~:text=Arduino%20Uno%20es%20una%20de,cualquier%20tarea%20que%20le%20pida).
Dispone de 14 pines digitales de E/S (de los cuales 6 pueden usarse como
salidas PWM) y 6 entradas analógicas. Estos pines se usan para conectar
los sensores ultrasónicos, el módulo Bluetooth y las señales de control
al driver de motores. El entorno de desarrollo (IDE) de Arduino es de
código abierto y facilita la programación del microcontrolador mediante
un lenguaje simplificado basado en C/C++. Gracias a su cristal de 16 MHz
y su capacidad de procesamiento, la placa puede leer sensores, ejecutar
la lógica de control (decisiones de movimiento) y generar las señales de
modulación por ancho de pulso (PWM) necesarias para controlar los
motores. En resumen, Arduino actúa como el cerebro eléctrico del
vehículo, interprete de comandos inalámbricos y coordinador de todos los
subsistemas.

## Control de motores: Driver L298N

El **módulo controlador de motores L298N** es un chip dual puente en H
que permite controlar la velocidad y dirección de hasta dos motores de
corriente continua. Gracias a sus dos puentes H internos, el L298N puede
invertir el sentido de giro de cada motor al cambiar la polaridad de la
alimentación. Este driver maneja tensiones de motor en un amplio rango
(aproximadamente 3--35 V) y corrientes de hasta 2 A por canal. En el
proyecto se utilizan dos L298N para controlar cuatro motores (dos en
paralelo por canal) o un L298N para controlar cada par de ruedas. El
Arduino envía señales digitales a los pines de entrada del L298N (por
ejemplo IN1, IN2, IN3, IN4) para determinar la dirección de cada motor.
Además, los pines de habilitación (ENA, ENB) del módulo L298N se
conectan a salidas PWM del Arduino, lo que permite variar la velocidad
de cada motor modulando la anchura del pulso. De esta forma, el L298N
actúa como amplificador de potencia: recibe las señales de bajo voltaje
del Arduino y las amplifica para proveer la tensión y corriente
necesaria a los motores DC. Su capacidad de regular tanto dirección como
velocidad hace posible que el vehículo responda con movimientos suaves y
precisos a los comandos recibidos.

## Comunicación inalámbrica: Módulo Bluetooth HC-05

El **módulo Bluetooth HC-05** establece un enlace inalámbrico tipo
serial (SPP) entre el Arduino y el teléfono móvil. Este dispositivo
opera con Bluetooth 2.0+EDR en la banda de 2.4 GHz y puede configurarse
en modo maestro o esclavo. Se conecta al Arduino mediante UART TTL
(pines RX/TX), lo que simula una conexión serie convencional. El HC-05
incluye un regulador interno de 3.3 V, permitiendo alimentarlo con un
rango de 3.6 a 6 V. En la práctica se usa para emparejar el vehículo con
la app móvil: el smartphone envía comandos (como cadenas de texto o
caracteres) al Arduino a través de este enlace. Por ejemplo, al
presionar un botón de "Adelante" en la app, se transmite el carácter
ASCII correspondiente, y Arduino lee este dato por el puerto serie para
iniciar el avance. El módulo tiene un alcance típico de unos 10 metros,
lo que brinda una comunicación estable sin cables. En conjunto, el HC-05
permite controlar Judy Móvil en tiempo real desde un celular,
reemplazando un cable serial por un enlace inalámbrico transparente.

## Aplicación móvil de control (MIT App Inventor)

Para el control remoto se desarrolló una aplicación Android con **MIT
App Inventor**, una plataforma visual orientada a la educación que
simplifica la creación de apps mediante bloques gráficos. La aplicación
incluye botones de control (adelante, atrás, izquierda, derecha,
detener, etc.) y un componente *BluetoothClient* que se encarga de
buscar y emparejar el HC-05. Al pulsar cada botón, la app envía por
Bluetooth un carácter predeterminado al Arduino (por ejemplo \'F\' para
avanzar, \'B\' para retroceder, \'L\' y \'R\' para girar, \'S\' para
detener). El código cargado en Arduino lee continuamente el puerto
serie; según el carácter recibido ejecuta la rutina de movimiento
correspondiente (activando las salidas PWM y dirección en el L298N).
Este mecanismo facilita el control manual del vehículo sin necesidad de
programar desde cero una app compleja: App Inventor maneja la interfaz
de usuario y la conexión Bluetooth, mientras que Arduino solo interpreta
los comandos recibidos.

## Detección de obstáculos: Sensores ultrasónicos HC-SR04

Judy Móvil emplea dos **sensores ultrasónicos HC-SR04** (montados en el
chasis delantero y/o lateral) para detectar obstáculos en su camino. El
HC-SR04 es un sensor de distancia de bajo costo que utiliza ultrasonido
en el rango de 40 kHz. Posee un emisor y un receptor piezoeléctrico.
Para medir distancia, Arduino activa el pin **TRIG** del sensor, que
emite una ráfaga de 8 pulsos ultrasónicos a 40 kHz. Al rebotar contra un
objeto, el ultrasonido retorna al sensor, y el pin **ECHO** pasa a nivel
alto durante el tiempo de ida y vuelta del pulso. El Arduino mide ese
intervalo de tiempo $t$ y calcula la distancia al objeto usando la
fórmula:

$$\text{Distancia} = \frac{t \cdot 340\ \text{m/s}}{2}$$

(suponiendo velocidad del sonido 340 m/s). El HC-SR04 puede medir en un
rango aproximado de **2 a 450 cm** con buena precisión (\~±3 mm). En la
programación, si la distancia medida por cualquiera de los sensores cae
por debajo de un umbral predefinido, Arduino considera que hay un
obstáculo cercano y puede entonces detener los motores o girar el
vehículo para evitar la colisión. Así, los dos sensores ultrasónicos
permiten al robot reaccionar dinámicamente ante objetos en su
trayectoria, mejorando la autonomía y la seguridad en su operación.

## Mecánica y sistema de energía

El chasis del vehículo está construido con una lámina rígida de plástico
de aproximadamente **200 mm de largo por 150 mm de ancho**, sobre la
cual se montan los demás componentes. En las esquinas van las
**ruedas**, fabricadas en plástico con diámetro de **66 mm** (anchura
\~25 mm). Cada rueda está acoplada a un motor DC de bajo voltaje (6--7.5
V), de unos 70 mm de longitud, con engranaje interno que brinda torque
adecuado para mover el chasis. El motor y la rueda forman una unidad
motriz que se sujeta al chasis. La fuente de energía principal son
**pilas 18650**; en el diseño original se emplearon 2 pilas alcalinas
(15 V total), alojadas en un portapilas integrado (soporte de unos 62×57
mm para 2 pilas). Estas pilas alimentan directamente los motores (aprox.
6 V) y, a través del regulador interno de Arduino, también proveen los 5
V necesarios para la lógica y sensores. El diseño mecánico busca un
balance entre ligereza (chasis de plástico y ruedas relativamente
grandes) y robustez (estructura firme capaz de soportar los componentes
electrónicos). En conjunto, el sistema mecánico y eléctrico asegura que
el vehículo pueda desplazarse sin problemas mientras integra todos los
módulos de control y detección.

## Especificación de componentes

  -------------------------------------------------------------------------
  Componente        Características principales                Precio
                                                               (aprox.)
  ----------------- ------------------------------------------ ------------
  **Driver de       Doble puente en H, controla 2 motores DC;  \\\$10.000
  motores L298N**   opera a 3--35 V, hasta 2 A por canal.      

  **Módulo          Bluetooth 2.0+EDR, interfaz Serial TTL,    \\\$22.000
  Bluetooth HC-05** alimentación 3.6--6 V.                     

  **Porta-pilas     Soporte de plástico para 2 pilas AA (3 V)  \\\$8.000
  (2xAA)**                                                     

  **Placa Arduino   Microcontrolador ATmega328P 16 MHz, 32 KB  \\\$53.000
  UNO R3**          Flash, 6 PWM, 6 analógicos.                

  **Rueda 66 mm     Diámetro 66 mm, ancho \~25 mm              \\\$20.000
  (x4)**                                                       (4 u.)

  **Motor DC 6V     70 mm de largo, 22 mm de diámetro; con     \\\$16.000
  (x4)**            caja de engranajes                         (4 u.)

  **Chasis plástico Plancha de 200×150 mm aprox. (se usaron 2  \\\$30.000
  (x2)**            chapas)                                    (2 u.)

  **Pilas AA (x5)** Pilas alcalinas de 1.5 V                   \\\$40.000
                                                               (5 u.)
  -------------------------------------------------------------------------

Los precios indicados son valores de referencia de adquisición local
según la fuente original, expresados en moneda local. Las
características técnicas se basan en las hojas de datos y
especificaciones estándar de cada componente. Esta lista resume los
elementos principales necesarios: el controlador de motores L298N y sus
parámetros, el módulo Bluetooth para comunicación, la placa Arduino UNO
para el procesamiento, las ruedas y motores para la tracción, el chasis
como soporte estructural y las pilas como sistema de energía. Todos
estos componentes se integran para dar forma al vehículo electrónico
**Judy Móvil**, que puede ser controlado a distancia y evita obstáculos
automáticamente según lo descrito arriba.

**Fuentes:** La información la buscamos en la plataforma Wikipedia,
Mercado Libre y Arduino Info.
