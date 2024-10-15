#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

void inicializa_motor();
void acionarBobinas(int passo);
int rotacao_motor_passo();
//extern bool rotacao_motor();

extern unsigned long tempo_anterior;
extern const unsigned long intervalo;