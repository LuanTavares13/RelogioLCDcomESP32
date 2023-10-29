#Projeto Relógio Inteligente com ESP32 e Display LCD
Este projeto tem como objetivo criar um dispositivo que exibe a hora e a data atuais em um display LCD, além de permitir alternar entre a exibição da data e da hora. O dispositivo também se conecta a um servidor NTP para sincronizar o tempo e ajustar automaticamente.

##Componentes Utilizados
*Placa ESP32 (ou compatível)
*Display LCD 16x2
*Push button (Botão de pressão)
*Acesso a uma rede Wi-Fi
*Servidor NTP (a.ntp.br neste exemplo)

##Funcionalidades
*Exibe a data e hora atuais em um display LCD 16x2.
*Alternância entre a exibição da data e da hora pressionando um botão.
*Sincroniza o tempo com um servidor NTP para manter a precisão.
*Cumprimento exibido com base na hora atual (Bom Dia, Boa Tarde, Boa Noite).

##Bibliotecas Utilizadas
*WiFi: Para a conexão à rede Wi-Fi.
*NTP (Network Time Protocol): Para sincronização do tempo com um servidor NTP.
*LiquidCrystal: Para controlar o display LCD.

##Configuração
O código faz a configuração inicial da rede Wi-Fi, fuso horário, servidor NTP e inicializa o display LCD. Ele também configura o botão de pressão como entrada com pull-up.

##Funcionamento
O dispositivo exibe a hora atual e o dia da semana no display LCD. Pressionando o botão, é possível alternar entre a exibição da data e do horário. Além disso, o cumprimento exibido muda com base na hora atual (Bom Dia, Boa Tarde, Boa Noite).

O tempo é sincronizado com um servidor NTP, garantindo a precisão da hora exibida. Quando a sincronização de tempo ocorre, uma notificação é exibida no monitor serial.

##Como Usar
1. Conecte a placa ESP32 ao display LCD e ao botão de pressão conforme especificado no código.
2. Carregue o código no ESP32 usando a plataforma Arduino IDE.
3. Conecte-se a uma rede Wi-Fi configurando o SSID e a senha.
4. O dispositivo exibirá a hora e a data atuais. Pressione o botão para alternar entre data e hora.
5. O dispositivo sincronizará automaticamente o tempo com o servidor NTP.
   
##Autor
Luan Tavares da Silva

Observação: Certifique-se de ajustar as informações de rede Wi-Fi, servidor NTP e outras configurações de acordo com suas necessidades antes de carregar o código no ESP32.
