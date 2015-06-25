#include <SoftwareSerial.h>

#define MAX 5
#define HEIGHT 5
#define echoPin_down 6// Echo Pin
#define trigPin_down 8 // Trigger Pin

#define echoPin_left 8 // Echo Pin
#define trigPin_left 9 // Trigger Pin

//decoding all input variations
const int A[MAX][MAX] = {{0,1,0},
                         {1,0,1},
                         {1,1,1},
                         {1,0,1},
                         {1,0,1}};

const int B[MAX][MAX] = {{1,1,1},
                         {1,0,1},
                         {1,1,0},
                         {1,0,1},
                         {1,1,1}};             
const int C[MAX][MAX] = {{1,1,1},
                         {1,0,0},
                         {1,0,0},
                         {1,0,0},
                         {1,1,1}};
     
const int D[MAX][MAX] = {{1,1,1,0},
                         {1,0,0,1},
                         {1,0,0,1},
                         {1,0,0,1},
                         {1,1,1,0}};
     
const int E[MAX][MAX] = {{1,1,1},
                         {1,0,0},
                         {1,1,1},
                         {1,0,0},
                         {1,1,1}};
     
const int F[MAX][MAX] = {{1,1,1},
                         {1,0,0},
                         {1,1,0},
                         {1,0,0},
                         {1,0,0}};
     
const int G[MAX][MAX] = {{1,1,1,1},
                         {1,0,0,0},
                         {1,0,1,1},
                         {1,0,0,1},
                         {1,1,1,1}}; 

const int H[MAX][MAX] = {{1,0,0,1},
                         {1,0,0,1},
                         {1,1,1,1},
                         {1,0,0,1},
                         {1,0,0,1}};

const int I[MAX][MAX] = {{1},
                         {1},
                         {1},
                         {1},
                         {1}};

const int J[MAX][MAX] = {{0,0,1},
                         {0,0,1},
                         {0,0,1},
                         {1,0,1},
                         {1,1,1}};

const int K[MAX][MAX] = {{1,0,1},
                         {1,0,1},
                         {1,1,0},
                         {1,0,1},
                         {1,0,1}};
     
const int L[MAX][MAX] = {{1,0,0},
                         {1,0,0},
                         {1,0,0},
                         {1,0,0},
                         {1,1,1}};
     
const int M[MAX][MAX] = {{1,0,0,0,1},
                         {1,1,0,1,1},
                         {1,0,1,0,1},
                         {1,0,0,0,1},
                         {1,0,0,0,1}};
     
const int N[MAX][MAX] = {{1,0,0,0,1},
                         {1,1,0,0,1},
                         {1,0,1,0,1},
                         {1,0,0,1,1},
                         {1,0,0,0,1}};

const int O[MAX][MAX] = {{0,1,1,0},
                         {1,0,0,1},
                         {1,0,0,1},
                         {1,0,0,1},
                         {0,1,1,0}};

const int P[MAX][MAX] = {{1,1,1},
                         {1,0,1},
                         {1,1,1},
                         {1,0,0},
                         {1,0,0}};
     
const int Q[MAX][MAX] = {{0,1,1,0},
                         {1,0,0,1},
                         {1,0,0,1},
                         {1,0,1,0},
                         {0,1,0,1}};    
    
const int R[MAX][MAX] = {{1,1,1},
                         {1,0,1},
                         {1,1,0},
                         {1,0,1},
                         {1,0,1}};     

const int S[MAX][MAX] = {{1,1,1},
                         {1,0,0},
                         {1,1,1},
                         {0,0,1},
                         {1,1,1}};      

const int T[MAX][MAX] = {{1,1,1},
                         {0,1,0},
                         {0,1,0},
                         {0,1,0},
                         {0,1,0}};

const int U[MAX][MAX] = {{1,0,0,1},
                         {1,0,0,1},
                         {1,0,0,1},
                         {1,0,0,1},
                         {0,1,1,0}};

const int V[MAX][MAX] = {{1,0,0,0,1},
                         {1,0,0,0,1},
                         {1,0,0,0,1},
                         {0,1,0,1,0},
                         {0,0,1,0,0}};
     
