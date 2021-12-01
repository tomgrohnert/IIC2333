## Respuesta

Especificar que la dirección para entrar a netflix es:

# www.netflix.com/netflix.html

# Primera Parte

# Respuestas:

R1: La ip de detino es la 3.3.0.2 la cual tiene un largo de 32 bits.

R2: La dirección de origen es la 172.67.7.2 y la dirección de destino es la 3.3.0.2

R3: En este caso la dirección de origen es la 3.3.0.2 y la dirección de destino es la 172.67.7.2

R4: En ambas capas pasa:

# In layers:

Layer1: 

- Fast Ethernet() receives the frame

Layer2:

- La dirección MAC del destino del frame compatibiliza con el puerto que recibe de la dirección MAC, la dirección broadcast o alguna dirección multicast.
- El dispositivo desencapsula el PDU del frame de Ethernet.

Layer3:

- La dirección ip de destino del paquete compatibiliza con la dirección ip del aparato or la dirección broadcast. El dispositivo desencapsula el paquete.
- El paquete es de tipo ICMP. El proceso ICMP lo procesa.
- El proceso ICMP recibe un mensaje de tipo Echo Request.

# Out layers:

Layer1:

- Fast Ethernet() envía para afuera el frame.

Layer2:

- La dirección IP next-hop es de tipo unicast. El proceso ARP lo busca en la tabla ARP.
- La dirección IP next-hop es de tipo tabla ARP. El proceso ARP setea la dirección MAC de destino del frame con la encontrada en la tabla recién descrita.
- El aparato desencapsula el PDU a una frame de Ethernet.

Layer3:

- El proceso ICMP response al Echo Request seteando el tipo ICMP a la respuesta Echo.
- El proceso ICMP envía la respuesta Echo.
- La dirección IP de destino 172.67.7.2 no es la misma subnet y no es la dirección broadcast.
- El Gateway por default está seteado. El aparato setea el next-hop al Gateway por default.

# Segunda Parte

R1: El http request del paquete http tiene 32 bytes.


R2:

- Paquete HTTP: El paquete HTTP es el cual se genera desde el laptop que generó el request y se manda hacia el servidor del servicio que se está solicitando con la IP
devuelta por el DNS. Este paquete es el cual sirve para enviar los datos solicitados por el laptop, lo que es finalmente la información que se quiere obtener. Es por esto
que en su contenido esta la información solicitada por el laptop del cliente.

- Paquete TCP: El paquete TCP es el cual se genera desde el laptop que generó el request y se manda hacia el servidor del servicio que se esta solicitando con la IP
devuelta por el DNS. Este paquete es sobre el protocolo de conexión antes de enviar los paquetes de datos. Aca contiene el tamaño máximo de segmento, núm
ero de secuencia además cuentan bytes en la secuencia. ACK contiene el sequence number del siguiente byte que se espera. 


- Paquete DNS: El paquete DNS es el cual se genera desde el laptop que generó el request y se manda hacia el servidor DNS en busca del IP asociado a la url con la cual
el laptop de origen generó la request. De esta forma el paquete de vuelta desde el servidor DNS al laptop contendrá la IP necesaria para poder luego generar las requests
de paquetes TCP y HTTP.

- Paquete ICMP: El paquete ICMP es sobre una red de protocolo que es responsable de reportar errores a través de la generación y envió de mensajes a la dirección de IP
de origen cuando hay problemas de red que son encontrados por el sistema. El contenido de este paquete es un tipo, un código y una suma de verificación. Finalmente
lo que trae en otras palabras son textos que le dicen a la IP de origen si es que se encuentran problemas en el sistema.

- Paquete STP: Este es un protocolo de red de capa 2 del modelo OSI. Este se encarga de reconocer y administrar bucles en topologías de redes nacidos a función de la redundancia
de ellas. En este caso aparecen cuando hayan Switches en alguna subred. 

R3:

- Paquete ICMP: Va desde el computador que inicia el request en dirección a el router Gateway para luego irse a la red. De esa forma pasa por el router central para ir en dirección a la subred indicada que sería donde se contiene el servidor DNS. De esta forma este paquete luego pasa por el router Gateway de esta subred y llega hasta el servidor. Como respuesta este paquete hace el mismo viaje de vuelta.


- Paquete DNS: Va desde el computador que inicia el request en dirección a el router Gateway para luego irse a la red. De esa forma pasa por el router central para ir en dirección a la subred indicada que sería donde se contiene el servidor DNS. De esta forma este paquete luego pasa por el router Gateway de esta subred y llega hasta el servidor. Como respuesta este paquete hace el mismo viaje de vuelta.

- Paquete STP: El paquete STP lo que hace es originarse en el switch el cual esta entre el router Gateway de la subred donde pertenece el servidor DNS. Primero inicia su viaje a el servidor DNS para luego salir nuevamente del switch al router Gateway.

- Paquete TCP: Va desde el computador que inicia el request en dirección al router Gateway para luego irse a la red. De esa forma pasa por el router central por el cual luego se desvía hacia la dirección de la subred que contiene el servidor de Netflix. Es por esto que pasar por el router Gateway de aquella subred para luego pasar por un switch y llegar al servidor de Netflix. Como respuesta este paquete hace el mismo viaje de vuelta al computador que inició el request.

- Paquete HTTP: Va desde el computador que inicia el request en dirección al router Gateway para luego irse a la red. De esa forma pasa por el router central por el cual luego se desvía hacia la dirección de la subred que contiene el servidor de Netflix. Es por esto que pasar por el router Gateway de aquella subred para luego pasar por un switch y llegar al servidor de Netflix. Como respuesta este paquete hace el mismo viaje de vuelta al computador que inició el request.
