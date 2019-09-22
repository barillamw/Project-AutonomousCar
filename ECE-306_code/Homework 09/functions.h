//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

//Main
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);

// Initialization
void Init_Conditions(void);


// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);
void menu_switch(void);
void Resistor_Menu(void);
void Shapes_Menu(void);
void Song_Menu(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void); 
void time_display(void);

/*//State Machines
void paths(void);
void Straight (void);
void Circle (void);
void Triangle (void);
void Fig_Eight (void);
void wait_case(void);
void start_case(void);
void run_case_straight(void);
void run_case_circle(void);
void run_case_eight(void);
void run_case_triangle(void);
void end_case(void);
*/

//Wheels
//void Forward(void);
void Forward_Off(void);
//void Reverse(void);
void Reverse_Off(void);
//void CCW_Turn(void);
//void CW_Turn(void);
void All_Wheel_Off(void);


//ADC
void Init_ADC(void);
__interrupt void ADC_ISR(void);
void Begin_ADC(void);
void End_ADC(void);
void Line_Detect(void);
void Read_ADC(void);
void displayADC(void);

//BCD Converter
void HEXtoBCD (int hex_value );

//Intercept
void intercept(void);
void time_display(void);
void calibrate(void);
void intercept(void);
int simplePID(void);
void end_intercept(void);
void lineFollowing(void);
void wheelControl(int direction);

//cruise
void driveForward(unsigned int speedL, unsigned int speedR);
void driveReverse(void);
int drivePivot(int length);
void turnRight(void);
void turnLeft(void);
void spinInPlace(void);
void blackLine(void);

void drive(void);
char getCurrentState(void);
void followCircle(void);

//serial
void Init_Serial(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);
__interrupt void eUSCI_A1_ISR(void);
__interrupt void eUSCI_A0_ISR(void);
void out_character_A0 (char character);
void out_character_A1 (char character);
void Transmit_NCSU_A1(void);
void Transmit_Test_A1(void);
void Transmit_Text_A0(void);
void Transmit_Text_A1(void);
void Recieved_Text(void);
void Begin_Serial(void);
void End_Serial(void);
void Configure_Serial(void);
void display_Text_A0(void);
void display_Text_A1(void);
void clear(void);
void serialProcess(void);









