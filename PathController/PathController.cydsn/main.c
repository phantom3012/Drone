/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"
#include "main.h"
#include "MOSI.h"
#include "SCLK.h"

#include <stdio.h>
#include <inttypes.h>

#include "sanitize.h"
#include "algorithm.h"
#include "cordic.h"

///////////////////////////
// Define globals below //
/////////////////////////
volatile char debug_msg[256];
volatile char fc_msg[256];
volatile uint8_t msg_ptr_head = 0, msg_ptr_tail = 0;
volatile uint8_t fc_msg_ptr_head = 0, fc_msg_ptr_tail = 0;
volatile task_queue_t task_queue[MAX_NUM_TASKS]; // hold up to 4 tasks descriptions that should be called from main
GP_timer_t GP_timer[MAX_NUM_TASKS];              // can have up to 5 concurrent GP timer events
uint8_t num_GP_timers = 0;                       // number of currently active GP timers
timer_evt_t GP_evt;                              // timer event is a timer name and how many WDT ticks out it is.
uint8_t tmr_dec;                                 // used to decimate WDT calls to compute seconds
uint16_t sec;                                    // seconds since power up
DroneNavigator_t virus;
const double TARGET_LAT = 43.06;
const double TARGET_LON = 89.28;
const double DT_S = 0.1;
GpsData_t gps_data;
GPSCoordinate_t coords = {0.0,0.0};

int main(void)
{
  static task_t active_task;
  uint16_t x;             // generic loop index variable
  uint8_t curr_GP_timers; // used to hold current number of GP_timers

  CyGlobalIntEnable; /* Enable global interrupts. */

  /////////////////////////
  // Initialize Globals //
  ///////////////////////
  for (x = 0; x < 4; x++)
  { // ensure no GP timers set
    GP_timer[x].time = 0;
  }
  num_rx_bytes_dbg_buff = 0;
  num_rx_bytes_gps_buff = 0;
  num_rx_bytes_FC = 0;

  ////////////////////////
  // Initialize locals //
  //////////////////////
  sec = 0;

  //////////////////////////////////////////////
  // Fire up peripherals needed for main app //
  ////////////////////////////////////////////
  init_periphs();

  ///////////////////////////
  // Main loop start here //
  /////////////////////////
  for (;;)
  {

    //////////////////////////
    // Task Handler below: //
    ////////////////////////
    if (num_tasks)
    {
      CyGlobalIntDisable;
      active_task = dequeue_task();
      CyGlobalIntEnable;
      switch (active_task)
      {
      case TMR_UPDT:
      { // roughly 200 time/sec
        tmr_dec++;
        if (tmr_dec == 199)
        { // ~1Hz rate
          tmr_dec = 0;
          sec++; // increment seconds
          if (sec == 6)
          {
            // set_GP_timer(TIMER1,1200);
            //  do something at 6 seconds in (left in as an example)
            // append_msg("I am alive!\n");
          }
          LED_display(sec);
        }
        GPS_UART_tmr++;
        /////////////////////////////////////////////////////
        // When not in middle of a reception the tmr goes //
        // from 6 -> 0x18.  If in a reception it starts  //
        // at 0 and if it hits 5 a timeout occurs.      //
        /////////////////////////////////////////////////
        if (GPS_UART_tmr == 0x18)
          GPS_UART_tmr = 6;    // beyond timeout
        if (GPS_UART_tmr == 5) // UART timeout, discard current buffer
          num_rx_bytes_gps_buff = 0;

        //////////////////////////////////////////////////
        // Decrement GP timers and look for expiration //
        ////////////////////////////////////////////////
        x = 0;
        curr_GP_timers = num_GP_timers; // num_GP timers might get incremented whild processing GP timers
        while (x < curr_GP_timers)
        {
          if (GP_timer[x].time)
          {
            GP_timer[x].time--;
            if (GP_timer[x].time == 0)
            {
              process_GP_timer_evt(GP_timer[x].evt);
              if (x < (curr_GP_timers - 1))
                x--; // if we shifted valid timer up we need to process it.
            }
          }
          x++;
        }
        break;
      }
      case DBG_CMD_PROC:
      {
        /// A command ending in carriage return (0x0D) has come in via the debug port ///
        /// The data bytes reside in an array called rx_bytes_dbg[]
        /// The number of bytes there is contained in num_rx_bytes_dbg
        processDbgCmd();
        break;
      }
      case GPS_PCKT_PROC:
      {
        /// A packet has come in the GPS port ///
        /// The data bytes reside in an array called rx_bytes_gps[]
        /// The number of bytes there is contained in num_rx_bytes_gps
        processGPS_Pckt();
        break;
      }
      case FC_PCKT_PROC:
      {
        /// A packet has come in the FC port ///
        /// The data bytes reside in an array called rx_bytes_FC[]
        /// The number of bytes is always 5 [0:4]
        processFC_Pckt();
        break;
      }
      default:
      {
        append_msg("ERR: unhandle task in task queue ");
        append_num16((uint8)active_task);
        append_msg("\r");
        break;
      }
      }
    }
    //////////////////////////////////////////////////////
    // If there is data in debug message then print it //
    ////////////////////////////////////////////////////
    /*if ((msg_ptr_tail!=msg_ptr_head) && (num_tasks==0)) {
        display_msg();
    }*/
    if ((fc_msg_ptr_tail != fc_msg_ptr_head) && (num_tasks == 0))
    {
      display_msg_FC();
    }
  }
}

