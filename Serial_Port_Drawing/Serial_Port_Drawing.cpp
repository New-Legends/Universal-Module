#include "Vofa_debug.hpp"


/*-------------以下为辅助数据收集模块-------------*/
/**
 * @brief 初始化数组对象
 * @param data_quantity_in 数据数量
 * @param data_type_in 数据类型大小（以字节为单位）
 * 
 * 该函数用于初始化draw_array对象的成员变量，包括数据类型、数据数量，
 * 并根据指定的数量和类型大小分配内存空间
 */
void draw_array::array_init(int data_quantity_in , size_t data_type_in)
{
    if (data_quantity_in <= 0) {
        return;
    }
    if (data_type_in <= 0){
        return;
    }

    // 设置数据类型大小和数据数量
    data_type = data_type_in;
    data_quantity = data_quantity_in;
    
    // 根据数据数量和类型大小分配连续的内存空间
    data_array_point = (float*)calloc(data_quantity_in,data_type);
}

/**
 * @brief 向数组指定位置写入数据（tips:零散数据最好多次调用）
 * @param index 要写入的数组索引位置
 * @param enter_data 要写入的32位浮点数据
 * @return 无返回值
 * 
 * 该函数将指定的浮点数据写入到数组的指定索引位置，
 * 写入前会进行指针有效性和数组边界检查。
 */
void draw_array::array_write(int index, float enter_data)
{
    // 检查指针是否为空
    if (data_array_point == NULL) {
        return;
    }
    
    // 检查数组索引边界
    if (index < 0 || index >= data_quantity) {
        return;
    }
    
    data_array_point[index] = enter_data;
}

/**
 * @brief 获取数据数组指针
 * 
 * @return float* 指向数据数组的指针
 */
float* draw_array::get_array()
{
    return data_array_point;
}

/**
 * @brief 释放数组内存并将其指针置为空
 * @param array_point 指向要释放的数组内存的指针
 * @return 无返回值
 * 
 * 该函数用于释放通过malloc或calloc等函数分配的数组内存，
 * 并将传入的指针设置为NULL，防止悬空指针的产生。
 */
void draw_array::clear_array(float* array_point)
{
    // 释放数组内存
    free(array_point);
    // 将指针置为空，避免悬空指针
    array_point = NULL;
}

int draw_array::get_quantity()
{
    return data_quantity;
}



// /*-------------以下为单浮点快速数调试模块---------------*/
// /**
//  * @brief 快速发送单精度浮点数数据通过UART接口
//  * 
//  * 
//  * @param huart 指向UART句柄结构体的指针，用于指定通信接口
//  * @param data_point 指向要发送的单精度浮点数数据的指针
//  * 
//  * @note 该函数无返回值
//  */
// void vofa_fast_float::single_float_fast(UART_HandleTypeDef* huart,float* data_point)
// {
//     vofa_init(huart);
//     buffer_init(1);
//     float_write(data_point);
//     float_send();
// }



/*-------------以下为浮点数调试模块（改进版本）-------------*/
/**
 * @brief 初始化调试模块
 * @param huart UART句柄指针，用于串口通信
 * @note 该函数初始化帧尾，并保存UART句柄指针
 */
void draw_float::general_init(UART_HandleTypeDef* huart)
{
    // 帧尾初始化
    tail[0]=0x00;
    tail[1]=0x00;
    tail[2]=0x80;
    tail[3]=0x7f;

    // 串口指针传递
    huart_piont = huart;
}

/**
 * @brief 初始化浮点数缓存
 * @param data_quantity_in 发送的数据数量
 * @param data_type 数据类型大小，默认为sizeof(float)
 * 
 * @details 该函数用于初始化vofa_float对象，分配指定数量的浮点数内存空间
 */
void draw_float::buffer_init(int data_quantity_in,size_t data_type_in)
{
    //数据类型存储
    data_type = data_type_in;

    // 保存数据数量并分配缓冲区
    data_quantity = data_quantity_in;
    tx_buffer_point = (float*)calloc(data_quantity,data_type);

}

/**
 * @brief 写入浮点数数据
 * 
 * 该函数用于将多个浮点数数据写入发送缓存区。通过循环遍历数据数组，
 * 将每个数据元素从源位置复制到缓存区。
 * 
 * @param float* data_point 写入数据指针，指向待写入数据的起始位置
 * @return void 无返回值
 */
void draw_float::float_write(float* data_point_in) 
{
    // 遍历所有数据项并进行赋值操作
    for(int i = 0; i < data_quantity; i++)
    {
        tx_buffer_point[i] = data_point_in[i];
    }
}

/**
 * @brief 发送多个浮点数数据
 * @details 通过UART接口循环发送多个浮点数数据，每个数据后跟随帧尾报文
 * @param void 无参数
 * @return void 无返回值
 */
void draw_float::float_send(void)
{
    for(int i = 0; i < data_quantity; i++)
    {
        temp_buffer[0] = tx_buffer_point[i];

        // 发送调试数据内容
        HAL_UART_Transmit(huart_piont,(uint8_t*)temp_buffer,sizeof(data_type),0xff);
    }
    
    // 发送帧尾报文
    HAL_UART_Transmit(huart_piont,tail,4,0xff);

}

void draw_float::buffer_free(void)
{
    // 释放动态分配的缓冲区内存
    free(tx_buffer_point);
    tx_buffer_point = NULL;
}




/*-------------以下为单浮点数调试模块（改进版）---------------*/
/**
 * @brief 单精度浮点数发送函数
 * @details 该函数用于通过UART接口发送单精度浮点数数据，调用auto_send函数实现具体的数据发送逻辑
 * 
 * @param huart UART句柄指针，指向要使用的UART外设
 * @param data_point 指向要发送的浮点数数据的指针
 * 
 * @return 无返回值
 */
void draw_float_single::single_float(UART_HandleTypeDef* huart,float* data_point)
{
    general_init(huart);
    buffer_init(1);
    float_write(data_point);
    float_send();
    buffer_free();
}