const int W[MAX][MAX] = {{1,0,0,0,1},
                         {1,0,0,0,1},
                         {1,0,1,0,1},
                         {1,1,0,1,1},
                         {1,0,0,0,1}};
     
const int X[MAX][MAX] = {{1,0,1},
                         {1,0,1},
                         {0,1,0},
                         {1,0,1},
                         {1,0,1}};

const int Y[MAX][MAX] = {{1,0,1},
                         {1,0,1},
                         {0,1,0},
                         {0,1,0},
                         {0,1,0}};
     
const int Z[MAX][MAX] = {{1,1,1},
                         {1,0,1},
                         {0,1,0},
                         {1,0,0},
                         {1,1,1}}; 
               
///////////////////////////////////////////////////
//variables for painting part 
const int pwm_pin3   = 3;   // ШИМ-сигнал датчика
const int pwm_pin5   = 5;
long duration_left, duration_down;


int pwm_val_left   = 0; // значение ШИМ-сигнала
int pwm_val_down   = 0;
int MedArraySize = 9;
int mod_left, mod_down = 0;

int previous_mod_down;
int previous_mod_left;

boolean drew = false;


int Range_left[] = {0,0,0,0,0,0,0,0,0};
int Range_down[] = {0,0,0,0,0,0,0,0,0};

//////////////////////////////////////////////////


/////////////////////////////////////////////////
////for input interpretation
char input_string[10];
char input_char;
byte index = 0;
int printed = 0;

boolean Input_Received = false;

int Total_Array[MAX][10*MAX];
int temp[MAX][MAX];
int start_pos = 0;
int WIDTH = 0;
///////////////////////////////////////////////
SoftwareSerial XBee(10,3); // RX, TX

//Reset the board
void(*resetFunc)(void) = 0; 

void setup() {
  XBee.begin(9600);
  while (!XBee){
    delay(500);
  }
  delay(500);
  
  
  Serial.begin(9600);
  memset(Total_Array,0,sizeof(Total_Array));
  while (!Serial){
    delay(500);
  }
  delay(500);
  Input_Received = false;
  
  //reseted the aruduni message to pc
  XBee.print("&");
  
  //////////////////////////////////////////////
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);  
  
  pinMode(trigPin_left, OUTPUT);
  pinMode(trigPin_down, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(echoPin_down, INPUT);
  
  ////////////////////////////////////////////
  
  ////////////Initial Set-up/////////////////
  int set_count = 0;
  while (!Input_Received)
  {
     if (set_count == 0)
     {
       XBee.write("Please input a word!*");
       set_count = 1; 
     }
     delay(500);
     while(XBee.available() > 0 )
    {
      if (index < 9)
      {
        input_char = XBee.read();
        if (input_char == '&') resetFunc();
        else{
          input_string[index] = input_char;
          index++;
          input_string[index] = '\0';
        }
      }
      Input_Received = true;
    }  
  }
  //////////////////////////////////////////////////
  // reading string input and writing to an array//
  while (1)
  {
    if ((Input_Received == true) && (printed == 0))
    {
     XBee.write("\n Input string is : *"); 
     int i = 0;
      
     while (input_string[i] != '\0')
     {
        XBee.write(input_string[i]);
        i++;
     }
   
      XBee.write("*");
      printed = 1;
      matrix_transform(Total_Array, input_string);
      XBee.write("Transformed Input *"); 
      print_Total_Array(Total_Array,MAX,10*MAX);
      break;  
    }   
  }
  //end reading a string and transforming it into array///
 //////////////////////////////////////////////////////////
}