void display_msg_FC(void)
{
  //// Send a max of 4-bytes at a time ////
  uint8_t cnt;

  cnt = 0;
  /// Wait for tx buffer empty ///
  // while (UART_FC_SpiUartGetTxBufferSize()) { ; }

  /// Send 4-bytes or remainder of message ///
  while ((fc_msg_ptr_tail != fc_msg_ptr_head) && (cnt < 4))
  {
    UART_FC_UartPutChar(fc_msg[fc_msg_ptr_tail]);
    fc_msg_ptr_tail = ((fc_msg_ptr_tail + 1) & 0x00FF); // modulo 256
    cnt++;
  }
}

void display_msg(void)
{
  //// Send a max of 4-bytes at a time ////
  uint8_t cnt;

  cnt = 0;
  /// Wait for tx buffer empty ///
  // while (UART_DBG_SpiUartGetTxBufferSize()) { ; }

  /// Send 4-bytes or remainder of message ///
  while ((msg_ptr_tail != msg_ptr_head) && (cnt < 4))
  {
    UART_DBG_UartPutChar(debug_msg[msg_ptr_tail]);
    msg_ptr_tail = ((msg_ptr_tail + 1) & 0x00FF); // modulo 256
    cnt++;
  }
}

void append_msg(char *new_msg)
{
  while (*new_msg != 0x00)
  {
    debug_msg[msg_ptr_head] = *new_msg;
    msg_ptr_head = ((msg_ptr_head + 1) & 0x00FF); // modulo 256
    new_msg++;
  }
}

void append_msg_FC(char *new_msg)
{
  while (*new_msg != 0x00)
  {
    fc_msg[fc_msg_ptr_head] = *new_msg;
    fc_msg_ptr_head = ((fc_msg_ptr_head + 1) & 0x00FF); // modulo 256
    new_msg++;
  }
}

void append_char(char byte)
{
  debug_msg[msg_ptr_head] = byte;
  msg_ptr_head = ((msg_ptr_head + 1) & 0x00FF); // modulo 256
}

void append_char_FC(char byte)
{
  fc_msg[fc_msg_ptr_head] = byte;
  fc_msg_ptr_head = ((fc_msg_ptr_head + 1) & 0x00FF); // modulo 256
}

