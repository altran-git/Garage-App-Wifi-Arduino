#include "socketapp.h"
#include "uip.h"

void ser_print(char*);

extern char incoming[50];
extern int doorStatus;
extern int sendData;
char temp[20];

//EMAIL//struct smtp_state {
//EMAIL//struct psock p;
//EMAIL//char inputbuffer[128];
//EMAIL//};

//EMAIL//static struct smtp_state s;

void socket_app_init(void){
  process1_init();
}

void process1_init(void){
  /* We start to listen for connections on TCP port 55555. */
  uip_listen(HTONS(55555));
}

void socket_app_appcall(void)
{
  switch(uip_conn->lport){
    case HTONS(55555):
      process1_app();
      break;
  }
  //EMAIL//switch(uip_conn->rport){
    //EMAIL//case HTONS(587):
      //EMAIL//process2_app();
      //EMAIL//break;
  //EMAIL//}
}

void process1_app(void){
  u16_t len;
  /*if(uip_connected() && uip_conn->lport == HTONS(55555)) {
      ser_print("1.  Accepted connection on port 55555\n");
  }*/
  if(uip_newdata()) {
      len = uip_datalen();
      memcpy(incoming, uip_appdata, len);
      incoming[len] = '\0';   
  }
  if(sendData != 0 && uip_conn->lport == HTONS(55555)){
        //ser_print("Sending status...\n");
        sprintf(temp, "%d", doorStatus);
        uip_send(temp, 1);
        sendData = 0;
  }
}

//EMAIL//
 /*void process2_app(){
    PSOCK_BEGIN(&s.p);
    
    PSOCK_WAIT_UNTIL(&s.p, uip_conn->rport == HTONS(587));
    //ser_print("2.  Accepted connection on port 587\n");
    //PSOCK_SEND_STR(&s.p, "HELO \r\n");
    PSOCK_SEND_STR(&s.p, "STARTTLS\r\n");
    PSOCK_SEND_STR(&s.p, "AUTH LOGIN \r\n");
    PSOCK_SEND_STR(&s.p, "YWxsYm95c2dhcmFnZQ==\r\n");
    PSOCK_SEND_STR(&s.p, "MjMwN2dpYW5lcmE=\r\n");
    PSOCK_SEND_STR(&s.p, "MAIL FROM: <allboysgarage@yahoo.com>\r\n");
    PSOCK_SEND_STR(&s.p, "RCPT TO: <trn_andy@yahoo.com>\r\n");
    PSOCK_SEND_STR(&s.p, "RCPT TO: <trac.tran@yahoo.com>\r\n");
    PSOCK_SEND_STR(&s.p, "DATA\r\n");
    //PSOCK_SEND_STR(&s.p, "TO: <trn_andy@yahoo.com>\r\n");
    PSOCK_SEND_STR(&s.p, "FROM: <allboysgarage@yahoo.com>\r\n");
    PSOCK_SEND_STR(&s.p, "subject: GARAGE OPENED!\r\n\r\n");
    PSOCK_SEND_STR(&s.p, "\r\n.\r\n");
    PSOCK_SEND_STR(&s.p, "QUIT\r\n");
    
    PSOCK_END(&s.p);
}*///EMAIL//


//EMAIL//
 /*unsigned char smtp_send()
{
  uip_ipaddr_t ipaddr;
  
  uip_ipaddr(ipaddr, 98,138,105,21);
  uip_connect(ipaddr, HTONS(587));

  PSOCK_INIT(&s.p, s.inputbuffer, sizeof(s.inputbuffer));

  return 1;
}*///EMAIL//


