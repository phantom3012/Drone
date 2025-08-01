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
#ifndef MAIN_H
#define MAIN_H


////////////////////////////////////////////////
// Main Loop task manager related stuff next //
//////////////////////////////////////////////
typedef enum {TMR_UPDT,DBG_CMD_PROC,GPS_PCKT_PROC,FC_PCKT_PROC} task_t;
typedef struct {
    task_t task;        // enumerated type describing task to call
    uint8_t priority;     // can be 0 thru 4 with 0 being highest priority
} task_queue_t;

/////////////////////////////////////////////////
// GP_timer related events and structure next //
///////////////////////////////////////////////
typedef enum { TIMER1 } timer_evt_t;
typedef struct {
    timer_evt_t evt;
    uint16 time;
} GP_timer_t;


////////////////////////////////////////////////////////////////
// Define enumerated types for other "states" of the machine //
//////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// Declare any global variables accessed from multiple files //
//////////////////////////////////////////////////////////////
volatile unsigned char rx_bytes_dbg[16];         // global to pass back received byte
volatile unsigned char rx_bytes_dbg_buff[16];
volatile uint8_t num_rx_bytes_dbg;              // glabal to pass back number of received bytes
volatile uint8_t num_rx_bytes_dbg_buff;
volatile unsigned char rx_bytes_gps[72];         // global to pass back received byte
volatile unsigned char rx_bytes_gps_buff[72];
volatile uint8_t num_rx_bytes_gps;
volatile uint8_t num_rx_bytes_gps_buff;
volatile unsigned char rx_bytes_FC[6];         // global to pass back received byte
volatile unsigned char rx_bytes_FC_buff[6];
volatile uint8_t num_rx_bytes_FC_buff;
volatile uint8_t num_rx_bytes_FC;
volatile uint8_t GPS_UART_tmr;
volatile uint8_t num_tasks;


///////////////////////////////////////
// Declare any function proto-types //
/////////////////////////////////////
void init_periphs(void);
void display_msg(void);
void display_msg_FC(void);
void append_msg(char *);
void append_char(char);
void append_num16(uint16_t);
void append_num32(uint32_t);
void set_GP_timer(timer_evt_t, uint16_t);
void cancel_GP_timer(timer_evt_t);
void process_GP_timer_evt(timer_evt_t);
void processDbgCmd(void);
void processFC_Pckt(void);
void processGPS_Pckt(void);
void enqueue_task(task_t, uint8_t);
task_t dequeue_task(void);
void LED_display(uint8_t);


////////////////////////////////////////////////////////////////
// Decare any defines needed for readability/maintainability //
//////////////////////////////////////////////////////////////
#define MAX_NUM_TASKS 5   // maximum number of tasks in the event queue


#endif /* MAIN_H */ 

/* [] END OF FILE */