void append_num16(uint16 num)
{
  uint16 count[5];
  uint16 base[5];
  char nonzero_found;
  int16 digit;
  char temp[2];

  base[0] = 1;
  base[1] = 10;
  base[2] = 100;
  base[3] = 1000;
  base[4] = 10000;
  temp[1] = 0;       // null terminate
  nonzero_found = 0; // flag as to when to print digit

  for (digit = 4; digit >= 0; digit--)
  {
    count[digit] = 0;
    while (num >= base[digit])
    {
      count[digit]++;
      num -= base[digit];
    }
    if ((count[digit]) || (nonzero_found) || (digit == 0))
    {
      nonzero_found = 1;
      temp[0] = (char)(count[digit] + 48);
      debug_msg[msg_ptr_head] = temp[0];
      msg_ptr_head = ((msg_ptr_head + 1) & 0x00FF); // modulo 256
    }
  }
  debug_msg[msg_ptr_head] = 0x00; // null terminate
}
void append_num32_FC(uint32_t num)
{
  uint8 count[10];
  uint32 base[10];
  char nonzero_found;
  int8 digit;
  char temp[2];

  base[0] = 1;
  base[1] = 10;
  base[2] = 100;
  base[3] = 1000;
  base[4] = 10000;
  base[5] = 100000;
  base[6] = 1000000;
  base[7] = 10000000;
  base[8] = 100000000;
  base[9] = 1000000000;
  temp[1] = 0;       // null terminate
  nonzero_found = 0; // flag as to when to print digit

  for (digit = 9; digit >= 0; digit--)
  {
    count[digit] = 0;
    while (num >= base[digit])
    {
      count[digit]++;
      num -= base[digit];
    }
    if ((count[digit]) || (nonzero_found) || (digit == 0))
    {
      nonzero_found = 1;
      temp[0] = (char)(count[digit] + 48);
      fc_msg[fc_msg_ptr_head] = temp[0];
      fc_msg_ptr_head = ((fc_msg_ptr_head + 1) & 0x00FF); // modulo 256
    }
  }
  fc_msg[fc_msg_ptr_head] = 0x00; // null terminate
}

void append_num32(uint32_t num)
{
  uint8 count[10];
  uint32 base[10];
  char nonzero_found;
  int8 digit;
  char temp[2];

  base[0] = 1;
  base[1] = 10;
  base[2] = 100;
  base[3] = 1000;
  base[4] = 10000;
  base[5] = 100000;
  base[6] = 1000000;
  base[7] = 10000000;
  base[8] = 100000000;
  base[9] = 1000000000;
  temp[1] = 0;       // null terminate
  nonzero_found = 0; // flag as to when to print digit

  for (digit = 9; digit >= 0; digit--)
  {
    count[digit] = 0;
    while (num >= base[digit])
    {
      count[digit]++;
      num -= base[digit];
    }
    if ((count[digit]) || (nonzero_found) || (digit == 0))
    {
      nonzero_found = 1;
      temp[0] = (char)(count[digit] + 48);
      debug_msg[msg_ptr_head] = temp[0];
      msg_ptr_head = ((msg_ptr_head + 1) & 0x00FF); // modulo 256
    }
  }
  debug_msg[msg_ptr_head] = 0x00; // null terminate
}

void append_float_FC(double val, int precision)
{
  if (val < 0)
  {
    append_char_FC('-');
    val = -val;
  }

  uint32_t int_part = (uint32_t)val;
  append_num32_FC(int_part);
  append_char_FC('.');

  double frac_part = val - int_part;
  for (int i = 0; i < precision; i++) {
    frac_part *= 10.0;
    int digit = (int)frac_part;
    append_char_FC((char)(digit + '0'));
    frac_part -= digit;
  }
}

void set_GP_timer(timer_evt_t EVT, uint16_t ticks)
////////////////////////////////////////////
// Every count of ticks = 1/64 of second //
//////////////////////////////////////////
{
  uint8_t indx;

  if (num_GP_timers < 5)
  {
    indx = 0;
    //////  Look for a timer of that EVT type already and update time ////
    while (indx < num_GP_timers)
    {
      if (GP_timer[indx].evt == EVT)
      {
        // append_msg("updating timer");
        // append_num16((uint16_t)(EVT));
        // append_msg("\r\n");
        GP_timer[indx].time = ticks;
        indx = 5; // set greater as indication of found
      }
      indx++;
    }
    if (indx == num_GP_timers)
    {
      //// This is a new timer event so create it ////
      GP_timer[num_GP_timers].evt = EVT;
      GP_timer[num_GP_timers].time = ticks;
      num_GP_timers++;
    }
  }
  else
  {
    append_msg("ERR: can't add timer EVT ");
    append_num16((uint16_t)(EVT));
    append_msg("\r\n");
  }
}

