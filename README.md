# SA3---Grupo-8

O código fornecido implementa um sistema que lê a temperatura e umidade de um sensor DHT22 e realiza as seguintes ações:

1. Configuração da conexão WiFi: O código define o nome da rede WiFi (`ssid`) e a senha (`password`) para se conectar à rede.

2. Conexão ao Broker MQTT: O código configura o endereço do servidor MQTT (`broker.emqx.io`) e realiza a conexão usando um cliente MQTT. Ele gera um ID de cliente único baseado em um valor aleatório e tenta se conectar ao broker. O código também subscreve ao tópico MQTT definido como `johann`.

3. Leitura do sensor DHT22: O código configura o pino de dados do sensor DHT22 (`DHT_PIN`) e usa a biblioteca `DHTesp` para ler a temperatura e umidade do sensor. Os valores lidos são armazenados nas variáveis `temperatura` e `umidade`.

4. Controle dos LEDs: Com base nos valores de temperatura e umidade lidos, o código controla dois LEDs conectados aos pinos definidos como `LEDPIN1` e `LEDPIN2`. Se a temperatura estiver acima de 35°C, o LED 1 é ligado; caso contrário, é desligado. Se a umidade estiver acima de 70%, o LED 2 é ligado; caso contrário, é desligado.

5. Requisição HTTP para o ThingSpeak: O código cria uma requisição HTTP usando a biblioteca `HTTPClient` para enviar os dados de temperatura e umidade para o serviço ThingSpeak. A URL da requisição é construída com os valores lidos.

6. Publicação MQTT: O código publica uma mensagem MQTT no tópico definido como `johann` com os valores de temperatura e umidade no formato JSON. A mensagem é construída usando a biblioteca `PubSubClient`.

7. Atraso: Após todas as operações, o código espera por 1.5 segundos antes de reiniciar o loop.

Em resumo, o código lê a temperatura e umidade do sensor DHT22, controla LEDs com base nesses valores, envia os dados para o ThingSpeak usando uma requisição HTTP e publica os dados em um tópico MQTT. Essas funcionalidades podem ser úteis para monitorar e controlar condições ambientais em um projeto IoT.
