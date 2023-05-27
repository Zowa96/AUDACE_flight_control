#ifndef MPU
#define MPU

#define MPU_ADDR 0x68

#include <math.h>

void setupMPU() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0x5);   // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  // Try to initialize!
  /* * <pre>
 *          |   ACCELEROMETER    |           GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
 * 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
 * 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
 * 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
 * 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
 * 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
 * 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
 * 7        |   -- Reserved --   |   -- Reserved --   | Reserved
 * </pre>
 */
}

int* MPU_measure(){

  //procedure per campionare i dati da MPU

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);          // request a total of 14 registers
  int16_t AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int16_t AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int16_t AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  int16_t temperature = Wire.read() << 8 | Wire.read();
  int16_t GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  int16_t GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  int16_t GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  int MPU[6];
  MPU[0] = temperature;
  MPU[1] = AcX;
  MPU[2] = AcY;
  MPU[3] = AcZ;
  MPU[4] = GyX;
  MPU[5] = GyY;
  MPU[6] = GyZ;

  //normalizzo l'accelerazione di MPU
  int MPUN[6] = normalize(MPU);


  //restituisco l'array normalizzato
  
  return MPUN;
}
//funzione che normalizza la terna solidale all'accelerometro

int* normalize(int* MPU){
  // ro è definito come l'angolo tra l'asse X e il piano generato da X e Y normali
  double ro = atan(  MPU[1] / sqrt(  (MPU[2])^2  +  (MPU[3])^2  )  );
  // phi è definito come l'angolo tra l'asse Y e il piano generato da X e Y normali
  double phi = atan(  MPU[2] / sqrt(  (MPU[1])^2  +  (MPU[3])^2  )  );
  // theta è definito come l'angolo tra l'asse Z dell'accelerometro e l'asse Z normale
  double theta = atan(  sqrt(  (MPU[1])^2  +  (MPU[2])^2  ) / MPU[3] );

  // Una volta ricavati gli angoli calcolo le proiezioni della terna mobile su quella fissa

  int AcXN =  (MPU[1] * cos(ro)) - (MPU[3] * sin(ro));
  int AcYN =  (MPU[2] * cos(phi)) - (MPU[3] * cos(ro) * sin(theta)) - (MPU[1] * sin(theta) * sin(ro));
  int AcZN =  (MPU[3] * cos(ro) * cos(theta)) + (MPU[1] * sin(ro) * cos(theta)) + MPU[2]  * sin(phi);

  MPU[1] = AcXN;
  MPU[2] = AcYN;
  MPU[3] = AcZN;

  return MPU;


}
#endif