void cancel_GP_timer(timer_evt_t EVT)
{
  uint8_t x, y;
  uint8_t found = 0;

  for (x = 0; x < num_GP_timers; x++)
  {
    if (GP_timer[x].evt == EVT)
    {
      found = 1;
      GP_timer[x].time = 0;
      num_GP_timers--;
      for (y = x; y < num_GP_timers; y++)
      {
        GP_timer[y] = GP_timer[y + 1];
      }
    }
  }
  if (!found)
  {
    append_msg("WARN: could not cancel timer EVT ");
    append_num16((uint16_t)(EVT));
    append_msg("\n\r");
  }
}

void process_GP_timer_evt(timer_evt_t EVT)
{
  cancel_GP_timer(EVT); // cancel current timer event now we are processing it
  switch (EVT)
  {
  case TIMER1:
  {
    append_msg("Hello World!");
    break;
  }

  default:
  {
    append_msg("ERR: unknown GP timer event\r\n");
    break;
  }
  }
}

void enqueue_task(task_t task_name, uint8_t priority)
{
  if (num_tasks < MAX_NUM_TASKS)
  {
    task_queue[num_tasks].task = task_name;
    task_queue[num_tasks].priority = priority;
    num_tasks++;
  }
  else
  {
    append_msg("ERR: tsk Q full:");
    append_num16((uint16)task_name);
  }
}

task_t dequeue_task(void)
{
  uint8 x, highest_prior, highest_location;
  task_t highest_task;

  if (num_tasks)
  {
    highest_location = 0;
    highest_task = task_queue[0].task;
    highest_prior = task_queue[0].priority;

    for (x = 1; x < num_tasks; x++)
    {
      if (task_queue[x].priority < highest_prior)
      {
        highest_location = x;
        highest_prior = task_queue[x].priority;
        highest_task = task_queue[x].task;
      }
    }
    ////// Now delete the entry found //////
    num_tasks--;
    for (x = highest_location; x < num_tasks; x++)
    {
      task_queue[x].task = task_queue[x + 1].task;
      task_queue[x].priority = task_queue[x + 1].priority;
    }
  }
  else
  {
    append_msg("ERR: no tasks in queue to dequeue\r");
  }
  return (highest_task);
}

/////////////////////////////
// Initialize Peripherals //
///////////////////////////
void init_periphs(void)
{
  UART_DBG_Start(); // start debug/command interface UART
  UART_DBG_SCB_IRQ_Start();

  UART_GPS_Start(); // start UART for GPS interface
  UART_GPS_SCB_IRQ_Start();

  UART_FC_Start();
  UART_FC_SCB_IRQ_Start();

  WDT_ISR_Start();
  LED_display(0x00);
}

void LED_display(uint8_t LEDs)
{
  if (LEDs & 0x40)
    LED6_Write(0x01);
  else
    LED6_Write(0x00);
  if (LEDs & 0x20)
    LED5_Write(0x01);
  else
    LED5_Write(0x00);
  if (LEDs & 0x10)
    LED4_Write(0x01);
  else
    LED4_Write(0x00);
  if (LEDs & 0x08)
    LED3_Write(0x01);
  else
    LED3_Write(0x00);
  if (LEDs & 0x04)
    LED2_Write(0x01);
  else
    LED2_Write(0x00);
  if (LEDs & 0x02)
    LED1_Write(0x01);
  else
    LED1_Write(0x00);
  if (LEDs & 0x01)
    LED0_Write(0x01);
  else
    LED0_Write(0x00);
}

