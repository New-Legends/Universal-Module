#include "Serial_Port_Drawing.hpp"
#include "Serial_Port_Drawing_Wrapper.h"
#include <new>

/* C++包装接口~ */
extern"C"
{



    /*------------------------以下为辅助数据收集模块-----------------------*/
                                /*实例管理函数*/
    // 创建句柄
    Collect_Array* array_create(void)
    {return reinterpret_cast<collect_array*>(new draw_array());}
    // 销毁句柄
    void array_destroy(collect_array* handle)
    {delete reinterpret_cast<draw_array*>(handle);}



                                /*实例操作函数*/
    // 初始化
    void array_init(collect_array* handle,int data_quantity_in)
    {
        if(handle){
            reinterpret_cast<draw_array*>(handle)->array_init(data_quantity_in);
        }
    }
    // 数据写入
    void array_write(collect_array* handle,int index,float enter_data)
    {
        if(handle){
            reinterpret_cast<draw_array*>(handle)->array_write(index,enter_data);
        }
    }
    // 数据清空
    void clear_array(collect_array* handle,float* array_point)
    {
        if(handle){
            reinterpret_cast<draw_array*>(handle)->clear_array(array_point);
        }
    }



                                /*实例描述函数*/
    // 获取数据数量
    int    get_quantity(collect_array* handle)
    {
        if(handle){
            return reinterpret_cast<draw_array*>(handle)->get_quantity();
        }
        else{
            return -1;
        }
    }
    // 获取数据指针
    float* array_point(collect_array* handle)
    {
        if(handle){
            return reinterpret_cast<draw_array*>(handle)->get_array();
        }
        else{
            return NULL;
        }
    }





    /*-------------以下为浮点数调试模块接口函数（改进版本）----------------*/
                            /*实例管理函数*/
    // 创建句柄
    Float_Handle* float_create()
    {return reinterpret_cast<float_handle*>(new draw_float());}
    // 销毁句柄
    void vofa_destroy(float_handle* handle)
    {delete reinterpret_cast<draw_float*>(handle);}


                            /*实例操作函数*/
    // 初始化
    void general_init(float_handle* handle, UART_HandleTypeDef* huart_in)
    {
        if(handle){
            reinterpret_cast<draw_float*>(handle)->general_init(huart_in);
        }
    }
    // 缓冲区初始化
    void buffer_init(float_handle* handle, int data_quantity_in)
    {
        if(handle){
        reinterpret_cast<draw_float*>(handle)->buffer_init(data_quantity_in);
        }
    }
    // 数据写入
    void float_write(float_handle* handle, float* data_point_in)
    {
        if(handle){
        reinterpret_cast<draw_float*>(handle)->float_write(data_point_in);
        }
    }
    // 数据发送
    void float_send(float_handle* handle)
    {
        if(handle){
        reinterpret_cast<draw_float*>(handle)->float_send();
        }
    }
    // 缓冲区释放
    void buffer_free(float_handle* handle)
    {
        if(handle){
        reinterpret_cast<draw_float*>(handle)->buffer_free();
        }
    }


    /*-------------以下为单浮点数调试模块（改进版）---------------*/
                                /*实例管理函数*/
    single_float_handle* single_create(void)
    {return reinterpret_cast<single_float_handle*>(new draw_float_single());}

    void single_vofa_destroy(single_float_handle* handle)
    {delete reinterpret_cast<draw_float_single*>(handle);}

                                /*实例操作函数*/
    void single_float(single_float_handle* handle,UART_HandleTypeDef* huart,float* data_point)
    {
        if(handle){
        reinterpret_cast<draw_float_single*>(handle)->single_float(huart,data_point);
        }
    }


}


