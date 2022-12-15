/***
@Author: Vincent Chan
@About: Motor Control libraries
***/
#include "main.h"

/*** Enabled peripherals ***/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

/*** User defined variables ***/
const int max_register_value = 3600;
enum MOTOR_INDEX{MOTOR1,MOTOR2,MOTOR3,MOTOR4};
enum MOTOR_DIRECTION{CLOCKWISE,COUNTERCLOCKWISE,BREAK};

/*** Function Prototypes ***/
void motor_peripherals_init(MOTOR_INDEX motor);
void motor_controller(MOTOR_INDEX motor,MOTOR_DIRECTION turn,int duty_cycle);
int calculate_MOTOR_timer_register(int percentage,double counter_max);

/*** Function Definition ***/
// 1. Enable motor peripherals based on MOTOR_INDEX
void motor_peripherals_init(MOTOR_INDEX motor)
{
	int x = 0;
	if(motor == MOTOR1)
	{
		// MOTOR1 with ENCODER 3
		// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
		HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
		HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
	}else if(motor == MOTOR2)
	{
		// MOTOR2 with ENCODER 4 [Align with BAT IN in the motor drive]
		// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
		HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
		HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	}else if (motor == MOTOR3)
	{
		// TO-DO: Configure motor 3
		HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
		HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
		x = 0;
	}else{
		// TO-DO: Configure motor 4
		HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
		HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
		x = 0;
	}
	x++;
}

// 2. Motor Controller
void motor_controller(MOTOR_INDEX motor,MOTOR_DIRECTION turn,int duty_cycle,int max_counter)
{
	int x = 0;
	duty_cycle = duty_cycle;
	if(motor == MOTOR1)
	{
		if(turn == CLOCKWISE)
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR1_IN1_GPIO_Port, MOTOR1_IN1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTOR1_IN2_GPIO_Port, MOTOR1_IN2_Pin,GPIO_PIN_RESET);
		}else if (turn == COUNTERCLOCKWISE)
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR2_IN1_GPIO_Port, MOTOR1_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR2_IN2_GPIO_Port, MOTOR1_IN2_Pin,GPIO_PIN_SET);
		}else
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR1_IN1_GPIO_Port, MOTOR1_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR1_IN2_GPIO_Port, MOTOR1_IN2_Pin,GPIO_PIN_RESET);
		}
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,calculate_MOTOR_timer_register(duty_cycle, max_counter));
	}else if(motor == MOTOR2)
	{
		if(turn == CLOCKWISE)
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR2_IN1_GPIO_Port, MOTOR2_IN1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTOR2_IN2_GPIO_Port, MOTOR2_IN2_Pin,GPIO_PIN_RESET);
		}else if (turn == COUNTERCLOCKWISE)
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR2_IN1_GPIO_Port, MOTOR2_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR2_IN2_GPIO_Port, MOTOR2_IN2_Pin,GPIO_PIN_SET);
		}else
		{
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
			HAL_GPIO_WritePin(MOTOR2_IN1_GPIO_Port, MOTOR2_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR2_IN2_GPIO_Port, MOTOR2_IN2_Pin,GPIO_PIN_RESET);
		}
			// FILL IT IN BY YOURSELF (╯ ͡❛ ‿ ͡❛)╯┻━┻
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,calculate_MOTOR_timer_register(duty_cycle, max_counter));
	}else if (motor == MOTOR3)
	{
		// TO-DO: Configure motor 3
		x = 0;
	}else{
		// TO-DO: Configure motor 4
		x = 0;
	}
	x++;
}	

// 3. Convert duty cycle to counter register value
int calculate_MOTOR_timer_register(int percentage,double counter_max)
{
	return (int)((percentage*counter_max)/100);
}