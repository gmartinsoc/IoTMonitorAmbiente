#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "hsNCE";
//const char* host = "srv03.labnet.nce.ufrj.br";
String servidor = "http://srv03.labnet.nce.ufrj.br";

//int contaFalhas=0;
int contReads = 0;
//inicia o json reads de leituras com {"reads":[{ codificado com url enconding
String reads = "%7B%22reads%22:%5B";
//String reads = "{\"reads\":[";
int id_no = 1;
String place = "sala6";
//Nome da Colecao
String nomecolecao = "monitoraNCE";

const int PinoEntradaAM2321= 14; //pinoD5
// Define pino e tipo do sensor DHT
DHT dht(PinoEntradaAM2321, DHT22);

WiFiClient client; //Declarando o cliente WI-FI

void setup(){
  
  pinMode(2,OUTPUT);
 //Serial.begin(9600);
 //digitalWrite(2,LOW);
  
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
  }

  //codigo para indicar que conexao com wifi foi estabelecida
  digitalWrite(2,LOW);
  delay(500);
  digitalWrite(2,HIGH);
  delay(200);
  digitalWrite(2,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
  
  //Serial.println("WI-FI connected.");
  // Inicializa o DHT22
  dht.begin();

}

void(* resetFunc) (void) = 0;

//void enviarBackup(String json){
//
//    if (client.connect(host, 80)) {
//     
//        contaFalhas=0;
//
//        //encerra json reads com }]}
//        json.concat("%5D%7D");
////      json.concat("}]}");
//          
//        String s = "GET /tempCode/sala6/?leitura=";
//        
//        //s.concat(json);
//
//        //Serial.println(s);
//                
//        client.println(s);   
//        client.println("Host: srv03.labnet.nce.ufrj.br");
//        //client.println("Accept-Charset: utf-8");
//        client.println("Connection: close");
//        client.println();   
//        
//        while (client.connected()){
//          if (client.available()) {
//            String line = client.readStringUntil('\n');
//          }
//        }
//        
//        client.stop();
//        
//    }else {
//        
//        client.stop();
//        contaFalhas++;
//        if (contaFalhas>5) resetFunc();
//        
//    }
//    
//    //inicia o json reads de leituras com {"reads":[{ codificado com url enconding
//    reads = "%7B%22reads%22:%5B";
////  reads = "{\"reads\":[";
//
//    //zera contador
//    contReads = 0;
//
//}

void enviar(String json){

  HTTPClient http;
  String url = servidor;
  json.concat("%5D%7D");
//  json.concat("}]}");
  
  //url.concat("/tempCode/sala6/?leitura=");
  url.concat("/tempCode/");
  url.concat(nomecolecao);
  url.concat("/?leitura=");
  
  url.concat(json);
  //Serial.println(url);
  http.begin(url);

  // start connection and send HTTP header  
  int httpCode = http.GET();
  int auxResp = httpCode - 200;

  //TODO: piscar leds com codigo para indicar erro ou sucesso
  if ((auxResp > 0) && (auxResp < 100)){
//    printf("Funcionou %d",httpCode);
    
    //pisca por 1 segundo caso envie com sucesso
    //LED BLUE on = LOW/ LED BLUE off = HIGH 
    digitalWrite(2,LOW);
    delay(1000);
    digitalWrite(2,HIGH);
        
  }else{
//    printf("Error:,%d",httpCode);    
    //Em caso de erro o led fica aceso ate a proxima leitura ser feita
    //LED BLUE on = LOW/ LED BLUE off = HIGH 
    digitalWrite(2,LOW);

  }

  //inicia o json reads de leituras com {"reads":[{ codificado com url enconding
  reads = "%7B%22reads%22:%5B";
//  reads = "{\"reads\":[";
  contReads = 0;

}

String criarJSON(float temp, float umd){

  int timestamp = contReads; //variavel global usada na contagem. paliativo ate conseguirmos incluir millis ou (melhor) gerarmos a estampa de tempo direto no nó.
 
  //json com leitura de temperatura e umidade que sera incluida no buffer    
  String r = "%7B%22temp%22:";
  //String r = "{\"temp\":";

  contReads ++;
  
  r.concat(String(temp));
  r.concat(",%22umd%22:");
//  r.concat(",\"umd\":");
  r.concat(String(umd));
  r.concat(",%22count%22:");
//  r.concat(",\"count\":");
  r.concat(String(contReads));
  r.concat(",%22timestamp%22:");
//  r.concat(",\"timestamp\":");
  r.concat(String(timestamp));
  r.concat(",%22id_no%22:");
//  r.concat(",\"id_no\":");
  r.concat(String(id_no));
  r.concat(",%22id_sensor%22:null,%22place%22:%22");
///  r.concat(",\"id_sensor\":null,\"place\":\"");
  r.concat(place);
  r.concat("%22%7D");
//  r.concat("\"}");

  return r;
  
}

void loop(){    

  
    float umd = dht.readHumidity();
    float temp = dht.readTemperature();

    String r = criarJSON(temp, umd);
    reads.concat(r);    
    
    //situacao de emergencia, envio imediato dos dados
    if (temp >= 40){
      
      enviar(reads);
      
    }else{
      if(contReads == 15){
        
        enviar(reads);

      }else{
        //adiciona virgula entre as leituras (read) no json
        reads.concat(",");
      }
            
    }
    
    delay(10000);
    //LED BLUE on = LOW/ LED BLUE off = HIGH 
    digitalWrite(2,HIGH);
    
}
