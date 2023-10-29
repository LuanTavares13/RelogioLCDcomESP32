#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 5, 18, 19, 21); // Inicialização do display LCD
const char* ssid = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* password = ""; // Senha da rede Wi-Fi
const char* ntpServer = "a.ntp.br"; // Servidor NTP
const long gmtOffset_sec = -3 * 3600; // Fuso horário
const int daylightOffset_sec = 0; // Deslocamento do horário de verão

bool mostrarData = true; // Variável para alternar entre data e hora

const char* diaDaSemana[] = {"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado"};
const char* nomeDoMes[] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};

// Função para centralizar texto no display
void centralizarTexto(String texto, int linha) {
  int tamanhoDoTexto = texto.length();
  int espacosEmBranco = (16 - tamanhoDoTexto) / 2; // Calcula a quantidade de espaços em branco para centralizar
  lcd.setCursor(espacosEmBranco, linha);
  lcd.print(texto);
}

// Função para exibir a data e hora no display
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Sem horário disponível (ainda)");
    return;
  }

  lcd.clear();

 if (mostrarData) {
    // Exibe a data centralizada na primeira linha e o dia da semana na segunda linha
    String data = "" + String(timeinfo.tm_mday) + "/" + nomeDoMes[timeinfo.tm_mon] + "/" + (1900 + timeinfo.tm_year);
    centralizarTexto(data, 1);
    centralizarTexto(diaDaSemana[timeinfo.tm_wday], 0);
  } else {
    // Define a saudação com base na hora atual e exibe centralizada na primeira linha 
    String saudacao;
    int horaAtual = timeinfo.tm_hour;
    if (horaAtual >= 6 && horaAtual < 12) {
      saudacao = "Bom dia!";
    } else if (horaAtual >= 12 && horaAtual < 18) {
      saudacao = "Boa tarde!";
    } else {
      saudacao = "Boa noite!";
    }
    centralizarTexto(saudacao, 0);

    String hora = String(timeinfo.tm_hour) + ":" + (timeinfo.tm_min < 10 ? "0" : "") + timeinfo.tm_min + ":" + (timeinfo.tm_sec < 10 ? "0" : "") + timeinfo.tm_sec;
    centralizarTexto(hora, 1);
  }
}

// Função chamada quando o tempo é sincronizado com o servidor NTP
void tempoDisponivel(struct timeval* t) {
  Serial.println("Recebido ajuste de tempo do NTP!");
  printLocalTime();
}

int botaoPin = 4;
int ultimoEstadoBotao = HIGH;
int estadoBotao = HIGH;

unsigned long ultimoTempoAlternancia = 0;
unsigned long intervaloAlternancia = 1000;

void setup() {
  Serial.begin(115200); // Inicialização da comunicação serial
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Inicializando...");

  // Configuração da notificação de tempo sincronizado
  sntp_set_time_sync_notification_cb(tempoDisponivel);
  sntp_servermode_dhcp(1);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer, ntpServer);

  pinMode(botaoPin, INPUT_PULLUP); // Configuração do pino do botão como entrada com pull-up

  Serial.printf("Conectando a: %s", ssid); 
  lcd.clear();
  lcd.print("Conectando a ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(1000);

  WiFi.begin(ssid, password); // Inicialização da conexão Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado com sucesso!");
  lcd.clear();
  centralizarTexto("Conectado com", 0);
  centralizarTexto("sucesso!!!", 1);
  delay(2000);
}

void loop() {
  estadoBotao = digitalRead(botaoPin);

  if (estadoBotao != ultimoEstadoBotao) {
    if (estadoBotao == LOW && millis() - ultimoTempoAlternancia >= intervaloAlternancia) {
      mostrarData = !mostrarData;
      ultimoTempoAlternancia = millis();
    }
    ultimoEstadoBotao = estadoBotao;
  }

  delay(1000);
  printLocalTime();
}
