#ifndef VOFA_DEBUG_H
#define VOFA_DEBUG_H
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif


/*  
 * 简介：这是一个最初为了适配vofa+进行串口绘图的模块，按包含类的添加顺序——draw_float、draw_array、draw_float_single
 * 各项类简介：1.draw_array: 辅助收集数据的数组、2.draw_float: 多浮点数调试，将整个数组发送出去、3.draw_float_single: 单浮点数调试
 * 
 * 碎碎念：这个模块还是有些欠缺的，我认为最好的办法是设定基类，基类内部所有函数都是虚函数，然后在继承的子类中实现功能。
 * 做梦：让这个模块可以适配常见的串口调试工具！！！
 * 
 * 最后的小祝福：希望你用起来会比较舒心~ (*^▽^*)
 * tingxu_tesu
 * 2021.07.05
*/
#pragma once
class draw_array//辅助收集的数组，尽量减少对原码的添加和修改
{
    private:
    int data_quantity;// 数据数量
    size_t data_type;// 数据类型
    float* data_array_point;// 数据数组指针
    
    public:
    void array_init(int data_quantity_in , size_t data_type = sizeof(float));// 初始化
    void array_write(int index , float enter_data);// 写入数据,零散数据最好多次调用写入
    void clear_array(float* array_point);
    
    float* get_array();     //获取数组指针
    int  get_quantity();    // 获取数据数量
};


#pragma once
class draw_float
{
    private:
        /* 数据成员 */
        int data_quantity;                  // 数据数量
        uint8_t tail[4];                    //帧尾常数
        float* tx_buffer_point;             // 发送缓存变量
        size_t data_type;                   // 数据类型表示
        float temp_buffer[1];                  // 临时发送缓存
        UART_HandleTypeDef* huart_piont;    // 串口句柄

    public:
        /* 函数成员 */
        void general_init(UART_HandleTypeDef* huart);             // 通用初始化

        void buffer_init(int data_quantity_in,size_t data_type_in = sizeof(float));    // 缓冲区初始化

        void float_write(float* data_point_in);                     // 指针传参数据写入

        void float_send(void);                                    // 浮点数 数据发送

        void buffer_free(void);                                   // 缓冲区释放

};


// #pragma once
// class draw_float_single:draw_float
// {
//     public:
//         void single_float(UART_HandleTypeDef* huart,float* data_point);             // 快速浮点数发送
// };




#pragma once
class draw_float_single:draw_float// 快速浮点数调试
{ 
    public:
        void single_float(UART_HandleTypeDef* huart,float* data_point);// 单浮点数发送
};

