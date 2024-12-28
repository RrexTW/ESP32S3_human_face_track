#include"iot_servo.h"
#include "esp_log.h"

#define SERVO_CH0_PIN (gpio_num_t)2
#define SERVO_CH1_PIN (gpio_num_t)14  //避免與鏡頭腳位衝突

servo_config_t servo_cfg = {
    .max_angle = 180,
    .min_width_us = 500,
    .max_width_us = 2500,
    .freq = 50,
    .timer_number = LEDC_TIMER_0,
    .channels = {
        .servo_pin = {
            SERVO_CH0_PIN,
            SERVO_CH1_PIN,
        },
        .ch = {
            LEDC_CHANNEL_0,
            LEDC_CHANNEL_1,
        },
    },
    .channel_number = 2,
} ;

static float x_angle=90;
static float y_angle=85;

void detected(float x,float y,int x_cent,int y_cent,const char*TAG){

/*
俯仰控制伺服馬達角度float(30~170)
左右搖擺伺服馬達角度float(10~170)
x,y為人臉位置/x_cent,y_cent為畫面中心位置
*/
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
    if(x<x_cent-20&&x_angle<170){
        if(x<x_cent-40)  x_angle+=5;
        x_angle+=5;
    }else if (x>x_cent+20&&x_angle>10){
        if(x>x_cent+40) x_angle-=5;
        x_angle-=5;
    }

    if(y>y_cent+10&&y_angle<170){
        if(y>y_cent+20) y_angle+=5;
        y_angle+=5;
    }else if (y<y_cent-10&&y_angle>=30){
        if (y<y_cent-20) y_angle-=5;
        y_angle-=5;
    }
//伺服馬達執行
    ESP_LOGI(TAG, "servo angle %.2f %.2f",x_angle,y_angle);
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, x_angle);
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 1, y_angle);
    
}

void servo_testmax(){
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, 170);
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 1, 170);
}