void loop() {
 
 digitalWrite(12,HIGH); //replace this with proper power supply! 
 
 // start of the drawing part
  while (!isEmpty(Total_Array))
  {
  
  // to reset arduino whenever new access is requested  
   while(XBee.available() > 0)
     if (XBee.read() == '&') resetFunc(); 
    
     print_Total_Array(Total_Array, MAX, 10*MAX);
    
     // receving values from HS-SR04 sensor
     for (int i = 0; i < MedArraySize; i++)
          {
            
            //left sensor
             digitalWrite(trigPin_left,LOW);
             delayMicroseconds(2); 
             
             digitalWrite(trigPin_left, HIGH);
             delayMicroseconds(10); 
             
             digitalWrite(trigPin_left, LOW);
             duration_left = pulseIn(echoPin_left, HIGH);
             Range_left[i] = duration_left/582;
             
             ///down (bottom) sensor
             digitalWrite(trigPin_down, LOW); 
             delayMicroseconds(2); 

             digitalWrite(trigPin_down, HIGH);
             delayMicroseconds(10); 

             digitalWrite(trigPin_down, LOW);
             duration_down = pulseIn(echoPin_down, HIGH);
             
             Range_down[i] = duration_down/582;
            delay(10);
          }
          
     //////////////////////////////////////////////////////////////
          //printing and retreving median
          //Serial.print("Unsorted: \n");
          //Serial.print("Left: ");
          //printArray(Range_left,MedArraySize);
          //Serial.print("Down: ");
          //printArray(Range_down,MedArraySize);
          //sort(Range_left,MedArraySize);
          //sort(Range_down,MedArraySize);
          //Serial.print("Sorted: \n");
          //Serial.print("Left: ");
          //printArray(Range_left,MedArraySize);
          //Serial.print("Down: ");
          //printArray(Range_down,MedArraySize);
          mod_left = mode(Range_left,MedArraySize);
          mod_down = mode(Range_down,MedArraySize);
          XBee.print("The left mode/median is: ");
          XBee.print(mod_left);
          XBee.print("*");
          XBee.print("The down mode/median is: ");
          XBee.print(mod_down);
          XBee.println("*");
         /////////////////////////////////////////////////////////////
         
         // drawing part. needed to be modified for while in the region -> draw /////
         if ((Total_Array[6-mod_down][mod_left-2] == 1) && (mod_down <=6) && (mod_left <= 6) && (mod_down >=2) && (mod_left >= 2))
         {
           digitalWrite(13,HIGH);

           drew = true;
           
           XBee.print("\n \n Draw " ); XBee.print("Array["); XBee.print(6-mod_down);XBee.print(";"); XBee.print(mod_left-2); XBee.print("]\n \n*");       
         }
       
       if ((drew) && ((previous_mod_down != mod_down) || (previous_mod_left != mod_left)))
       {
         Total_Array[6-previous_mod_down][previous_mod_left-2] = 0;
         digitalWrite(13,LOW);
         drew = false;
         //print_Total_Array(Total_Array, MAX, 10*MAX);
       }
       
       previous_mod_down = mod_down;
       previous_mod_left = mod_left;
           
    }  
  
 ////////////////////////////////////////////////////////////
 if (isEmpty(Total_Array) && (Input_Received))        
   XBee.print("Printing is completed. Congratulations! \n*");
   
 ////////////////////////////////////////////////////////////
 
}

boolean isEmpty(int Total_Array[MAX][10*MAX])
{
  for (int i=0; i < 10*MAX; ++i)
  {
    for (int j=0; j<MAX; ++j)
    {
      if (Total_Array[j][i] == 1)
        return false;
    }
  }
  return true;
}

