#include "ovpressure.h"
#include <string.h>

OVPressure::OVPressure()
{
    memset(g_arr, 0, NUM);
}

/**
 * @brief OVPressure::init
 * @return
 */
bool OVPressure::init()
{
#ifdef ARDUINO
    //init BMP180
    return bmp.begin();
#else
    return true;
#endif
}

/**
 * @brief OVPressure::getPressure
 * @param sample count
 *
 * @return pressure in mmH2O
 */
uint16_t OVPressure::getPressure(int samples)
{
#ifdef ARDUINO
    long P, P_H2O;
    while(samples--)
    {
      P = 0;
      for(int i=0; i<(NUM-1); i++)
      {
          g_arr[i] = g_arr[i+1];
          P = P + g_arr[i];
      }
      g_arr[NUM-1] = bmp.readPressure();
      P = P + g_arr[NUM-1];
      P = P/5;
      P_H2O = P/98;       //98 H2O
    }
    return P_H2O;
#else
    return 0;
#endif
}

/**
 * @brief OVPressure::model
 * @param fx
 * @param F
 * @param hx
 * @param H
 */
void OVPressure::model(double fx[Nsta], double F[Nsta][Nsta], double hx[Mobs], double H[Mobs][Nsta])
{

}
