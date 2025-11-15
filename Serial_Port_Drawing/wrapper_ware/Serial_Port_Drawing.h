#ifndef  VOFA_C_WRAPPER_H
#define  VOFA_C_WRAPPER_H


/*C语言接口*/
#ifdef __cplusplus
extern "C" {
#endif



/*-------------以下为辅助数据收集模块-------------*/
typedef struct Collect_Array collect_array;
collect_array* array_create(void);
void array_destroy(collect_array* handle);

void array_init(collect_array* handle,int data_quantity_in);           //初始化数组
void array_write(collect_array* handle,int index,float enter_data);    //写入数据

float* array_point(collect_array* handle);     //获取数组指针
int    get_quantity(collect_array* handle);    //获取数组长度

void clear_array(collect_array* handle,float* array_point);            //清空数组


/*-------------以下为浮点数调试模块接口函数（改进版本）-------------*/
typedef struct Float_Handle float_handle;  // vofa句柄
float_handle* float_create(void);          // 创建句柄
void float_destroy(float_handle* handle);  // 销毁句柄

void general_init(float_handle* handle,UART_HandleTypeDef* huart_in); // 帧尾和串口初始化
void buffer_init(float_handle* handle,int data_quantity_in);          // 创建缓冲区
void float_write(float_handle* handle,float* data_point_in);          // 输入数据
void float_send(float_handle* handle);                                // 发送数据 
void buffer_free(float_handle* handle);                               // 释放缓冲区


/*-------------以下为单浮点数调试模块（改进版）---------------*/
typedef struct Single_Float_Handle single_float_handle;  // vofa句柄
single_float_handle* single_create(void);           // 创建句柄
void single_destroy(single_float_handle* handle);   // 销毁句柄

void single_float(single_float_handle* handle,UART_HandleTypeDef* huart,float* data_point);// 单浮点数发送





#ifdef __cplusplus
}
#endif


#endif



