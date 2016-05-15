
// ************* PINS *************** //
#define RMOTOR 10 // Motor da direita (pin PWM)
#define LMOTOR 11 // Motor da esquerda (pin PWM)
#define LSENSOR A0 // Sensor da esquerda 
#define RSENSOR A1 // sensor da direita

// ************ PARÂMETROS ************ //
#define BRANCO 300  // Esta variável irá estipular a diferença entre os dados do sensor quando atinge o preto e o branco
#define WMAX 50     // Velocidade em linha reta
#define WMIN 20     // Velocidade durante curva
#define W 30        // Velocidade linear durante a curva

// *********** PROP. FÍSICAS ************ //
#define WMAX 100 // velocidade angular máxima atingida pelo motor
#define R_eixo 60 // Raio do eixo da roda
#define R_roda 30 // Raio da roda

// Obs: O sentido positivo é o horário

void setup{
    pinMode( RMOTOR , OUTPUT);
    pinMode( LMOTOR , OUTPUT);
    pinMode( RSENSOR , INPUT );
    pinMode( LSENSOR , INPUT );
}

void loop{
    int state = 0, rData, lData;    
    
    lData = analogRead( LSENSOR );
    rData = analogRead( RSENSOR );
    
    //Nenhum sensor toca a linha
    if ( lData >= BRANCO && rData >= BRANCO ) {
        state = 0;            
    }
    // Sensor da direita toca a linha
    else if( lData >= BRANCO ) {
        state = 1
    } 
    //Sensor da esqueda toca a linha
    else {
        state = 2;
    }
    //Obs : o caso em que os dois sensores tocam a linha foi desprezado
    
    switch (state){
        // Vai reto
        case 0: 
                velocidade( VMAX , 0);
                break;
        //Vira para a direita
        case 1:
                velocidade( VMIN , W);
                break;
        //Vira para a esquerda        
        case 2:
                velocidade( VMIN , -W);
                break;
    }
}

// Essa função transfoma a velocidade linear e angular desejadas em saidas para o motor 
void velocidade( int Vt, int Wt)
{   int WL, int WR;

    WL = (Vt + Wt*R_eixo/2) / R_roda ;
    WR = (Vt - Wt*R_eixo/2) / R_roda ; 

    digitalWrite( LMOTOR , map( WL , 0 , WMAX , 0 , 1023 ));
    digitalWrite( RMOTOR , map( WL , 0 , WMAX , 0 , 1023 ));

}


      