void matrix_transform(int Total_Array[MAX][10*MAX], char input_string[10])
{
  int i=0;
  while (input_string[i] != '\0')
 {
    switch (input_string[i]){
      case 'A': {
        WIDTH = 3;
        concat_arrays(Total_Array,A,HEIGHT,WIDTH);
        break;}
      case 'B': {
        WIDTH = 3;
        concat_arrays(Total_Array,B,HEIGHT,WIDTH);
        break;}
      case 'C': {
        WIDTH = 3;
        concat_arrays(Total_Array,C,HEIGHT,WIDTH);
        break;}
       case 'D': {
        WIDTH = 4;
        concat_arrays(Total_Array,D,HEIGHT,WIDTH);
        break;}
       case 'E': {
        WIDTH = 3;
        concat_arrays(Total_Array,E,HEIGHT,WIDTH);
        break;}
       case 'F': {
        WIDTH = 3;
        concat_arrays(Total_Array,F,HEIGHT,WIDTH);
        break;}
       case 'G': {
        WIDTH = 4;
        concat_arrays(Total_Array,G,HEIGHT,WIDTH);
        break;}
       case 'H': {
        WIDTH = 4;
        concat_arrays(Total_Array,H,HEIGHT,WIDTH);
        break;}
       case 'I': {
        WIDTH = 1;
        concat_arrays(Total_Array,I,HEIGHT,WIDTH);
        break;}
       case 'J': {
        WIDTH = 3;
        concat_arrays(Total_Array,J,HEIGHT,WIDTH);
        break;}
       case 'K': {
        WIDTH = 3;
        concat_arrays(Total_Array,K,HEIGHT,WIDTH);
        break;}
       case 'L': {
        WIDTH = 3;
        concat_arrays(Total_Array,L,HEIGHT,WIDTH);
        break;}
       case 'M': {
        WIDTH = 5;
        concat_arrays(Total_Array,M,HEIGHT,WIDTH);
        break;}
       case 'N': {
        WIDTH = 5;
        concat_arrays(Total_Array,N,HEIGHT,WIDTH);
        break;}
       case 'O': {
        WIDTH = 4;
        concat_arrays(Total_Array,O,HEIGHT,WIDTH);
        break;}
       case 'P': {
        WIDTH = 3;
        concat_arrays(Total_Array,P,HEIGHT,WIDTH);
        break;}
       case 'Q': {
        WIDTH = 4;
        concat_arrays(Total_Array,Q,HEIGHT,WIDTH);
        break;}
       case 'R': {
        WIDTH = 3;
        concat_arrays(Total_Array,R,HEIGHT,WIDTH);
        break;}
       case 'S': {
        WIDTH = 3;
        concat_arrays(Total_Array,S,HEIGHT,WIDTH);
        break;}
       case 'T': {
        WIDTH = 3;
        concat_arrays(Total_Array,T,HEIGHT,WIDTH);
        break;}
       case 'U': {
        WIDTH = 4;
        concat_arrays(Total_Array,U,HEIGHT,WIDTH);
        break;}
       case 'V': {
        WIDTH = 5;
        concat_arrays(Total_Array,V,HEIGHT,WIDTH);
        break;}
       case 'W': {
        WIDTH = 5;
        concat_arrays(Total_Array,W,HEIGHT,WIDTH);
        break;}
       case 'X': {
        WIDTH = 3;
        concat_arrays(Total_Array,X,HEIGHT,WIDTH);
        break;}
       case 'Y': {
        WIDTH = 3;
        concat_arrays(Total_Array,Y,HEIGHT,WIDTH);
        break;}
       case 'Z': {
        WIDTH = 3;
        concat_arrays(Total_Array,Z,HEIGHT,WIDTH);
        break;}
    }
    i++;
 }
 XBee.write("*");
}

void print_Total_Array(const int a[MAX][10*MAX], int y_range, int x_range) {
  for (int y=0; y<y_range; ++y)
  {
    for (int x=0; x<x_range; ++x)
        if (a[y][x] == 1) XBee.print(a[y][x]);
      else XBee.write(" ");
    XBee.write("*");
  }
  XBee.write("*");
}

void sort(int *a, int n){
 for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

int mode(int *x,int n){

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while(x[i]==x[i+1]){
      count++;
      i++;
    }
    if(count>prevCount&count>maxCount){
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if(count==0){
      i++;
    }
    if(count==maxCount){//If the dataset has 2 or more modes.
      bimodal=1;
    }
    if(mode==0||bimodal==1){//Return the median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}

void concat_arrays(int Total_Array[MAX][10*MAX], const int temp[MAX][MAX], int y_range, int x_range)
{
  for (int y=0; y<y_range; ++y)
  {
    for (int x=0; x<x_range; ++x)
      if (temp[y][x] == 1) Total_Array[y][x+start_pos] = 1; 
  }
  start_pos = x_range+start_pos+1;
}