void processDbgCmd(void)
{
  // append_msg_FC(rx_bytes_dbg);

  parse_gps(rx_bytes_dbg, &gps_data);

  /*//-----------Debug----------//
  char latitude[35];
  char longitude[35];
  int valid = gps_data.is_valid;
  snprintf(latitude, sizeof(latitude), "%" PRId32 "\n", gps_data.lat_dege6);
  snprintf(longitude, sizeof(longitude), "%" PRId32 "\n", gps_data.lon_dege6);
  append_msg_FC(latitude);
  append_msg_FC(longitude);
  append_num32_FC(valid);
  append_msg_FC("\n--------------------\n");
  //---------Debug----------//*/

  coords.lat = ((double)gps_data.lat_dege6) / 1000000.0;
  coords.lon = ((double)gps_data.lon_dege6) / 1000000.0;
  // Debug print for coords
  /*append_msg_FC("DBG: lat=");
  append_float_FC(coords.lat, 6);
  append_msg_FC(" lon=");
  append_float_FC(coords.lon, 6);
  append_msg_FC("\n");*/

  // uint8_t indx;

  /* if (!strncmp("DoSomething1",rx_bytes_dbg,12)) {
    append_msg("You typed DoSomething1\n");
  }
  else if (!strncmp("DoSomething2",rx_bytes_dbg,12)) {
    append_msg("You typed DoSomething2\n");
  }
  else {
      append_msg("Unrecognized command\r\n");
      for (indx=0; indx<num_rx_bytes_dbg; indx++) {
          append_char(rx_bytes_dbg[indx]);
      }
      append_msg("\n");
  }*/
}

void processFC_Pckt(void)
{

  // cancel_GP_timer(TIMER1);
  // append_msg("Cancelled timer1");

  uint8_t packet_type = 0x00;
  uint8_t payload_bytes[4];
  for (uint8_t i = 0; i < num_rx_bytes_FC - 1; i++)
  {
    append_char_FC(rx_bytes_FC[i]);
    uint8_t value = rx_bytes_FC[i] - '0';
    //append_num32_FC(value);
    //append_msg_FC("\n");
    if (value < 0 || value > 9)
    {
      append_msg_FC("Unreal_FC");
      return;
    }
    else
    {
      if (i == 0)
      {
        packet_type = value;
      }
      else
      {
        payload_bytes[i - 1] = value;
      }
    }
  }
  /*append_num32_FC(payload_bytes[0]);
  append_num32_FC(payload_bytes[1]);
  append_num32_FC(payload_bytes[2]);
  append_num32_FC(payload_bytes[3]);*/

  switch (packet_type)
  {
  case 0x01:
  {
    // Pilot control (learn attitude vs direction)
  }
  break;
  case 0x02:
  {
    // recheck attitude vs direction (pass bearing to virus/initalize navigation)
  }
  break;
  case 0x03:
  {
    // try to hover with home coords (gather last pitch and roll commands and start virus to hover over current position)
    // wait to start the navigation till you have a lock on the gps coords
  }
  break;
  case 0x04:
  {
    // Check if coords are set
    if (coords.lat == 0.0 && coords.lon == 0.0)
    {
      append_msg_FC("Coords not set or invalid GPS\n");
    }
    /*append_msg_FC("lat: ");
    append_float_FC(coords.lat, 6);
    append_msg_FC("\nlon: ");
    append_float_FC(coords.lon, 6);
    append_msg_FC("\n");*/

    double pitch_cmd;
    double roll_cmd;
    // stop algorithm if started and restart to navigate home
    // reset/re-initalize the navigation and set target coords as selected home position (have a global default home coords)
    navigator_init(
      &virus,
      TARGET_LAT,
      TARGET_LON,
      0.6,
      15.0,
      15.0,
      5.0);
    append_msg_FC("Reached case 4!");

    bool target_reached = navigator_update(
      &virus,
      coords,
      0.0, //heading to be updated after calculation (case 1)
      DT_S,
      &pitch_cmd,
      &roll_cmd);
    append_msg_FC("PITCH:");
    append_float_FC(pitch_cmd,6);
    append_msg_FC(",ROLL:");
    append_float_FC(roll_cmd, 6);
    
  }
  break;
  case 0x05:
  {
    // stop algorithm and give pilot back the control
  }
  break;
  default:
  {
    append_msg_FC("[ERROR]Unknown_packet_type");
    return;
  }
  break;
  }

  /*for (uint8_t i = 0; i < num_rx_bytes_FC; i++) {
      fc_msg[fc_msg_ptr_head] = rx_bytes_FC[i];
      fc_msg_ptr_head = ((fc_msg_ptr_head+1)&0x00FF);       // modulo 256
  }
  num_rx_bytes_FC = 0;
  display_msg_FC();*/
}

void processGPS_Pckt(void)
{
}

/* [] END OF FILE */
